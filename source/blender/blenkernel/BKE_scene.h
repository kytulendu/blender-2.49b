/**
 * blenlib/BKE_scene.h (mar-2001 nzc)
 *	
 * $Id: BKE_scene.h 19838 2009-04-21 09:44:29Z campbellbarton $ 
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
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */
#ifndef BKE_SCENE_H
#define BKE_SCENE_H

struct bglMats;
struct Scene;
struct Object;
struct Base;
struct Text;
struct AviCodecData;
struct QuicktimeCodecData;
struct SculptData;
struct RenderData;

/* sequence related defines */
#define WHILE_SEQ(base)	{											\
	int totseq_, seq_; Sequence **seqar;	\
		build_seqar( base,  &seqar, &totseq_);	\
			for(seq_ = 0; seq_ < totseq_; seq_++) {	\
				seq= seqar[seq_];
				
				
#define END_SEQ					}						\
				if(seqar) MEM_freeN(seqar);		\
}

/* note; doesn't work when scene is empty */
#define SETLOOPER(s, b) sce= s, b= (Base*)sce->base.first; b; b= (Base*)(b->next?b->next:sce->set?(sce=sce->set)->base.first:NULL)


void free_avicodecdata(struct AviCodecData *acd);
void free_qtcodecdata(struct QuicktimeCodecData *acd);

void free_scene(struct Scene *me);
struct Scene *add_scene(char *name);
struct Base *object_in_scene(struct Object *ob, struct Scene *sce);

void set_scene_bg(struct Scene *sce);
void set_scene_name(char *name);

int next_object(int val, struct Base **base, struct Object **ob);
struct Object *scene_find_camera(struct Scene *sc);

struct Base *scene_add_base(struct Scene *sce, struct Object *ob);
void scene_deselect_all(struct Scene *sce);
void scene_select_base(struct Scene *sce, struct Base *selbase);

/* checks for cycle, returns 1 if it's all OK */
int scene_check_setscene(struct Scene *sce);

void scene_update_for_newframe(struct Scene *sce, unsigned int lay);

void scene_add_render_layer(struct Scene *sce);

/* render profile */
int get_render_subsurf_level(struct RenderData *r, int level);
int get_render_child_particle_number(struct RenderData *r, int num);
int get_render_shadow_samples(struct RenderData *r, int samples);
float get_render_aosss_error(struct RenderData *r, float error);

void free_dome_warp_text(struct Text *txt);

#endif

