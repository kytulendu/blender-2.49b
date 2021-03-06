/**
 * $Id: GlutMouseManager.cpp 14444 2008-04-16 22:40:48Z hos $
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

#include "GlutMouseManager.h"
#include "MT_assert.h"

MEM_SmartPtr<GlutMouseManager> GlutMouseManager::m_s_instance = MEM_SmartPtr<GlutMouseManager>();


	GlutMouseManager *
GlutMouseManager::
Instance(
){
	if (m_s_instance == NULL) {
		m_s_instance = new GlutMouseManager();
	}

	return m_s_instance;
}	

// these are the functions you should pass to GLUT	

	void
GlutMouseManager::
Mouse(
	int button,
	int state,
	int x,
	int y
){
	GlutMouseManager *manager = GlutMouseManager::Instance();

	if (manager->m_handler != NULL) {
		manager->m_handler->Mouse(button,state,x,y);
	}
}

	void
GlutMouseManager::
Motion(
	int x,
	int y
){
	GlutMouseManager *manager = GlutMouseManager::Instance();

	if (manager->m_handler != NULL) {
		manager->m_handler->Motion(x,y);
	}
}

	void
GlutMouseManager::
InstallHandler(
	GlutMouseHandler *handler
){

	MT_assert(m_handler == NULL);
	m_handler = handler;
}

	void
GlutMouseManager::
ReleaseHandler(
){
	m_handler = NULL;
}

GlutMouseManager::
~GlutMouseManager(
){

	delete(m_handler);
}


