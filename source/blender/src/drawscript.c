/**
 * $Id: drawscript.c 17209 2008-10-28 18:47:13Z campbellbarton $
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
 * Inc., 59 Temple Place - Suite 330, Boston, MA	02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: drawtext.c.
 *
 * Contributor(s): Willian Padovani Germano.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include <stdlib.h>
#include <math.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#endif	 
#include "MEM_guardedalloc.h"
#include "PIL_time.h"

#include "BMF_Api.h"

#include "BLI_blenlib.h"

#include "DNA_space_types.h"
#include "DNA_screen_types.h"
#include "DNA_userdef_types.h"

#include "BKE_utildefines.h"
#include "BKE_text.h"
#include "BKE_global.h"
#include "BKE_main.h"

#ifndef DISABLE_PYTHON
#include "BPY_extern.h"
#endif

#include "BIF_gl.h"
#include "BIF_keyval.h"
#include "BIF_interface.h"
#include "BIF_drawscript.h"
#include "BIF_editfont.h"
#include "BIF_spacetypes.h"
#include "BIF_usiblender.h"
#include "BIF_screen.h"
#include "BIF_toolbox.h"
#include "BIF_space.h"
#include "BIF_mywindow.h"

#include "BSE_filesel.h"

#include "mydevice.h"
#include "blendef.h" 
#include "interface.h"

void drawscriptspace(ScrArea *sa, void *spacedata);
void winqreadscriptspace(struct ScrArea *sa, void *spacedata, struct BWinEvent *evt);

void drawscriptspace(ScrArea *sa, void *spacedata)
{
	SpaceScript *sc = curarea->spacedata.first;
	Script *script = NULL;

	glClearColor(0.6, 0.6,	0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	myortho2(-0.5, curarea->winrct.xmax-curarea->winrct.xmin-0.5, -0.5, curarea->winrct.ymax-curarea->winrct.ymin-0.5);

#ifdef DISABLE_PYTHON
	return;
#else
	if (!sc->script) return;

	script = sc->script;

	/* Is this script loaded from a file and it needs running??? */
	if (	(G.f & G_DOSCRIPTLINKS) &&
				script->scriptname[0] != '\0' &&
				(script->flags == 0 &&
				script->py_event == NULL &&
				script->py_button == NULL &&
				script->py_draw ==	NULL )
		) {
		if (!BPY_run_script(script)) {
			/* if this fails, script will be free'd */
			script = NULL;
		}
	}
	
	if (script) {
		if (script->py_draw) {
			BPY_spacescript_do_pywin_draw(sc);
		} else if (!script->flags && !script->py_event && !script->py_button) {
			/* quick hack for 2.37a for scripts that call the progress bar inside a
			 * file selector callback, to show previous space after finishing, w/o
			 * needing an event */
			addqueue(curarea->win, MOUSEX, 0);
		}
	}
#endif /* DISABLE_PYTHON */
}

void winqreadscriptspace(struct ScrArea *sa, void *spacedata, struct BWinEvent *evt)
{
#ifndef DISABLE_PYTHON
	unsigned short event = evt->event;
	short val = evt->val;
	char ascii = evt->ascii;
	SpaceScript *sc = curarea->spacedata.first;
	Script *script = sc->script;

	if (script) {
		/* Is this script loaded from a file and it needs running??? */
		if (	(G.f & G_DOSCRIPTLINKS) &&
				 script->scriptname[0] != '\0' &&
					(script->flags == 0 &&
				 script->py_event == NULL &&
				 script->py_button == NULL &&
				 script->py_draw ==	NULL )
		   ) {
			if (!BPY_run_script(script)) {
				/* if this fails, script will be free'd */
				script = NULL;
			}
		}
	}
	
	if (script) {
		if (script->py_event || script->py_button)
			BPY_spacescript_do_pywin_event(sc, event, val, ascii);

		/* for file/image sel scripts: if user leaves file/image selection space,
		 * this frees the script (since it can't be accessed anymore): */
		else if (script->flags == SCRIPT_FILESEL) {
			script->flags = 0;
			script->lastspace = SPACE_SCRIPT;
		}

		if (!script->flags) {/* finished with this script, let's free it */
			if (script->lastspace != SPACE_SCRIPT)
				newspace (curarea, script->lastspace);
			BPY_free_finished_script(script);
			sc->script = NULL;
		}
	}
	else {
		if (event == QKEY)
			if (val && (G.qual & LR_CTRLKEY) && okee("Quit Blender")) exit_usiblender();
	}
#endif
	return;

}

void free_scriptspace (SpaceScript *sc)
{
	if (!sc) return;
#ifndef DISABLE_PYTHON	
	/*free buttons references*/
	if (sc->but_refs) {
		BPy_Set_DrawButtonsList(sc->but_refs);
		BPy_Free_DrawButtonsList();
		sc->but_refs = NULL;
	}
#endif
	sc->script = NULL;
}
