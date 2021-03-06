/**
 * $Id: KX_RayCast.h 16275 2008-08-27 19:34:19Z ben2610 $
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

#ifndef __KX_RAYCAST_H__
#define __KX_RAYCAST_H__

#include "PHY_IPhysicsEnvironment.h"
#include "PHY_IPhysicsController.h"
#include "MT_Point3.h"
#include "MT_Vector3.h"

class RAS_MeshObject; 
struct KX_ClientObjectInfo;
class KX_IPhysicsController;

/**
 *  Defines a function for doing a ray cast.
 *
 *  eg KX_RayCast::RayTest(ignore_physics_controller, physics_environment, frompoint, topoint, result_point, result_normal, KX_RayCast::Callback<KX_MyClass>(this, data)
 *
 *  Calls myclass->RayHit(client, hit_point, hit_normal, data) for all client
 *  between frompoint and topoint
 *
 *  myclass->RayHit should return true to end the raycast, false to ignore the current client.
 *
 *  Returns true if a client was accepted, false if nothing found.
 */
class KX_RayCast : public PHY_IRayCastFilterCallback
{
public:
	bool					m_hitFound;
	MT_Point3				m_hitPoint;
	MT_Vector3				m_hitNormal;
	const RAS_MeshObject*	m_hitMesh;
	int						m_hitPolygon;

	KX_RayCast(KX_IPhysicsController* ignoreController, bool faceNormal);
	virtual ~KX_RayCast() {}

	/**
	 * The physic environment returns the ray casting result through this function
	 */
	virtual void reportHit(PHY_RayCastResult* result);

	/** ray test callback.
	 *  either override this in your class, or use a callback wrapper.
	 */
	virtual bool RayHit(KX_ClientObjectInfo* client) = 0;

	/** 
	 *  Callback wrapper.
	 *
	 *  Construct with KX_RayCast::Callback<MyClass>(this, data)
	 *  and pass to KX_RayCast::RayTest
	 */
	template<class T> class Callback;
	
	/// Public interface.
	/// Implement bool RayHit in your class to receive ray callbacks.
	static bool RayTest(
		PHY_IPhysicsEnvironment* physics_environment, 
		const MT_Point3& frompoint, 
		const MT_Point3& topoint, 
		KX_RayCast& callback);
	
};

template<class T> class KX_RayCast::Callback : public KX_RayCast
{
	T *self;
	void *data;
public:
	Callback(T *_self, KX_IPhysicsController* controller=NULL, void *_data = NULL, bool faceNormal=false)
		: KX_RayCast(controller, faceNormal),
		self(_self),
		data(_data)
	{
	}
	
	~Callback() {}

	virtual bool RayHit(KX_ClientObjectInfo* client)
	{
		return self->RayHit(client, this, data);
	}

	virtual	bool needBroadphaseRayCast(PHY_IPhysicsController* controller)
	{
		KX_ClientObjectInfo* info = static_cast<KX_ClientObjectInfo*>(controller->getNewClientInfo());
		
		if (!info)
		{
			MT_assert(info && "Physics controller with no client object info");
			return false;
		}
		return self->NeedRayCast(info);
	}

};
	

#endif
