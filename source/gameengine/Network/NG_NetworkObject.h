/*
 * $Id: NG_NetworkObject.h 15444 2008-07-05 17:05:05Z lukep $
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
 * NetworkGame_NetworkObject generic Network Object class
 */
#ifndef NG_NETWORKOBJECT_H
#define NG_NETWORKOBJECT_H

#include "STR_String.h"

class NG_NetworkObject
{
	STR_String m_name;
public:
	NG_NetworkObject();
	~NG_NetworkObject();
	const STR_String& GetName();
};

#endif //NG_NETWORKOBJECT_H

