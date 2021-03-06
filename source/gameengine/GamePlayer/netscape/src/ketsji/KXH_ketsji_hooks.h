/**
 * $Id: KXH_ketsji_hooks.h 15444 2008-07-05 17:05:05Z lukep $
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
 * Hooks from gameengine to plugin. These are used by the GPU canvas.
 */

#ifndef KXH_KETSJI_HOOKS_H
#define KXH_KETSJI_HOOKS_H 

#define KXH_DECLARE_HANDLE(name) typedef struct name##__ { int unused; } *name

#ifndef __KXH_PLUGIN_HANDLE
#define __KXH_PLUGIN_HANDLE
	KXH_DECLARE_HANDLE(KXH_plugin_handle);
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/** Acquire drawing context. */
	bool
	KXH_begin_draw(KXH_plugin_handle h);

	/** Swap buffers in the drawing context. This does not release the
	 * context! */
	void
	KXH_swap_buffers(KXH_plugin_handle h);

	/** Release drawing context. */
	void
	KXH_end_draw(KXH_plugin_handle h);
	

#ifdef __cplusplus
}
#endif

#endif

