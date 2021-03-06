//
// Adjust dynamics settins for this object
//
// $Id: KX_SCA_DynamicActuator.cpp 20210 2009-05-15 03:26:53Z campbellbarton $
//
// ***** BEGIN GPL LICENSE BLOCK *****
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
// All rights reserved.
//
// The Original Code is: all of this file.
//
// Contributor(s): none yet.
//
// ***** END GPL LICENSE BLOCK *****

//
// Previously existed as:

// \source\gameengine\GameLogic\SCA_DynamicActuator.cpp

// Please look here for revision history.

#include "KX_SCA_DynamicActuator.h"
#include "blendef.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* ------------------------------------------------------------------------- */
/* Python functions                                                          */
/* ------------------------------------------------------------------------- */

/* Integration hooks ------------------------------------------------------- */

	PyTypeObject 

KX_SCA_DynamicActuator::Type = {
#if (PY_VERSION_HEX >= 0x02060000)
	PyVarObject_HEAD_INIT(NULL, 0)
#else
	/* python 2.5 and below */
	PyObject_HEAD_INIT( NULL )  /* required py macro */
	0,                          /* ob_size */
#endif
	"KX_SCA_DynamicActuator",
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

PyParentObject KX_SCA_DynamicActuator::Parents[] = {
	&KX_SCA_DynamicActuator::Type,
	&SCA_IActuator::Type,
	&SCA_ILogicBrick::Type,
	&CValue::Type,
	NULL
};


PyMethodDef KX_SCA_DynamicActuator::Methods[] = {
	// ---> deprecated
	KX_PYMETHODTABLE(KX_SCA_DynamicActuator, setOperation),
   	KX_PYMETHODTABLE(KX_SCA_DynamicActuator, getOperation),
	{NULL,NULL} //Sentinel
};

PyAttributeDef KX_SCA_DynamicActuator::Attributes[] = {
	KX_PYATTRIBUTE_SHORT_RW("mode",0,4,false,KX_SCA_DynamicActuator,m_dyn_operation),
	KX_PYATTRIBUTE_FLOAT_RW("mass",0.0,MAXFLOAT,KX_SCA_DynamicActuator,m_setmass),
	{ NULL }	//Sentinel
};


PyObject* KX_SCA_DynamicActuator::py_getattro(PyObject *attr)
{
	py_getattro_up(SCA_IActuator);
}

PyObject* KX_SCA_DynamicActuator::py_getattro_dict() {
	py_getattro_dict_up(SCA_IActuator);
}

int KX_SCA_DynamicActuator::py_setattro(PyObject *attr, PyObject* value)
{
	py_setattro_up(SCA_IActuator);
}


/* 1. setOperation */
KX_PYMETHODDEF_DOC(KX_SCA_DynamicActuator, setOperation,
"setOperation(operation?)\n"
"\t - operation? : type of dynamic operation\n"
"\t                0 = restore dynamics\n"
"\t                1 = disable dynamics\n"
"\t                2 = enable rigid body\n"
"\t                3 = disable rigid body\n"
"Change the dynamic status of the parent object.\n")
{
	ShowDeprecationWarning("setOperation()", "the mode property");
	int dyn_operation;
	
	if (!PyArg_ParseTuple(args, "i:setOperation", &dyn_operation))
	{
		return NULL;	
	}
	if (dyn_operation <0 || dyn_operation>3) {
		PyErr_SetString(PyExc_IndexError, "Dynamic Actuator's setOperation() range must be between 0 and 3");
		return NULL;
	}
	m_dyn_operation= dyn_operation;
	Py_RETURN_NONE;
}

KX_PYMETHODDEF_DOC(KX_SCA_DynamicActuator, getOperation,
"getOperation() -> integer\n"
"Returns the operation type of this actuator.\n"
)
{
	ShowDeprecationWarning("getOperation()", "the mode property");
	return PyInt_FromLong((long)m_dyn_operation);
}


/* ------------------------------------------------------------------------- */
/* Native functions                                                          */
/* ------------------------------------------------------------------------- */

KX_SCA_DynamicActuator::KX_SCA_DynamicActuator(SCA_IObject *gameobj,
													   short dyn_operation,
													   float setmass,
													   PyTypeObject* T) : 

	SCA_IActuator(gameobj, T),
	m_dyn_operation(dyn_operation),
	m_setmass(setmass)
{
} /* End of constructor */


KX_SCA_DynamicActuator::~KX_SCA_DynamicActuator()
{ 
	// there's nothing to be done here, really....
} /* end of destructor */



bool KX_SCA_DynamicActuator::Update()
{
	// bool result = false;	/*unused*/
	KX_GameObject *obj = (KX_GameObject*) GetParent();
	bool bNegativeEvent = IsNegativeEvent();
	KX_IPhysicsController* controller;
	RemoveAllEvents();

	if (bNegativeEvent)
		return false; // do nothing on negative events
	
	if (!obj)
		return false; // object not accessible, shouldnt happen
	controller = obj->GetPhysicsController();
	if (!controller)
		return false;	// no physic object

	switch (m_dyn_operation)
	{
		case 0:			
			obj->RestoreDynamics();	
			break;
		case 1:
			obj->SuspendDynamics();
			break;
		case 2:
			controller->setRigidBody(true);	
			break;
		case 3:
			controller->setRigidBody(false);
			break;
		case 4:
			controller->SetMass(m_setmass);
			break;
	}

	return false;
}



CValue* KX_SCA_DynamicActuator::GetReplica()
{
	KX_SCA_DynamicActuator* replica = 
		new KX_SCA_DynamicActuator(*this);

	if (replica == NULL)
		return NULL;

	replica->ProcessReplica();
	return replica;
};


/* eof */
