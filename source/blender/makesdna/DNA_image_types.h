/**
 * blenlib/DNA_image_types.h (mar-2001 nzc)
 *
 * $Id: DNA_image_types.h 16366 2008-09-04 20:51:28Z blendix $ 
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
#ifndef DNA_IMAGE_TYPES_H
#define DNA_IMAGE_TYPES_H

#include "DNA_ID.h"

struct PackedFile;
struct anim;
struct ImBuf;
struct RenderResult;
struct GPUTexture;


/* ImageUser is in Texture, in Nodes, Background Image, Image Window, .... */
/* should be used in conjunction with an ID * to Image. */
typedef struct ImageUser {
	int framenr;				/* movies, sequences: current to display */
	int frames;					/* total amount of frames to use */
	int offset, sfra;			/* offset within movie, start frame in global time */
	short fie_ima, cycl;		/* fields/image in movie, cyclic flag */
	short flag, ok;
	
	short multi_index, layer, pass;	 /* listbase indices, for menu browsing or retrieve buffer */
	short menunr;					/* localized menu entry, for handling browse event */
} ImageUser;

/* iuser->flag */
#define	IMA_ANIM_ALWAYS		1
#define IMA_ANIM_REFRESHED	2
/* #define IMA_DO_PREMUL	4 */

typedef struct Image {
	ID id;
	
	char name[240];			/* file path */
	
	ListBase ibufs;					/* not written in file */
	struct GPUTexture *gputexture;	/* not written in file */
	
	/* sources from: */
	struct anim *anim;
	struct RenderResult *rr;
	
	short ok, flag;
	short source, type, pad, pad1;
	int lastframe;

	/* texture page */
	short tpageflag, totbind;
	short xrep, yrep;
	short twsta, twend;
	unsigned int bindcode;	/* only for current image... */
	unsigned int *repbind;	/* for repeat of parts of images */
	
	struct PackedFile * packedfile;
	struct PreviewImage * preview;

	float lastupdate;
	int lastused;
	short animspeed;
	
	short gen_x, gen_y, gen_type;	/* for generated images */
	
	/* display aspect - for UV editing images resized for faster openGL display */
	float aspx, aspy;
	
/*#ifdef WITH_VERSE*/
	void *vnode;		/* pointer at verse bitmap node */
/*#endif*/
} Image;


/* **************** IMAGE ********************* */

/* flag */
#define IMA_FIELDS		1
#define IMA_STD_FIELD	2
#define IMA_DO_PREMUL	4

#define	IMA_REFLECT		16
#define IMA_NOCOLLECT   32
#define IMA_ANTIALI		64
#define IMA_OLD_PREMUL	128

/* tpageflag */
#define IMA_TILES			1
#define IMA_TWINANIM		2
#define IMA_COLCYCLE		4	/* Depreciated */
#define IMA_MIPMAP_COMPLETE 8   /* all mipmap levels in OpenGL texture set? */
#define IMA_CLAMP_U		16 
#define IMA_CLAMP_V		32

/* ima->type and ima->source moved to BKE_image.h, for API */

#endif

