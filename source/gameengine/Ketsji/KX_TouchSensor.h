/**
 * Senses touch and collision events
 *
 * $Id: KX_TouchSensor.h 22701 2009-08-22 10:51:21Z campbellbarton $
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

#ifndef __KX_TOUCHSENSOR
#define __KX_TOUCHSENSOR

#include "SCA_ISensor.h"
#include "ListValue.h"

struct PHY_CollData;

#include "KX_ClientObjectInfo.h"

#if defined(_WIN64)
typedef unsigned __int64 uint_ptr;
#else
typedef unsigned long uint_ptr;
#endif

class KX_TouchEventManager;

class KX_TouchSensor : public SCA_ISensor
{
protected:
	Py_Header;

	/**
	 * The sensor should only look for objects with this property.
	 */
	STR_String				m_touchedpropname;	
	bool					m_bFindMaterial;
	bool					m_bTouchPulse;		/* changes in the colliding objects trigger pulses */
	
	class PHY_IPhysicsController*	m_physCtrl;

	bool					m_bCollision;
	bool					m_bTriggered;
	bool					m_bLastTriggered;

	// Use with m_bTouchPulse to detect changes
	int						m_bLastCount;		/* size of m_colliders last tick */
	uint_ptr				m_bColliderHash;	/* hash collision objects pointers to trigger incase one object collides and another takes its place */
	uint_ptr				m_bLastColliderHash;

	SCA_IObject*		    m_hitObject;
	class CListValue*		m_colliders;
	
public:
	KX_TouchSensor(class SCA_EventManager* eventmgr,
		class KX_GameObject* gameobj,
		bool bFindMaterial,
		bool bTouchPulse,
		const STR_String& touchedpropname,
		PyTypeObject* T=&Type) ;
	virtual ~KX_TouchSensor();

	virtual CValue* GetReplica();
	virtual void ProcessReplica();
	virtual void SynchronizeTransform();
	virtual bool Evaluate();
	virtual void Init();
	virtual void ReParent(SCA_IObject* parent);
	
	virtual void RegisterSumo(KX_TouchEventManager* touchman);
	virtual void UnregisterSumo(KX_TouchEventManager* touchman);
	virtual void UnregisterToManager();

//	virtual DT_Bool HandleCollision(void* obj1,void* obj2,
//						 const DT_CollData * coll_data); 

	virtual bool	NewHandleCollision(void*obj1,void*obj2,const PHY_CollData* colldata);

	// Allows to do pre-filtering and save computation time
	// obj1 = sensor physical controller, obj2 = physical controller of second object
	// return value = true if collision should be checked on pair of object
	virtual bool	BroadPhaseFilterCollision(void*obj1,void*obj2) { return true; }
	virtual bool	BroadPhaseSensorFilterCollision(void*obj1,void*obj2);
	virtual sensortype GetSensorType() { return ST_TOUCH; }
  

	virtual bool IsPositiveTrigger() {
		bool result = m_bTriggered;
		if (m_invert) result = !result;
		return result;
	}

	
	virtual void EndFrame();

	// todo: put some info for collision maybe

	/* --------------------------------------------------------------------- */
	/* Python interface ---------------------------------------------------- */
	/* --------------------------------------------------------------------- */
	
	virtual PyObject* py_getattro(PyObject *attr);
	virtual PyObject* py_getattro_dict();
	virtual int py_setattro(PyObject *attr, PyObject *value);

	//Deprecated ----->
	/* 1. setProperty */
	KX_PYMETHOD_DOC_O(KX_TouchSensor,SetProperty);
	/* 2. getProperty */
	KX_PYMETHOD_DOC_NOARGS(KX_TouchSensor,GetProperty);
	/* 3. getHitObject */
	KX_PYMETHOD_DOC_NOARGS(KX_TouchSensor,GetHitObject);
	/* 4. getHitObject */
	KX_PYMETHOD_DOC_NOARGS(KX_TouchSensor,GetHitObjectList);
	/* 5. getTouchMaterial */
	KX_PYMETHOD_DOC_NOARGS(KX_TouchSensor,GetTouchMaterial);
#if 0
	/* 6. setTouchMaterial */
	KX_PYMETHOD_DOC_O(KX_TouchSensor,SetTouchMaterial);
#endif
	//<-----
	
	static PyObject*	pyattr_get_object_hit(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_object_hit_list(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	
	
};

#endif //__KX_TOUCHSENSOR

