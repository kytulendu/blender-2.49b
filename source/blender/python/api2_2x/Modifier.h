/* 
 * $Id: Modifier.h 14444 2008-04-16 22:40:48Z hos $
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
 * This is a new part of Blender.
 *
 * Contributor(s): Ken Hughes
 *
 * ***** END GPL LICENSE BLOCK *****
*/

#ifndef EXPP_MODIFIER_H
#define EXPP_MODIFIER_H

#include <Python.h>
#include "DNA_object_types.h"
#include "DNA_modifier_types.h"
#include "DNA_listBase.h"

/*****************************************************************************/
/* Python BPy_Modifier and BPy_ModSeq structure definition:                  */
/*****************************************************************************/
typedef struct {
	PyObject_HEAD		/* required macro */
	Object *object;
	ModifierData *iter;
} BPy_ModSeq;

typedef struct {
	PyObject_HEAD		/* required macro */
	Object *object;
	/* if md this is null, the modifier has been removed and we need to raise
	an error when its data is accessed */
	ModifierData *md; 
} BPy_Modifier;

extern PyTypeObject ModSeq_Type;
extern PyTypeObject Modifier_Type;
#define BPy_ModSeq_Check(v)  ((v)->ob_type == &ModSeq_Type)
#define BPy_Modifier_Check(v)  ((v)->ob_type == &Modifier_Type)

/* 
 *   prototypes
 */

PyObject *Modifier_Init( void );
PyObject *ModSeq_CreatePyObject( Object *obj, ModifierData *iter );
PyObject *Modifier_CreatePyObject( Object *obj, ModifierData *md );
ModifierData *Modifier_FromPyObject( PyObject * py_obj );

#endif				/* EXPP_MODIFIER_H */
