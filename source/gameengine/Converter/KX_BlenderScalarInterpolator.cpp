/**
 * $Id: KX_BlenderScalarInterpolator.cpp 17031 2008-10-11 22:29:50Z blendix $
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

#include "KX_BlenderScalarInterpolator.h"

extern "C" {
#include "DNA_ipo_types.h"
#include "BKE_ipo.h"
}

static const int BL_MAX_CHANNELS = 32;

float BL_ScalarInterpolator::GetValue(float currentTime) const {
	return IPO_GetFloatValue(m_blender_ipo, m_channel, currentTime);
}

 

BL_InterpolatorList::BL_InterpolatorList(struct Ipo *ipo) {
	IPO_Channel channels[BL_MAX_CHANNELS];

	int num_channels = IPO_GetChannels(ipo, channels);

	int i;

	for (i = 0; i != num_channels; ++i) {
		BL_ScalarInterpolator *new_ipo =
			new BL_ScalarInterpolator(ipo, channels[i]); 

		//assert(new_ipo);
		push_back(new_ipo);
	}
}

BL_InterpolatorList::~BL_InterpolatorList() {
	BL_InterpolatorList::iterator i;
	for (i = begin(); !(i == end()); ++i) {
		delete *i;
	}
}


KX_IScalarInterpolator *BL_InterpolatorList::GetScalarInterpolator(BL_IpoChannel channel) {
	BL_InterpolatorList::iterator i = begin();
	while (!(i == end()) && 
		   (static_cast<BL_ScalarInterpolator *>(*i))->GetChannel() != 
		   channel) {
		++i;
	}
	
	return (i == end()) ? 0 : *i;
}	

