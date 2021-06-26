/**
 * $Id: KX_CameraIpoSGController.cpp 15444 2008-07-05 17:05:05Z lukep $
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

#include "KX_CameraIpoSGController.h"
#include "KX_ScalarInterpolator.h"
#include "KX_Camera.h"
#include "RAS_CameraData.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if defined(_WIN64)
typedef unsigned __int64 uint_ptr;
#else
typedef unsigned long uint_ptr;
#endif

bool KX_CameraIpoSGController::Update(double currentTime)
{
	if (m_modified)
	{
		T_InterpolatorList::iterator i;
		for (i = m_interpolators.begin(); !(i == m_interpolators.end()); ++i) {
			(*i)->Execute(m_ipotime);
		}
		
		SG_Spatial* ob = (SG_Spatial*)m_pObject;
		KX_Camera* kxcamera = (KX_Camera*) ob->GetSGClientObject();
		RAS_CameraData* camdata = kxcamera->GetCameraData();
		
		if (m_modify_lens)
			camdata->m_lens = m_lens;

		if (m_modify_clipstart )
			camdata->m_clipstart = m_clipstart;

		if (m_modify_clipend)
			camdata->m_clipend = m_clipend;
		
		if (m_modify_lens || m_modify_clipstart || m_modify_clipend)
			kxcamera->InvalidateProjectionMatrix();

		m_modified=false;
	}
	return false;
}


void KX_CameraIpoSGController::AddInterpolator(KX_IInterpolator* interp)
{
	this->m_interpolators.push_back(interp);
}

SG_Controller*	KX_CameraIpoSGController::GetReplica(class SG_Node* destnode)
{
	KX_CameraIpoSGController* iporeplica = new KX_CameraIpoSGController(*this);
	// clear object that ipo acts on
	iporeplica->ClearObject();

	// dirty hack, ask Gino for a better solution in the ipo implementation
	// hacken en zagen, in what we call datahiding, not written for replication :(

	T_InterpolatorList oldlist = m_interpolators;
	iporeplica->m_interpolators.clear();

	T_InterpolatorList::iterator i;
	for (i = oldlist.begin(); !(i == oldlist.end()); ++i) {
		KX_ScalarInterpolator* copyipo = new KX_ScalarInterpolator(*((KX_ScalarInterpolator*)*i));
		iporeplica->AddInterpolator(copyipo);

		MT_Scalar* scaal = ((KX_ScalarInterpolator*)*i)->GetTarget();
		uint_ptr orgbase = (uint_ptr)this;
		uint_ptr orgloc = (uint_ptr)scaal;
		uint_ptr offset = orgloc-orgbase;
		uint_ptr newaddrbase = (uint_ptr)iporeplica + offset;
		MT_Scalar* blaptr = (MT_Scalar*) newaddrbase;
		copyipo->SetNewTarget((MT_Scalar*)blaptr);
	}
	
	return iporeplica;
}

KX_CameraIpoSGController::~KX_CameraIpoSGController()
{

	T_InterpolatorList::iterator i;
	for (i = m_interpolators.begin(); !(i == m_interpolators.end()); ++i) {
		delete (*i);
	}
	
}

	void
KX_CameraIpoSGController::SetOption(
	int option,
	int value) 
{
	/* Setting options */

}
