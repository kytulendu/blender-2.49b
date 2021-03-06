/**
 * @file KX_IPhysicsController.cpp
 * $Id: KX_IPhysicsController.cpp 20239 2009-05-17 12:51:51Z ben2610 $
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
#include "KX_IPhysicsController.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "PHY_DynamicTypes.h"

KX_IPhysicsController::KX_IPhysicsController(bool dyna, bool sensor, bool compound, void* userdata)

:	m_bDyna(dyna),
	m_bSensor(sensor),
	m_bCompound(compound),
	m_suspendDynamics(false),
	m_userdata(userdata)
{
}

KX_IPhysicsController::~KX_IPhysicsController()
{
}


