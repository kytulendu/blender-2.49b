/*
 * IMB_cmap.h
 *
 * $Id: IMB_cmap.h 14444 2008-04-16 22:40:48Z hos $
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
/**
 * \file IMB_cmap.h
 * \ingroup imbuf
 * \brief Function declarations for cmap.c
 */
#ifndef IMB_CMAP_H
#define IMB_CMAP_H

struct ImBuf;

void imb_makecolarray(struct ImBuf *ibuf, unsigned char *mem, short nocols);
void imb_losecmapbits(struct ImBuf *ibuf, unsigned int *coltab);
short *imb_coldeltatab(unsigned char *coltab, short mincol, short maxcol, short cbits);

#endif

