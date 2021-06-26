/**
 * $Id: BMF_font_helvb12.cpp 14444 2008-04-16 22:40:48Z hos $
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "BMF_FontData.h"
#include "BMF_Settings.h"

#if BMF_INCLUDE_HELVB12

static unsigned char bitmap_data[]= {
	0x00,0xc0,0xc0,0x00,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xa0,0xa0,0xa0,0x6c,
	0x00,0x6c,0x00,0x6c,0x00,0xff,0x00,0x36,
	0x00,0x36,0x00,0x36,0x00,0x7f,0x80,0x1b,
	0x00,0x1b,0x00,0x1b,0x00,0x30,0x30,0x78,
	0xec,0xac,0x3c,0x38,0x70,0xf0,0xd4,0xdc,
	0x78,0x30,0x63,0x80,0x37,0xc0,0x36,0xc0,
	0x1f,0xc0,0x1b,0x80,0x0c,0x00,0x76,0x00,
	0xfe,0x00,0xdb,0x00,0xfb,0x00,0x71,0x80,
	0x73,0x80,0xff,0x00,0xce,0x00,0xcf,0x00,
	0xdd,0x80,0x79,0x80,0x38,0x00,0x6c,0x00,
	0x6c,0x00,0x7c,0x00,0x38,0x00,0x80,0x40,
	0xc0,0xc0,0x30,0x60,0x60,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0x60,0x60,0x30,
	0xc0,0x60,0x60,0x30,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x60,0x60,0xc0,0xd8,0x70,
	0x70,0xf8,0x20,0x30,0x30,0xfc,0xfc,0x30,
	0x30,0x80,0x40,0xc0,0xc0,0xfc,0xfc,0xc0,
	0xc0,0xc0,0xc0,0xc0,0x60,0x60,0x60,0x20,
	0x30,0x30,0x30,0x18,0x18,0x18,0x78,0xfc,
	0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xfc,
	0x78,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x30,0xf0,0xf0,0x30,0xfc,0xfc,0xc0,0x60,
	0x70,0x38,0x18,0xcc,0xcc,0xfc,0x78,0x78,
	0xfc,0xcc,0xcc,0x0c,0x38,0x38,0x0c,0xcc,
	0xfc,0x78,0x0c,0x0c,0xfe,0xfe,0xcc,0x6c,
	0x6c,0x3c,0x3c,0x1c,0x1c,0x78,0xfc,0xcc,
	0xcc,0x0c,0xfc,0xf8,0xc0,0xc0,0xfc,0xfc,
	0x78,0xfc,0xcc,0xcc,0xcc,0xfc,0xf8,0xc0,
	0xcc,0xfc,0x78,0x60,0x60,0x60,0x30,0x30,
	0x30,0x18,0x18,0x0c,0xfc,0xfc,0x78,0xfc,
	0xcc,0xcc,0xcc,0x78,0x78,0xcc,0xcc,0xfc,
	0x78,0x78,0xfc,0xcc,0x0c,0x7c,0xfc,0xcc,
	0xcc,0xcc,0xfc,0x78,0xc0,0xc0,0x00,0x00,
	0x00,0x00,0xc0,0xc0,0x80,0x40,0xc0,0xc0,
	0x00,0x00,0x00,0x00,0xc0,0xc0,0x0c,0x38,
	0xe0,0xe0,0x38,0x0c,0xfc,0xfc,0x00,0xfc,
	0xfc,0xc0,0x70,0x1c,0x1c,0x70,0xc0,0x30,
	0x30,0x00,0x30,0x30,0x38,0x1c,0xcc,0xcc,
	0xfc,0x78,0x1f,0x00,0x71,0x80,0x40,0x00,
	0xdd,0x80,0xb6,0xc0,0xb2,0x40,0xb3,0x60,
	0xdb,0x20,0x4d,0xa0,0x60,0x40,0x39,0xc0,
	0x0f,0x00,0xc3,0xc3,0xff,0x7e,0x66,0x66,
	0x3c,0x3c,0x3c,0x18,0x18,0xf8,0xfc,0xcc,
	0xcc,0xcc,0xf8,0xf8,0xcc,0xcc,0xfc,0xf8,
	0x78,0xfc,0xcc,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xcc,0xfc,0x78,0xf8,0xfc,0xce,0xc6,0xc6,
	0xc6,0xc6,0xc6,0xce,0xfc,0xf8,0xfc,0xfc,
	0xc0,0xc0,0xc0,0xf8,0xf8,0xc0,0xc0,0xfc,
	0xfc,0xc0,0xc0,0xc0,0xc0,0xc0,0xf8,0xf8,
	0xc0,0xc0,0xfc,0xfc,0x76,0xfe,0xc6,0xc6,
	0xde,0xde,0xc0,0xc0,0xc6,0xfe,0x7c,0xc6,
	0xc6,0xc6,0xc6,0xc6,0xfe,0xfe,0xc6,0xc6,
	0xc6,0xc6,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0x70,0xf8,0xd8,
	0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
	0xc6,0xce,0xcc,0xd8,0xf8,0xf0,0xf0,0xd8,
	0xcc,0xcc,0xc6,0xfc,0xfc,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc9,0x80,
	0xc9,0x80,0xdd,0x80,0xdd,0x80,0xf7,0x80,
	0xf7,0x80,0xe3,0x80,0xe3,0x80,0xe3,0x80,
	0xc1,0x80,0xc1,0x80,0xc6,0xc6,0xce,0xce,
	0xde,0xd6,0xf6,0xe6,0xe6,0xc6,0xc6,0x7c,
	0xfe,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,
	0xfe,0x7c,0xc0,0xc0,0xc0,0xc0,0xfc,0xfe,
	0xc6,0xc6,0xc6,0xfe,0xfc,0x06,0x7e,0xfc,
	0xce,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0xfe,
	0x7c,0xc6,0xc6,0xc6,0xce,0xfc,0xfc,0xc6,
	0xc6,0xc6,0xfe,0xfc,0x78,0xfc,0xcc,0x0c,
	0x1c,0x78,0xe0,0xc0,0xcc,0xfc,0x78,0x30,
	0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0xfc,0xfc,0x7c,0xfe,0xc6,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0xc6,0xc6,0x18,0x18,0x18,
	0x3c,0x3c,0x3c,0x66,0x66,0x66,0xc3,0xc3,
	0x33,0x00,0x33,0x00,0x33,0x00,0x3b,0x00,
	0x7f,0x80,0x6d,0x80,0x6d,0x80,0x6d,0x80,
	0xcc,0xc0,0xcc,0xc0,0xcc,0xc0,0xc3,0xc3,
	0x66,0x7e,0x3c,0x18,0x3c,0x7e,0x66,0xc3,
	0xc3,0x18,0x18,0x18,0x18,0x18,0x3c,0x3c,
	0x66,0x66,0xc3,0xc3,0xfe,0xfe,0xc0,0x60,
	0x60,0x30,0x18,0x18,0x0c,0xfe,0xfe,0xe0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xe0,0x30,0x30,0x30,
	0x70,0x60,0x60,0x60,0xe0,0xc0,0xc0,0xc0,
	0xe0,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0xe0,0x88,0xd8,
	0x70,0x70,0x20,0xfe,0xc0,0xc0,0x80,0x40,
	0x76,0xfc,0xcc,0xfc,0x7c,0x8c,0xfc,0x78,
	0xd8,0xfc,0xcc,0xcc,0xcc,0xcc,0xfc,0xd8,
	0xc0,0xc0,0xc0,0x78,0xfc,0xcc,0xc0,0xc0,
	0xcc,0xfc,0x78,0x6c,0xfc,0xcc,0xcc,0xcc,
	0xcc,0xfc,0x6c,0x0c,0x0c,0x0c,0x78,0xfc,
	0xc0,0xfc,0xfc,0xcc,0xfc,0x78,0x60,0x60,
	0x60,0x60,0x60,0x60,0xf0,0xf0,0x60,0x70,
	0x30,0x78,0xfc,0x0c,0x6c,0xfc,0xcc,0xcc,
	0xcc,0xcc,0xfc,0x6c,0xcc,0xcc,0xcc,0xcc,
	0xcc,0xec,0xfc,0xd8,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0x00,
	0xc0,0xc0,0xc0,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0x00,0x60,0x60,
	0xcc,0xd8,0xd8,0xf0,0xe0,0xf0,0xd8,0xcc,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xcc,0xc0,
	0xcc,0xc0,0xcc,0xc0,0xcc,0xc0,0xcc,0xc0,
	0xee,0xc0,0xff,0xc0,0xbb,0x80,0xcc,0xcc,
	0xcc,0xcc,0xcc,0xec,0xfc,0xd8,0x78,0xfc,
	0xcc,0xcc,0xcc,0xcc,0xfc,0x78,0xc0,0xc0,
	0xc0,0xd8,0xfc,0xcc,0xcc,0xcc,0xcc,0xfc,
	0xd8,0x0c,0x0c,0x0c,0x6c,0xfc,0xcc,0xcc,
	0xcc,0xcc,0xfc,0x6c,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xe0,0xb0,0x78,0xfc,0xcc,0x1c,
	0x78,0xe0,0xfc,0x78,0x30,0x70,0x60,0x60,
	0x60,0x60,0xf0,0xf0,0x60,0x60,0x6c,0xfc,
	0xdc,0xcc,0xcc,0xcc,0xcc,0xcc,0x30,0x30,
	0x78,0x78,0x78,0xcc,0xcc,0xcc,0x24,0x24,
	0x76,0x76,0x7e,0xdb,0xdb,0xdb,0xcc,0xcc,
	0x78,0x38,0x70,0x78,0xcc,0xcc,0xe0,0xf0,
	0x30,0x30,0x38,0x78,0x78,0x48,0xcc,0xcc,
	0xcc,0xfc,0xfc,0x60,0x30,0x30,0x18,0xfc,
	0xfc,0x30,0x60,0x60,0x60,0x60,0x60,0x40,
	0x80,0x40,0x60,0x60,0x60,0x60,0x30,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0xc0,0x60,0x60,0x60,
	0x60,0x60,0x20,0x10,0x20,0x60,0x60,0x60,
	0x60,0xc0,0x98,0xfc,0x64,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0x00,0xc0,0xc0,
	0xc0,0x78,0xfc,0xec,0xe0,0xd0,0xd4,0xfc,
	0x78,0x0c,0xdc,0xfe,0x60,0x30,0x30,0xfc,
	0x30,0x60,0x64,0x7c,0x38,0xcc,0x78,0xcc,
	0xcc,0x78,0xcc,0x18,0x18,0x18,0x7e,0x18,
	0x7e,0x3c,0x66,0x66,0xc3,0xc3,0x80,0x80,
	0x80,0x80,0x80,0x80,0x00,0x00,0x80,0x80,
	0x80,0x80,0x80,0x78,0xfc,0xcc,0x1c,0x38,
	0x6c,0xcc,0xcc,0xd8,0x70,0xe0,0xcc,0xfc,
	0x78,0xd8,0xd8,0x1f,0x00,0x71,0xc0,0x6e,
	0xc0,0xdb,0x60,0xdb,0x60,0xd8,0x60,0xdb,
	0x60,0xdb,0x60,0x6e,0xc0,0x71,0xc0,0x1f,
	0x00,0xf0,0x00,0xd0,0xb0,0x70,0xb0,0x60,
	0x36,0x6c,0xd8,0x6c,0x36,0x0c,0x0c,0xfc,
	0xfc,0xe0,0xe0,0x1f,0x00,0x71,0xc0,0x7b,
	0xc0,0xdb,0x60,0xdf,0x60,0xde,0x60,0xdb,
	0x60,0xdb,0x60,0x7e,0xc0,0x71,0xc0,0x1f,
	0x00,0xf0,0xf0,0x60,0x90,0x90,0x60,0xfc,
	0xfc,0x00,0x30,0x30,0xfc,0xfc,0x30,0x30,
	0xf0,0x40,0x20,0x10,0x90,0x60,0x60,0x90,
	0x10,0x20,0x90,0x60,0xc0,0x70,0x30,0xc0,
	0xc0,0xc0,0xec,0xfc,0xdc,0xcc,0xcc,0xcc,
	0xcc,0xcc,0x36,0x36,0x36,0x36,0x36,0x36,
	0x36,0x36,0x76,0xf6,0xf6,0xf6,0xfe,0x7e,
	0xc0,0xc0,0xc0,0x60,0x40,0x40,0x40,0x40,
	0x40,0xc0,0x40,0xf8,0x00,0x70,0xd8,0xd8,
	0xd8,0x70,0xd8,0x6c,0x36,0x6c,0xd8,0x20,
	0x80,0x27,0xc0,0x12,0x80,0x12,0x80,0x09,
	0x80,0x4c,0x80,0x44,0x00,0x42,0x00,0x42,
	0x00,0xc1,0x00,0x41,0x00,0x23,0xc0,0x21,
	0x00,0x10,0x80,0x10,0x40,0x0a,0x40,0x4d,
	0x80,0x44,0x00,0x42,0x00,0x42,0x00,0xc1,
	0x00,0x41,0x00,0x20,0x80,0x27,0xc0,0x12,
	0x80,0x12,0x80,0x09,0x80,0x6c,0x80,0x94,
	0x00,0x12,0x00,0x22,0x00,0x91,0x00,0x61,
	0x00,0x78,0xfc,0xcc,0xcc,0xe0,0x70,0x30,
	0x30,0x00,0x30,0x30,0xc3,0xc3,0x7e,0x7e,
	0x24,0x3c,0x18,0x18,0x00,0x0c,0x38,0x30,
	0xc3,0xc3,0x7e,0x7e,0x24,0x3c,0x18,0x18,
	0x00,0x30,0x1c,0x0c,0xc3,0xc3,0x7e,0x7e,
	0x24,0x3c,0x18,0x18,0x00,0x66,0x3c,0x18,
	0xc3,0xc3,0x7e,0x7e,0x24,0x3c,0x18,0x18,
	0x00,0x2c,0x3e,0x1a,0xc3,0xc3,0x7e,0x7e,
	0x24,0x3c,0x18,0x18,0x00,0x6c,0x6c,0xc3,
	0xc3,0x7e,0x7e,0x24,0x3c,0x18,0x18,0x00,
	0x18,0x34,0x18,0xc7,0xe0,0xc7,0xe0,0xfe,
	0x00,0x7e,0x00,0x66,0x00,0x67,0xc0,0x37,
	0xc0,0x36,0x00,0x3e,0x00,0x1f,0xe0,0x1f,
	0xe0,0x60,0x30,0x20,0x78,0xfc,0xcc,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xcc,0xfc,0x78,0xfc,
	0xfc,0xc0,0xf8,0xf8,0xc0,0xfc,0xfc,0x00,
	0x18,0x70,0x60,0xfc,0xfc,0xc0,0xf8,0xf8,
	0xc0,0xfc,0xfc,0x00,0x60,0x38,0x18,0xfc,
	0xfc,0xc0,0xf8,0xf8,0xc0,0xfc,0xfc,0x00,
	0xcc,0x78,0x30,0xfc,0xfc,0xc0,0xf8,0xf8,
	0xc0,0xfc,0xfc,0x00,0xd8,0xd8,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0x60,0x00,0x30,
	0xe0,0xc0,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x00,0xc0,0x70,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30,0x30,0x30,0x00,0xcc,
	0x78,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x30,0x30,0x00,0xd8,0xd8,0x7c,0x7e,0x67,
	0x63,0x63,0xfb,0xfb,0x63,0x67,0x7e,0x7c,
	0xc6,0xce,0xce,0xde,0xf6,0xe6,0xe6,0xc6,
	0x00,0x58,0x7c,0x34,0x7c,0xfe,0xc6,0xc6,
	0xc6,0xc6,0xfe,0x7c,0x00,0x18,0x70,0x60,
	0x7c,0xfe,0xc6,0xc6,0xc6,0xc6,0xfe,0x7c,
	0x00,0x30,0x1c,0x0c,0x7c,0xfe,0xc6,0xc6,
	0xc6,0xc6,0xfe,0x7c,0x00,0xcc,0x78,0x30,
	0x7c,0xfe,0xc6,0xc6,0xc6,0xc6,0xfe,0x7c,
	0x00,0x58,0x7c,0x34,0x7c,0xfe,0xc6,0xc6,
	0xc6,0xc6,0xfe,0x7c,0x00,0x6c,0x6c,0xcc,
	0x78,0x30,0x30,0x78,0xcc,0xde,0x00,0x7f,
	0x00,0x63,0x00,0x73,0x00,0x7b,0x00,0x6b,
	0x00,0x6f,0x00,0x67,0x00,0x63,0x00,0x7f,
	0x00,0x3d,0x80,0x7c,0xfe,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0x00,0x18,0x70,0x60,0x7c,
	0xfe,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x00,
	0x30,0x1c,0x0c,0x7c,0xfe,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0x00,0xcc,0x78,0x30,0x7c,
	0xfe,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x00,
	0x6c,0x6c,0x18,0x18,0x18,0x18,0x3c,0x7e,
	0xe7,0xc3,0x00,0x30,0x1c,0x0c,0xc0,0xc0,
	0xfc,0xfe,0xc6,0xc6,0xc6,0xfe,0xfc,0xc0,
	0xc0,0xd8,0xdc,0xcc,0xcc,0xcc,0xd8,0xd8,
	0xcc,0xcc,0xfc,0x78,0x76,0xfc,0xcc,0xfc,
	0x7c,0x8c,0xfc,0x78,0x00,0x18,0x70,0x60,
	0x76,0xfc,0xcc,0xfc,0x7c,0x8c,0xfc,0x78,
	0x00,0x60,0x38,0x18,0x76,0xfc,0xcc,0xfc,
	0x7c,0x8c,0xfc,0x78,0x00,0xcc,0x78,0x30,
	0x76,0xfc,0xcc,0xfc,0x7c,0x8c,0xfc,0x78,
	0x00,0x58,0x7c,0x34,0x76,0xfc,0xcc,0xfc,
	0x7c,0x8c,0xfc,0x78,0x00,0xd8,0xd8,0x76,
	0xfc,0xcc,0xfc,0x7c,0x8c,0xfc,0x78,0x00,
	0x30,0x68,0x30,0x77,0x80,0xff,0xc0,0xcc,
	0x00,0xff,0xc0,0x7f,0xc0,0x8c,0xc0,0xff,
	0xc0,0x7b,0x80,0x60,0x30,0x20,0x78,0xfc,
	0xcc,0xc0,0xc0,0xcc,0xfc,0x78,0x78,0xfc,
	0xc0,0xfc,0xfc,0xcc,0xfc,0x78,0x00,0x18,
	0x70,0x60,0x78,0xfc,0xc0,0xfc,0xfc,0xcc,
	0xfc,0x78,0x00,0x60,0x38,0x18,0x78,0xfc,
	0xc0,0xfc,0xfc,0xcc,0xfc,0x78,0x00,0xcc,
	0x78,0x30,0x78,0xfc,0xc0,0xfc,0xfc,0xcc,
	0xfc,0x78,0x00,0xd8,0xd8,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0x00,0x30,0xe0,
	0xc0,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x00,0xc0,0x70,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30,0x30,0x00,0xcc,0x78,
	0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x30,0x00,0xd8,0xd8,0x78,0xfc,0xcc,0xcc,
	0xcc,0xcc,0xfc,0x78,0xb0,0x60,0xd0,0xcc,
	0xcc,0xcc,0xcc,0xcc,0xec,0xfc,0xd8,0x00,
	0xb0,0xf8,0x68,0x78,0xfc,0xcc,0xcc,0xcc,
	0xcc,0xfc,0x78,0x00,0x18,0x70,0x60,0x78,
	0xfc,0xcc,0xcc,0xcc,0xcc,0xfc,0x78,0x00,
	0x60,0x38,0x18,0x78,0xfc,0xcc,0xcc,0xcc,
	0xcc,0xfc,0x78,0x00,0xcc,0x78,0x30,0x78,
	0xfc,0xcc,0xcc,0xcc,0xcc,0xfc,0x78,0x00,
	0xb0,0xf8,0x68,0x78,0xfc,0xcc,0xcc,0xcc,
	0xcc,0xfc,0x78,0x00,0xd8,0xd8,0x30,0x30,
	0x00,0xfc,0xfc,0x00,0x30,0x30,0xc0,0x78,
	0xfc,0xcc,0xec,0xdc,0xcc,0xfc,0x78,0x0c,
	0x6c,0xfc,0xdc,0xcc,0xcc,0xcc,0xcc,0xcc,
	0x00,0x18,0x70,0x60,0x6c,0xfc,0xdc,0xcc,
	0xcc,0xcc,0xcc,0xcc,0x00,0x60,0x38,0x18,
	0x6c,0xfc,0xdc,0xcc,0xcc,0xcc,0xcc,0xcc,
	0x00,0xcc,0x78,0x30,0x6c,0xfc,0xdc,0xcc,
	0xcc,0xcc,0xcc,0xcc,0x00,0xd8,0xd8,0xe0,
	0xf0,0x30,0x30,0x38,0x78,0x78,0x48,0xcc,
	0xcc,0xcc,0x00,0x60,0x38,0x18,0xc0,0xc0,
	0xc0,0xd8,0xfc,0xcc,0xcc,0xcc,0xcc,0xfc,
	0xd8,0xc0,0xc0,0xc0,0xe0,0xf0,0x30,0x30,
	0x38,0x78,0x78,0x48,0xcc,0xcc,0xcc,0x00,
	0xd8,0xd8,
};

BMF_FontData BMF_font_helvb12 = {
	-1, -3,
	11, 12,
	{
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0, 0, 0, 0, 12, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{1, 1, 0, 0, 3, 0},
		{2, 11, -1, 0, 4, 1},
		{3, 3, 0, -8, 4, 12},
		{9, 11, 1, 0, 7, 15},
		{6, 13, 0, 2, 7, 37},
		{10, 11, 0, 0, 11, 50},
		{9, 11, 0, 0, 9, 72},
		{2, 4, 0, -7, 3, 94},
		{4, 14, 0, 3, 4, 98},
		{4, 14, 1, 3, 4, 112},
		{5, 5, 0, -6, 6, 126},
		{6, 6, 0, -1, 7, 131},
		{2, 4, 0, 2, 3, 137},
		{6, 2, -1, -3, 9, 141},
		{2, 2, 0, 0, 3, 143},
		{5, 13, 1, 2, 4, 145},
		{6, 11, 0, 0, 7, 158},
		{4, 11, 0, 0, 6, 169},
		{6, 11, 0, 0, 7, 180},
		{6, 11, 0, 0, 7, 191},
		{7, 11, 0, 0, 7, 202},
		{6, 11, 0, 0, 7, 213},
		{6, 11, 0, 0, 7, 224},
		{6, 11, 0, 0, 7, 235},
		{6, 11, 0, 0, 7, 246},
		{6, 11, 0, 0, 7, 257},
		{2, 8, -1, 0, 4, 268},
		{2, 10, -1, 2, 4, 276},
		{6, 6, 0, -1, 7, 286},
		{6, 5, 0, -2, 7, 292},
		{6, 6, 0, -1, 7, 297},
		{6, 11, 0, 0, 7, 303},
		{11, 12, 0, 1, 12, 314},
		{8, 11, 0, 0, 8, 338},
		{6, 11, -1, 0, 8, 349},
		{6, 11, -1, 0, 8, 360},
		{7, 11, -1, 0, 9, 371},
		{6, 11, -1, 0, 8, 382},
		{6, 11, -1, 0, 7, 393},
		{7, 11, -1, 0, 9, 404},
		{7, 11, -1, 0, 9, 415},
		{2, 11, -2, 0, 6, 426},
		{5, 11, 0, 0, 6, 437},
		{7, 11, -1, 0, 8, 448},
		{6, 11, -1, 0, 7, 459},
		{9, 11, -1, 0, 11, 470},
		{7, 11, -1, 0, 9, 492},
		{7, 11, -1, 0, 9, 503},
		{7, 11, -1, 0, 9, 514},
		{7, 12, -1, 1, 9, 525},
		{7, 11, -1, 0, 9, 537},
		{6, 11, -1, 0, 8, 548},
		{6, 11, 0, 0, 6, 559},
		{7, 11, -1, 0, 9, 570},
		{8, 11, 0, 0, 8, 581},
		{10, 11, 0, 0, 10, 592},
		{8, 11, 0, 0, 8, 614},
		{8, 11, 0, 0, 8, 625},
		{7, 11, 0, 0, 7, 636},
		{3, 14, 0, 3, 4, 647},
		{4, 11, 0, 0, 5, 661},
		{3, 14, 0, 3, 4, 672},
		{5, 5, 0, -6, 7, 686},
		{7, 1, 0, 2, 7, 691},
		{2, 4, 0, -7, 3, 692},
		{7, 8, 0, 0, 7, 696},
		{6, 11, 0, 0, 7, 704},
		{6, 8, 0, 0, 7, 715},
		{6, 11, 0, 0, 7, 723},
		{6, 8, 0, 0, 7, 734},
		{4, 11, 0, 0, 5, 742},
		{6, 11, 0, 3, 7, 753},
		{6, 11, 0, 0, 7, 764},
		{2, 11, -1, 0, 5, 775},
		{3, 14, 0, 3, 5, 786},
		{6, 11, 0, 0, 6, 800},
		{2, 11, -1, 0, 5, 811},
		{10, 8, 0, 0, 11, 822},
		{6, 8, 0, 0, 7, 838},
		{6, 8, 0, 0, 7, 846},
		{6, 11, 0, 3, 7, 854},
		{6, 11, 0, 3, 7, 865},
		{4, 8, 0, 0, 4, 876},
		{6, 8, 0, 0, 7, 884},
		{4, 10, 0, 0, 5, 892},
		{6, 8, 0, 0, 7, 902},
		{6, 8, 0, 0, 7, 910},
		{8, 8, 0, 0, 9, 918},
		{6, 8, 0, 0, 7, 926},
		{6, 11, 0, 3, 7, 934},
		{6, 8, 0, 0, 7, 945},
		{4, 14, 0, 3, 4, 953},
		{1, 13, -1, 2, 3, 967},
		{4, 14, 0, 3, 4, 980},
		{6, 3, 0, -3, 7, 994},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{0,0,0,0,0, -1},
		{2, 11, 0, 3, 3, 997},
		{6, 10, 0, 1, 7, 1008},
		{7, 11, 0, 0, 7, 1018},
		{6, 6, 0, -3, 7, 1029},
		{8, 11, 1, 0, 7, 1035},
		{1, 13, -1, 2, 3, 1046},
		{6, 14, 0, 3, 7, 1059},
		{5, 2, 0, -9, 5, 1073},
		{11, 11, 0, 0, 12, 1075},
		{4, 7, 0, -4, 5, 1097},
		{7, 5, 0, -2, 8, 1104},
		{6, 4, -1, -3, 9, 1109},
		{3, 2, 0, -3, 4, 1113},
		{11, 11, 0, 0, 12, 1115},
		{4, 2, 0, -9, 4, 1137},
		{4, 4, -1, -7, 6, 1139},
		{6, 9, 0, -1, 7, 1143},
		{4, 6, 0, -5, 4, 1152},
		{4, 6, 0, -5, 4, 1158},
		{4, 3, -1, -9, 4, 1164},
		{6, 11, 0, 3, 7, 1167},
		{7, 14, -1, 3, 10, 1178},
		{2, 2, 0, -5, 3, 1192},
		{3, 3, -1, 3, 5, 1194},
		{2, 6, 0, -5, 4, 1197},
		{5, 7, 0, -4, 6, 1203},
		{7, 5, 0, -2, 8, 1210},
		{10, 11, 0, 0, 11, 1215},
		{10, 11, 0, 0, 11, 1237},
		{10, 11, 0, 0, 11, 1259},
		{6, 11, 0, 3, 7, 1281},
		{8, 12, 0, 0, 8, 1292},
		{8, 12, 0, 0, 8, 1304},
		{8, 12, 0, 0, 8, 1316},
		{8, 12, 0, 0, 8, 1328},
		{8, 11, 0, 0, 8, 1340},
		{8, 12, 0, 0, 8, 1351},
		{11, 11, 0, 0, 12, 1363},
		{6, 14, -1, 3, 8, 1385},
		{6, 12, -1, 0, 8, 1399},
		{6, 12, -1, 0, 8, 1411},
		{6, 12, -1, 0, 8, 1423},
		{6, 11, -1, 0, 8, 1435},
		{4, 12, -1, 0, 6, 1446},
		{4, 12, -1, 0, 6, 1458},
		{6, 12, 0, 0, 6, 1470},
		{5, 11, 0, 0, 6, 1482},
		{8, 11, 0, 0, 9, 1493},
		{7, 12, -1, 0, 9, 1504},
		{7, 12, -1, 0, 9, 1516},
		{7, 12, -1, 0, 9, 1528},
		{7, 12, -1, 0, 9, 1540},
		{7, 12, -1, 0, 9, 1552},
		{7, 11, -1, 0, 9, 1564},
		{6, 6, 0, -1, 7, 1575},
		{9, 11, 0, 0, 9, 1581},
		{7, 12, -1, 0, 9, 1603},
		{7, 12, -1, 0, 9, 1615},
		{7, 12, -1, 0, 9, 1627},
		{7, 11, -1, 0, 9, 1639},
		{8, 12, 0, 0, 8, 1650},
		{7, 11, -1, 0, 9, 1662},
		{6, 11, 0, 0, 7, 1673},
		{7, 12, 0, 0, 7, 1684},
		{7, 12, 0, 0, 7, 1696},
		{7, 12, 0, 0, 7, 1708},
		{7, 12, 0, 0, 7, 1720},
		{7, 11, 0, 0, 7, 1732},
		{7, 12, 0, 0, 7, 1743},
		{10, 8, 0, 0, 11, 1755},
		{6, 11, 0, 3, 7, 1771},
		{6, 12, 0, 0, 7, 1782},
		{6, 12, 0, 0, 7, 1794},
		{6, 12, 0, 0, 7, 1806},
		{6, 11, 0, 0, 7, 1818},
		{4, 12, 0, 0, 5, 1829},
		{4, 12, 0, 0, 5, 1841},
		{6, 12, 1, 0, 5, 1853},
		{5, 11, 1, 0, 5, 1865},
		{6, 11, 0, 0, 7, 1876},
		{6, 12, 0, 0, 7, 1887},
		{6, 12, 0, 0, 7, 1899},
		{6, 12, 0, 0, 7, 1911},
		{6, 12, 0, 0, 7, 1923},
		{6, 12, 0, 0, 7, 1935},
		{6, 11, 0, 0, 7, 1947},
		{6, 8, 0, 0, 7, 1958},
		{6, 10, 0, 1, 7, 1966},
		{6, 12, 0, 0, 7, 1976},
		{6, 12, 0, 0, 7, 1988},
		{6, 12, 0, 0, 7, 2000},
		{6, 11, 0, 0, 7, 2012},
		{6, 15, 0, 3, 7, 2023},
		{6, 14, 0, 3, 7, 2038},
		{6, 14, 0, 3, 7, 2052},
	},
	bitmap_data
};

#endif

