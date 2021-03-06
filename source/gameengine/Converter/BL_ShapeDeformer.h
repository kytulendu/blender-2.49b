/**
 * $Id: BL_ShapeDeformer.h 20200 2009-05-14 13:47:08Z ben2610 $
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

#ifndef BL_SHAPEDEFORMER
#define BL_SHAPEDEFORMER

#ifdef WIN32
#pragma warning (disable:4786) // get rid of stupid stl-visual compiler debug warning
#endif //WIN32

#include "BL_SkinDeformer.h"
#include "BL_DeformableGameObject.h"
#include <vector>

struct IpoCurve;

class BL_ShapeDeformer : public BL_SkinDeformer  
{
public:
	BL_ShapeDeformer(BL_DeformableGameObject *gameobj,
                     Object *bmeshobj,
                     BL_SkinMeshObject *mesh)
					:	
						BL_SkinDeformer(gameobj,bmeshobj, mesh),
						m_lastShapeUpdate(-1)
	{
	};

	/* this second constructor is needed for making a mesh deformable on the fly. */
	BL_ShapeDeformer(BL_DeformableGameObject *gameobj,
					struct Object *bmeshobj_old,
					struct Object *bmeshobj_new,
					class BL_SkinMeshObject *mesh,
					bool release_object,
					bool recalc_normal,
					BL_ArmatureObject* arma = NULL)
					:
						BL_SkinDeformer(gameobj, bmeshobj_old, bmeshobj_new, mesh, release_object, recalc_normal, arma),
						m_lastShapeUpdate(-1)
	{
	};

	virtual RAS_Deformer *GetReplica();
	virtual void ProcessReplica();
	virtual ~BL_ShapeDeformer();

	bool Update (void);
	bool LoadShapeDrivers(Object* arma);
	bool ExecuteShapeDrivers(void);

	void ForceUpdate()
	{
		m_lastShapeUpdate = -1.0;
	};

protected:
	vector<IpoCurve*>		 m_shapeDrivers;
	double					 m_lastShapeUpdate;

};

#endif

