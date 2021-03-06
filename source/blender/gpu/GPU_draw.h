/**
 * $Id: GPU_draw.h 19485 2009-03-31 22:34:34Z gsrb3d $
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This shader is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version. The Blender
 * Foundation also sells licenses for use in proprietary software under
 * the Blender License.  See http://www.blender.org/BL/ for information
 * about this.
 *
 * This shader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this shader; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2005 Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Brecht Van Lommel.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#ifndef GPU_GAME_H
#define GPU_GAME_H

#ifdef __cplusplus
extern "C" {
#endif

struct MTFace;
struct Image;
struct Scene;
struct Object;

/* OpenGL drawing functions related to shading. These are also
 * shared with the game engine, where there were previously
 * duplicates of some of these functions. */

/* Initialize
 * - sets the default Blender opengl state, if in doubt, check
 *   the contents of this function
 * - this is called when starting Blender, for opengl rendering,
 *   and for switching back from the game engine for example. */

void GPU_state_init(void);

/* Material drawing
 * - first the state is initialized by a particular object and
 *   it's materials
 * - after this, materials can be quickly enabled by their number,
 *   GPU_enable_material returns 0 if drawing should be skipped
 * - after drawing, the material must be disabled again */

void GPU_set_object_materials(struct Scene *scene, struct Object *ob,
	int glsl, int *do_alpha_pass);
int GPU_enable_material(int nr, void *attribs);
void GPU_disable_material(void);

void GPU_set_material_blend_mode(int blendmode);
int GPU_get_material_blend_mode(void);

/* TexFace drawing
 * - this is mutually exclusive with material drawing, a mesh should
 *   be drawn using one or the other
 * - passing NULL clears the state again */

int GPU_set_tpage(struct MTFace *tface);

/* Lights
 * - returns how many lights were enabled
 * - this affects fixed functions materials and texface, not glsl */

int GPU_default_lights(void);
int GPU_scene_object_lights(struct Scene *scene, struct Object *ob,
	int lay, float viewmat[][4], int ortho);

/* Text render
 * - based on moving uv coordinates */

void GPU_render_text(struct MTFace *tface, int mode,
	const char *textstr, int textlen, unsigned int *col,
	float *v1, float *v2, float *v3, float *v4, int glattrib);

/* Mipmap settings
 * - these will free textures on changes */

void GPU_set_mipmap(int mipmap);
void GPU_set_linear_mipmap(int linear);
void GPU_paint_set_mipmap(int mipmap);

/* Image updates and free
 * - these deal with images bound as opengl textures */

void GPU_paint_update_image(struct Image *ima, int x, int y, int w, int h);
void GPU_update_images_framechange(void);
int GPU_update_image_time(struct Image *ima, double time);
int GPU_verify_image(struct Image *ima, int tftile, int tfmode, int compare);
void GPU_free_image(struct Image *ima);
void GPU_free_images(void);

#ifdef __cplusplus
}
#endif

#endif

