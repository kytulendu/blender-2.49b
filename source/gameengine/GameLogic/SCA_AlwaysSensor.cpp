/**
 * Always trigger
 *
 * $Id: SCA_AlwaysSensor.cpp 20130 2009-05-10 20:53:58Z ben2610 $
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef WIN32
// This warning tells us about truncation of __long__ stl-generated names.
// It can occasionally cause DevStudio to have internal compiler warnings.
#pragma warning( disable : 4786 )     
#endif

#include "SCA_AlwaysSensor.h"
#include "SCA_LogicManager.h"
#include "SCA_EventManager.h"

/* ------------------------------------------------------------------------- */
/* Native functions                                                          */
/* ------------------------------------------------------------------------- */

SCA_AlwaysSensor::SCA_AlwaysSensor(class SCA_EventManager* eventmgr,
								 SCA_IObject* gameobj,
								 PyTypeObject* T)
	: SCA_ISensor(gameobj,eventmgr, T)
{
	//SetDrawColor(255,0,0);
	Init();
}

void SCA_AlwaysSensor::Init()
{
	m_alwaysresult = true;
}

SCA_AlwaysSensor::~SCA_AlwaysSensor()
{
	/* intentionally empty */
}



CValue* SCA_AlwaysSensor::GetReplica()
{
	CValue* replica = new SCA_AlwaysSensor(*this);//m_float,GetName());
	// this will copy properties and so on...
	replica->ProcessReplica();

	return replica;
}



bool SCA_AlwaysSensor::IsPositiveTrigger()
{ 
	return (m_invert ? false : true);
}



bool SCA_AlwaysSensor::Evaluate()
{
	/* Nice! :) */
		//return true;
	/* even nicer ;) */
		//return false;
	
	/* nicest ! */
	bool result = m_alwaysresult;
	m_alwaysresult = false;
	return result;
}

/* ------------------------------------------------------------------------- */
/* Python functions                                                          */
/* ------------------------------------------------------------------------- */

/* Integration hooks ------------------------------------------------------- */
PyTypeObject SCA_AlwaysSensor::Type = {
#if (PY_VERSION_HEX >= 0x02060000)
	PyVarObject_HEAD_INIT(NULL, 0)
#else
	/* python 2.5 and below */
	PyObject_HEAD_INIT( NULL )  /* required py macro */
	0,                          /* ob_size */
#endif
	"SCA_AlwaysSensor",
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

PyParentObject SCA_AlwaysSensor::Parents[] = {
	&SCA_AlwaysSensor::Type,
	&SCA_ISensor::Type,
	&SCA_ILogicBrick::Type,
	&CValue::Type,
	NULL
};

PyMethodDef SCA_AlwaysSensor::Methods[] = {
	{NULL,NULL} //Sentinel
};

PyAttributeDef SCA_AlwaysSensor::Attributes[] = {
	{ NULL }	//Sentinel
};

PyObject* SCA_AlwaysSensor::py_getattro(PyObject *attr) {
	py_getattro_up(SCA_ISensor);
}

PyObject* SCA_AlwaysSensor::py_getattro_dict() {
	py_getattro_dict_up(SCA_ISensor);
}

/* eof */
