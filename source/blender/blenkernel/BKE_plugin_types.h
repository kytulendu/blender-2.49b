/**
 * blenlib/BKE_plugin_types.h (mar-2001 nzc)
 *
 * Renderrecipe and scene decription. The fact that there is a
 * hierarchy here is a bit strange, and not desirable.
 *
 * $Id: BKE_plugin_types.h 14463 2008-04-18 19:10:03Z sirdude $ 
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
#ifndef BKE_PLUGIN_TYPES_H
#define BKE_PLUGIN_TYPES_H

struct ImBuf;

typedef	int (*TexDoitold)(int stype, void *cast, float *texvec, float *dxt, float *dyt);
typedef	int (*TexDoit)(int stype, void *cast, float *texvec, float *dxt, float *dyt, float *result );
typedef void (*SeqDoit)(void*, float, float, int, int,
						struct ImBuf*, struct ImBuf*,
						struct ImBuf*, struct ImBuf*);

typedef struct VarStruct {
	int type;
	char name[16];
	float def, min, max;
	char tip[80];
} VarStruct;

typedef struct _PluginInfo {
	char *name;
	char *snames;

	int stypes;
	int nvars;
	VarStruct *varstr;
	float *result;
	float *cfra;

	void (*init)(void);
	void (*callback)(int);
	void (*tex_doit)(void *);
	SeqDoit seq_doit;
	void (*instance_init)(void *);
} PluginInfo;

#endif

