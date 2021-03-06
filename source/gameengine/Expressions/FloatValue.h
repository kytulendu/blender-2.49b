/*
 * FloatValue.h: interface for the CFloatValue class.
 * $Id: FloatValue.h 20130 2009-05-10 20:53:58Z ben2610 $
 * Copyright (c) 1996-2000 Erwin Coumans <coockie@acm.org>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Erwin Coumans makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */
#if !defined _FLOATVALUE_H
#define _FLOATVALUE_H

#include "Value.h"

class CFloatValue : public CPropValue 
{
	//PLUGIN_DECLARE_SERIAL (CFloatValue,CValue)
public:
	CFloatValue();
	CFloatValue(float fl);
	CFloatValue(float fl,const char *name,AllocationTYPE alloctype=CValue::HEAPVALUE);

	virtual const STR_String & GetText();

	void Configure(CValue* menuvalue);
	virtual double GetNumber();
	virtual void SetValue(CValue* newval);
	float GetFloat();
	void SetFloat(float fl);
	virtual ~CFloatValue();
	virtual CValue* GetReplica();
	virtual CValue* Calc(VALUE_OPERATOR op, CValue *val);
	virtual CValue* CalcFinal(VALUE_DATA_TYPE dtype, VALUE_OPERATOR op, CValue *val);
	virtual PyObject*	ConvertValueToPython();

protected:
	float m_float;
	STR_String* m_pstrRep;

};

#endif // !defined _FLOATVALUE_H

