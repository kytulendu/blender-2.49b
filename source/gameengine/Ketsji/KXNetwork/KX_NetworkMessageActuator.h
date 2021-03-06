/**
 * $Id: KX_NetworkMessageActuator.h 19826 2009-04-20 23:17:52Z campbellbarton $
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
 * Ketsji Logic Extenstion: Network Message Actuator class
 */
#ifndef __KX_NETWORKMESSAGEACTUATOR_H
#define __KX_NETWORKMESSAGEACTUATOR_H

#include "STR_String.h"
#include "SCA_IActuator.h"
#include "NG_NetworkMessage.h"

class KX_NetworkMessageActuator : public SCA_IActuator
{
	Py_Header;
	bool m_lastEvent;
	class NG_NetworkScene* m_networkscene;	// needed for replication
	STR_String m_toPropName;
	STR_String m_subject;
	bool m_bPropBody;
	STR_String m_body;
public:
	KX_NetworkMessageActuator(
		SCA_IObject* gameobj,
		NG_NetworkScene* networkscene,
		const STR_String &toPropName,
		const STR_String &subject,
		int bodyType,
		const STR_String &body,
		PyTypeObject* T=&Type);
	virtual ~KX_NetworkMessageActuator();

	virtual bool Update();
	virtual CValue* GetReplica();

	/* ------------------------------------------------------------ */
	/* Python interface ------------------------------------------- */
	/* ------------------------------------------------------------ */

	virtual PyObject* py_getattro(PyObject *attr);
	virtual PyObject* py_getattro_dict();
	virtual int py_setattro(PyObject *attr, PyObject *value);

	// Deprecated ----->
	KX_PYMETHOD(KX_NetworkMessageActuator, SetToPropName);
	KX_PYMETHOD(KX_NetworkMessageActuator, SetSubject);
	KX_PYMETHOD(KX_NetworkMessageActuator, SetBodyType);
	KX_PYMETHOD(KX_NetworkMessageActuator, SetBody);
	// <-----

};

#endif //__KX_NETWORKMESSAGEACTUATOR_H

