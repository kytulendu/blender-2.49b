/**
 * VoidValue.h: interface for the CVoidValue class.
 * $Id: VoidValue.h 19669 2009-04-12 06:41:01Z campbellbarton $
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
#ifndef __VOIDVALUE_H__
#define __VOIDVALUE_H__

#include "Value.h"

//
// Void value, used to transport *any* type of data
//
class CVoidValue : public CPropValue  
{
	//PLUGIN_DECLARE_SERIAL (CVoidValue,CValue)

public:
	/// Construction/destruction
	CVoidValue()																: m_bDeleteOnDestruct(false), m_pAnything(NULL)	 { }
	CVoidValue(void * voidptr, bool bDeleteOnDestruct, AllocationTYPE alloctype)	: m_bDeleteOnDestruct(bDeleteOnDestruct), m_pAnything(voidptr)  { if (alloctype == STACKVALUE) CValue::DisableRefCount(); }
	virtual				~CVoidValue();											// Destruct void value, delete memory if we're owning it

	/// Value -> String or number
	virtual const STR_String &	GetText();												// Get string description of void value (unimplemented)
	virtual double		GetNumber()												{ return -1; }

	/// Value calculation
	virtual CValue*		Calc(VALUE_OPERATOR op, CValue *val);
	virtual CValue*		CalcFinal(VALUE_DATA_TYPE dtype, VALUE_OPERATOR op, CValue* val);

	/// Value replication
	virtual CValue*		GetReplica();
	
	/// Data members
	bool				m_bDeleteOnDestruct;
	void*				m_pAnything;
};

#endif // !defined _VOIDVALUE_H

