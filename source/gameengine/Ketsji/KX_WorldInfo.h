/**
 * $Id: KX_WorldInfo.h 15444 2008-07-05 17:05:05Z lukep $
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
#ifndef __KX_WORLDINFO_H
#define __KX_WORLDINFO_H

#include "MT_Scalar.h"

class MT_CmMatrix4x4;

class KX_WorldInfo
{
public:
	KX_WorldInfo(){}
	virtual ~KX_WorldInfo();

	virtual bool	hasWorld()=0;
	virtual bool	hasMist()=0;
	virtual float	getBackColorRed()=0;
	virtual float	getBackColorGreen()=0;
	virtual float	getBackColorBlue()=0;
	virtual float	getMistStart()=0;
	virtual float	getMistDistance()=0;
	virtual float	getMistColorRed()=0;
	virtual float	getMistColorGreen()=0;
	virtual float	getMistColorBlue()=0;

	virtual float	getAmbientColorRed()=0;
	virtual float	getAmbientColorGreen()=0;
	virtual float	getAmbientColorBlue()=0;

	virtual void	setMistStart(float)=0;
	virtual void	setMistDistance(float)=0;
	virtual void	setMistColorRed(float)=0;
	virtual void	setMistColorGreen(float)=0;
	virtual void	setMistColorBlue(float)=0;
};

#endif //__KX_WORLDINFO_H

