/**
 * Implementationclass to derive controllers from
 *
 * $Id: SG_Controller.h 15486 2008-07-08 12:18:43Z ben2610 $
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
 */

#ifndef __SG_CONTROLLER_H
#define __SG_CONTROLLER_H

#include "SG_IObject.h"

/**
 * A scenegraph controller
 */
class SG_Controller 
{
public:
	SG_Controller(
	) :
		m_pObject(NULL) {
	}

	virtual 
	~SG_Controller(
	) {};

	virtual 
		bool	
	Update(
		double time
	)=0;

	virtual 
		void 
	SetObject (
		SG_IObject* object
	);

		void
	ClearObject(
	);

	virtual 
		void	
	SetSimulatedTime(
		double time
	)=0;

	virtual	
		SG_Controller*	
	GetReplica(
		class SG_Node* destnode
	)=0;

	/**
	 * Hacky way of passing options to specific controllers
	 * @param option An integer identifying the option.
	 * @param value  The value of this option.
	 * @attention This has been placed here to give sca-elements 
	 * @attention some control over the controllers. This is 
	 * @attention necessary because the identity of the controller
	 * @attention is lost on the way here.
	 */
	virtual
		void
	SetOption(
		int option,
		int value
	)=0;

	/**
	 * Option-identifiers: SG_CONTR_<controller-type>_<option>. 
	 * Options only apply to a specific controller type. The 
	 * semantics are defined by whoever uses the setting.
	 */
	enum SG_Controller_option {
		SG_CONTR_NODEF = 0,
		SG_CONTR_IPO_IPO_AS_FORCE,
		SG_CONTR_IPO_IPO_ADD,
		SG_CONTR_IPO_LOCAL,
		SG_CONTR_IPO_RESET,
		SG_CONTR_CAMIPO_LENS,
		SG_CONTR_CAMIPO_CLIPEND,
		SG_CONTR_CAMIPO_CLIPSTART,
		SG_CONTR_MAX
	};

protected:
	SG_IObject*		m_pObject;

};

#endif //__SG_CONTROLLER_H

