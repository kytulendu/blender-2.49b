/**
 * $Id: GHOST_CallbackEventConsumer.cpp 14444 2008-04-16 22:40:48Z hos $
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

/**

 * $Id: GHOST_CallbackEventConsumer.cpp 14444 2008-04-16 22:40:48Z hos $
 * Copyright (C) 2001 NaN Technologies B.V.
 * @author	Maarten Gribnau
 * @date	October 25, 2001
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "GHOST_Debug.h"
#include "GHOST_C-api.h"
#include "GHOST_CallbackEventConsumer.h"

GHOST_CallbackEventConsumer::GHOST_CallbackEventConsumer(GHOST_EventCallbackProcPtr eventCallback,
														GHOST_TUserDataPtr userData)
{
	m_eventCallback = eventCallback;
	m_userData = userData;
}


bool GHOST_CallbackEventConsumer::processEvent(GHOST_IEvent* event)
{
	return m_eventCallback((GHOST_EventHandle)event, m_userData) != 0;
}
