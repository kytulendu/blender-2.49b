/**
 * $Id: GHOST_DisplayManager.h 14444 2008-04-16 22:40:48Z hos $
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
 * @file	GHOST_DisplayManager.h
 * Declaration of GHOST_DisplayManager class.
 */

#ifndef _GHOST_DISPLAY_MANAGER_H_
#define _GHOST_DISPLAY_MANAGER_H_

#include "GHOST_Types.h"

#ifdef WIN32
#pragma warning (disable:4786) // suppress stl-MSVC debug info warning
#endif // WIN32

#include <vector>

/**
 * Manages system displays  (platform independent implementation).
 * @author	Maarten Gribnau
 * @date	September 21, 2001
 */
class GHOST_DisplayManager
{
public:
	enum { kMainDisplay = 0 };
	/**
	 * Constructor.
	 */
	GHOST_DisplayManager(void);
	
	/**
	 * Destructor.
	 */
	virtual ~GHOST_DisplayManager(void);

	/**
	 * Initializes the list with devices and settings.
	 * @return Indication of success.
	 */
	virtual GHOST_TSuccess initialize(void);

	/**
	 * Returns the number of display devices on this system.
	 * @param numDisplays The number of displays on this system.
	 * @return Indication of success.
	 */
	virtual GHOST_TSuccess getNumDisplays(GHOST_TUns8& numDisplays) const;

	/**
	 * Returns the number of display settings for this display device.
	 * @param display The index of the display to query with 0 <= display < getNumDisplays().
	 * @param setting The number of settings of the display device with this index.
	 * @return Indication of success.
	 */
	virtual GHOST_TSuccess getNumDisplaySettings(GHOST_TUns8 display, GHOST_TInt32& numSettings) const;

	/**
	 * Returns the current setting for this display device. 
	 * @param display The index of the display to query with 0 <= display < getNumDisplays().
	 * @param index	  The setting index to be returned.
	 * @param setting The setting of the display device with this index.
	 * @return Indication of success.
	 */
	virtual GHOST_TSuccess getDisplaySetting(GHOST_TUns8 display, GHOST_TInt32 index, GHOST_DisplaySetting& setting) const;

	/**
	 * Returns the current setting for this display device. 
	 * @param display The index of the display to query with 0 <= display < getNumDisplays().
	 * @param setting The current setting of the display device with this index.
	 * @return Indication of success.
	 */
	virtual GHOST_TSuccess getCurrentDisplaySetting(GHOST_TUns8 display, GHOST_DisplaySetting& setting) const;

	/**
	 * Changes the current setting for this display device.
	 * The setting given to this method is matched againts the available diplay settings.
	 * The best match is activated (@see findMatch()).
	 * @param display The index of the display to query with 0 <= display < getNumDisplays().
	 * @param setting The setting of the display device to be matched and activated.
	 * @return Indication of success.
	 */
	virtual GHOST_TSuccess setCurrentDisplaySetting(GHOST_TUns8 display, const GHOST_DisplaySetting& setting);

protected:
	typedef std::vector<GHOST_DisplaySetting> GHOST_DisplaySettings;

	/**
	 * Finds the best display settings match.
	 * @param display	The index of the display device.
	 * @param setting	The setting to match.
	 * @param match		The optimal display setting.
	 * @return Indication of success.
	 */
	GHOST_TSuccess findMatch(GHOST_TUns8 display, const GHOST_DisplaySetting& setting, GHOST_DisplaySetting& match) const;

	/**
	 * Retrieves settings for each display device and stores them.
	 * @return Indication of success.
	 */
	GHOST_TSuccess initializeSettings(void);
	
	/** Tells whether the list of display modes has been stored already. */
	bool m_settingsInitialized;
	/** The list with display settings for the main display. */
	std::vector<GHOST_DisplaySettings> m_settings;
};


#endif // _GHOST_DISPLAY_MANAGER_H_

