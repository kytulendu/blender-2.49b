/**
 * $Id: KX_ClientObjectInfo.h 20502 2009-05-29 16:55:22Z ben2610 $
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
#ifndef __KX_CLIENTOBJECT_INFO_H
#define __KX_CLIENTOBJECT_INFO_H

/* Note, the way this works with/without sumo is a bit odd */
#ifdef USE_SUMO_SOLID
#include <SM_Object.h>
#endif //USE_SUMO_SOLID

#include <list>

class SCA_ISensor;
class KX_GameObject;
/**
 * Client Type and Additional Info. This structure can be use instead of a bare void* pointer, for safeness, and additional info for callbacks
 */
struct KX_ClientObjectInfo
#ifdef USE_SUMO_SOLID
  : public SM_ClientObject
#endif
{
	enum clienttype {
		STATIC,
		ACTOR,
		RESERVED1,
		SENSOR,
		OBSENSOR,
		OBACTORSENSOR
	}		m_type;
	KX_GameObject*	m_gameobject;
	void*		m_auxilary_info;
	std::list<SCA_ISensor*>	m_sensors;
public:
	KX_ClientObjectInfo(KX_GameObject *gameobject, clienttype type = STATIC, void *auxilary_info = NULL) :
#ifdef USE_SUMO_SOLID
		SM_ClientObject(),
#endif
		m_type(type),
		m_gameobject(gameobject),
		m_auxilary_info(auxilary_info)
	{}
	
	KX_ClientObjectInfo(const KX_ClientObjectInfo &copy) :
#ifdef USE_SUMO_SOLID		
		  SM_ClientObject(copy),
#endif
		  m_type(copy.m_type),
		  m_gameobject(copy.m_gameobject),
		  m_auxilary_info(copy.m_auxilary_info)
	{
	}
	
	virtual ~KX_ClientObjectInfo() {}
	
	virtual bool hasCollisionCallback() 
	{
		return m_sensors.size() != 0;
	}
	
	bool isActor() { return m_type <= ACTOR; }
	bool isSensor() { return m_type >= SENSOR && m_type <= OBACTORSENSOR; }
};

#endif //__KX_CLIENTOBJECT_INFO_H

