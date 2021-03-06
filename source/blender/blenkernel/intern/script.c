/* blenkernel/script.c
 *
 *
 * $Id: script.c 17209 2008-10-28 18:47:13Z campbellbarton $
 *
 * Function(s) related to struct script management.
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
 * This is a new part of Blender.
 *
 * Contributor(s): Willian P. Germano.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include "BKE_script.h"
#include "DNA_space_types.h"

#include "MEM_guardedalloc.h"
#include "BKE_bad_level_calls.h" /* for BPY_clear_script */

/*
#include "BLI_blenlib.h"
#include "BKE_utildefines.h"
#include "BKE_library.h"
#include "BKE_global.h"
#include "BKE_main.h"

#ifndef DISABLE_PYTHON
#include "BPY_extern.h" // Blender Python library
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
*/

/* XXX this function and so also the file should not be needed anymore,
 * since we have to force clearing all Python related data before freeing
 * Blender's library. Still testing, will decide later (Willian). */
void free_script (Script *script)
{
	if (!script) return;
#ifndef DISABLE_PYTHON
	BPY_clear_script(script);
#endif
}
