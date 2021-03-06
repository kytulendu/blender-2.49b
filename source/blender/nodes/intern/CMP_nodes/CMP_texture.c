/**
 * $Id: CMP_texture.c 14352 2008-04-07 15:21:25Z blendix $
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
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include "../CMP_util.h"

/* **************** TEXTURE ******************** */
static bNodeSocketType cmp_node_texture_in[]= {
	{	SOCK_VECTOR, 1, "Offset",		0.0f, 0.0f, 0.0f, 0.0f, -2.0f, 2.0f},
	{	SOCK_VECTOR, 1, "Scale",		1.0f, 1.0f, 1.0f, 1.0f, -10.0f, 10.0f},
	{	-1, 0, ""	}
};
static bNodeSocketType cmp_node_texture_out[]= {
	{	SOCK_VALUE, 0, "Value",		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
	{	SOCK_RGBA , 0, "Color",		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{	-1, 0, ""	}
};

/* called without rect allocated */
static void texture_procedural(CompBuf *cbuf, float *out, float xco, float yco)
{
	bNode *node= cbuf->node;
	TexResult texres= {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, NULL};
	float vec[3], *size, nor[3]={0.0f, 0.0f, 0.0f}, col[4];
	int retval, type= cbuf->procedural_type;
	
	size= cbuf->procedural_size;
	
	vec[0]= size[0]*(xco + cbuf->procedural_offset[0]);
	vec[1]= size[1]*(yco + cbuf->procedural_offset[1]);
	vec[2]= size[2]*cbuf->procedural_offset[2];
	
	retval= multitex_ext((Tex *)node->id, vec, NULL, NULL, 0, &texres);
	
	if(type==CB_VAL) {
		if(texres.talpha)
			col[0]= texres.ta;
		else
			col[0]= texres.tin;
	}
	else if(type==CB_RGBA) {
		if(texres.talpha)
			col[3]= texres.ta;
		else
			col[3]= texres.tin;
		
		if((retval & TEX_RGB)) {
			col[0]= texres.tr;
			col[1]= texres.tg;
			col[2]= texres.tb;
		}
		else col[0]= col[1]= col[2]= col[3];
	}
	else { 
		VECCOPY(col, nor);
	}

	typecheck_compbuf_color(out, col, cbuf->type, cbuf->procedural_type);
}

/* texture node outputs get a small rect, to make sure all other nodes accept it */
/* only the pixel-processor nodes do something with it though */
static void node_composit_exec_texture(void *data, bNode *node, bNodeStack **in, bNodeStack **out)
{
	/* outputs: value, color, normal */
	
	if(node->id) {
		RenderData *rd= data;
		RenderResult *rr= RE_GetResult(RE_GetRender(G.scene->id.name)); /* G.scene is WEAK! */
		short sizex, sizey;
		
		/* first make the preview image */
		CompBuf *prevbuf= alloc_compbuf(140, 140, CB_RGBA, 1); /* alloc */
		
		if (rr) {
			sizex = rr->rectx;
			sizey = rr->recty;
		} else {
			sizex = rd->xsch;
			sizey = rd->ysch;
		}
		
		prevbuf->rect_procedural= texture_procedural;
		prevbuf->node= node;
		VECCOPY(prevbuf->procedural_offset, in[0]->vec);
		VECCOPY(prevbuf->procedural_size, in[1]->vec);
		prevbuf->procedural_type= CB_RGBA;
		composit1_pixel_processor(node, prevbuf, prevbuf, out[0]->vec, do_copy_rgba, CB_RGBA);
		generate_preview(node, prevbuf);
		free_compbuf(prevbuf);
		
		if(out[0]->hasoutput) {
			CompBuf *stackbuf= alloc_compbuf(sizex, sizey, CB_VAL, 1); /* alloc */
			
			stackbuf->rect_procedural= texture_procedural;
			stackbuf->node= node;
			VECCOPY(stackbuf->procedural_offset, in[0]->vec);
			VECCOPY(stackbuf->procedural_size, in[1]->vec);
			stackbuf->procedural_type= CB_VAL;
			
			out[0]->data= stackbuf; 
		}
		if(out[1]->hasoutput) {
			CompBuf *stackbuf= alloc_compbuf(sizex, sizey, CB_RGBA, 1); /* alloc */
			
			stackbuf->rect_procedural= texture_procedural;
			stackbuf->node= node;
			VECCOPY(stackbuf->procedural_offset, in[0]->vec);
			VECCOPY(stackbuf->procedural_size, in[1]->vec);
			stackbuf->procedural_type= CB_RGBA;
			
			out[1]->data= stackbuf;
		}
	}
}

bNodeType cmp_node_texture= {
	/* *next,*prev */	NULL, NULL,
	/* type code   */	CMP_NODE_TEXTURE,
	/* name        */	"Texture",
	/* width+range */	120, 80, 240,
	/* class+opts  */	NODE_CLASS_INPUT, NODE_OPTIONS|NODE_PREVIEW,
	/* input sock  */	cmp_node_texture_in,
	/* output sock */	cmp_node_texture_out,
	/* storage     */	"",
	/* execfunc    */	node_composit_exec_texture,
	/* butfunc     */	NULL,
	/* initfunc    */	NULL,
	/* freestoragefunc    */	NULL,
	/* copystoragefunc    */	NULL,
	/* id          */	NULL
	
};


