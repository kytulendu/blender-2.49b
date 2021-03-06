/**
 * $Id: SCA_IController.cpp 20471 2009-05-28 07:11:12Z campbellbarton $
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

#include "SCA_IController.h"
#include "SCA_LogicManager.h"
#include "SCA_IActuator.h"
#include "SCA_ISensor.h"
#include "PyObjectPlus.h"
#include "../Ketsji/KX_PythonSeq.h" /* not nice, only need for KX_PythonSeq_CreatePyObject */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

SCA_IController::SCA_IController(SCA_IObject* gameobj,
								 PyTypeObject* T)
	:
	SCA_ILogicBrick(gameobj,T),
	m_statemask(0),
	m_justActivated(false)
{
}
	

	
SCA_IController::~SCA_IController()
{
	//UnlinkAllActuators();
}



std::vector<class SCA_ISensor*>& SCA_IController::GetLinkedSensors()
{
	return m_linkedsensors;
}



std::vector<class SCA_IActuator*>& SCA_IController::GetLinkedActuators()
{
	return m_linkedactuators;
}



void SCA_IController::UnlinkAllSensors()
{
	std::vector<class SCA_ISensor*>::iterator sensit;
	for (sensit = m_linkedsensors.begin();!(sensit==m_linkedsensors.end());++sensit)
	{
		if (IsActive()) 
		{
			(*sensit)->DecLink();
		}
		(*sensit)->UnlinkController(this);
	}
	m_linkedsensors.clear();
}



void SCA_IController::UnlinkAllActuators()
{
	std::vector<class SCA_IActuator*>::iterator actit;
	for (actit = m_linkedactuators.begin();!(actit==m_linkedactuators.end());++actit)
	{
		if (IsActive()) 
		{
			(*actit)->DecLink();
		}
		(*actit)->UnlinkController(this);
	}
	m_linkedactuators.clear();
}

void SCA_IController::LinkToActuator(SCA_IActuator* actua)
{
	m_linkedactuators.push_back(actua);
	if (IsActive())
	{
		actua->IncLink();
	}
}

void	SCA_IController::UnlinkActuator(class SCA_IActuator* actua)
{
	std::vector<class SCA_IActuator*>::iterator actit;
	for (actit = m_linkedactuators.begin();!(actit==m_linkedactuators.end());++actit)
	{
		if ((*actit) == actua)
		{
			if (IsActive())
			{
				(*actit)->DecLink();
			}
			*actit = m_linkedactuators.back();
			m_linkedactuators.pop_back();
			return;
		}
	}
	printf("Missing link from controller %s:%s to actuator %s:%s\n", 
		m_gameobj->GetName().ReadPtr(), GetName().ReadPtr(), 
		actua->GetParent()->GetName().ReadPtr(), actua->GetName().ReadPtr());
}

void SCA_IController::LinkToSensor(SCA_ISensor* sensor)
{
	m_linkedsensors.push_back(sensor);
	if (IsActive())
	{
		sensor->IncLink();
	}
}

void SCA_IController::UnlinkSensor(class SCA_ISensor* sensor)
{
	std::vector<class SCA_ISensor*>::iterator sensit;
	for (sensit = m_linkedsensors.begin();!(sensit==m_linkedsensors.end());++sensit)
	{
		if ((*sensit) == sensor)
		{
			if (IsActive())
			{
				sensor->DecLink();
			}
			*sensit = m_linkedsensors.back();
			m_linkedsensors.pop_back();
			return;
		}
	}
	printf("Missing link from controller %s:%s to sensor %s:%s\n", 
		m_gameobj->GetName().ReadPtr(), GetName().ReadPtr(), 
		sensor->GetParent()->GetName().ReadPtr(), sensor->GetName().ReadPtr());
}


void SCA_IController::ApplyState(unsigned int state)
{
	std::vector<class SCA_IActuator*>::iterator actit;
	std::vector<class SCA_ISensor*>::iterator sensit;

	if (m_statemask & state) 
	{
		if (!IsActive()) 
		{
			// reactive the controller, all the links to actuator are valid again
			for (actit = m_linkedactuators.begin();!(actit==m_linkedactuators.end());++actit)
			{
				(*actit)->IncLink();
			}

			for (sensit = m_linkedsensors.begin();!(sensit==m_linkedsensors.end());++sensit)
			{
				(*sensit)->IncLink();
			}
			SetActive(true);
			m_justActivated = true;
		}
	} else if (IsActive())
	{
		for (actit = m_linkedactuators.begin();!(actit==m_linkedactuators.end());++actit)
		{
			(*actit)->DecLink();
		}
		for (sensit = m_linkedsensors.begin();!(sensit==m_linkedsensors.end());++sensit)
		{
			(*sensit)->DecLink();
		}
		SetActive(false);
		m_justActivated = false;
	}
}

/* Python api */

PyTypeObject SCA_IController::Type = {
#if (PY_VERSION_HEX >= 0x02060000)
	PyVarObject_HEAD_INIT(NULL, 0)
#else
	/* python 2.5 and below */
	PyObject_HEAD_INIT( NULL )  /* required py macro */
	0,                          /* ob_size */
#endif
		"SCA_IController",
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

PyParentObject SCA_IController::Parents[] = {
	&SCA_IController::Type,
	&CValue::Type,
	NULL
};

PyMethodDef SCA_IController::Methods[] = {
	//Deprecated functions ------>
	{"getSensor", (PyCFunction) SCA_IController::sPyGetSensor, METH_O},
	{"getActuator", (PyCFunction) SCA_IController::sPyGetActuator, METH_O},
	{"getSensors", (PyCFunction) SCA_IController::sPyGetSensors, METH_NOARGS},
	{"getActuators", (PyCFunction) SCA_IController::sPyGetActuators, METH_NOARGS},
	{"getState", (PyCFunction) SCA_IController::sPyGetState, METH_NOARGS},
	//<----- Deprecated
	{NULL,NULL} //Sentinel
};

PyAttributeDef SCA_IController::Attributes[] = {
	KX_PYATTRIBUTE_RO_FUNCTION("state", SCA_IController, pyattr_get_state),
	KX_PYATTRIBUTE_RO_FUNCTION("sensors", SCA_IController, pyattr_get_sensors),
	KX_PYATTRIBUTE_RO_FUNCTION("actuators", SCA_IController, pyattr_get_actuators),
	KX_PYATTRIBUTE_BOOL_RW("useHighPriority",SCA_IController,m_bookmark),
	{ NULL }	//Sentinel
};

PyObject* SCA_IController::py_getattro(PyObject *attr)
{
	py_getattro_up(SCA_ILogicBrick);
}

PyObject* SCA_IController::py_getattro_dict() {
	py_getattro_dict_up(SCA_ILogicBrick);
}

int SCA_IController::py_setattro(PyObject *attr, PyObject *value)
{
	py_setattro_up(SCA_ILogicBrick);
}



PyObject* SCA_IController::PyGetActuators()
{
	ShowDeprecationWarning("getActuators()", "the actuators property");
	
	PyObject* resultlist = PyList_New(m_linkedactuators.size());
	for (unsigned int index=0;index<m_linkedactuators.size();index++)
	{
		PyList_SET_ITEM(resultlist,index, m_linkedactuators[index]->GetProxy());
	}

	return resultlist;
}

PyObject* SCA_IController::PyGetSensor(PyObject* value)
{
	ShowDeprecationWarning("getSensor(string)", "the sensors[string] property");
	
	char *scriptArg = PyString_AsString(value);
	if (scriptArg==NULL) {
		PyErr_SetString(PyExc_TypeError, "controller.getSensor(string): Python Controller, expected a string (sensor name)");
		return NULL;
	}
	
	for (unsigned int index=0;index<m_linkedsensors.size();index++)
	{
		SCA_ISensor* sensor = m_linkedsensors[index];
		STR_String& realname = sensor->GetName();
		if (realname == scriptArg)
		{
			return sensor->GetProxy();
		}
	}
	
	PyErr_Format(PyExc_AttributeError, "controller.getSensor(string): Python Controller, unable to find requested sensor \"%s\"", scriptArg);
	return NULL;
}

PyObject* SCA_IController::PyGetActuator(PyObject* value)
{
	ShowDeprecationWarning("getActuator(string)", "the actuators[string] property");
	
	char *scriptArg = PyString_AsString(value);
	if (scriptArg==NULL) {
		PyErr_SetString(PyExc_TypeError, "controller.getActuator(string): Python Controller, expected a string (actuator name)");
		return NULL;
	}
	
	for (unsigned int index=0;index<m_linkedactuators.size();index++)
	{
		SCA_IActuator* actua = m_linkedactuators[index];
		if (actua->GetName() == scriptArg)
		{
			return actua->GetProxy();
		}
	}
	
	PyErr_Format(PyExc_AttributeError, "controller.getActuator(string): Python Controller, unable to find requested actuator \"%s\"", scriptArg);
	return NULL;
}

PyObject* SCA_IController::PyGetSensors()
{
	ShowDeprecationWarning("getSensors()", "the sensors property");
	
	PyObject* resultlist = PyList_New(m_linkedsensors.size());
	for (unsigned int index=0;index<m_linkedsensors.size();index++)
	{
		PyList_SET_ITEM(resultlist,index, m_linkedsensors[index]->GetProxy());
	}
	
	return resultlist;
}

PyObject* SCA_IController::PyGetState()
{
	ShowDeprecationWarning("getState()", "the state property");
	return PyInt_FromLong(m_statemask);
}

PyObject* SCA_IController::pyattr_get_state(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef)
{
	SCA_IController* self= static_cast<SCA_IController*>(self_v);
	return PyInt_FromLong(self->m_statemask);
}

PyObject* SCA_IController::pyattr_get_sensors(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef)
{
	return KX_PythonSeq_CreatePyObject((static_cast<SCA_IController*>(self_v))->m_proxy, KX_PYGENSEQ_CONT_TYPE_SENSORS);	
}

PyObject* SCA_IController::pyattr_get_actuators(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef)
{
	return KX_PythonSeq_CreatePyObject((static_cast<SCA_IController*>(self_v))->m_proxy, KX_PYGENSEQ_CONT_TYPE_ACTUATORS);	
}
