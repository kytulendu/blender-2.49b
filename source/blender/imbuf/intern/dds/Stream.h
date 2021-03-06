/**
 * $Id: Stream.h 19485 2009-03-31 22:34:34Z gsrb3d $
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

/* simple memory stream functions with buffer overflow check */

#ifndef _STREAM_H
#define _STREAM_H

struct Stream
{
	unsigned char *mem; // location in memory
	unsigned int size;  // size
	unsigned int pos;   // current position
	Stream(unsigned char *m, unsigned int s) : mem(m), size(s), pos(0) {};
	unsigned int seek(unsigned int p);
};

unsigned int mem_read(Stream & mem, unsigned long long & i);
unsigned int mem_read(Stream & mem, unsigned int & i);
unsigned int mem_read(Stream & mem, unsigned short & i);
unsigned int mem_read(Stream & mem, unsigned char & i);
unsigned int mem_read(Stream & mem, unsigned char *i, unsigned int cnt);

#endif // _STREAM_H

