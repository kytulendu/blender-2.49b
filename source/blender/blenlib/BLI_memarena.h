/* 
 * Memory arena ADT
 * 
 * $Id: BLI_memarena.h 17435 2008-11-12 22:35:58Z campbellbarton $
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
 * 
 * Memory arena's are commonly used when the program
 * needs to quickly allocate lots of little bits of
 * data, which are all freed at the same moment.
 * 
 */

#ifndef BLI_MEMARENA_H
#define BLI_MEMARENA_H

	/* A reasonable standard buffer size, big
	 * enough to not cause much internal fragmentation, 
	 * small enough not to waste resources
	 */
#define BLI_MEMARENA_STD_BUFSIZE	(1<<14)

struct MemArena;
typedef struct MemArena MemArena;


struct MemArena*	BLI_memarena_new	(int bufsize);
void				BLI_memarena_free	(struct MemArena *ma);

void				BLI_memarena_use_malloc (struct MemArena *ma);
void				BLI_memarena_use_calloc (struct MemArena *ma);

void*				BLI_memarena_alloc	(struct MemArena *ma, int size);

#endif

