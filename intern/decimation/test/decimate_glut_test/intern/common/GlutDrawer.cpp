/**
 * $Id: GlutDrawer.cpp 14444 2008-04-16 22:40:48Z hos $
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "GlutDrawer.h"
#include "MT_assert.h"

MEM_SmartPtr<GlutDrawManager> GlutDrawManager::m_s_instance = MEM_SmartPtr<GlutDrawManager>();

	GlutDrawManager *
GlutDrawManager::
Instance(
){
	if (m_s_instance == NULL) {
		m_s_instance = new GlutDrawManager();
	}

	return m_s_instance;
}


// this is the function you should pass to glut

	void
GlutDrawManager::
Draw(
){
	GlutDrawManager *manager = GlutDrawManager::Instance();

	if (manager->m_drawer != NULL) {
		manager->m_drawer->Draw();
	}
}

	void
GlutDrawManager::
InstallDrawer(
	GlutDrawer * drawer
){

	MT_assert(m_drawer == NULL);
	m_drawer = drawer;
}

	void
GlutDrawManager::
ReleaseDrawer(
){
	m_drawer = NULL;
}


GlutDrawManager::
~GlutDrawManager(
){

	delete(m_drawer);
}









