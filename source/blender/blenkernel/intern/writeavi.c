/**
 * Functions for writing avi-format files.
 * Added interface for generic movie support (ton)
 *
 * $Id: writeavi.c 14669 2008-05-04 09:41:15Z campbellbarton $
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
 * Contributor(s): Robert Wenzlaff
 *
 * ***** END GPL LICENSE BLOCK *****
 * 
 */

#include <string.h>

#include "MEM_guardedalloc.h"

#include "DNA_scene_types.h"

#include "BLI_blenlib.h"

#include "BKE_global.h"
#include "BKE_writeavi.h"
#include "AVI_avi.h"


/* ********************** general blender movie support ***************************** */

#ifdef WITH_QUICKTIME
#include "quicktime_export.h"
#endif

#if defined(_WIN32) && !defined(FREE_WINDOWS)
#include "BIF_writeavicodec.h"
#endif

#ifdef WITH_FFMPEG
#include "BKE_writeffmpeg.h"
#endif

#include "BKE_writeframeserver.h"

bMovieHandle *BKE_get_movie_handle(int imtype)
{
	static bMovieHandle mh;
	
	/* set the default handle, as builtin */
	mh.start_movie= start_avi;
	mh.append_movie= append_avi;
	mh.end_movie= end_avi;
	mh.get_next_frame = 0;
	
	/* do the platform specific handles */
#ifdef __sgi
	if (imtype == R_MOVIE) {
		
	}
#endif
#if defined(_WIN32) && !defined(FREE_WINDOWS)
	if (imtype == R_AVICODEC) {		
		mh.start_movie= start_avi_codec;
		mh.append_movie= append_avi_codec;
		mh.end_movie= end_avi_codec;
	}
#endif
#ifdef WITH_QUICKTIME
	if (imtype == R_QUICKTIME) {
		mh.start_movie= start_qt;
		mh.append_movie= append_qt;
		mh.end_movie= end_qt;
	}
#endif
#ifdef WITH_FFMPEG
	if (imtype == R_FFMPEG) {
		mh.start_movie = start_ffmpeg;
		mh.append_movie = append_ffmpeg;
		mh.end_movie = end_ffmpeg;
	}
#endif
	if (imtype == R_FRAMESERVER) {
		mh.start_movie = start_frameserver;
		mh.append_movie = append_frameserver;
		mh.end_movie = end_frameserver;
		mh.get_next_frame = frameserver_loop;
	}
	
	return &mh;
}

/* ****************************************************************** */


static AviMovie *avi=NULL;
static int sframe;

void makeavistring (RenderData *rd, char *string) 
{
	char txt[64];

	if (string==0) return;

	strcpy(string, rd->pic);
	BLI_convertstringcode(string, G.sce);

	BLI_make_existing_file(string);

	if (BLI_strcasecmp(string + strlen(string) - 4, ".avi")) {
		sprintf(txt, "%04d_%04d.avi", (rd->sfra) , (rd->efra) );
		strcat(string, txt);
	}
}

void start_avi(RenderData *rd, int rectx, int recty)
{
	int x, y;
	char name[256];
	AviFormat format;
	int quality;
	double framerate;
	
	makeavistring(rd, name);

	sframe = (rd->sfra);
	x = rectx;
	y = recty;

	quality= rd->quality;
	framerate= (double) rd->frs_sec / (double) rd->frs_sec_base;
	
	avi = MEM_mallocN (sizeof(AviMovie), "avimovie");

	/* RPW 11-21-2002 
	 if (rd->imtype != AVI_FORMAT_MJPEG) format = AVI_FORMAT_AVI_RGB;
	*/
	if (rd->imtype != R_AVIJPEG ) format = AVI_FORMAT_AVI_RGB;
	else format = AVI_FORMAT_MJPEG;

	if (AVI_open_compress (name, avi, 1, format) != AVI_ERROR_NONE) {
		printf("cannot open or start AVI movie file");
		MEM_freeN (avi);
		avi = NULL;
		return;
	}
			
	AVI_set_compress_option (avi, AVI_OPTION_TYPE_MAIN, 0, AVI_OPTION_WIDTH, &x);
	AVI_set_compress_option (avi, AVI_OPTION_TYPE_MAIN, 0, AVI_OPTION_HEIGHT, &y);
	AVI_set_compress_option (avi, AVI_OPTION_TYPE_MAIN, 0, AVI_OPTION_QUALITY, &quality);		
	AVI_set_compress_option (avi, AVI_OPTION_TYPE_MAIN, 0, AVI_OPTION_FRAMERATE, &framerate);

	avi->interlace= 0;
	avi->odd_fields= 0;
/* 	avi->interlace= rd->mode & R_FIELDS; */
/* 	avi->odd_fields= (rd->mode & R_ODDFIELD)?1:0; */
	
	printf("Created avi: %s\n", name);
}

void append_avi(int frame, int *pixels, int rectx, int recty)
{
	unsigned int *rt1, *rt2, *rectot;
	int x, y;
	char *cp, rt;
	
	if (avi == NULL) {
		G.afbreek = 1;
		return;
	}

	/* note that libavi free's the buffer... stupid interface - zr */
	rectot= MEM_mallocN(rectx*recty*sizeof(int), "rectot");
	rt1= rectot;
	rt2= (unsigned int*)pixels + (recty-1)*rectx;
	/* flip y and convert to abgr */
	for (y=0; y < recty; y++, rt1+= rectx, rt2-= rectx) {
		memcpy (rt1, rt2, rectx*sizeof(int));
		
		cp= (char *)rt1;
		for(x= rectx; x>0; x--) {
			rt= cp[0];
			cp[0]= cp[3];
			cp[3]= rt;
			rt= cp[1];
			cp[1]= cp[2];
			cp[2]= rt;
			cp+= 4;
		}
	}
	
	AVI_write_frame (avi, (frame-sframe), AVI_FORMAT_RGB32, rectot, rectx*recty*4);
//	printf ("added frame %3d (frame %3d in avi): ", frame, frame-sframe);
}

void end_avi(void)
{
	if (avi == NULL) return;

	AVI_close_compress (avi);
	MEM_freeN (avi);
	avi= NULL;
}
