/*
 * $Id: genfile.h 14444 2008-04-16 22:40:48Z hos $
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
 * blenloader genfile private function prototypes
 */

#ifndef GENFILE_H
#define GENFILE_H

struct SDNA;

int dna_findstruct_nr(struct SDNA *sdna, char *str);
char *dna_get_structDNA_compareflags(struct SDNA *sdna, struct SDNA *newsdna);
void dna_switch_endian_struct(struct SDNA *oldsdna, int oldSDNAnr, char *data);
void *dna_reconstruct(struct SDNA *newsdna, struct SDNA *oldsdna, char *compflags, int oldSDNAnr, int blocks, void *data);
int dna_elem_offset(struct SDNA *sdna, char *stype, char *vartype, char *name);

struct SDNA *dna_sdna_from_data(void *data, int datalen, int do_endian_swap);
void dna_freestructDNA(struct SDNA *sdna);

#endif

