/**
 * blenlib/DNA_fileglobal_types.h (mar-2001 nzc)
 *	
 * $Id: DNA_fileglobal_types.h 14444 2008-04-16 22:40:48Z hos $ 
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
#ifndef DNA_FILEGLOBAL_TYPES_H
#define DNA_FILEGLOBAL_TYPES_H

/**
 * FileGlobal stores a part of the current user-unterface settings at
 * the moment of saving, and the file-specific settings.
 */
typedef struct FileGlobal {
	char subvstr[4];		/* needs to be here, for human fileformat recognition */
	short subversion, pads;
	short minversion, minsubversion;
	short displaymode, winpos;
	void *curscreen;
	void *curscene;
	int fileflags;
	int globalf;
} FileGlobal;


/* minversion: in file, the oldest past blender version you can use compliant */
/* example: if in 2.43 the meshes lose mesh data, minversion is 2.43 then too */
/* or: in 2.42, subversion 1, same as above, minversion then is 2.42, min subversion 1 */
/* (defines for version are in the BKE_blender.h file, for historic reasons) */


#endif

