/**
 * Sense if other objects are near
 *
 * $Id: KX_NearSensor.cpp 22082 2009-07-31 09:05:13Z campbellbarton $
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

#include "KX_NearSensor.h"
#include "SCA_LogicManager.h"
#include "KX_GameObject.h"
#include "KX_TouchEventManager.h"
#include "KX_Scene.h" // needed to create a replica
#include "PHY_IPhysicsEnvironment.h"
#include "PHY_IPhysicsController.h"
#include "PHY_IMotionState.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
KX_NearSensor::KX_NearSensor(SCA_EventManager* eventmgr,
							 KX_GameObject* gameobj,
							 float margin,
							 float resetmargin,
							 bool bFindMaterial,
							 const STR_String& touchedpropname,
 							 PHY_IPhysicsController*	ctrl,
							 PyTypeObject* T)
			 :KX_TouchSensor(eventmgr,
							 gameobj,
							 bFindMaterial,
							 false,
							 touchedpropname,
							 T),
			 m_Margin(margin),
			 m_ResetMargin(resetmargin)

{

	gameobj->getClientInfo()->m_sensors.remove(this);
	m_client_info = new KX_ClientObjectInfo(gameobj, KX_ClientObjectInfo::SENSOR);
	m_client_info->m_sensors.push_back(this);
	
	//DT_ShapeHandle shape = (DT_ShapeHandle) vshape;
	m_physCtrl = ctrl;
	if (m_physCtrl)
	{
		m_physCtrl->SetMargin(m_Margin);
		m_physCtrl->setNewClientInfo(m_client_info);
	}
	SynchronizeTransform();
}

void KX_NearSensor::SynchronizeTransform()
{
	// The near and radar sensors are using a different physical object which is 
	// not linked to the parent object, must synchronize it.
	if (m_physCtrl)
	{
		PHY_IMotionState* motionState = m_physCtrl->GetMotionState();
		KX_GameObject* parent = ((KX_GameObject*)GetParent());
		const MT_Point3& pos = parent->NodeGetWorldPosition();
		float ori[12];
		parent->NodeGetWorldOrientation().getValue(ori);
		motionState->setWorldPosition(pos[0], pos[1], pos[2]);
		motionState->setWorldOrientation(ori);
		m_physCtrl->WriteMotionStateToDynamics(true);
	}
}

CValue* KX_NearSensor::GetReplica()
{
	KX_NearSensor* replica = new KX_NearSensor(*this);
	replica->ProcessReplica();
	return replica;
}

void KX_NearSensor::ProcessReplica()
{
	KX_TouchSensor::ProcessReplica();
	
	m_client_info = new KX_ClientObjectInfo(m_client_info->m_gameobject, KX_ClientObjectInfo::SENSOR);
	
	if (m_physCtrl)
	{
		m_physCtrl = m_physCtrl->GetReplica();
		if (m_physCtrl)
		{
			//static_cast<KX_TouchEventManager*>(m_eventmgr)->GetPhysicsEnvironment()->addSensor(replica->m_physCtrl);
			m_physCtrl->SetMargin(m_Margin);
			m_physCtrl->setNewClientInfo(m_client_info);
		}
		
	}
}

void KX_NearSensor::ReParent(SCA_IObject* parent)
{
	SCA_ISensor::ReParent(parent);
	m_client_info->m_gameobject = static_cast<KX_GameObject*>(parent); 
	m_client_info->m_sensors.push_back(this);
	//Synchronize here with the actual parent.
	SynchronizeTransform();
}



KX_NearSensor::~KX_NearSensor()
{
	// for nearsensor, the sensor is the 'owner' of sumoobj
	// for touchsensor, it's the parent
	if (m_physCtrl)
	{
		//static_cast<KX_TouchEventManager*>(m_eventmgr)->GetPhysicsEnvironment()->removeSensor(m_physCtrl);
		delete m_physCtrl;
		m_physCtrl = NULL;
	}
	
		
	if (m_client_info)
		delete m_client_info;
}


bool KX_NearSensor::Evaluate()
{
	bool result = false;
//	KX_GameObject* parent = static_cast<KX_GameObject*>(GetParent());

	if (m_bTriggered != m_bLastTriggered)
	{
		m_bLastTriggered = m_bTriggered;
		if (m_bTriggered)
		{
			if (m_physCtrl)
			{
				m_physCtrl->SetRadius(m_ResetMargin);
			}
		} else
		{
			if (m_physCtrl)
			{
				m_physCtrl->SetRadius(m_Margin);
			}

		}
		result = true;
	}

	return result;
}

// this function is called at broad phase stage to check if the two controller
// need to interact at all. It is used for Near/Radar sensor that don't need to
// check collision with object not included in filter
bool	KX_NearSensor::BroadPhaseFilterCollision(void*obj1,void*obj2)
{
	KX_GameObject* parent = static_cast<KX_GameObject*>(GetParent());
	
	// need the mapping from PHY_IPhysicsController to gameobjects now
	assert(obj1==m_physCtrl && obj2);
	KX_ClientObjectInfo* client_info = static_cast<KX_ClientObjectInfo*>((static_cast<PHY_IPhysicsController*>(obj2))->getNewClientInfo());

	KX_GameObject* gameobj = ( client_info ? 
			client_info->m_gameobject :
			NULL);
	
	if (gameobj && (gameobj != parent))
	{
		// only take valid colliders
		if (client_info->m_type == KX_ClientObjectInfo::ACTOR)
		{
			if ((m_touchedpropname.Length() == 0) || 
				(gameobj->GetProperty(m_touchedpropname)))
			{
				return true;
			}
		}
	}

	return false;
}

bool	KX_NearSensor::NewHandleCollision(void* obj1,void* obj2,const PHY_CollData * coll_data)
{
//	KX_TouchEventManager* toucheventmgr = static_cast<KX_TouchEventManager*>(m_eventmgr);
//	KX_GameObject* parent = static_cast<KX_GameObject*>(GetParent());
	
	// need the mapping from PHY_IPhysicsController to gameobjects now
	
	KX_ClientObjectInfo* client_info =static_cast<KX_ClientObjectInfo*> (obj1 == m_physCtrl? 
					((PHY_IPhysicsController*)obj2)->getNewClientInfo() : 
					((PHY_IPhysicsController*)obj1)->getNewClientInfo());

	KX_GameObject* gameobj = ( client_info ? 
			client_info->m_gameobject :
			NULL);
	
	// Add the same check as in SCA_ISensor::Activate(), 
	// we don't want to record collision when the sensor is not active.
	if (m_links && !m_suspended &&
		gameobj /* done in BroadPhaseFilterCollision() && (gameobj != parent)*/)
	{
		if (!m_colliders->SearchValue(gameobj))
			m_colliders->Add(gameobj->AddRef());
		// only take valid colliders
		// These checks are done already in BroadPhaseFilterCollision()
		//if (client_info->m_type == KX_ClientObjectInfo::ACTOR)
		//{
		//	if ((m_touchedpropname.Length() == 0) || 
		//		(gameobj->GetProperty(m_touchedpropname)))
		//	{
				m_bTriggered = true;
				m_hitObject = gameobj;
		//	}
		//}
	}
	
	return false; // was DT_CONTINUE; but this was defined in Sumo as false
}


/* ------------------------------------------------------------------------- */
/* Python Functions															 */
/* ------------------------------------------------------------------------- */

//No methods

/* ------------------------------------------------------------------------- */
/* Python Integration Hooks                                                  */
/* ------------------------------------------------------------------------- */

PyTypeObject KX_NearSensor::Type = {
#if (PY_VERSION_HEX >= 0x02060000)
	PyVarObject_HEAD_INIT(NULL, 0)
#else
	/* python 2.5 and below */
	PyObject_HEAD_INIT( NULL )  /* required py macro */
	0,                          /* ob_size */
#endif
	"KX_NearSensor",
	sizeof(PyObjectPlus_Proxy),
	0,
	py_base_dealloc,
	0,
	0,
	0,
	0,
	py_base_repr,
	0,0,0,0,0,0,
	py_base_getattro,
	py_base_setattro,
	0,0,0,0,0,0,0,0,0,
	Methods
};



PyParentObject KX_NearSensor::Parents[] = {
	&KX_NearSensor::Type,
	&KX_TouchSensor::Type,
	&SCA_ISensor::Type,
	&SCA_ILogicBrick::Type,
	&CValue::Type,
	NULL
};



PyMethodDef KX_NearSensor::Methods[] = {
	//No methods
	{NULL,NULL} //Sentinel
};

PyAttributeDef KX_NearSensor::Attributes[] = {
	KX_PYATTRIBUTE_FLOAT_RW_CHECK("distance", 0, 100, KX_NearSensor, m_Margin, CheckResetDistance),
	KX_PYATTRIBUTE_FLOAT_RW_CHECK("resetDistance", 0, 100, KX_NearSensor, m_ResetMargin, CheckResetDistance),
	{NULL} //Sentinel
};


PyObject* KX_NearSensor::py_getattro(PyObject *attr)
{
	py_getattro_up(KX_TouchSensor);
}

PyObject* KX_NearSensor::py_getattro_dict() {
	py_getattro_dict_up(KX_TouchSensor);
}

int KX_NearSensor::py_setattro(PyObject*attr, PyObject* value)
{
	py_setattro_up(KX_TouchSensor);
}
