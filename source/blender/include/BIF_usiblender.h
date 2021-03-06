/**
 * $Id: BIF_usiblender.h 14444 2008-04-16 22:40:48Z hos $
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

#ifndef BIF_USIBLENDER_H
#define BIF_USIBLENDER_H

typedef struct RecentFile {
	struct RecentFile *next, *prev;
	char *filename;
} RecentFile;

void exit_usiblender(void);

void BIF_init(void);

void BIF_read_file(char *name);
int BIF_read_homefile(int from_memory);
void BIF_read_autosavefile(void);

void BIF_write_file(char *target);
void BIF_write_homefile(void);
void BIF_write_autosave(void);
void BIF_clear_tempfiles(void);

#endif

