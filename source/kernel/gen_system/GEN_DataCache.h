/**
 * $Id: GEN_DataCache.h 14444 2008-04-16 22:40:48Z hos $
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
#ifndef __GEN_DATACACHE_H
#define __GEN_DATACACHE_H

#include "STR_HashedString.h"
#include "GEN_Map.h"

template <class T> 
class GEN_DataCache
{
	GEN_Map<STR_HashedString,T*>	m_dataCache;
	virtual	T*	LoadData(const STR_String& name)=0;
	virtual void	FreeCacheObjects()=0;

public:
	GEN_DataCache() {};
	virtual ~GEN_DataCache() {};

	T*		GetData(const STR_String& paramname)
	{
		T* result=NULL;

		T** resultptr = m_dataCache[paramname];
		if (resultptr)
		{
			result = *resultptr;
		}
		
		else
		{
			result = LoadData(paramname);
			if (result)
			{
				m_dataCache.insert(paramname,result);
			}
		}

		return result;
	}
	
	virtual void	ClearCache()
	{
		FreeCacheObjects();
		m_dataCache.clear();
	}
};

#endif //__GEN_DATACACHE_H

