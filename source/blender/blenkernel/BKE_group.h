/**
 * blenlib/BKE_group.h (mar-2001 nzc)
 *	
 * $Id: BKE_group.h 14444 2008-04-16 22:40:48Z hos $ 
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
#ifndef BKE_GROUP_H
#define BKE_GROUP_H

struct Group;
struct GroupObject;
struct Object;
struct bAction;

void		free_group_object(struct GroupObject *go);
void		free_group(struct Group *group);
void		unlink_group(struct Group *group);
struct Group *add_group(char *name);
void		add_to_group(struct Group *group, struct Object *ob);
int			rem_from_group(struct Group *group, struct Object *ob);
struct Group *find_group(struct Object *ob, struct Group *group);
int			object_in_group(struct Object *ob, struct Group *group);
int			group_is_animated(struct Object *parent, struct Group *group);

void		group_tag_recalc(struct Group *group);
void		group_handle_recalc_and_update(struct Object *parent, struct Group *group);
struct Object *group_get_member_with_action(struct Group *group, struct bAction *act);
void		group_relink_nla_objects(struct Object *ob);

#endif

