/**
 * 'Or' together all inputs
 *
 * $Id: SCA_ORController.cpp 20130 2009-05-10 20:53:58Z ben2610 $
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

#include "SCA_ORController.h"
#include "SCA_ISensor.h"
#include "SCA_LogicManager.h"
#include "BoolValue.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* ------------------------------------------------------------------------- */
/* Native functions                                                          */
/* ------------------------------------------------------------------------- */

SCA_ORController::SCA_ORController(SCA_IObject* gameobj,
								   PyTypeObject* T)
		:SCA_IController(gameobj, T)
{
}



SCA_ORController::~SCA_ORController()
{
}



CValue* SCA_ORController::GetReplica()
{
	CValue* replica = new SCA_ORController(*this);
	// this will copy properties and so on...
	replica->ProcessReplica();

	return replica;
}


void SCA_ORController::Trigger(SCA_LogicManager* logicmgr)
{

	bool sensorresult = false;
	SCA_ISensor* sensor;

	vector<SCA_ISensor*>::const_iterator is=m_linkedsensors.begin();
	while ( (!sensorresult) && (!(is==m_linkedsensors.end())) )
	{
		sensor = *is;
		if (sensor->GetState()) sensorresult = true;
		is++;
	}
	
	for (vector<SCA_IActuator*>::const_iterator i=m_linkedactuators.begin();
	!(i==m_linkedactuators.end());i++)
	{
		SCA_IActuator* actua = *i;
		logicmgr->AddActiveActuator(actua,sensorresult);
	}
}

/* ------------------------------------------------------------------------- */
/* Python functions                                                          */
/* ------------------------------------------------------------------------- */

/* Integration hooks ------------------------------------------------------- */
PyTypeObject SCA_ORController::Type = {
#if (PY_VERSION_HEX >= 0x02060000)
	PyVarObject_HEAD_INIT(NULL, 0)
#else
	/* python 2.5 and below */
	PyObject_HEAD_INIT( NULL )  /* required py macro */
	0,                          /* ob_size */
#endif
	"SCA_ORController",
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

PyParentObject SCA_ORController::Parents[] = {
	&SCA_ORController::Type,
	&SCA_IController::Type,
	&SCA_ILogicBrick::Type,
	&CValue::Type,
	NULL
};

PyMethodDef SCA_ORController::Methods[] = {
	{NULL,NULL} //Sentinel
};

PyAttributeDef SCA_ORController::Attributes[] = {
	{ NULL }	//Sentinel
};


PyObject* SCA_ORController::py_getattro(PyObject *attr) {
	py_getattro_up(SCA_IController);
}

PyObject* SCA_ORController::py_getattro_dict() {
	py_getattro_dict_up(SCA_IController);
}

/* eof */
