/**
 * $Id: SCA_ISensor.h 20378 2009-05-24 12:53:49Z ben2610 $
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
 * Interface Class for all logic Sensors. Implements
 * pulsemode and pulsefrequency, and event suppression.
 */

#ifndef __SCA_ISENSOR
#define __SCA_ISENSOR

#include "SCA_IController.h"

#include <vector>
#include <cstddef>

/**
 * Interface Class for all logic Sensors. Implements
 * pulsemode,pulsefrequency 
 * Use of SG_DList element: link sensors to their respective event manager
 *                          Head: SCA_EventManager::m_sensors
 * Use of SG_QList element: not used
 */
class SCA_ISensor : public SCA_ILogicBrick
{
	Py_Header;
protected:
	class SCA_EventManager* m_eventmgr;

	/** Pulse positive  pulses? */
	bool m_pos_pulsemode;

	/** Pulse negative pulses? */
	bool m_neg_pulsemode;

	/** Repeat frequency in pulse mode. */
	int m_pulse_frequency;

	/** Number of ticks since the last positive pulse. */
	int m_pos_ticks;

	/** Number of ticks since the last negative pulse. */
	int m_neg_ticks;

	/** invert the output signal*/
	bool m_invert;

	/** detect level instead of edge*/
	bool m_level;

	/** tap mode */
	bool m_tap;

	/** sensor has been reset */
	bool m_reset;

	/** Sensor must ignore updates? */
	bool m_suspended;

	/** number of connections to controller */
	int m_links;

	/** current sensor state */
	bool m_state;

	/** previous state (for tap option) */
	bool m_prev_state;

	std::vector<class SCA_IController*>		m_linkedcontrollers;

public:

	enum sensortype {
		ST_NONE = 0,
		ST_TOUCH,
		ST_NEAR,
		ST_RADAR,
		// to be updated as needed
	};

	SCA_ISensor(SCA_IObject* gameobj,
				class SCA_EventManager* eventmgr,
				PyTypeObject* T );;
	~SCA_ISensor();
	virtual void	ReParent(SCA_IObject* parent);

	/** Because we want sensors to share some behaviour, the Activate has     */
	/* an implementation on this level. It requires an evaluate on the lower */
	/* level of individual sensors. Mapping the old activate()s is easy.     */
	/* The IsPosTrig() also has to change, to keep things consistent.        */
	void Activate(class SCA_LogicManager* logicmgr);
	virtual bool Evaluate() = 0;
	virtual bool IsPositiveTrigger();
	virtual void Init();

	virtual CValue* GetReplica()=0;

	/** Set parameters for the pulsing behaviour.
	 * @param posmode Trigger positive pulses?
	 * @param negmode Trigger negative pulses?
	 * @param freq    Frequency to use when doing pulsing.
	 */
	void SetPulseMode(bool posmode,
					  bool negmode,
					  int freq);
	
	/** Set inversion of pulses on or off. */
	void SetInvert(bool inv);
	/** set the level detection on or off */
	void SetLevel(bool lvl);
	void SetTap(bool tap);

	virtual void RegisterToManager();
	virtual void UnregisterToManager();
	void ReserveController(int num)
	{
		m_linkedcontrollers.reserve(num);
	}
	void LinkToController(SCA_IController* controller);
	void UnlinkController(SCA_IController* controller);
	void UnlinkAllControllers();
	void ActivateControllers(class SCA_LogicManager* logicmgr);

	virtual void ProcessReplica();

	virtual double GetNumber();

	virtual sensortype GetSensorType() { return ST_NONE; }

	/** Stop sensing for a while. */
	void Suspend();

	/** Is this sensor switched off? */
	bool IsSuspended();
	
	/** get the state of the sensor: positive or negative */
	bool GetState()
	{
		return m_state;
	}

	/** Resume sensing. */
	void Resume();

	void ClrLink()
		{ m_links = 0; }
	void IncLink()
		{ if (!m_links++) RegisterToManager(); }
	void DecLink();
	bool IsNoLink() const 
		{ return !m_links; }

	/* Python functions: */
	
	virtual PyObject* py_getattro(PyObject *attr);
	virtual PyObject* py_getattro_dict();
	virtual int py_setattro(PyObject *attr, PyObject *value);

	//Deprecated functions ----->
	KX_PYMETHOD_DOC_NOARGS(SCA_ISensor,IsPositive);
	KX_PYMETHOD_DOC_NOARGS(SCA_ISensor,IsTriggered);
	KX_PYMETHOD_DOC_NOARGS(SCA_ISensor,GetUsePosPulseMode);
	KX_PYMETHOD_DOC_VARARGS(SCA_ISensor,SetUsePosPulseMode);
	KX_PYMETHOD_DOC_NOARGS(SCA_ISensor,GetFrequency);
	KX_PYMETHOD_DOC_VARARGS(SCA_ISensor,SetFrequency);
	KX_PYMETHOD_DOC_NOARGS(SCA_ISensor,GetUseNegPulseMode);
	KX_PYMETHOD_DOC_VARARGS(SCA_ISensor,SetUseNegPulseMode);
	KX_PYMETHOD_DOC_NOARGS(SCA_ISensor,GetInvert);
	KX_PYMETHOD_DOC_VARARGS(SCA_ISensor,SetInvert);
	KX_PYMETHOD_DOC_NOARGS(SCA_ISensor,GetLevel);
	KX_PYMETHOD_DOC_VARARGS(SCA_ISensor,SetLevel);
	//<------
	KX_PYMETHOD_DOC_NOARGS(SCA_ISensor,reset);
	
	static PyObject*	pyattr_get_triggered(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_positive(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int          pyattr_check_level(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int          pyattr_check_tap(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
};

#endif //__SCA_ISENSOR

