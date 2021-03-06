/**
 * $Id: KX_ConvertActuators.h 20130 2009-05-10 20:53:58Z ben2610 $
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
#ifndef __KX_CONVERTACTUATORS_H
#define __KX_CONVERTACTUATORS_H

void BL_ConvertActuators(char* maggiename,
	 struct Object* blenderobject,
	 class KX_GameObject* gameobj,
	 class SCA_LogicManager* logicmgr,
	 class KX_Scene* scene,
	 class KX_KetsjiEngine* ketsjiEngine,
	 int activeLayerBitInfo,
	 bool isInActiveLayer,
	 class RAS_IRenderTools* rendertools, 
	 class KX_BlenderSceneConverter* converter);


#endif //__KX_CONVERTACTUATORS_H

