/**
 * $Id: GHOST_EventButton.h 14444 2008-04-16 22:40:48Z hos $
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
 * @file	GHOST_EventButton.h
 * Declaration of GHOST_EventButton class.
 */

#ifndef _GHOST_EVENT_BUTTON_H_
#define _GHOST_EVENT_BUTTON_H_

#include "GHOST_Event.h"

/**
 * Mouse button event.
 * @author	Maarten Gribnau
 * @date	May 11, 2001
 */
class GHOST_EventButton : public GHOST_Event
{
public:
	/**
	 * Constructor.
	 * @param time		The time this event was generated.
	 * @param type		The type of this event.
	 * @param x			The x-coordinate of the location the cursor was at at the time of the event.
	 * @param y			The y-coordinate of the location the cursor was at at the time of the event.
	 * @param buttons	The state of the buttons  was at at the time of the event.
	 */
	GHOST_EventButton(GHOST_TUns64 time, GHOST_TEventType type, GHOST_IWindow* window, GHOST_TButtonMask button)
		: GHOST_Event(time, type, window)
	{
		m_buttonEventData.button = button;
		m_data = &m_buttonEventData;
	}

protected:
	/** The button event data. */
	GHOST_TEventButtonData m_buttonEventData;
};

#endif // _GHOST_EVENT_BUTTON_H_

