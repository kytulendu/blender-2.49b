/*
 * IMB_bmp.h
 *
 * $Id: IMB_bmp.h 14444 2008-04-16 22:40:48Z hos $
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
 * \file IMB_bmp.h
 * \ingroup imbuf
 * \brief Function declarations for bmp.c
 */

#ifndef IMB_BMP_H
#define IMB_BMP_H

struct ImBuf;

int imb_is_a_bmp(void *buf);
struct ImBuf *imb_bmp_decode(unsigned char *mem, int size, int flags);
short imb_savebmp(struct ImBuf *ibuf, char *name, int flags);

#endif

