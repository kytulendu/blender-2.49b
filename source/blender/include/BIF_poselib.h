/**
 * $Id: BIF_poselib.h 14444 2008-04-16 22:40:48Z hos $
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
 * The Original Code is Copyright (C) 2007 Blender Foundation
 * All rights reserved.
 *
 * The Original Code is: this is a new part of Blender
 *
 * Contributor(s): Joshua Leung
 *
 * ***** END GPL LICENSE BLOCK *****
 */
 
#ifndef BIF_POSELIB_H
#define BIF_POSELIB_H

struct Object;
struct bAction;
struct TimeMarker;

char *poselib_build_poses_menu(struct bAction *act, char title[]);
int poselib_get_free_index(struct bAction *act);
struct TimeMarker *poselib_get_active_pose(struct bAction *act);

struct bAction *poselib_init_new(struct Object *ob);
struct bAction *poselib_validate(struct Object *ob);

void poselib_validate_act(struct bAction *act);

void poselib_remove_pose(struct Object *ob, struct TimeMarker *marker);
void poselib_rename_pose(struct Object *ob);
void poselib_add_current_pose(struct Object *ob, int mode);

void poselib_preview_poses(struct Object *ob, short apply_active);

#endif
