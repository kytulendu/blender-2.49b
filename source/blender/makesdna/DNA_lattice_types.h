/**
 * $Id: DNA_lattice_types.h 14444 2008-04-16 22:40:48Z hos $ 
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
#ifndef DNA_LATTICE_TYPES_H
#define DNA_LATTICE_TYPES_H

#include "DNA_ID.h"

struct BPoint;
struct Ipo;
struct Key;
struct MDeformVert;

typedef struct Lattice {
	ID id;
	
	short pntsu, pntsv, pntsw, flag;
	short opntsu, opntsv, opntsw, pad2;
	char typeu, typev, typew, type;
	int pad;
	
	float fu, fv, fw, du, dv, dw;
	
	struct BPoint *def;
	
	struct Ipo *ipo;
	struct Key *key;
	
	struct MDeformVert *dvert;
} Lattice;

/* ***************** LATTICE ********************* */

/* flag */
#define LT_GRID		1
#define LT_OUTSIDE	2

#endif

