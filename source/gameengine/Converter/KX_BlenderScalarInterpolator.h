/**
 * $Id: KX_BlenderScalarInterpolator.h 15444 2008-07-05 17:05:05Z lukep $
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
#ifndef __KX_SCALARINTERPOLATOR_H
#define __KX_SCALARINTERPOLATOR_H

#include <vector>

#include "KX_IScalarInterpolator.h"

typedef unsigned short BL_IpoChannel;

class BL_ScalarInterpolator : public KX_IScalarInterpolator {
public:
	BL_ScalarInterpolator() {} // required for use in STL list
	BL_ScalarInterpolator(struct Ipo *ipo, BL_IpoChannel channel) :
		m_blender_ipo(ipo),
		m_channel(channel)
		{}

	virtual ~BL_ScalarInterpolator() {}
	
	virtual float GetValue(float currentTime) const;

	BL_IpoChannel GetChannel() const { return m_channel; }

private:
	struct Ipo    *m_blender_ipo;
	BL_IpoChannel  m_channel;
};


class BL_InterpolatorList : public std::vector<KX_IScalarInterpolator *> {
public:
	BL_InterpolatorList(struct Ipo *ipo);
	~BL_InterpolatorList();

	KX_IScalarInterpolator *GetScalarInterpolator(BL_IpoChannel channel);	
};

#endif //__KX_SCALARINTERPOLATOR_H

