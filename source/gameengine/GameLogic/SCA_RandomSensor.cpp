/**
 * Generate random pulses
 *
 * $Id: SCA_RandomSensor.cpp 20362 2009-05-23 14:46:43Z ben2610 $
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

#include "SCA_RandomSensor.h"
#include "SCA_EventManager.h"
#include "SCA_RandomEventManager.h"
#include "SCA_LogicManager.h"
#include "ConstExpr.h"
#include <iostream>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* ------------------------------------------------------------------------- */
/* Native functions                                                          */
/* ------------------------------------------------------------------------- */

SCA_RandomSensor::SCA_RandomSensor(SCA_EventManager* eventmgr, 
				 SCA_IObject* gameobj, 
				 int startseed,
  				 PyTypeObject* T)
    : SCA_ISensor(gameobj,eventmgr, T)
{
	m_basegenerator = new SCA_RandomNumberGenerator(startseed);
	Init();
}



SCA_RandomSensor::~SCA_RandomSensor() 
{
	m_basegenerator->Release();
}

void SCA_RandomSensor::Init()
{
    m_iteration  = 0;
	m_interval = 0;
	m_lastdraw   = false;
    m_currentDraw = m_basegenerator->Draw();
}


CValue* SCA_RandomSensor::GetReplica()
{
	CValue* replica = new SCA_RandomSensor(*this);
	// this will copy properties and so on...
	replica->ProcessReplica();

	return replica;
}

void SCA_RandomSensor::ProcessReplica()
{
	SCA_ISensor::ProcessReplica();
	// increment reference count so that we can release the generator at this end
	m_basegenerator->AddRef();
}


bool SCA_RandomSensor::IsPositiveTrigger()
{ 
	return (m_invert !=m_lastdraw);
}


bool SCA_RandomSensor::Evaluate()
{
    /* Random generator is the generator from Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming Vol. 2                   */
    /* (2nd Ed.), pp102]                                                     */
    /* It's a very simple max. length sequence generator. We can             */
    /* draw 32 bool values before having to generate the next                */
    /* sequence value. There are some theorems that will tell you            */
    /* this is a reasonable way of generating bools. Check Knuth.            */
    /* Furthermore, we only draw each <delay>-eth frame.                     */

	bool evaluateResult = false;

	if (++m_interval > m_pulse_frequency) {
	    bool drawResult = false;
		m_interval = 0;
		if (m_iteration > 31) {
			m_currentDraw = m_basegenerator->Draw();
			drawResult = (m_currentDraw & 0x1) == 0;
			m_iteration = 1;
		} else {
			drawResult = ((m_currentDraw >> m_iteration) & 0x1) == 0;
			m_iteration++;
		}
		evaluateResult = drawResult != m_lastdraw;
		m_lastdraw = drawResult;
	}
    
    /* now pass this result to some controller */
	return evaluateResult;
}

/* ------------------------------------------------------------------------- */
/* Python functions                                                          */
/* ------------------------------------------------------------------------- */

/* Integration hooks ------------------------------------------------------- */
PyTypeObject SCA_RandomSensor::Type = {
#if (PY_VERSION_HEX >= 0x02060000)
	PyVarObject_HEAD_INIT(NULL, 0)
#else
	/* python 2.5 and below */
	PyObject_HEAD_INIT( NULL )  /* required py macro */
	0,                          /* ob_size */
#endif
	"SCA_RandomSensor",
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

PyParentObject SCA_RandomSensor::Parents[] = {
	&SCA_RandomSensor::Type,
	&SCA_ISensor::Type,
	&SCA_ILogicBrick::Type,
	&CValue::Type,
	NULL
};

PyMethodDef SCA_RandomSensor::Methods[] = {
	//Deprecated functions ----->
	{"setSeed",     (PyCFunction) SCA_RandomSensor::sPySetSeed, METH_VARARGS, (PY_METHODCHAR)SetSeed_doc},
	{"getSeed",     (PyCFunction) SCA_RandomSensor::sPyGetSeed, METH_NOARGS, (PY_METHODCHAR)GetSeed_doc},
	{"getLastDraw", (PyCFunction) SCA_RandomSensor::sPyGetLastDraw, METH_NOARGS, (PY_METHODCHAR)GetLastDraw_doc},
	//<----- Deprecated
	{NULL,NULL} //Sentinel
};

PyAttributeDef SCA_RandomSensor::Attributes[] = {
	KX_PYATTRIBUTE_BOOL_RO("lastDraw",SCA_RandomSensor,m_lastdraw),
	KX_PYATTRIBUTE_RW_FUNCTION("seed", SCA_RandomSensor, pyattr_get_seed, pyattr_set_seed),
	{NULL} //Sentinel
};

PyObject* SCA_RandomSensor::py_getattro(PyObject *attr) {
	py_getattro_up(SCA_ISensor);
}

PyObject* SCA_RandomSensor::py_getattro_dict() {
	py_getattro_dict_up(SCA_ISensor);
}

int SCA_RandomSensor::py_setattro(PyObject *attr, PyObject *value)
{
	py_setattro_up(SCA_ISensor);
}

/* 1. setSeed                                                            */
const char SCA_RandomSensor::SetSeed_doc[] = 
"setSeed(seed)\n"
"\t- seed: integer\n"
"\tSet the initial seed of the generator. Equal seeds produce\n"
"\tequal series. If the seed is 0, the generator will produce\n"
"\tthe same value on every call.\n";
PyObject* SCA_RandomSensor::PySetSeed(PyObject* args) {
	ShowDeprecationWarning("setSeed()", "the seed property");
	long seedArg;
	if(!PyArg_ParseTuple(args, "i:setSeed", &seedArg)) {
		return NULL;
	}
	
	m_basegenerator->SetSeed(seedArg);
	
	Py_RETURN_NONE;
}

/* 2. getSeed                                                            */
const char SCA_RandomSensor::GetSeed_doc[] = 
"getSeed()\n"
"\tReturns the initial seed of the generator. Equal seeds produce\n"
"\tequal series.\n";
PyObject* SCA_RandomSensor::PyGetSeed() {
	ShowDeprecationWarning("getSeed()", "the seed property");
	return PyInt_FromLong(m_basegenerator->GetSeed());
}

/* 3. getLastDraw                                                            */
const char SCA_RandomSensor::GetLastDraw_doc[] = 
"getLastDraw()\n"
"\tReturn the last value that was drawn.\n";
PyObject* SCA_RandomSensor::PyGetLastDraw() {
	ShowDeprecationWarning("getLastDraw()", "the lastDraw property");
	return PyInt_FromLong(m_lastdraw);
}


PyObject* SCA_RandomSensor::pyattr_get_seed(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef)
{
	SCA_RandomSensor* self= static_cast<SCA_RandomSensor*>(self_v);
	return PyInt_FromLong(self->m_basegenerator->GetSeed());
}

int SCA_RandomSensor::pyattr_set_seed(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value)
{
	SCA_RandomSensor* self= static_cast<SCA_RandomSensor*>(self_v);
	if (!PyInt_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "sensor.seed = int: Random Sensor, expected an integer");
		return PY_SET_ATTR_FAIL;
	}
	self->m_basegenerator->SetSeed(PyInt_AsLong(value));
	return PY_SET_ATTR_SUCCESS;
}

/* eof */
