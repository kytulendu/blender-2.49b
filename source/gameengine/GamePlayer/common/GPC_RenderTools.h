/**
 * $Id: GPC_RenderTools.h 19398 2009-03-24 15:45:08Z blendix $
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

#ifndef __GPC_RENDERTOOLS_H
#define __GPC_RENDERTOOLS_H

#ifdef WIN32
// don't show stl-warnings
#pragma warning (disable:4786)
#include <windows.h>
#endif // WIN32

#include "RAS_IRenderTools.h"

#include "BMF_Api.h"

struct KX_ClientObjectInfo;
class KX_RayCast;

/* BlenderRenderTools are a set of tools to apply 2D/3D graphics effects, which
 * are not part of the (polygon) Rasterizer. Effects like 2D text, 3D (polygon)
 * text, lighting.
 *
 * Most of this code is duplicated in KX_BlenderRenderTools, so this should be
 * moved to some common location to avoid duplication. */

class GPC_RenderTools : public RAS_IRenderTools
{
	int		m_lastlightlayer;
	bool	m_lastlighting;
	void	*m_lastauxinfo;
	static unsigned int m_numgllights;

	BMF_Font* m_font;

public:
						GPC_RenderTools();
	virtual				~GPC_RenderTools();

	void				EndFrame(RAS_IRasterizer* rasty);
	void				BeginFrame(RAS_IRasterizer* rasty);

	void				EnableOpenGLLights(RAS_IRasterizer *rasty);
	void				DisableOpenGLLights();
	void				ProcessLighting(RAS_IRasterizer *rasty, bool uselights, const MT_Transform& viewmat);

	/* @attention mode is ignored here */
	void			    RenderText2D(RAS_TEXT_RENDER_MODE mode,
									 const char* text,
									 int xco,
									 int yco,
									 int width,
									 int height);
	void				RenderText(int mode,
								   class RAS_IPolyMaterial* polymat,
								   float v1[3],
								   float v2[3],
								   float v3[3],
								   float v4[3],
								   int glattrib);

	void				applyTransform(RAS_IRasterizer* rasty, double* oglmatrix, int objectdrawmode);
	int					applyLights(int objectlayer, const MT_Transform& viewmat);

	void				PushMatrix();
	void				PopMatrix();

	bool RayHit(KX_ClientObjectInfo* client, KX_RayCast* result, void * const data);
	bool NeedRayCast(KX_ClientObjectInfo* client) { return true; }

	virtual void MotionBlur(RAS_IRasterizer* rasterizer);

	virtual void Update2DFilter(vector<STR_String>& propNames, void* gameObj, RAS_2DFilterManager::RAS_2DFILTER_MODE filtermode, int pass, STR_String& text);

	virtual	void Render2DFilters(RAS_ICanvas* canvas);

	virtual void SetClientObject(RAS_IRasterizer *rasty, void* obj);
};

#endif  // __GPC_RENDERTOOLS_H



