/**
 * $Id: BMF_font_helvb14.cpp 14444 2008-04-16 22:40:48Z hos $
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

#if BMF_INCLUDE_HELVB14

static unsigned char bitmap_data[]= {
	0x00,0xc0,0xc0,0x00,0x00,0x80,0x80,0x80,
	0xc0,0xc0,0xc0,0xc0,0xc0,0x90,0xd8,0xd8,
	0xd8,0x48,0x48,0x48,0xfe,0xfe,0x24,0x24,
	0x7f,0x7f,0x12,0x12,0x12,0x10,0x10,0x38,
	0x7c,0xd6,0xd6,0x16,0x3c,0x78,0xd0,0xd6,
	0xd6,0x7c,0x38,0x10,0x30,0xc0,0x11,0xe0,
	0x19,0x20,0x09,0x20,0x0d,0xe0,0x64,0xc0,
	0xf6,0x00,0x92,0x00,0x93,0x00,0xf1,0x00,
	0x61,0x80,0x71,0x80,0xff,0x00,0xce,0x00,
	0xc6,0x00,0xcf,0x00,0x79,0x00,0x30,0x00,
	0x38,0x00,0x6c,0x00,0x6c,0x00,0x7c,0x00,
	0x38,0x00,0x80,0x40,0xc0,0xc0,0x30,0x20,
	0x60,0x40,0x40,0xc0,0xc0,0xc0,0xc0,0xc0,
	0x40,0x40,0x60,0x20,0x30,0xc0,0x40,0x60,
	0x20,0x20,0x30,0x30,0x30,0x30,0x30,0x20,
	0x20,0x60,0x40,0xc0,0xd8,0x50,0x20,0xf8,
	0x20,0x20,0x30,0x30,0x30,0xfc,0xfc,0x30,
	0x30,0x30,0x80,0x40,0x40,0xc0,0xc0,0xfe,
	0xfe,0xc0,0xc0,0x80,0x80,0xc0,0x40,0x40,
	0x60,0x20,0x20,0x30,0x10,0x10,0x30,0x78,
	0x48,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0x48,
	0x78,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0xf0,0x30,0x10,0xfc,0xfc,
	0x60,0x60,0x30,0x18,0x18,0x0c,0xcc,0xcc,
	0x78,0x30,0x30,0x78,0xcc,0xcc,0x0c,0x38,
	0x38,0x0c,0xcc,0xcc,0x78,0x30,0x18,0x18,
	0xfc,0xfc,0x98,0x58,0x58,0x38,0x38,0x38,
	0x18,0x18,0x70,0xf8,0xcc,0x0c,0x0c,0xcc,
	0xfc,0xd8,0x60,0x60,0x7c,0x7c,0x30,0x78,
	0xcc,0xcc,0xcc,0xcc,0xfc,0xd8,0xc0,0x4c,
	0x7c,0x38,0x60,0x60,0x60,0x20,0x30,0x30,
	0x10,0x18,0x08,0x0c,0xfc,0xfc,0x70,0xf8,
	0xcc,0xcc,0xcc,0x78,0x30,0x78,0xcc,0xcc,
	0x7c,0x38,0x70,0xf8,0xc8,0x0c,0x6c,0xfc,
	0xcc,0xcc,0xcc,0xcc,0x78,0x30,0xc0,0xc0,
	0x00,0x00,0x00,0x00,0xc0,0xc0,0x80,0x40,
	0x40,0xc0,0xc0,0x00,0x00,0x00,0x00,0xc0,
	0xc0,0x02,0x0e,0x3c,0xf0,0xf0,0x3c,0x0e,
	0x02,0xfc,0xfc,0x00,0x00,0xfc,0xfc,0x80,
	0xe0,0x78,0x1e,0x1e,0x78,0xe0,0x80,0x30,
	0x30,0x00,0x30,0x30,0x18,0x18,0x0c,0xcc,
	0xcc,0x7c,0x38,0x0f,0x80,0x38,0x60,0x60,
	0x00,0x4d,0xc0,0xd3,0x20,0x93,0x30,0x91,
	0x10,0x91,0x90,0xc9,0x90,0x46,0x90,0x60,
	0x30,0x30,0x20,0x1c,0xc0,0x07,0x80,0xe1,
	0xc0,0x61,0x80,0x7f,0x80,0x7f,0x80,0x33,
	0x00,0x33,0x00,0x33,0x00,0x1e,0x00,0x1e,
	0x00,0x1e,0x00,0x0c,0x00,0x0c,0x00,0xfc,
	0xfe,0xc7,0xc3,0xc7,0xfe,0xfc,0xc6,0xc3,
	0xc7,0xfe,0xfc,0x3c,0x7e,0x63,0xc3,0xc0,
	0xc0,0xc0,0xc0,0xc3,0x63,0x7e,0x3c,0xfc,
	0xfe,0xc6,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,
	0xc6,0xfe,0xfc,0xfe,0xfe,0xc0,0xc0,0xc0,
	0xfe,0xfe,0xc0,0xc0,0xc0,0xfe,0xfe,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xfc,0xfc,0xc0,0xc0,
	0xc0,0xfe,0xfe,0x3e,0x80,0x7f,0x80,0x63,
	0x80,0xc1,0x80,0xc7,0x80,0xc7,0x80,0xc0,
	0x00,0xc0,0x00,0xc1,0x80,0x63,0x80,0x7f,
	0x00,0x3e,0x00,0xc3,0xc3,0xc3,0xc3,0xc3,
	0xff,0xff,0xc3,0xc3,0xc3,0xc3,0xc3,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0x78,0xfc,0xcc,0xcc,0xcc,
	0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0xc3,
	0x80,0xc7,0x00,0xc6,0x00,0xcc,0x00,0xdc,
	0x00,0xf8,0x00,0xf0,0x00,0xd8,0x00,0xcc,
	0x00,0xce,0x00,0xc7,0x00,0xc3,0x00,0xfe,
	0xfe,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xcc,0xc0,0xcc,0xc0,0xcc,
	0xc0,0xde,0xc0,0xde,0xc0,0xd2,0xc0,0xd2,
	0xc0,0xf3,0xc0,0xf3,0xc0,0xe1,0xc0,0xe1,
	0xc0,0xe1,0xc0,0xc3,0xc7,0xc7,0xcf,0xcf,
	0xdb,0xdb,0xf3,0xf3,0xe3,0xe3,0xc3,0x3e,
	0x00,0x7f,0x00,0x63,0x00,0xc1,0x80,0xc1,
	0x80,0xc1,0x80,0xc1,0x80,0xc1,0x80,0xc1,
	0x80,0x63,0x00,0x7f,0x00,0x3e,0x00,0xc0,
	0xc0,0xc0,0xc0,0xf8,0xfc,0xce,0xc6,0xc6,
	0xce,0xfc,0xf8,0x01,0x80,0x3d,0x80,0x7f,
	0x00,0x67,0x00,0xcd,0x80,0xcd,0x80,0xc1,
	0x80,0xc1,0x80,0xc1,0x80,0xc1,0x80,0x63,
	0x00,0x7f,0x00,0x3e,0x00,0xc3,0xc3,0xc3,
	0xc3,0xc7,0xfe,0xfe,0xc7,0xc3,0xc7,0xfe,
	0xfc,0x3c,0x7e,0xe7,0xc3,0x07,0x1e,0x78,
	0xe0,0xc3,0xe7,0x7e,0x3c,0x18,0x18,0x18,
	0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xff,
	0xff,0x3c,0x7e,0xe7,0xc3,0xc3,0xc3,0xc3,
	0xc3,0xc3,0xc3,0xc3,0xc3,0x18,0x18,0x18,
	0x3c,0x3c,0x24,0x66,0x66,0x66,0xc3,0xc3,
	0xc3,0x30,0xc0,0x30,0xc0,0x30,0xc0,0x39,
	0xc0,0x79,0xe0,0x69,0x60,0x6f,0x60,0x6f,
	0x60,0xc6,0x30,0xc6,0x30,0xc6,0x30,0xc6,
	0x30,0xe3,0x80,0x63,0x00,0x63,0x00,0x36,
	0x00,0x36,0x00,0x1c,0x00,0x1c,0x00,0x36,
	0x00,0x36,0x00,0x63,0x00,0x63,0x00,0xe3,
	0x80,0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,
	0x00,0x0c,0x00,0x1e,0x00,0x1e,0x00,0x33,
	0x00,0x33,0x00,0x61,0x80,0x61,0x80,0xe1,
	0xc0,0xff,0xff,0x60,0x70,0x30,0x18,0x18,
	0x0c,0x0e,0x06,0xff,0xff,0xe0,0xe0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xe0,0xe0,0x10,0x10,0x30,0x20,
	0x20,0x60,0x40,0x40,0xc0,0x80,0x80,0xe0,
	0xe0,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0xe0,0xe0,0xcc,0xcc,
	0x48,0x78,0x78,0x30,0x30,0xfe,0xc0,0xc0,
	0x80,0x40,0x6c,0xfc,0xcc,0xcc,0x7c,0x1c,
	0xcc,0xfc,0x78,0xd8,0xfc,0xee,0xc6,0xc6,
	0xc6,0xee,0xfc,0xd8,0xc0,0xc0,0xc0,0x38,
	0x7c,0xec,0xc0,0xc0,0xc0,0xec,0x7c,0x38,
	0x36,0x7e,0xee,0xc6,0xc6,0xc6,0xee,0x7e,
	0x36,0x06,0x06,0x06,0x38,0x7c,0xcc,0xc0,
	0xfc,0xcc,0xcc,0x78,0x30,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0xf0,0xf0,0x60,0x70,
	0x30,0x78,0xfc,0xc6,0x36,0x7e,0xee,0xc6,
	0xc6,0xc6,0xee,0x7e,0x36,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0xe6,0xfe,0xdc,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0x00,0xc0,0xc0,0xc0,0xe0,0x60,
	0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x00,0x60,0x60,0xce,0xcc,0xd8,0xd8,
	0xf0,0xf0,0xd8,0xd8,0xcc,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xcc,0xc0,0xcc,0xc0,
	0xcc,0xc0,0xcc,0xc0,0xcc,0xc0,0xcc,0xc0,
	0xcc,0xc0,0xff,0xc0,0xdb,0x80,0xc6,0xc6,
	0xc6,0xc6,0xc6,0xc6,0xe6,0xfe,0xdc,0x38,
	0x7c,0xee,0xc6,0xc6,0xc6,0xee,0x7c,0x38,
	0xc0,0xc0,0xc0,0xd8,0xfc,0xee,0xc6,0xc6,
	0xc6,0xee,0xfc,0xd8,0x06,0x06,0x06,0x36,
	0x7e,0xee,0xc6,0xc6,0xc6,0xee,0x7e,0x36,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xe0,0xf8,
	0xd0,0x78,0xfc,0xcc,0x1c,0x78,0xe0,0xcc,
	0xfc,0x78,0x30,0x70,0x60,0x60,0x60,0x60,
	0x60,0xf0,0xf0,0x60,0x60,0x76,0xfe,0xce,
	0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x30,0x30,
	0x30,0x78,0x78,0x48,0xcc,0xcc,0xcc,0x33,
	0x00,0x33,0x00,0x33,0x00,0x73,0x80,0x7f,
	0x80,0x4c,0x80,0x4c,0x80,0xcc,0xc0,0xcc,
	0xc0,0xc6,0xee,0x6c,0x38,0x38,0x38,0x6c,
	0xee,0xc6,0x60,0x70,0x10,0x18,0x38,0x38,
	0x2c,0x6c,0x6c,0xc6,0xc6,0xc6,0xfc,0xfc,
	0x60,0x60,0x30,0x18,0x18,0xfc,0xfc,0x30,
	0x70,0x60,0x60,0x60,0x60,0x60,0xc0,0x60,
	0x60,0x60,0x60,0x60,0x70,0x30,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0xc0,0xe0,0x60,
	0x60,0x60,0x60,0x60,0x30,0x60,0x60,0x60,
	0x60,0x60,0xe0,0xc0,0x98,0xfc,0x64,0xc0,
	0xc0,0xc0,0xc0,0xc0,0x80,0x80,0x80,0x00,
	0x00,0xc0,0xc0,0x20,0x20,0x38,0x7c,0xec,
	0xe0,0xd0,0xd0,0xdc,0x7c,0x38,0x08,0x08,
	0xcc,0xfe,0x70,0x30,0x30,0xf8,0x60,0xc0,
	0xcc,0xcc,0x7c,0x38,0xcc,0x78,0xcc,0xcc,
	0xcc,0xcc,0x78,0xcc,0x18,0x18,0x18,0x7e,
	0x18,0x7e,0x18,0x3c,0x24,0x66,0x42,0xc3,
	0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x38,
	0x7c,0x6c,0x0c,0x18,0x7c,0xe6,0xc6,0xce,
	0x7c,0x30,0x60,0x6c,0x7c,0x38,0xd8,0xd8,
	0x1e,0x00,0x33,0x00,0x40,0x80,0xde,0xc0,
	0xb3,0x40,0xa0,0x40,0xa0,0x40,0xb3,0x40,
	0xde,0xc0,0x40,0x80,0x33,0x00,0x1e,0x00,
	0xf0,0x00,0xd0,0xb0,0x70,0xb0,0x60,0x24,
	0x6c,0xd8,0xd8,0x6c,0x24,0x06,0x06,0x06,
	0xfe,0xfe,0xe0,0xe0,0x1e,0x00,0x33,0x00,
	0x40,0x80,0xd2,0xc0,0x96,0x40,0x9c,0x40,
	0x92,0x40,0x92,0x40,0xdc,0xc0,0x40,0x80,
	0x33,0x00,0x1e,0x00,0xf0,0x60,0x90,0x90,
	0x90,0x60,0xfc,0xfc,0x00,0x30,0x30,0x30,
	0xfc,0xfc,0x30,0x30,0x30,0xf0,0x80,0x40,
	0x20,0x90,0xb0,0x60,0x60,0xb0,0x10,0x60,
	0x30,0x90,0x60,0xc0,0x60,0xc0,0xc0,0xc0,
	0xf6,0xfe,0xce,0xc6,0xc6,0xc6,0xc6,0xc6,
	0xc6,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x74,0xf4,0xf4,0xf4,0xf4,0x74,0x3e,
	0xc0,0xc0,0xc0,0x60,0x40,0x20,0x20,0x20,
	0x20,0x20,0xe0,0x20,0xf0,0x00,0x60,0x90,
	0x90,0x90,0x60,0x90,0xd8,0x6c,0x6c,0xd8,
	0x90,0x20,0x40,0x10,0x40,0x13,0xe0,0x0a,
	0x40,0x09,0x40,0x24,0xc0,0x24,0x40,0x22,
	0x00,0x22,0x00,0x21,0x00,0xe1,0x00,0x20,
	0x80,0x21,0xe0,0x11,0x00,0x10,0x80,0x08,
	0x40,0x09,0x20,0x25,0x60,0x24,0xc0,0x22,
	0x00,0x22,0x00,0x21,0x00,0xe1,0x00,0x20,
	0x80,0x20,0x40,0x10,0x40,0x13,0xe0,0x0a,
	0x40,0x09,0x40,0x64,0xc0,0xb4,0x40,0x12,
	0x00,0x62,0x00,0x31,0x00,0x91,0x00,0x60,
	0x80,0x70,0xf8,0xcc,0xcc,0xc0,0x60,0x60,
	0x30,0x30,0x00,0x30,0x30,0xe1,0xc0,0x61,
	0x80,0x7f,0x80,0x3f,0x00,0x33,0x00,0x33,
	0x00,0x12,0x00,0x1e,0x00,0x1e,0x00,0x0c,
	0x00,0x0c,0x00,0x00,0x00,0x0c,0x00,0x18,
	0x00,0xe1,0xc0,0x61,0x80,0x7f,0x80,0x3f,
	0x00,0x33,0x00,0x33,0x00,0x12,0x00,0x1e,
	0x00,0x1e,0x00,0x0c,0x00,0x0c,0x00,0x00,
	0x00,0x0c,0x00,0x06,0x00,0xe1,0xc0,0x61,
	0x80,0x7f,0x80,0x3f,0x00,0x33,0x00,0x33,
	0x00,0x12,0x00,0x1e,0x00,0x1e,0x00,0x0c,
	0x00,0x0c,0x00,0x00,0x00,0x36,0x00,0x1c,
	0x00,0xe1,0xc0,0x61,0x80,0x7f,0x80,0x3f,
	0x00,0x33,0x00,0x33,0x00,0x12,0x00,0x1e,
	0x00,0x1e,0x00,0x0c,0x00,0x0c,0x00,0x00,
	0x00,0x16,0x00,0x0d,0x00,0xe1,0xc0,0x61,
	0x80,0x7f,0x80,0x3f,0x00,0x33,0x00,0x33,
	0x00,0x12,0x00,0x1e,0x00,0x1e,0x00,0x0c,
	0x00,0x0c,0x00,0x00,0x00,0x36,0x00,0x36,
	0x00,0xe1,0xc0,0x61,0x80,0x7f,0x80,0x3f,
	0x00,0x33,0x00,0x33,0x00,0x12,0x00,0x1e,
	0x00,0x1e,0x00,0x0c,0x00,0x0c,0x00,0x0c,
	0x00,0x0a,0x00,0x06,0x00,0xe3,0xf8,0x63,
	0xf8,0x7f,0x00,0x7f,0x00,0x33,0x00,0x33,
	0xf8,0x3b,0xf8,0x1b,0x00,0x1b,0x00,0x1f,
	0x00,0x0f,0xf8,0x0f,0xf8,0x18,0x0c,0x08,
	0x3c,0x7e,0x63,0xc3,0xc0,0xc0,0xc0,0xc0,
	0xc3,0x63,0x7e,0x3c,0xfe,0xfe,0xc0,0xc0,
	0xc0,0xfe,0xfe,0xc0,0xc0,0xfe,0xfe,0x00,
	0x18,0x30,0xfe,0xfe,0xc0,0xc0,0xc0,0xfe,
	0xfe,0xc0,0xc0,0xfe,0xfe,0x00,0x18,0x0c,
	0xfe,0xfe,0xc0,0xc0,0xc0,0xfe,0xfe,0xc0,
	0xc0,0xfe,0xfe,0x00,0x6c,0x38,0xfe,0xfe,
	0xc0,0xc0,0xc0,0xfe,0xfe,0xc0,0xc0,0xfe,
	0xfe,0x00,0x6c,0x6c,0x60,0x60,0x60,0x60,
	0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x00,
	0x60,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0x00,0xc0,0x60,
	0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x00,0xd8,0x70,0x30,0x30,
	0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x30,0x00,0xd8,0xd8,0x7e,0x00,0x7f,0x00,
	0x63,0x00,0x61,0x80,0x61,0x80,0xf9,0x80,
	0xf9,0x80,0x61,0x80,0x61,0x80,0x63,0x00,
	0x7f,0x00,0x7e,0x00,0xc3,0xc7,0xc7,0xcf,
	0xcb,0xdb,0xd3,0xf3,0xe3,0xe3,0xc3,0x00,
	0x2c,0x1a,0x3e,0x00,0x7f,0x00,0x63,0x00,
	0xc1,0x80,0xc1,0x80,0xc1,0x80,0xc1,0x80,
	0xc1,0x80,0x63,0x00,0x7f,0x00,0x3e,0x00,
	0x00,0x00,0x0c,0x00,0x18,0x00,0x3e,0x00,
	0x7f,0x00,0x63,0x00,0xc1,0x80,0xc1,0x80,
	0xc1,0x80,0xc1,0x80,0xc1,0x80,0x63,0x00,
	0x7f,0x00,0x3e,0x00,0x00,0x00,0x18,0x00,
	0x0c,0x00,0x3e,0x00,0x7f,0x00,0x63,0x00,
	0xc1,0x80,0xc1,0x80,0xc1,0x80,0xc1,0x80,
	0xc1,0x80,0x63,0x00,0x7f,0x00,0x3e,0x00,
	0x00,0x00,0x36,0x00,0x1c,0x00,0x3e,0x00,
	0x7f,0x00,0x63,0x00,0xc1,0x80,0xc1,0x80,
	0xc1,0x80,0xc1,0x80,0xc1,0x80,0x63,0x00,
	0x7f,0x00,0x3e,0x00,0x00,0x00,0x2c,0x00,
	0x1a,0x00,0x3e,0x00,0x7f,0x00,0x63,0x00,
	0xc1,0x80,0xc1,0x80,0xc1,0x80,0xc1,0x80,
	0xc1,0x80,0x63,0x00,0x7f,0x00,0x3e,0x00,
	0x00,0x00,0x36,0x00,0x36,0x00,0x84,0xcc,
	0x78,0x30,0x30,0x78,0xcc,0x84,0xbe,0x00,
	0xff,0x00,0x63,0x00,0xf1,0x80,0xd1,0x80,
	0xc9,0x80,0xc9,0x80,0xc5,0x80,0xc7,0x80,
	0x63,0x00,0x7f,0x80,0x3e,0x80,0x3c,0x7e,
	0xe7,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,
	0xc3,0x00,0x18,0x30,0x3c,0x7e,0xe7,0xc3,
	0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0x00,
	0x18,0x0c,0x3c,0x7e,0xe7,0xc3,0xc3,0xc3,
	0xc3,0xc3,0xc3,0xc3,0xc3,0x00,0x6c,0x38,
	0x3c,0x7e,0xe7,0xc3,0xc3,0xc3,0xc3,0xc3,
	0xc3,0xc3,0xc3,0x00,0x6c,0x6c,0x0c,0x00,
	0x0c,0x00,0x0c,0x00,0x0c,0x00,0x0c,0x00,
	0x1e,0x00,0x1e,0x00,0x33,0x00,0x33,0x00,
	0x61,0x80,0xe1,0xc0,0x00,0x00,0x0c,0x00,
	0x06,0x00,0xc0,0xc0,0xf8,0xfc,0xce,0xc6,
	0xc6,0xce,0xfc,0xf8,0xc0,0xc0,0xd8,0xdc,
	0xc6,0xc6,0xc6,0xdc,0xd8,0xcc,0xcc,0xcc,
	0x7c,0x38,0x6c,0xfc,0xcc,0xcc,0x7c,0x1c,
	0xcc,0xfc,0x78,0x00,0x30,0x60,0x6c,0xfc,
	0xcc,0xcc,0x7c,0x1c,0xcc,0xfc,0x78,0x00,
	0x30,0x18,0x6c,0xfc,0xcc,0xcc,0x7c,0x1c,
	0xcc,0xfc,0x78,0x00,0xd8,0x70,0x6c,0xfc,
	0xcc,0xcc,0x7c,0x1c,0xcc,0xfc,0x78,0x00,
	0x58,0x34,0x6c,0xfc,0xcc,0xcc,0x7c,0x1c,
	0xcc,0xfc,0x78,0x00,0xd8,0xd8,0x6c,0xfc,
	0xcc,0xcc,0x7c,0x1c,0xcc,0xfc,0x78,0x00,
	0x30,0x28,0x18,0x73,0x80,0xff,0xc0,0xcc,
	0xc0,0xcc,0x00,0x7f,0xc0,0x1c,0xc0,0xcc,
	0xc0,0xff,0xc0,0x73,0x80,0x30,0x18,0x10,
	0x38,0x7c,0xec,0xc0,0xc0,0xc0,0xec,0x7c,
	0x38,0x38,0x7c,0xcc,0xc0,0xfc,0xcc,0xcc,
	0x78,0x30,0x00,0x30,0x60,0x38,0x7c,0xcc,
	0xc0,0xfc,0xcc,0xcc,0x78,0x30,0x00,0x30,
	0x18,0x38,0x7c,0xcc,0xc0,0xfc,0xcc,0xcc,
	0x78,0x30,0x00,0x6c,0x38,0x38,0x7c,0xcc,
	0xc0,0xfc,0xcc,0xcc,0x78,0x30,0x00,0xd8,
	0xd8,0x60,0x60,0x60,0x60,0x60,0x60,0x60,
	0x60,0x60,0x00,0x60,0xc0,0xc0,0xc0,0xc0,
	0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0x00,0xc0,
	0x60,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x30,0x30,0x00,0xd8,0x70,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30,0x30,0x30,0x00,0xd8,
	0xd8,0x38,0x7c,0xee,0xc6,0xc6,0xc6,0xee,
	0x7c,0x3c,0xf8,0x38,0x6c,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0xe6,0xfe,0xdc,0x00,0x58,
	0x34,0x38,0x7c,0xee,0xc6,0xc6,0xc6,0xee,
	0x7c,0x38,0x00,0x18,0x30,0x38,0x7c,0xee,
	0xc6,0xc6,0xc6,0xee,0x7c,0x38,0x00,0x30,
	0x18,0x38,0x7c,0xee,0xc6,0xc6,0xc6,0xee,
	0x7c,0x38,0x00,0x6c,0x38,0x38,0x7c,0xee,
	0xc6,0xc6,0xc6,0xee,0x7c,0x38,0x00,0x58,
	0x34,0x38,0x7c,0xee,0xc6,0xc6,0xc6,0xee,
	0x7c,0x38,0x00,0x6c,0x6c,0x30,0x30,0x00,
	0xfc,0xfc,0x00,0x30,0x30,0xb8,0x7c,0xee,
	0xe6,0xd6,0xce,0xee,0x7c,0x3a,0x76,0xfe,
	0xce,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x00,
	0x18,0x30,0x76,0xfe,0xce,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0x00,0x30,0x18,0x76,0xfe,
	0xce,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x00,
	0x6c,0x38,0x76,0xfe,0xce,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0x00,0x6c,0x6c,0x60,0x70,
	0x10,0x18,0x38,0x38,0x2c,0x6c,0x6c,0xc6,
	0xc6,0xc6,0x00,0x30,0x18,0xc0,0xc0,0xc0,
	0xd8,0xfc,0xee,0xc6,0xc6,0xc6,0xee,0xfc,
	0xd8,0xc0,0xc0,0xc0,0x60,0x70,0x10,0x18,
	0x38,0x38,0x2c,0x6c,0x6c,0xc6,0xc6,0xc6,
	0x00,0x6c,0x6c,
};

BMF_FontData BMF_font_helvb14 = {
	-2, -3,
	12, 14,
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
		{2, 12, -1, 0, 4, 1},
		{5, 4, 0, -8, 6, 13},
		{8, 12, 1, 0, 7, 17},
		{7, 15, 0, 2, 7, 29},
		{11, 11, 0, 0, 12, 44},
		{9, 12, 0, 0, 9, 66},
		{2, 4, -1, -8, 4, 90},
		{4, 15, 0, 3, 4, 94},
		{4, 15, 1, 3, 4, 109},
		{5, 6, 0, -6, 5, 124},
		{6, 8, -1, 0, 8, 130},
		{2, 5, 0, 3, 3, 138},
		{7, 2, 0, -3, 8, 143},
		{2, 2, 0, 0, 3, 145},
		{4, 11, 0, 0, 4, 147},
		{6, 12, 0, 0, 7, 158},
		{4, 12, 0, 0, 7, 170},
		{6, 12, 0, 0, 7, 182},
		{6, 12, 0, 0, 7, 194},
		{6, 12, 0, 0, 7, 206},
		{6, 12, 0, 0, 7, 218},
		{6, 12, 0, 0, 7, 230},
		{6, 12, 0, 0, 7, 242},
		{6, 12, 0, 0, 7, 254},
		{6, 12, 0, 0, 7, 266},
		{2, 8, -1, 0, 4, 278},
		{2, 11, -1, 3, 4, 286},
		{7, 8, 0, 0, 8, 297},
		{6, 6, -1, -1, 8, 305},
		{7, 8, 0, 0, 8, 311},
		{6, 12, -1, 0, 8, 319},
		{12, 14, 0, 2, 13, 331},
		{10, 12, 1, 0, 9, 359},
		{8, 12, 0, 0, 9, 383},
		{8, 12, 0, 0, 9, 395},
		{8, 12, 0, 0, 9, 407},
		{7, 12, 0, 0, 8, 419},
		{7, 12, -1, 0, 8, 431},
		{9, 12, 0, 0, 10, 443},
		{8, 12, 0, 0, 9, 467},
		{2, 12, -1, 0, 5, 479},
		{6, 12, 0, 0, 7, 491},
		{9, 12, -1, 0, 10, 503},
		{7, 12, -1, 0, 8, 527},
		{10, 12, 0, 0, 11, 539},
		{8, 12, 0, 0, 9, 563},
		{9, 12, 0, 0, 10, 575},
		{7, 12, -1, 0, 9, 599},
		{9, 13, 0, 1, 10, 611},
		{8, 12, 0, 0, 9, 637},
		{8, 12, 0, 0, 9, 649},
		{8, 12, 0, 0, 9, 661},
		{8, 12, 0, 0, 9, 673},
		{8, 12, 0, 0, 9, 685},
		{12, 12, 0, 0, 13, 697},
		{9, 12, 0, 0, 10, 721},
		{10, 12, 1, 0, 9, 745},
		{8, 12, 0, 0, 9, 769},
		{3, 15, 0, 3, 4, 781},
		{4, 11, 0, 0, 4, 796},
		{3, 15, 0, 3, 4, 807},
		{6, 7, -1, -4, 8, 822},
		{7, 1, 0, 3, 7, 829},
		{2, 4, -1, -8, 4, 830},
		{6, 9, 0, 0, 7, 834},
		{7, 12, 0, 0, 8, 843},
		{6, 9, 0, 0, 7, 855},
		{7, 12, 0, 0, 8, 864},
		{6, 9, 0, 0, 7, 876},
		{4, 12, 0, 0, 5, 885},
		{7, 12, 0, 3, 8, 897},
		{7, 12, 0, 0, 8, 909},
		{2, 12, 0, 0, 3, 921},
		{3, 15, 1, 3, 3, 933},
		{7, 12, 0, 0, 7, 948},
		{2, 12, 0, 0, 3, 960},
		{10, 9, 0, 0, 11, 972},
		{7, 9, 0, 0, 8, 990},
		{7, 9, 0, 0, 8, 999},
		{7, 12, 0, 3, 8, 1008},
		{7, 12, 0, 3, 8, 1020},
		{5, 9, 0, 0, 5, 1032},
		{6, 9, 0, 0, 7, 1041},
		{4, 11, 0, 0, 5, 1050},
		{7, 9, 0, 0, 8, 1061},
		{6, 9, 0, 0, 7, 1070},
		{10, 9, 0, 0, 11, 1079},
		{7, 9, 0, 0, 8, 1097},
		{7, 12, 0, 3, 8, 1106},
		{6, 9, 0, 0, 7, 1118},
		{4, 15, 0, 3, 5, 1127},
		{1, 15, -1, 3, 4, 1142},
		{4, 15, 0, 3, 5, 1157},
		{6, 3, -1, -3, 8, 1172},
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
		{2, 12, -1, 3, 4, 1175},
		{6, 13, 0, 2, 7, 1187},
		{7, 12, 0, 0, 7, 1200},
		{6, 8, 0, -2, 7, 1212},
		{8, 12, 1, 0, 7, 1220},
		{1, 15, -1, 3, 4, 1232},
		{7, 15, 0, 3, 7, 1247},
		{5, 2, 1, -10, 4, 1262},
		{10, 12, 0, 0, 10, 1264},
		{4, 7, 0, -5, 5, 1288},
		{6, 6, 0, -1, 7, 1295},
		{7, 5, 0, -2, 8, 1301},
		{3, 2, 0, -3, 4, 1306},
		{10, 12, 0, 0, 10, 1308},
		{4, 1, 0, -11, 4, 1332},
		{4, 5, 0, -7, 5, 1333},
		{6, 11, -1, 0, 8, 1338},
		{4, 7, 0, -5, 4, 1349},
		{4, 7, 0, -5, 4, 1356},
		{3, 2, -1, -10, 4, 1363},
		{7, 12, 0, 3, 8, 1365},
		{7, 15, 0, 3, 7, 1377},
		{2, 2, 0, -5, 3, 1392},
		{3, 3, 0, 3, 4, 1394},
		{3, 7, 0, -5, 4, 1397},
		{4, 7, 0, -5, 5, 1404},
		{6, 6, 0, -1, 7, 1411},
		{11, 12, 1, 0, 11, 1417},
		{11, 12, 1, 0, 11, 1441},
		{11, 12, 0, 0, 11, 1465},
		{6, 12, -1, 3, 8, 1489},
		{10, 14, 1, 0, 9, 1501},
		{10, 14, 1, 0, 9, 1529},
		{10, 14, 1, 0, 9, 1557},
		{10, 14, 1, 0, 9, 1585},
		{10, 14, 1, 0, 9, 1613},
		{10, 14, 1, 0, 9, 1641},
		{13, 12, 1, 0, 13, 1669},
		{8, 15, 0, 3, 9, 1693},
		{7, 14, 0, 0, 8, 1708},
		{7, 14, 0, 0, 8, 1722},
		{7, 14, 0, 0, 8, 1736},
		{7, 14, 0, 0, 8, 1750},
		{3, 14, 0, 0, 5, 1764},
		{3, 14, -1, 0, 5, 1778},
		{5, 14, 1, 0, 5, 1792},
		{5, 14, 1, 0, 5, 1806},
		{9, 12, 1, 0, 9, 1820},
		{8, 14, 0, 0, 9, 1844},
		{9, 14, 0, 0, 10, 1858},
		{9, 14, 0, 0, 10, 1886},
		{9, 14, 0, 0, 10, 1914},
		{9, 14, 0, 0, 10, 1942},
		{9, 14, 0, 0, 10, 1970},
		{6, 8, -1, 0, 8, 1998},
		{9, 12, 0, 0, 10, 2006},
		{8, 14, 0, 0, 9, 2030},
		{8, 14, 0, 0, 9, 2044},
		{8, 14, 0, 0, 9, 2058},
		{8, 14, 0, 0, 9, 2072},
		{10, 14, 1, 0, 9, 2086},
		{7, 12, -1, 0, 9, 2114},
		{7, 12, 0, 0, 8, 2126},
		{6, 12, 0, 0, 7, 2138},
		{6, 12, 0, 0, 7, 2150},
		{6, 12, 0, 0, 7, 2162},
		{6, 12, 0, 0, 7, 2174},
		{6, 12, 0, 0, 7, 2186},
		{6, 13, 0, 0, 7, 2198},
		{10, 9, 0, 0, 11, 2211},
		{6, 12, 0, 3, 7, 2229},
		{6, 12, 0, 0, 7, 2241},
		{6, 12, 0, 0, 7, 2253},
		{6, 12, 0, 0, 7, 2265},
		{6, 12, 0, 0, 7, 2277},
		{3, 12, 1, 0, 3, 2289},
		{3, 12, 0, 0, 3, 2301},
		{5, 12, 2, 0, 3, 2313},
		{5, 12, 2, 0, 3, 2325},
		{7, 12, 0, 0, 8, 2337},
		{7, 12, 0, 0, 8, 2349},
		{7, 12, 0, 0, 8, 2361},
		{7, 12, 0, 0, 8, 2373},
		{7, 12, 0, 0, 8, 2385},
		{7, 12, 0, 0, 8, 2397},
		{7, 12, 0, 0, 8, 2409},
		{6, 8, -1, 0, 8, 2421},
		{7, 9, 0, 0, 8, 2429},
		{7, 12, 0, 0, 8, 2438},
		{7, 12, 0, 0, 8, 2450},
		{7, 12, 0, 0, 8, 2462},
		{7, 12, 0, 0, 8, 2474},
		{7, 15, 0, 3, 8, 2486},
		{7, 15, 0, 3, 8, 2501},
		{7, 15, 0, 3, 8, 2516},
	},
	bitmap_data
};

#endif

