/**
 * @mainpage SG_ParentRelation   

 * @section 
 * 
 * This is an abstract interface class to the Scene Graph library. 
 * It allows you to specify how child nodes react to parent nodes.
 * Normally a child will use it's parent's transforms to compute
 * it's own global transforms. How this is performed depends on
 * the type of relation. For example if the parent is a vertex 
 * parent to this child then the child should not inherit any 
 * rotation information from the parent. Or if the parent is a
 * 'slow parent' to this child then the child should react 
 * slowly to changes in the parent's position. The exact relation
 * is left for you to implement by filling out this interface 
 * with concrete examples. 
 * 
 * There is exactly one SG_ParentRelation per SG_Node. Subclasses
 * should not be value types and should be allocated on the heap.
 *
 * $Id: SG_ParentRelation.h 19592 2009-04-07 22:14:06Z ben2610 $
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
 * 
 */

#ifndef __SG_ParentRelation_h
#define __SG_ParentRelation_h

class SG_Spatial;

class SG_ParentRelation {

public :

	/**
	 * Update the childs local and global coordinates
	 * based upon the parents global coordinates. 
	 * You must also handle the case when this node has no
	 * parent (parent == NULL). Usually you should just 
	 * copy the local coordinates of the child to the 
	 * world coordinates.
	 */ 
	
	virtual
		bool
	UpdateChildCoordinates(
		SG_Spatial * child,
		const SG_Spatial * parent,
		bool& parentUpdated
	) = 0;

	virtual 
	~SG_ParentRelation(
	){
	};

	/** 
	 * You must provide a way of duplicating an
	 * instance of an SG_ParentRelation. This should
	 * return a pointer to a new duplicate allocated
	 * on the heap. Responsibilty for deleting the 
	 * duplicate resides with the caller of this method.
	 */

	virtual 
		SG_ParentRelation *
	NewCopy(
	) = 0;

	/**
	 * Vertex Parent Relation are special: they don't propagate rotation
	 */
	virtual
		bool
	IsVertexRelation(
	) { 
		return false;
	}
	
	/**
	 * Need this to see if we are able to adjust time-offset from the python api
	 */
	virtual
		bool
	IsSlowRelation(
	) { 
		return false;
	}
protected :

	/** 
	 * Protected constructors 
	 * this class is not meant to be instantiated.
	 */

	SG_ParentRelation(
	) {	
	};

	/**
	 * Copy construction should not be implemented
	 */

	SG_ParentRelation(
		const SG_ParentRelation &
	); 
};	

#endif

