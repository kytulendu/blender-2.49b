/**
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
 * The Original Code is Copyright (C) 2005 Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Mathias Panzenböck (panzi) <grosser.meister.morti@gmx.net>.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include "../TEX_util.h"

static bNodeSocketType outputs[]= { 
	{ SOCK_VECTOR, 0, "Coordinates", 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f },
	{ -1, 0, "" }
};

static void vectorfn(float *out, float *coord, bNode *node, bNodeStack **in, short thread)
{
	out[0] = coord[0];
	out[1] = coord[1];
	out[2] = coord[2];
}

static void exec(void *data, bNode *node, bNodeStack **in, bNodeStack **out)
{
	tex_output(node, in, out[0], &vectorfn);
	
	tex_do_preview(node, out[0], data);
}

bNodeType tex_node_coord= {
	/* *next,*prev */	NULL, NULL,
	/* type code   */	TEX_NODE_COORD,
	/* name        */	"Coordinates",
	/* width+range */	120, 110, 160,
	/* class+opts  */	NODE_CLASS_INPUT, NODE_OPTIONS,
	/* input sock  */	NULL,
	/* output sock */	outputs,
	/* storage     */	"node_coord",
	/* execfunc    */	exec,
	/* butfunc     */	NULL,
	/* initfunc    */	NULL,
	/* freestoragefunc    */	NULL,
	/* copystoragefunc    */	NULL,
	/* id          */	NULL
};

