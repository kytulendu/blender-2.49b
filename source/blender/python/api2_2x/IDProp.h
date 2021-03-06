/**
 * $Id: IDProp.h
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
 * Contributor(s): Joseph Eagar
 *
 * ***** END GPL LICENSE BLOCK *****
 */
 
#include <Python.h>

struct ID;
struct IDProperty;
struct BPy_IDGroup_Iter;

typedef struct BPy_IDProperty {
	PyObject_VAR_HEAD
	struct ID *id;
	struct IDProperty *prop, *parent;
	PyObject *data_wrap;
} BPy_IDProperty;

typedef struct BPy_IDArray {
	PyObject_VAR_HEAD
	struct ID *id;
	struct IDProperty *prop;
} BPy_IDArray;

typedef struct BPy_IDGroup_Iter {
	PyObject_VAR_HEAD
	BPy_IDProperty *group;
	struct IDProperty *cur;
	int mode;
} BPy_IDGroup_Iter;

PyObject *BPy_Wrap_IDProperty(struct ID *id, struct IDProperty *prop, struct IDProperty *parent);
void IDProp_Init_Types(void);

#define IDPROP_ITER_KEYS	0
#define IDPROP_ITER_ITEMS	1
