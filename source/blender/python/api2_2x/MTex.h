/* 
 * $Id: MTex.h 16427 2008-09-08 23:39:32Z khughes $
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
 * Contributor(s): Alex Mole
 *
 * ***** END GPL LICENSE BLOCK *****
*/

#ifndef EXPP_MTEX_H
#define EXPP_MTEX_H

#include <Python.h>
#include "DNA_texture_types.h"


/*****************************************************************************/
/* Python BPy_MTex structure definition                                      */
/*****************************************************************************/

#define	MATERIAL_MTEX_TYPE	1
#define	WORLD_MTEX_TYPE	2
#define	LAMP_MTEX_TYPE	3

typedef struct {
	PyObject_HEAD
	MTex * mtex;
	unsigned short type;
} BPy_MTex;

extern PyTypeObject MTex_Type;

#define BPy_MTex_Check(v)  ((v)->ob_type == &MTex_Type)

/*****************************************************************************/
/* Module Blender.Texture.MTex - public functions                            */
/*****************************************************************************/

PyObject *MTex_Init( void );
PyObject *MTex_CreatePyObject( struct MTex *obj, unsigned short type );
MTex *MTex_FromPyObject( PyObject * py_obj );


#endif				/* EXPP_MTEX_H */
