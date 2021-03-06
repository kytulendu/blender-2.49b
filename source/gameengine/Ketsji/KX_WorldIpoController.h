/**
 * $Id: KX_WorldIpoController.h 15444 2008-07-05 17:05:05Z lukep $
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
#ifndef KX_WORLDIPOCONTROLLER_H
#define KX_WORLDIPOCONTROLLER_H

#include "SG_Controller.h"
#include "SG_Spatial.h"
#include "KX_IInterpolator.h"

class KX_WorldIpoController : public SG_Controller
{
public:
	MT_Scalar           m_mist_rgb[3];
	MT_Scalar           m_mist_start;
	MT_Scalar           m_mist_dist;

private:
	T_InterpolatorList	m_interpolators;
	unsigned short	    m_modify_mist_color  : 1;
	unsigned short		m_modify_mist_start	 : 1;
	unsigned short  	m_modify_mist_dist 	 : 1;
	bool				m_modified;

	double		        m_ipotime;

public:
	KX_WorldIpoController() : 
				m_modify_mist_color(false),
				m_modify_mist_start(false),
				m_modify_mist_dist(false),
				m_modified(true),
				m_ipotime(0.0)
		{}

	virtual ~KX_WorldIpoController();

	virtual	SG_Controller*	GetReplica(class SG_Node* destnode);

	virtual bool Update(double time);
	
	virtual void SetSimulatedTime(double time) {
		m_ipotime = time;
		m_modified = true;
	}

	void	SetModifyMistStart(bool modify) {	
		m_modify_mist_start = modify;
	}

	void	SetModifyMistColor(bool modify) {	
		m_modify_mist_color = modify;
	}

	void	SetModifyMistDist(bool modify) {	
		m_modify_mist_dist = modify;
	}

		void
	SetOption(
		int option,
		int value
	){
		// intentionally empty
	};

	void	AddInterpolator(KX_IInterpolator* interp);
};

#endif // KX_LIGHTIPOSGCONTROLLER_H

