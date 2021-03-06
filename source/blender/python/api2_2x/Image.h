/* 
 * $Id: Image.h 14444 2008-04-16 22:40:48Z hos $
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
 * Contributor(s): Willian P. Germano, Alex Mole
 *
 * ***** END GPL LICENSE BLOCK *****
*/

#ifndef EXPP_IMAGE_H
#define EXPP_IMAGE_H

#include <Python.h>
#include "DNA_image_types.h"


/*****************************************************************************/
/* Python BPy_Image structure definition                                     */
/*****************************************************************************/
typedef struct {
	PyObject_HEAD 
	Image * image; /* libdata must be second */

} BPy_Image;

extern PyTypeObject Image_Type;	/* The Image PyType Object */

#define BPy_Image_Check(v)  ((v)->ob_type == &Image_Type)	/*for type checking */

/*****************************************************************************/
/* Module Blender.Image - public functions                                   */
/*****************************************************************************/
PyObject *Image_Init( void );
PyObject *Image_CreatePyObject( Image * image );
Image *Image_FromPyObject( PyObject * pyobj );

#endif				/* EXPP_IMAGE_H */
