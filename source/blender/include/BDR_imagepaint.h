/**
 * $Id: BDR_imagepaint.h 16366 2008-09-04 20:51:28Z blendix $
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

#ifndef BDR_IMAGEPAINT_H
#define BDR_IMAGEPAINT_H

void imagepaint_redraw_tool(void);
void imagepaint_pick(short mousebutton);
void imagepaint_paint(short mousebutton, short texturepaint);

void undo_imagepaint_step(int step);
void undo_imagepaint_clear(void);

#endif /*  BDR_IMAGEPAINT_H */

