/**
 * Execute Python scripts
 *
 * $Id: SCA_PythonController.h 20083 2009-05-06 09:12:08Z campbellbarton $
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

#ifndef KX_PYTHONCONTROLLER_H
#define KX_PYTHONCONTROLLER_H
	      
#include "SCA_IController.h"
#include "SCA_LogicManager.h"
#include "BoolValue.h"

#include <vector>

class SCA_IObject;
class SCA_PythonController : public SCA_IController
{
	Py_Header;
	struct _object *		m_bytecode; /* SCA_PYEXEC_SCRIPT only */
	PyObject*				m_function; /* SCA_PYEXEC_MODULE only */
	int						m_function_argc;
	bool					m_bModified;
	bool					m_debug;	/* use with SCA_PYEXEC_MODULE for reloading every logic run */
	int						m_mode;

	
 protected:
	STR_String				m_scriptText;
	STR_String				m_scriptName;
	PyObject*				m_pythondictionary;	/* for SCA_PYEXEC_SCRIPT only */
	PyObject*				m_pythonfunction;	/* for SCA_PYEXEC_MODULE only */
 
	std::vector<class SCA_ISensor*>		m_triggeredSensors;
 
 public:
	enum SCA_PyExecMode
	{
		SCA_PYEXEC_SCRIPT = 0,
		SCA_PYEXEC_MODULE,
		SCA_PYEXEC_MAX
	};

	static SCA_PythonController* m_sCurrentController; // protected !!!

	//for debugging
	//virtual	CValue*		AddRef();
	//virtual int			Release();												// Release a reference to this value (when reference count reaches 0, the value is removed from the heap)

	SCA_PythonController(SCA_IObject* gameobj, int mode, PyTypeObject* T = &Type);
	virtual ~SCA_PythonController();

	virtual CValue* GetReplica();
	virtual void  Trigger(class SCA_LogicManager* logicmgr);
  
	void	SetScriptText(const STR_String& text);
	void	SetScriptName(const STR_String& name);
	void	SetDictionary(PyObject*	pythondictionary);
	void	SetDebug(bool debug) { m_debug = debug; }
	void	AddTriggeredSensor(class SCA_ISensor* sensor)
		{ m_triggeredSensors.push_back(sensor); }
	int		IsTriggered(class SCA_ISensor* sensor);
	bool	Compile();
	bool	Import();
	void	ErrorPrint(const char *error_msg);
	

	static const char* sPyGetCurrentController__doc__;
	static PyObject* sPyGetCurrentController(PyObject* self);
	static const char* sPyAddActiveActuator__doc__;
	static PyObject* sPyAddActiveActuator(PyObject* self, 
										  PyObject* args);
	static SCA_IActuator* LinkedActuatorFromPy(PyObject *value);
		
	virtual PyObject* py_getattro(PyObject *attr);
	virtual PyObject* py_getattro_dict();
	virtual int py_setattro(PyObject *attr, PyObject *value);

		
	KX_PYMETHOD_O(SCA_PythonController,Activate);
	KX_PYMETHOD_O(SCA_PythonController,DeActivate);
	KX_PYMETHOD_O(SCA_PythonController,SetScript);
	KX_PYMETHOD_NOARGS(SCA_PythonController,GetScript);

	
	static PyObject*	pyattr_get_script(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_script(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	

};

#endif //KX_PYTHONCONTROLLER_H

