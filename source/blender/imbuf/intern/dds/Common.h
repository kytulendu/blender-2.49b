/**
 * $Id: Common.h 19485 2009-03-31 22:34:34Z gsrb3d $
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
 * Contributors: Amorilia (amorilia@gamebox.net)
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#ifndef _DDS_COMMON_H
#define _DDS_COMMON_H

#ifndef MIN
#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#endif
#ifndef CLAMP
#define CLAMP(x,a,b) MIN(MAX((x), (a)), (b))
#endif

template<typename T>
inline void
swap(T & a, T & b)
{
  T tmp = a;
  a = b;
  b = tmp;
}

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

#endif
