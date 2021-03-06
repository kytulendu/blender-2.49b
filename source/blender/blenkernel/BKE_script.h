/**
 * blenlib/BKE_script.h (mar-2001 nzc)
 *	
 * $Id: BKE_script.h 14444 2008-04-16 22:40:48Z hos $ 
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
 * This is a new part of Blender.
 *
 * Contributor(s): Willian P. Germano.
 *
 * ***** END GPL LICENSE BLOCK *****
 */
#ifndef BKE_SCRIPT_H
#define BKE_SCRIPT_H

#ifdef __cplusplus
extern "C" {
#endif

struct Script;

void free_script (struct Script *script);

#ifdef __cplusplus
}
#endif

#endif /* BKE_SCRIPT_H */
