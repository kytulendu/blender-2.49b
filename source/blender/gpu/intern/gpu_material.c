/**
 * $Id: gpu_material.c 20860 2009-06-13 16:49:30Z sirdude $
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version. 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2006 Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Brecht Van Lommel.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include <math.h>
#include <string.h>

#include "GL/glew.h"

#include "MEM_guardedalloc.h"

#include "DNA_image_types.h"
#include "DNA_lamp_types.h"
#include "DNA_listBase.h"
#include "DNA_material_types.h"
#include "DNA_object_types.h"
#include "DNA_scene_types.h"
#include "DNA_texture_types.h"
#include "DNA_view3d_types.h"
#include "DNA_world_types.h"

#include "BKE_anim.h"
#include "BKE_colortools.h"
#include "BKE_DerivedMesh.h"
#include "BKE_global.h"
#include "BKE_main.h"
#include "BKE_node.h"
#include "BKE_scene.h"
#include "BKE_texture.h"
#include "BKE_utildefines.h"

#include "BLI_arithb.h"
#include "BLI_blenlib.h"

#include "GPU_extensions.h"
#include "GPU_material.h"

#include "gpu_codegen.h"

#include <string.h>

/* Structs */

typedef enum DynMatProperty {
	DYN_LAMP_CO = 1,
	DYN_LAMP_VEC = 2,
	DYN_LAMP_IMAT = 4,
	DYN_LAMP_PERSMAT = 8,
} DynMatProperty;

struct GPUMaterial {
	Scene *scene;
	Material *ma;

	/* for creating the material */
	ListBase nodes;
	GPUNodeLink *outlink;

	/* for binding the material */
	GPUPass *pass;
	GPUVertexAttribs attribs;
	int bound;
	int builtins;
	int alpha, obcolalpha;
	int dynproperty;

	/* for passing uniforms */
	int viewmatloc, invviewmatloc;
	int obmatloc, invobmatloc;
	int obcolloc;

	ListBase lamps;
};

struct GPULamp {
	Scene *scene;
	Object *ob;
	Object *par;
	Lamp *la;

	int type, mode, lay;

	float dynenergy, dyncol[3];
	float energy, col[3];

	float co[3], vec[3];
	float dynco[3], dynvec[3];
	float obmat[4][4];
	float imat[4][4];
	float dynimat[4][4];

	float spotsi, spotbl, k;
	float dist, att1, att2;

	float bias, d, clipend;
	int size;

	int falloff_type;
	struct CurveMapping *curfalloff;

	float winmat[4][4];
	float viewmat[4][4];
	float persmat[4][4];
	float dynpersmat[4][4];

	GPUFrameBuffer *fb;
	GPUTexture *tex;

	ListBase materials;
};

/* Functions */

static GPUMaterial *GPU_material_construct_begin(Material *ma)
{
	GPUMaterial *material = MEM_callocN(sizeof(GPUMaterial), "GPUMaterial");

	material->ma= ma;

	return material;
}

static void gpu_material_set_attrib_id(GPUMaterial *material)
{
	GPUVertexAttribs *attribs;
	GPUShader *shader;
	GPUPass *pass;
	char name[32];
	int a, b;

	attribs= &material->attribs;
	pass= material->pass;
	if(!pass) {
		attribs->totlayer = 0;
		return;
	}
	
	shader= GPU_pass_shader(pass);
	if(!shader) {
		attribs->totlayer = 0;
		return;
	}

	/* convert from attribute number to the actual id assigned by opengl,
	 * in case the attrib does not get a valid index back, it was probably
	 * removed by the glsl compiler by dead code elimination */

	for(a=0, b=0; a<attribs->totlayer; a++) {
		sprintf(name, "att%d", attribs->layer[a].glindex);
		attribs->layer[a].glindex = GPU_shader_get_attribute(shader, name);

		if(attribs->layer[a].glindex >= 0) {
			attribs->layer[b] = attribs->layer[a];
			b++;
		}
	}

	attribs->totlayer = b;
}

static int GPU_material_construct_end(GPUMaterial *material)
{
	if (material->outlink) {
		GPUNodeLink *outlink;
		GPUShader *shader;

		outlink = material->outlink;
		material->pass = GPU_generate_pass(&material->nodes, outlink,
			&material->attribs, &material->builtins, material->ma->id.name);

		if(!material->pass)
			return 0;

		gpu_material_set_attrib_id(material);
		
		shader = GPU_pass_shader(material->pass);

		if(material->builtins & GPU_VIEW_MATRIX)
			material->viewmatloc = GPU_shader_get_uniform(shader, GPU_builtin_name(GPU_VIEW_MATRIX));
		if(material->builtins & GPU_INVERSE_VIEW_MATRIX)
			material->invviewmatloc = GPU_shader_get_uniform(shader, GPU_builtin_name(GPU_INVERSE_VIEW_MATRIX));
		if(material->builtins & GPU_OBJECT_MATRIX)
			material->obmatloc = GPU_shader_get_uniform(shader, GPU_builtin_name(GPU_OBJECT_MATRIX));
		if(material->builtins & GPU_INVERSE_OBJECT_MATRIX)
			material->invobmatloc = GPU_shader_get_uniform(shader, GPU_builtin_name(GPU_INVERSE_OBJECT_MATRIX));
		if(material->builtins & GPU_OBCOLOR)
			material->obcolloc = GPU_shader_get_uniform(shader, GPU_builtin_name(GPU_OBCOLOR));

		return 1;
	}

	return 0;
}

void GPU_material_free(Material *ma)
{
	LinkData *link;
	LinkData *nlink, *mlink, *next;

	for(link=ma->gpumaterial.first; link; link=link->next) {
		GPUMaterial *material = link->data;

		if(material->pass)
			GPU_pass_free(material->pass);

		for(nlink=material->lamps.first; nlink; nlink=nlink->next) {
			GPULamp *lamp = nlink->data;

			for(mlink=lamp->materials.first; mlink; mlink=next) {
				next = mlink->next;
				if(mlink->data == ma)
					BLI_freelinkN(&lamp->materials, mlink);
			}
		}

		BLI_freelistN(&material->lamps);

		MEM_freeN(material);
	}

	BLI_freelistN(&ma->gpumaterial);
}

void GPU_material_bind(GPUMaterial *material, int oblay, int viewlay, double time)
{
	if(material->pass) {
		LinkData *nlink;
		GPULamp *lamp;

		/* handle layer lamps */
		for(nlink=material->lamps.first; nlink; nlink=nlink->next) {
			lamp= nlink->data;

			if((lamp->lay & viewlay) && (!(lamp->mode & LA_LAYER) || (lamp->lay & oblay))) {
				lamp->dynenergy = lamp->energy;
				VECCOPY(lamp->dyncol, lamp->col);
			}
			else {
				lamp->dynenergy = 0.0f;
				lamp->dyncol[0]= lamp->dyncol[1]= lamp->dyncol[2] = 0.0f;
			}
		}

		GPU_pass_bind(material->pass, time);
		material->bound = 1;
	}
}

void GPU_material_bind_uniforms(GPUMaterial *material, float obmat[][4], float viewmat[][4], float viewinv[][4], float obcol[4])
{
	if(material->pass) {
		GPUShader *shader = GPU_pass_shader(material->pass);
		LinkData *nlink;
		GPULamp *lamp;
		float invmat[4][4], col[4];

		/* handle builtins */
		if(material->builtins & GPU_VIEW_MATRIX) {
			GPU_shader_uniform_vector(shader, material->viewmatloc, 16, 1, (float*)viewmat);
		}
		if(material->builtins & GPU_INVERSE_VIEW_MATRIX) {
			GPU_shader_uniform_vector(shader, material->invviewmatloc, 16, 1, (float*)viewinv);
		}
		if(material->builtins & GPU_OBJECT_MATRIX) {
			GPU_shader_uniform_vector(shader, material->obmatloc, 16, 1, (float*)obmat);
		}
		if(material->builtins & GPU_INVERSE_OBJECT_MATRIX) {
			Mat4Invert(invmat, obmat);
			GPU_shader_uniform_vector(shader, material->invobmatloc, 16, 1, (float*)invmat);
		}
		if(material->builtins & GPU_OBCOLOR) {
			QUATCOPY(col, obcol);
			CLAMP(col[3], 0.0f, 1.0f);
			GPU_shader_uniform_vector(shader, material->obcolloc, 4, 1, col);
		}

		/* update lamps */
		for(nlink=material->lamps.first; nlink; nlink=nlink->next) {
			lamp= nlink->data;

			if(material->dynproperty & DYN_LAMP_VEC) {
				VECCOPY(lamp->dynvec, lamp->vec);
				Normalize(lamp->dynvec);
				VecNegf(lamp->dynvec);
				Mat4Mul3Vecfl(viewmat, lamp->dynvec);
			}

			if(material->dynproperty & DYN_LAMP_CO) {
				VECCOPY(lamp->dynco, lamp->co);
				Mat4MulVecfl(viewmat, lamp->dynco);
			}

			if(material->dynproperty & DYN_LAMP_IMAT)
				Mat4MulMat4(lamp->dynimat, viewinv, lamp->imat);
			if(material->dynproperty & DYN_LAMP_PERSMAT)
				Mat4MulMat4(lamp->dynpersmat, viewinv, lamp->persmat);
		}

		GPU_pass_update_uniforms(material->pass);
	}
}

void GPU_material_unbind(GPUMaterial *material)
{
	if (material->pass) {
		material->bound = 0;
		GPU_pass_unbind(material->pass);
	}
}

int GPU_material_bound(GPUMaterial *material)
{
	return material->bound;
}

void GPU_material_vertex_attributes(GPUMaterial *material, GPUVertexAttribs *attribs)
{
	*attribs = material->attribs;
}

void GPU_material_output_link(GPUMaterial *material, GPUNodeLink *link)
{
	if(!material->outlink)
		material->outlink= link;
}

void GPU_material_enable_alpha(GPUMaterial *material)
{
	material->alpha= 1;
}

GPUBlendMode GPU_material_blend_mode(GPUMaterial *material, float obcol[3])
{
	if(material->alpha || (material->obcolalpha && obcol[3] < 1.0f))
		return GPU_BLEND_ALPHA;
	else
		return GPU_BLEND_SOLID;
}

void gpu_material_add_node(GPUMaterial *material, GPUNode *node)
{
	BLI_addtail(&material->nodes, node);
}

/* Code generation */

static GPUNodeLink *lamp_get_visibility(GPUMaterial *mat, GPULamp *lamp, GPUNodeLink **lv, GPUNodeLink **dist)
{
	GPUNodeLink *visifac, *inpr;

	/* from get_lamp_visibility */
	if(lamp->type==LA_SUN || lamp->type==LA_HEMI) {
		mat->dynproperty |= DYN_LAMP_VEC;
		GPU_link(mat, "lamp_visibility_sun_hemi", GPU_dynamic_uniform(lamp->dynvec), lv, dist, &visifac);
		return visifac;
	}
	else {
		mat->dynproperty |= DYN_LAMP_CO;
		GPU_link(mat, "lamp_visibility_other", GPU_builtin(GPU_VIEW_POSITION), GPU_dynamic_uniform(lamp->dynco), lv, dist, &visifac);

		if(lamp->type==LA_AREA)
			return visifac;

		switch(lamp->falloff_type)
		{
			case LA_FALLOFF_CONSTANT:
				break;
			case LA_FALLOFF_INVLINEAR:
				GPU_link(mat, "lamp_falloff_invlinear", GPU_uniform(&lamp->dist), *dist, &visifac);
				break;
			case LA_FALLOFF_INVSQUARE:
				GPU_link(mat, "lamp_falloff_invsquare", GPU_uniform(&lamp->dist), *dist, &visifac);
				break;
			case LA_FALLOFF_SLIDERS:
				GPU_link(mat, "lamp_falloff_sliders", GPU_uniform(&lamp->dist), GPU_uniform(&lamp->att1), GPU_uniform(&lamp->att2), *dist, &visifac);
				break;
			case LA_FALLOFF_CURVE:
				{
					float *array;
					int size;

					curvemapping_table_RGBA(lamp->curfalloff, &array, &size);
					GPU_link(mat, "lamp_falloff_curve", GPU_uniform(&lamp->dist), GPU_texture(size, array), *dist, &visifac);
				}
				break;
		}

		if(lamp->mode & LA_SPHERE)
			GPU_link(mat, "lamp_visibility_sphere", GPU_uniform(&lamp->dist), *dist, visifac, &visifac);

		if(lamp->type == LA_SPOT) {
			if(lamp->mode & LA_SQUARE) {
				mat->dynproperty |= DYN_LAMP_VEC|DYN_LAMP_IMAT;
				GPU_link(mat, "lamp_visibility_spot_square", GPU_dynamic_uniform(lamp->dynvec), GPU_dynamic_uniform((float*)lamp->dynimat), *lv, &inpr);
			}
			else {
				mat->dynproperty |= DYN_LAMP_VEC;
				GPU_link(mat, "lamp_visibility_spot_circle", GPU_dynamic_uniform(lamp->dynvec), *lv, &inpr);
			}
			
			GPU_link(mat, "lamp_visibility_spot", GPU_uniform(&lamp->spotsi), GPU_uniform(&lamp->spotbl), inpr, visifac, &visifac);
		}

		GPU_link(mat, "lamp_visibility_clamp", visifac, &visifac);

		return visifac;
	}
}

#if 0
static void area_lamp_vectors(LampRen *lar)
{
    float xsize= 0.5*lar->area_size, ysize= 0.5*lar->area_sizey, multifac;

    /* make it smaller, so area light can be multisampled */
    multifac= 1.0f/sqrt((float)lar->ray_totsamp);
    xsize *= multifac;
    ysize *= multifac;

    /* corner vectors */
    lar->area[0][0]= lar->co[0] - xsize*lar->mat[0][0] - ysize*lar->mat[1][0];
    lar->area[0][1]= lar->co[1] - xsize*lar->mat[0][1] - ysize*lar->mat[1][1];
    lar->area[0][2]= lar->co[2] - xsize*lar->mat[0][2] - ysize*lar->mat[1][2];

    /* corner vectors */
    lar->area[1][0]= lar->co[0] - xsize*lar->mat[0][0] + ysize*lar->mat[1][0];
    lar->area[1][1]= lar->co[1] - xsize*lar->mat[0][1] + ysize*lar->mat[1][1];
    lar->area[1][2]= lar->co[2] - xsize*lar->mat[0][2] + ysize*lar->mat[1][2];

    /* corner vectors */
    lar->area[2][0]= lar->co[0] + xsize*lar->mat[0][0] + ysize*lar->mat[1][0];
    lar->area[2][1]= lar->co[1] + xsize*lar->mat[0][1] + ysize*lar->mat[1][1];
    lar->area[2][2]= lar->co[2] + xsize*lar->mat[0][2] + ysize*lar->mat[1][2];

    /* corner vectors */
    lar->area[3][0]= lar->co[0] + xsize*lar->mat[0][0] - ysize*lar->mat[1][0];
    lar->area[3][1]= lar->co[1] + xsize*lar->mat[0][1] - ysize*lar->mat[1][1];
    lar->area[3][2]= lar->co[2] + xsize*lar->mat[0][2] - ysize*lar->mat[1][2];
    /* only for correction button size, matrix size works on energy */
    lar->areasize= lar->dist*lar->dist/(4.0*xsize*ysize);
}
#endif

static void ramp_blend(GPUMaterial *mat, GPUNodeLink *fac, GPUNodeLink *col1, GPUNodeLink *col2, int type, GPUNodeLink **outcol)
{
	static char *names[] = {"mix_blend", "mix_add", "mix_mult", "mix_sub",
		"mix_screen", "mix_div", "mix_diff", "mix_dark", "mix_light",
		"mix_overlay", "mix_dodge", "mix_burn", "mix_hue", "mix_sat",
		"mix_val", "mix_color"};

	GPU_link(mat, names[type], fac, col1, col2, outcol);
}

static void do_colorband_blend(GPUMaterial *mat, ColorBand *coba, GPUNodeLink *fac, float rampfac, int type, GPUNodeLink *incol, GPUNodeLink **outcol)
{
	GPUNodeLink *tmp, *alpha, *col;
	float *array;
	int size;

	/* do colorband */
	colorband_table_RGBA(coba, &array, &size);
	GPU_link(mat, "valtorgb", fac, GPU_texture(size, array), &col, &tmp);

	/* use alpha in fac */
	GPU_link(mat, "mtex_alpha_from_col", col, &alpha);
	GPU_link(mat, "math_multiply", alpha, GPU_uniform(&rampfac), &fac);

	/* blending method */
	ramp_blend(mat, fac, incol, col, type, outcol);
}

static void ramp_diffuse_result(GPUShadeInput *shi, GPUNodeLink **diff)
{
	Material *ma= shi->mat;
	GPUMaterial *mat= shi->gpumat;
	GPUNodeLink *fac;

	if(!(G.fileflags & G_FILE_GLSL_NO_RAMPS)) {
		if(ma->ramp_col) {
			if(ma->rampin_col==MA_RAMP_IN_RESULT) {
				GPU_link(mat, "ramp_rgbtobw", *diff, &fac);
				
				/* colorband + blend */
				do_colorband_blend(mat, ma->ramp_col, fac, ma->rampfac_col, ma->rampblend_col, *diff, diff);
			}
		}
	}
}

static void add_to_diffuse(GPUMaterial *mat, Material *ma, GPUShadeInput *shi, GPUNodeLink *is, GPUNodeLink *rgb, GPUNodeLink **diff)
{
	GPUNodeLink *fac, *tmp, *addcol;
	
	if(!(G.fileflags & G_FILE_GLSL_NO_RAMPS) &&
	   ma->ramp_col && (ma->mode & MA_RAMP_COL)) {
		/* MA_RAMP_IN_RESULT is exceptional */
		if(ma->rampin_col==MA_RAMP_IN_RESULT) {
			addcol = shi->rgb;
		}
		else {
			/* input */
			switch(ma->rampin_col) {
			case MA_RAMP_IN_ENERGY:
				GPU_link(mat, "ramp_rgbtobw", rgb, &fac);
				break;
			case MA_RAMP_IN_SHADER:
				fac= is;
				break;
			case MA_RAMP_IN_NOR:
				GPU_link(mat, "vec_math_dot", shi->view, shi->vn, &tmp, &fac);
				break;
			default:
				GPU_link(mat, "set_value_zero", &fac);
				break;
			}

			/* colorband + blend */
			do_colorband_blend(mat, ma->ramp_col, fac, ma->rampfac_col, ma->rampblend_col, shi->rgb, &addcol);
		}
	}
	else
		addcol = shi->rgb;

	/* output to */
	GPU_link(mat, "shade_madd", *diff, rgb, addcol, diff);
}

static void ramp_spec_result(GPUShadeInput *shi, GPUNodeLink **spec)
{
	Material *ma= shi->mat;
	GPUMaterial *mat= shi->gpumat;
	GPUNodeLink *fac;

	if(!(G.fileflags & G_FILE_GLSL_NO_RAMPS) &&
	   ma->ramp_spec && ma->rampin_spec==MA_RAMP_IN_RESULT) {
		GPU_link(mat, "ramp_rgbtobw", *spec, &fac);
		
		/* colorband + blend */
		do_colorband_blend(mat, ma->ramp_spec, fac, ma->rampfac_spec, ma->rampblend_spec, *spec, spec);
	}
}

static void do_specular_ramp(GPUShadeInput *shi, GPUNodeLink *is, GPUNodeLink *t, GPUNodeLink **spec)
{
	Material *ma= shi->mat;
	GPUMaterial *mat= shi->gpumat;
	GPUNodeLink *fac, *tmp;

	*spec = shi->specrgb;

	/* MA_RAMP_IN_RESULT is exception */
	if(ma->ramp_spec && (ma->rampin_spec!=MA_RAMP_IN_RESULT)) {
		
		/* input */
		switch(ma->rampin_spec) {
		case MA_RAMP_IN_ENERGY:
			fac = t;
			break;
		case MA_RAMP_IN_SHADER:
			fac = is;
			break;
		case MA_RAMP_IN_NOR:
			GPU_link(mat, "vec_math_dot", shi->view, shi->vn, &tmp, &fac);
			break;
		default:
			GPU_link(mat, "set_value_zero", &fac);
			break;
		}
		
		/* colorband + blend */
		do_colorband_blend(mat, ma->ramp_spec, fac, ma->rampfac_spec, ma->rampblend_spec, *spec, spec);
	}
}

void add_user_list(ListBase *list, void *data)
{
	LinkData *link = MEM_callocN(sizeof(LinkData), "GPULinkData");
	link->data = data;
	BLI_addtail(list, link);
}

static void shade_one_light(GPUShadeInput *shi, GPUShadeResult *shr, GPULamp *lamp)
{
	Material *ma= shi->mat;
	GPUMaterial *mat= shi->gpumat;
	GPUNodeLink *lv, *dist, *visifac, *is, *inp, *i, *vn, *view;
	GPUNodeLink *outcol, *specfac, *t, *shadfac;
	float one = 1.0f;

	if((lamp->mode & LA_ONLYSHADOW) && !(ma->mode & MA_SHADOW))
		return;
	
	vn= shi->vn;
	view= shi->view;

	visifac= lamp_get_visibility(mat, lamp, &lv, &dist);

	/*if(ma->mode & MA_TANGENT_V)
		GPU_link(mat, "shade_tangent_v", lv, GPU_attribute(CD_TANGENT, ""), &vn);*/
	
	GPU_link(mat, "shade_inp", vn, lv, &inp);

	if(lamp->mode & LA_NO_DIFF) {
		GPU_link(mat, "shade_is_no_diffuse", &is);
	}
	else if(lamp->type == LA_HEMI) {
		GPU_link(mat, "shade_is_hemi", inp, &is);
	}
	else {
		if(lamp->type == LA_AREA) {
			float area[4][4], areasize;

			memset(&area, 0, sizeof(area));
			memset(&areasize, 0, sizeof(areasize));
			mat->dynproperty |= DYN_LAMP_VEC|DYN_LAMP_CO;
			GPU_link(mat, "shade_inp_area", GPU_builtin(GPU_VIEW_POSITION), GPU_dynamic_uniform(lamp->dynco), GPU_dynamic_uniform(lamp->dynvec), vn, GPU_uniform((float*)area),
				GPU_uniform(&areasize), GPU_uniform(&lamp->k), &inp);
		}

		is= inp; /* Lambert */

		if(!(G.fileflags & G_FILE_GLSL_NO_SHADERS)) {
			if(ma->diff_shader==MA_DIFF_ORENNAYAR)
				GPU_link(mat, "shade_diffuse_oren_nayer", inp, vn, lv, view, GPU_uniform(&ma->roughness), &is);
			else if(ma->diff_shader==MA_DIFF_TOON)
				GPU_link(mat, "shade_diffuse_toon", vn, lv, view, GPU_uniform(&ma->param[0]), GPU_uniform(&ma->param[1]), &is);
			else if(ma->diff_shader==MA_DIFF_MINNAERT)
				GPU_link(mat, "shade_diffuse_minnaert", inp, vn, view, GPU_uniform(&ma->darkness), &is);
			else if(ma->diff_shader==MA_DIFF_FRESNEL)
				GPU_link(mat, "shade_diffuse_fresnel", vn, lv, view, GPU_uniform(&ma->param[0]), GPU_uniform(&ma->param[1]), &is);
		}
	}

	if(!(G.fileflags & G_FILE_GLSL_NO_SHADERS))
		if(ma->shade_flag & MA_CUBIC)
			GPU_link(mat, "shade_cubic", is, &is);
	
	i = is;
	GPU_link(mat, "shade_visifac", i, visifac, shi->refl, &i);

	vn = shi->vn;
	/*if(ma->mode & MA_TANGENT_VN)
		GPU_link(mat, "shade_tangent_v_spec", GPU_attribute(CD_TANGENT, ""), &vn);*/

	/* this replaces if(i > 0.0) conditional until that is supported */
	// done in shade_visifac now, GPU_link(mat, "mtex_value_clamp_positive", i, &i);

	if((ma->mode & MA_SHADOW) && GPU_lamp_has_shadow_buffer(lamp)) {
		if(!(G.fileflags & G_FILE_GLSL_NO_SHADOWS)) {
			mat->dynproperty |= DYN_LAMP_PERSMAT;

			GPU_link(mat, "test_shadowbuf",
				GPU_builtin(GPU_VIEW_POSITION),
				GPU_dynamic_texture(lamp->tex),
				GPU_dynamic_uniform((float*)lamp->dynpersmat),
				GPU_uniform(&lamp->bias), inp, &shadfac);
			
			if(lamp->mode & LA_ONLYSHADOW) {
				GPU_link(mat, "shade_only_shadow", i, shadfac,
					GPU_dynamic_uniform(&lamp->dynenergy), &shadfac);
				
				if(!(lamp->mode & LA_NO_DIFF))
					GPU_link(mat, "shade_only_shadow_diffuse", shadfac, shi->rgb,
						shr->diff, &shr->diff);

				if(!(lamp->mode & LA_NO_SPEC))
					GPU_link(mat, "shade_only_shadow_specular", shadfac, shi->specrgb,
						shr->spec, &shr->spec);
				
				add_user_list(&mat->lamps, lamp);
				add_user_list(&lamp->materials, shi->gpumat->ma);
				return;
			}
			
			GPU_link(mat, "math_multiply", i, shadfac, &i);
		}
	}
	else if((G.fileflags & G_FILE_GLSL_NO_SHADOWS) && (lamp->mode & LA_ONLYSHADOW)) {
		add_user_list(&mat->lamps, lamp);
		add_user_list(&lamp->materials, shi->gpumat->ma);
		return;
	}
	else
		GPU_link(mat, "set_value", GPU_uniform(&one), &shadfac);

	if(GPU_link_changed(shi->refl) || ma->ref != 0.0f) {
		if(!(lamp->mode & LA_NO_DIFF)) {
			GPUNodeLink *rgb;
			GPU_link(mat, "shade_mul_value", i, GPU_dynamic_uniform(lamp->dyncol), &rgb);
			add_to_diffuse(mat, ma, shi, is, rgb, &shr->diff);
		}
	}

	if(G.fileflags & G_FILE_GLSL_NO_SHADERS);
	else if(!(lamp->mode & LA_NO_SPEC) && !(lamp->mode & LA_ONLYSHADOW) &&
	   (GPU_link_changed(shi->spec) || ma->spec != 0.0f)) {
		if(lamp->type == LA_HEMI) {
			GPU_link(mat, "shade_hemi_spec", vn, lv, view, GPU_uniform(&ma->spec), shi->har, visifac, &t);
			GPU_link(mat, "shade_add_spec", t, GPU_dynamic_uniform(lamp->dyncol), shi->specrgb, &outcol);
			GPU_link(mat, "shade_add", shr->spec, outcol, &shr->spec);
		}
		else {
			if(ma->spec_shader==MA_SPEC_PHONG)
				GPU_link(mat, "shade_phong_spec", vn, lv, view, shi->har, &specfac);
			else if(ma->spec_shader==MA_SPEC_COOKTORR)
				GPU_link(mat, "shade_cooktorr_spec", vn, lv, view, shi->har, &specfac);
			else if(ma->spec_shader==MA_SPEC_BLINN)
				GPU_link(mat, "shade_blinn_spec", vn, lv, view, GPU_uniform(&ma->refrac), shi->har, &specfac);
			else if(ma->spec_shader==MA_SPEC_WARDISO)
				GPU_link(mat, "shade_wardiso_spec", vn, lv, view, GPU_uniform(&ma->rms), &specfac);
			else
				GPU_link(mat, "shade_toon_spec", vn, lv, view, GPU_uniform(&ma->param[2]), GPU_uniform(&ma->param[3]), &specfac);

			if(lamp->type==LA_AREA)
				GPU_link(mat, "shade_spec_area_inp", specfac, inp, &specfac);

			GPU_link(mat, "shade_spec_t", shadfac, shi->spec, visifac, specfac, &t);

			if(ma->mode & MA_RAMP_SPEC) {
				GPUNodeLink *spec;
				do_specular_ramp(shi, specfac, t, &spec);
				GPU_link(mat, "shade_add_spec", t, GPU_dynamic_uniform(lamp->dyncol), spec, &outcol);
				GPU_link(mat, "shade_add", shr->spec, outcol, &shr->spec);
			}
			else {
				GPU_link(mat, "shade_add_spec", t, GPU_dynamic_uniform(lamp->dyncol), shi->specrgb, &outcol);
				GPU_link(mat, "shade_add", shr->spec, outcol, &shr->spec);
			}
		}
	}

	add_user_list(&mat->lamps, lamp);
	add_user_list(&lamp->materials, shi->gpumat->ma);
}

static void material_lights(GPUShadeInput *shi, GPUShadeResult *shr)
{
	Base *base;
	Object *ob;
	Scene *sce;
	GPULamp *lamp;
	
	for(SETLOOPER(shi->gpumat->scene, base)) {
		ob= base->object;

		if(ob->type==OB_LAMP) {
			lamp = GPU_lamp_from_blender(shi->gpumat->scene, ob, NULL);
			if(lamp)
				shade_one_light(shi, shr, lamp);
		}

		if (ob->transflag & OB_DUPLI) {
			DupliObject *dob;
			ListBase *lb = object_duplilist(shi->gpumat->scene, ob);
			
			for(dob=lb->first; dob; dob=dob->next) {
				Object *ob = dob->ob;
				
				if(ob->type==OB_LAMP) {
					Mat4CpyMat4(ob->obmat, dob->mat);

					lamp = GPU_lamp_from_blender(shi->gpumat->scene, ob, base->object);
					if(lamp)
						shade_one_light(shi, shr, lamp);
				}
			}
			
			free_object_duplilist(lb);
		}
	}
}

static void texture_rgb_blend(GPUMaterial *mat, GPUNodeLink *tex, GPUNodeLink *out, GPUNodeLink *fact, GPUNodeLink *facg, int blendtype, GPUNodeLink **in)
{
	switch(blendtype) {
	case MTEX_BLEND:
		GPU_link(mat, "mtex_rgb_blend", out, tex, fact, facg, in);
		break;
	case MTEX_MUL:
		GPU_link(mat, "mtex_rgb_mul", out, tex, fact, facg, in);
		break;
	case MTEX_SCREEN:
		GPU_link(mat, "mtex_rgb_screen", out, tex, fact, facg, in);
		break;
	case MTEX_OVERLAY:
		GPU_link(mat, "mtex_rgb_overlay", out, tex, fact, facg, in);
		break;
	case MTEX_SUB:
		GPU_link(mat, "mtex_rgb_sub", out, tex, fact, facg, in);
		break;
	case MTEX_ADD:
		GPU_link(mat, "mtex_rgb_add", out, tex, fact, facg, in);
		break;
	case MTEX_DIV:
		GPU_link(mat, "mtex_rgb_div", out, tex, fact, facg, in);
		break;
	case MTEX_DIFF:
		GPU_link(mat, "mtex_rgb_diff", out, tex, fact, facg, in);
		break;
	case MTEX_DARK:
		GPU_link(mat, "mtex_rgb_dark", out, tex, fact, facg, in);
		break;
	case MTEX_LIGHT:
		GPU_link(mat, "mtex_rgb_light", out, tex, fact, facg, in);
		break;
	case MTEX_BLEND_HUE:
		GPU_link(mat, "mtex_rgb_hue", out, tex, fact, facg, in);
		break;
	case MTEX_BLEND_SAT:
		GPU_link(mat, "mtex_rgb_sat", out, tex, fact, facg, in);
		break;
	case MTEX_BLEND_VAL:
		GPU_link(mat, "mtex_rgb_val", out, tex, fact, facg, in);
		break;
	case MTEX_BLEND_COLOR:
		GPU_link(mat, "mtex_rgb_color", out, tex, fact, facg, in);
		break;
	default:
		GPU_link(mat, "set_rgb_zero", &in);
		break;
	}
}

static void texture_value_blend(GPUMaterial *mat, GPUNodeLink *tex, GPUNodeLink *out, GPUNodeLink *fact, GPUNodeLink *facg, int blendtype, int flip, GPUNodeLink **in)
{
	float flipf = (flip)? 1.0f: 0.0;

	switch(blendtype) {
	case MTEX_BLEND:
		GPU_link(mat, "mtex_value_blend", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	case MTEX_MUL:
		GPU_link(mat, "mtex_value_mul", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	case MTEX_SCREEN:
		GPU_link(mat, "mtex_value_screen", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	case MTEX_SUB:
		GPU_link(mat, "mtex_value_sub", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	case MTEX_ADD:
		GPU_link(mat, "mtex_value_add", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	case MTEX_DIV:
		GPU_link(mat, "mtex_value_div", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	case MTEX_DIFF:
		GPU_link(mat, "mtex_value_diff", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	case MTEX_DARK:
		GPU_link(mat, "mtex_value_dark", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	case MTEX_LIGHT:
		GPU_link(mat, "mtex_value_light", out, tex, fact, facg, GPU_uniform(&flipf), in);
		break;
	default:
		GPU_link(mat, "set_value_zero", &in);
		break;
	}
}

static void do_material_tex(GPUShadeInput *shi)
{
	Material *ma= shi->mat;
	GPUMaterial *mat= shi->gpumat;
	MTex *mtex;
	Tex *tex;
	GPUNodeLink *texco, *tin, *trgb, *tnor, *tcol, *stencil, *tnorfac;
	GPUNodeLink *texco_norm, *texco_orco, *texco_object, *texco_tangent;
	GPUNodeLink *texco_global, *texco_uv = NULL;
	GPUNodeLink *colfac, *newnor, *varfac, *orn;
	char *lastuvname = NULL;
	float one = 1.0f, norfac, ofs[3];
	int tex_nr, rgbnor, talpha;

	GPU_link(mat, "set_value", GPU_uniform(&one), &stencil);

	GPU_link(mat, "texco_norm", GPU_builtin(GPU_VIEW_NORMAL), &texco_norm);
	GPU_link(mat, "texco_orco", GPU_attribute(CD_ORCO, ""), &texco_orco);
	GPU_link(mat, "texco_object", GPU_builtin(GPU_INVERSE_VIEW_MATRIX),
		GPU_builtin(GPU_INVERSE_OBJECT_MATRIX),
		GPU_builtin(GPU_VIEW_POSITION), &texco_object);
	GPU_link(mat, "texco_tangent", GPU_attribute(CD_TANGENT, ""), &texco_tangent);
	GPU_link(mat, "texco_global", GPU_builtin(GPU_INVERSE_VIEW_MATRIX),
		GPU_builtin(GPU_VIEW_POSITION), &texco_global);

	orn= texco_norm;

	/* go over texture slots */
	for(tex_nr=0; tex_nr<MAX_MTEX; tex_nr++) {
		/* separate tex switching */
		if(ma->septex & (1<<tex_nr)) continue;
		
		if(ma->mtex[tex_nr]) {
			mtex= ma->mtex[tex_nr];
			
			tex= mtex->tex;
			if(tex==0) continue;

			/* which coords */
			if(mtex->texco==TEXCO_ORCO)
				texco= texco_orco;
			else if(mtex->texco==TEXCO_OBJECT)
				texco= texco_object;
			else if(mtex->texco==TEXCO_NORM)
				texco= orn;
			else if(mtex->texco==TEXCO_TANGENT)
				texco= texco_object;
			else if(mtex->texco==TEXCO_GLOB)
				texco= texco_global;
			else if(mtex->texco==TEXCO_REFL)
				texco= shi->ref;
			else if(mtex->texco==TEXCO_UV) {
				if(1) { //!(texco_uv && strcmp(mtex->uvname, lastuvname) == 0)) {
					GPU_link(mat, "texco_uv", GPU_attribute(CD_MTFACE, mtex->uvname), &texco_uv);
					lastuvname = mtex->uvname;
				}
				texco= texco_uv;
			}
			else
				continue;

			/* in case of uv, this would just undo a multiplication in texco_uv */
			if(mtex->texco != TEXCO_UV)
				GPU_link(mat, "mtex_2d_mapping", texco, &texco);

			if(mtex->size[0] != 1.0f || mtex->size[1] != 1.0f || mtex->size[2] != 1.0f)
				GPU_link(mat, "mtex_mapping_size", texco, GPU_uniform(mtex->size), &texco);

			ofs[0] = mtex->ofs[0] + 0.5f - 0.5f*mtex->size[0];
			ofs[1] = mtex->ofs[1] + 0.5f - 0.5f*mtex->size[1];
			ofs[2] = 0.0f;
			if(ofs[0] != 0.0f || ofs[1] != 0.0f || ofs[2] != 0.0f)
				GPU_link(mat, "mtex_mapping_ofs", texco, GPU_uniform(ofs), &texco);

			talpha = 0;
			rgbnor = 0;

			if(tex && tex->type == TEX_IMAGE && tex->ima) {
				GPU_link(mat, "mtex_image", texco, GPU_image(tex->ima, NULL), &tin, &trgb, &tnor);
				rgbnor= TEX_RGB;

				if(tex->imaflag & TEX_USEALPHA)
					talpha= 1;
		    }
			else continue;

			/* texture output */
			if((rgbnor & TEX_RGB) && (mtex->texflag & MTEX_RGBTOINT)) {
				GPU_link(mat, "mtex_rgbtoint", trgb, &tin);
				rgbnor -= TEX_RGB;
			}

			if(mtex->texflag & MTEX_NEGATIVE) {
				if(rgbnor & TEX_RGB)
					GPU_link(mat, "mtex_rgb_invert", trgb, &trgb);
				else
					GPU_link(mat, "mtex_value_invert", tin, &tin);
			}

			if(mtex->texflag & MTEX_STENCIL) {
				if(rgbnor & TEX_RGB)
					GPU_link(mat, "mtex_rgb_stencil", stencil, trgb, &stencil, &trgb);
				else
					GPU_link(mat, "mtex_value_stencil", stencil, tin, &stencil, &tin);
			}

			/* mapping */
			if(mtex->mapto & (MAP_COL+MAP_COLSPEC)) {
				/* stencil maps on the texture control slider, not texture intensity value */
				if(mtex->colfac == 1.0f)
					colfac = stencil;
				else
					GPU_link(mat, "math_multiply", GPU_uniform(&mtex->colfac), stencil, &colfac);

				if((rgbnor & TEX_RGB)==0) {
					GPU_link(mat, "set_rgb", GPU_uniform(&mtex->r), &tcol);
				}
				else {
					GPU_link(mat, "set_rgba", trgb, &tcol);

					if(mtex->mapto & MAP_ALPHA)
						GPU_link(mat, "set_value", stencil, &tin);
					else if(talpha)
						GPU_link(mat, "mtex_alpha_from_col", trgb, &tin);
					else
						GPU_link(mat, "set_value_one", &tin);
				}
				
				if(mtex->mapto & MAP_COL)
					texture_rgb_blend(mat, tcol, shi->rgb, tin, colfac, mtex->blendtype, &shi->rgb);
				
				if(!(G.fileflags & G_FILE_GLSL_NO_EXTRA_TEX) && (mtex->mapto & MAP_COLSPEC))
					texture_rgb_blend(mat, tcol, shi->specrgb, tin, colfac, mtex->blendtype, &shi->specrgb);
			}

			if(!(G.fileflags & G_FILE_GLSL_NO_EXTRA_TEX) && (mtex->mapto & MAP_NORM)) {
				if(mtex->maptoneg & MAP_NORM) tex->norfac= -mtex->norfac;
				else tex->norfac= mtex->norfac;
				
				if((tex->type==TEX_IMAGE) && (tex->imaflag & TEX_NORMALMAP)) {
					tex->norfac = mtex->norfac;

					if(mtex->maptoneg & MAP_NORM)
						GPU_link(mat, "mtex_negate_texnormal", tnor, &tnor);

					if(mtex->normapspace == MTEX_NSPACE_TANGENT)
						GPU_link(mat, "mtex_nspace_tangent", GPU_attribute(CD_TANGENT, ""), shi->vn, tnor, &newnor);
					else
						newnor = tnor;

					norfac = MIN2(mtex->norfac, 1.0);
					if(norfac == 1.0f && !GPU_link_changed(stencil)) {
						shi->vn = newnor;
					}
					else {
						tnorfac = GPU_uniform(&norfac);

						if(GPU_link_changed(stencil))
							GPU_link(mat, "math_multiply", tnorfac, stencil, &tnorfac);

						GPU_link(mat, "mtex_blend_normal", tnorfac, shi->vn, newnor, &shi->vn);
					}
				}

				GPU_link(mat, "vec_math_negate", shi->vn, &orn);
				GPU_link(mat, "texco_refl", shi->vn, shi->view, &shi->ref);
			}

			if((mtex->mapto & MAP_VARS)) {
				if(mtex->varfac == 1.0f)
					varfac = stencil;
				else
					GPU_link(mat, "math_multiply", GPU_uniform(&mtex->varfac), stencil, &varfac);

				if(rgbnor & TEX_RGB) {
					if(talpha)
						GPU_link(mat, "mtex_alpha_from_col", trgb, &tin);
					else
						GPU_link(mat, "mtex_rgbtoint", trgb, &tin);
				}

				if(!(G.fileflags & G_FILE_GLSL_NO_EXTRA_TEX) && mtex->mapto & MAP_REF) {
					int flip= mtex->maptoneg & MAP_REF;
					texture_value_blend(mat, GPU_uniform(&mtex->def_var), shi->refl, tin, varfac, mtex->blendtype, flip, &shi->refl);
					GPU_link(mat, "mtex_value_clamp_positive", shi->refl, &shi->refl);
				}
				if(!(G.fileflags & G_FILE_GLSL_NO_EXTRA_TEX) && mtex->mapto & MAP_SPEC) {
					int flip= mtex->maptoneg & MAP_SPEC;
					texture_value_blend(mat, GPU_uniform(&mtex->def_var), shi->spec, tin, varfac, mtex->blendtype, flip, &shi->spec);
					GPU_link(mat, "mtex_value_clamp_positive", shi->spec, &shi->spec);
				}
				if(!(G.fileflags & G_FILE_GLSL_NO_EXTRA_TEX) && mtex->mapto & MAP_EMIT) {
					int flip= mtex->maptoneg & MAP_EMIT;
					texture_value_blend(mat, GPU_uniform(&mtex->def_var), shi->emit, tin, varfac, mtex->blendtype, flip, &shi->emit);
					GPU_link(mat, "mtex_value_clamp_positive", shi->emit, &shi->emit);
				}
				if(!(G.fileflags & G_FILE_GLSL_NO_EXTRA_TEX) && mtex->mapto & MAP_HAR) {
					int flip= mtex->maptoneg & MAP_HAR;
					GPU_link(mat, "mtex_har_divide", shi->har, &shi->har);
					texture_value_blend(mat, GPU_uniform(&mtex->def_var), shi->har, tin, varfac, mtex->blendtype, flip, &shi->har);
					GPU_link(mat, "mtex_har_multiply_clamp", shi->har, &shi->har);
				}
				if(mtex->mapto & MAP_ALPHA) {
					int flip= mtex->maptoneg & MAP_ALPHA;
					texture_value_blend(mat, GPU_uniform(&mtex->def_var), shi->alpha, tin, varfac, mtex->blendtype, flip, &shi->alpha);
					GPU_link(mat, "mtex_value_clamp", shi->alpha, &shi->alpha);
				}
				if(!(G.fileflags & G_FILE_GLSL_NO_EXTRA_TEX) && mtex->mapto & MAP_AMB) {
					int flip= mtex->maptoneg & MAP_AMB;
					texture_value_blend(mat, GPU_uniform(&mtex->def_var), shi->amb, tin, varfac, mtex->blendtype, flip, &shi->amb);
					GPU_link(mat, "mtex_value_clamp", shi->amb, &shi->amb);
				}
			}
		}
	}
}

void GPU_shadeinput_set(GPUMaterial *mat, Material *ma, GPUShadeInput *shi)
{
	float hard = ma->har;

	memset(shi, 0, sizeof(*shi));

	shi->gpumat = mat;
	shi->mat = ma;

	GPU_link(mat, "set_rgb", GPU_uniform(&ma->r), &shi->rgb);
	GPU_link(mat, "set_rgb", GPU_uniform(&ma->specr), &shi->specrgb);
	GPU_link(mat, "shade_norm", GPU_builtin(GPU_VIEW_NORMAL), &shi->vn);
	GPU_link(mat, "set_value", GPU_uniform(&ma->alpha), &shi->alpha);
	GPU_link(mat, "set_value", GPU_uniform(&ma->ref), &shi->refl);
	GPU_link(mat, "set_value", GPU_uniform(&ma->spec), &shi->spec);
	GPU_link(mat, "set_value", GPU_uniform(&ma->emit), &shi->emit);
	GPU_link(mat, "set_value", GPU_uniform(&hard), &shi->har);
	GPU_link(mat, "set_value", GPU_uniform(&ma->amb), &shi->amb);
	GPU_link(mat, "shade_view", GPU_builtin(GPU_VIEW_POSITION), &shi->view);
	GPU_link(mat, "vcol_attribute", GPU_attribute(CD_MCOL, ""), &shi->vcol);
	GPU_link(mat, "texco_refl", shi->vn, shi->view, &shi->ref);
}

void GPU_shaderesult_set(GPUShadeInput *shi, GPUShadeResult *shr)
{
	GPUMaterial *mat= shi->gpumat;
	GPUNodeLink *emit, *ulinfac, *ulogfac, *mistfac;
	Material *ma= shi->mat;
	World *world= mat->scene->world;
	float linfac, logfac, misttype;

	memset(shr, 0, sizeof(*shr));

	if(ma->mode & MA_VERTEXCOLP)
		shi->rgb = shi->vcol;

	do_material_tex(shi);

	if(ma->mode & MA_ZTRA)
		GPU_material_enable_alpha(mat);

	if((G.fileflags & G_FILE_GLSL_NO_LIGHTS) || (ma->mode & MA_SHLESS)) {
		shr->combined = shi->rgb;
		shr->alpha = shi->alpha;
		GPU_link(mat, "set_rgb", shi->rgb, &shr->diff);
		GPU_link(mat, "set_rgb_zero", &shr->spec);
	}
	else {
		if(GPU_link_changed(shi->emit) || ma->emit != 0.0f) {
			if((ma->mode & (MA_VERTEXCOL|MA_VERTEXCOLP))== MA_VERTEXCOL) {
				GPU_link(mat, "shade_add", shi->emit, shi->vcol, &emit);
				GPU_link(mat, "shade_mul", emit, shi->rgb, &shr->diff);
			}
			else
				GPU_link(mat, "shade_mul_value", shi->emit, shi->rgb, &shr->diff);
		}
		else
			GPU_link(mat, "set_rgb_zero", &shr->diff);

		GPU_link(mat, "set_rgb_zero", &shr->spec);

		material_lights(shi, shr);

		shr->combined = shr->diff;
		shr->alpha = shi->alpha;

		if(world) {
        	/* exposure correction */
			if(world->exp!=0.0f || world->range!=1.0f) {
				linfac= 1.0 + pow((2.0*world->exp + 0.5), -10);
				logfac= log((linfac-1.0)/linfac)/world->range;

				GPU_link(mat, "set_value", GPU_uniform(&linfac), &ulinfac);
				GPU_link(mat, "set_value", GPU_uniform(&logfac), &ulogfac);

				GPU_link(mat, "shade_exposure_correct", shr->combined,
					ulinfac, ulogfac, &shr->combined);
				GPU_link(mat, "shade_exposure_correct", shr->spec,
					ulinfac, ulogfac, &shr->spec);
			}

			/* ambient color */
			if(world->ambr!=0.0f || world->ambg!=0.0f || world->ambb!=0.0f) {
				if(GPU_link_changed(shi->amb) || ma->amb != 0.0f)
					GPU_link(mat, "shade_maddf", shr->combined, GPU_uniform(&ma->amb),
						GPU_uniform(&world->ambr), &shr->combined);
			}
		}

		if(ma->mode & MA_RAMP_COL) ramp_diffuse_result(shi, &shr->combined);
		if(ma->mode & MA_RAMP_SPEC) ramp_spec_result(shi, &shr->spec);

		if(GPU_link_changed(shi->spec) || ma->spec != 0.0f)
			GPU_link(mat, "shade_add", shr->combined, shr->spec, &shr->combined);
	}

	GPU_link(mat, "mtex_alpha_to_col", shr->combined, shr->alpha, &shr->combined);

	if(ma->shade_flag & MA_OBCOLOR)
		GPU_link(mat, "shade_obcolor", shr->combined, GPU_builtin(GPU_OBCOLOR), &shr->combined);

	if(world && (world->mode & WO_MIST) && !(ma->mode & MA_NOMIST)) {
		misttype = world->mistype;

		GPU_link(mat, "shade_mist_factor", GPU_builtin(GPU_VIEW_POSITION),
			GPU_uniform(&world->miststa), GPU_uniform(&world->mistdist),
			GPU_uniform(&misttype), GPU_uniform(&world->misi), &mistfac);

		GPU_link(mat, "mix_blend", mistfac, shr->combined,
			GPU_uniform(&world->horr), &shr->combined);
	}

	if(!(ma->mode & MA_ZTRA)) {
		if(world && (GPU_link_changed(shr->alpha) || ma->alpha != 1.0f))
			GPU_link(mat, "shade_world_mix", GPU_uniform(&world->horr),
				shr->combined, &shr->combined);

		GPU_link(mat, "shade_alpha_opaque", shr->combined, &shr->combined);
	}

	if(ma->shade_flag & MA_OBCOLOR) {
		mat->obcolalpha = 1;
		GPU_link(mat, "shade_alpha_obcolor", shr->combined, GPU_builtin(GPU_OBCOLOR), &shr->combined);
	}
}

GPUNodeLink *GPU_blender_material(GPUMaterial *mat, Material *ma)
{
	GPUShadeInput shi;
	GPUShadeResult shr;

	GPU_shadeinput_set(mat, ma, &shi);
	GPU_shaderesult_set(&shi, &shr);

	return shr.combined;
}

GPUMaterial *GPU_material_from_blender(Scene *scene, Material *ma)
{
	GPUMaterial *mat;
	GPUNodeLink *outlink;
	LinkData *link;

	for(link=ma->gpumaterial.first; link; link=link->next)
		if(((GPUMaterial*)link->data)->scene == scene)
			return link->data;

	mat = GPU_material_construct_begin(ma);
	mat->scene = scene;

	if(!(G.fileflags & G_FILE_GLSL_NO_NODES) && ma->nodetree && ma->use_nodes) {
		ntreeGPUMaterialNodes(ma->nodetree, mat);
	}
	else {
		outlink = GPU_blender_material(mat, ma);
		GPU_material_output_link(mat, outlink);
	}

	/*if(!GPU_material_construct_end(mat)) {
		GPU_material_free(mat);
		mat= NULL;
		return 0;
	}*/

	GPU_material_construct_end(mat);

	link = MEM_callocN(sizeof(LinkData), "GPUMaterialLink");
	link->data = mat;
	BLI_addtail(&ma->gpumaterial, link);

	return mat;
}

void GPU_materials_free()
{
	Object *ob;
	Material *ma;
	extern Material defmaterial;

	for(ma=G.main->mat.first; ma; ma=ma->id.next)
		GPU_material_free(ma);

	GPU_material_free(&defmaterial);

	for(ob=G.main->object.first; ob; ob=ob->id.next)
		GPU_lamp_free(ob);
}

/* Lamps and shadow buffers */

void GPU_lamp_update(GPULamp *lamp, int lay, float obmat[][4])
{
	float mat[4][4];

	lamp->lay = lay;

	Mat4CpyMat4(mat, obmat);
	Mat4Ortho(mat);

	VECCOPY(lamp->vec, mat[2]);
	VECCOPY(lamp->co, mat[3]);
	Mat4CpyMat4(lamp->obmat, mat);
	Mat4Invert(lamp->imat, mat);
}

void GPU_lamp_update_colors(GPULamp *lamp, float r, float g, float b, float energy)
{
	lamp->energy = energy;
	if(lamp->mode & LA_NEG) lamp->energy= -lamp->energy;

	lamp->col[0]= r* lamp->energy;
	lamp->col[1]= g* lamp->energy;
	lamp->col[2]= b* lamp->energy;
}

static void gpu_lamp_from_blender(Scene *scene, Object *ob, Object *par, Lamp *la, GPULamp *lamp)
{
	float temp, angle, pixsize, wsize;

	lamp->scene = scene;
	lamp->ob = ob;
	lamp->par = par;
	lamp->la = la;

	/* add_render_lamp */
	lamp->mode = la->mode;
	lamp->type = la->type;

	lamp->energy = la->energy;
	if(lamp->mode & LA_NEG) lamp->energy= -lamp->energy;

	lamp->col[0]= la->r*lamp->energy;
	lamp->col[1]= la->g*lamp->energy;
	lamp->col[2]= la->b*lamp->energy;

	GPU_lamp_update(lamp, ob->lay, ob->obmat);

	lamp->spotsi= la->spotsize;
	if(lamp->mode & LA_HALO)
		if(lamp->spotsi > 170.0)
			lamp->spotsi = 170.0;
	lamp->spotsi= cos(M_PI*lamp->spotsi/360.0);
	lamp->spotbl= (1.0 - lamp->spotsi)*la->spotblend;
	lamp->k= la->k;

	lamp->dist= la->dist;
	lamp->falloff_type= la->falloff_type;
	lamp->att1= la->att1;
	lamp->att2= la->att2;
	lamp->curfalloff= la->curfalloff;

	/* initshadowbuf */
	lamp->bias = 0.02f*la->bias;
	lamp->size = la->bufsize;
	lamp->d= la->clipsta;
	lamp->clipend= la->clipend;

	/* arbitrary correction for the fact we do no soft transition */
	lamp->bias *= 0.25f;

	/* makeshadowbuf */
	angle= saacos(lamp->spotsi);
	temp= 0.5f*lamp->size*cos(angle)/sin(angle);
	pixsize= (lamp->d)/temp;
	wsize= pixsize*0.5f*lamp->size;
		
	i_window(-wsize, wsize, -wsize, wsize, lamp->d, lamp->clipend, lamp->winmat);
}

static void gpu_lamp_shadow_free(GPULamp *lamp)
{
	if(lamp->tex) {
		GPU_texture_free(lamp->tex);
		lamp->tex= NULL;
	}
	if(lamp->fb) {
		GPU_framebuffer_free(lamp->fb);
		lamp->fb= NULL;
	}
}

GPULamp *GPU_lamp_from_blender(Scene *scene, Object *ob, Object *par)
{
	Lamp *la;
	GPULamp *lamp;
	LinkData *link;

	for(link=ob->gpulamp.first; link; link=link->next) {
		lamp = (GPULamp*)link->data;

		if(lamp->par == par && lamp->scene == scene)
			return link->data;
	}

	lamp = MEM_callocN(sizeof(GPULamp), "GPULamp");

	link = MEM_callocN(sizeof(LinkData), "GPULampLink");
	link->data = lamp;
	BLI_addtail(&ob->gpulamp, link);

	la = ob->data;
	gpu_lamp_from_blender(scene, ob, par, la, lamp);

	if(la->type==LA_SPOT && (la->mode & LA_SHAD_BUF)) {
		/* opengl */
		lamp->fb = GPU_framebuffer_create();
		if(!lamp->fb) {
			gpu_lamp_shadow_free(lamp);
			return lamp;
		}

		lamp->tex = GPU_texture_create_depth(lamp->size, lamp->size);
		if(!lamp->tex) {
			gpu_lamp_shadow_free(lamp);
			return lamp;
		}

		if(!GPU_framebuffer_texture_attach(lamp->fb, lamp->tex)) {
			gpu_lamp_shadow_free(lamp);
			return lamp;
		}

		GPU_framebuffer_restore();
	}

	return lamp;
}

void GPU_lamp_free(Object *ob)
{
	GPULamp *lamp;
	LinkData *link;
	LinkData *nlink;
	Material *ma;

	for(link=ob->gpulamp.first; link; link=link->next) {
		lamp = link->data;

		while(lamp->materials.first) {
			nlink = lamp->materials.first;
			ma = nlink->data;
			BLI_freelinkN(&lamp->materials, nlink);

			if(ma->gpumaterial.first)
				GPU_material_free(ma);
		}

		gpu_lamp_shadow_free(lamp);

		MEM_freeN(lamp);
	}

	BLI_freelistN(&ob->gpulamp);
}

int GPU_lamp_has_shadow_buffer(GPULamp *lamp)
{
	return (!(G.fileflags & G_FILE_GLSL_NO_SHADOWS) &&
	        !(G.fileflags & G_FILE_GLSL_NO_LIGHTS) &&
			lamp->tex && lamp->fb);
}

void GPU_lamp_shadow_buffer_bind(GPULamp *lamp, float viewmat[][4], int *winsize, float winmat[][4])
{
	float rangemat[4][4], persmat[4][4];

	/* initshadowbuf */
	Mat4Invert(lamp->viewmat, lamp->obmat);
	Normalize(lamp->viewmat[0]);
	Normalize(lamp->viewmat[1]);
	Normalize(lamp->viewmat[2]);

	/* makeshadowbuf */
	Mat4MulMat4(persmat, lamp->viewmat, lamp->winmat);

	/* opengl depth buffer is range 0.0..1.0 instead of -1.0..1.0 in blender */
	Mat4One(rangemat);
	rangemat[0][0] = 0.5f;
	rangemat[1][1] = 0.5f;
	rangemat[2][2] = 0.5f;
	rangemat[3][0] = 0.5f;
	rangemat[3][1] = 0.5f;
	rangemat[3][2] = 0.5f;

	Mat4MulMat4(lamp->persmat, persmat, rangemat);

	/* opengl */
	GPU_framebuffer_texture_bind(lamp->fb, lamp->tex);

	/* set matrices */
	Mat4CpyMat4(viewmat, lamp->viewmat);
	Mat4CpyMat4(winmat, lamp->winmat);
	*winsize = lamp->size;
}

void GPU_lamp_shadow_buffer_unbind(GPULamp *lamp)
{
	GPU_framebuffer_texture_unbind(lamp->fb, lamp->tex);
	GPU_framebuffer_restore();
}

int GPU_lamp_shadow_layer(GPULamp *lamp)
{
	if(lamp->fb && lamp->tex && (lamp->mode & (LA_LAYER|LA_LAYER_SHADOW)))
		return lamp->lay;
	else
		return -1;
}

