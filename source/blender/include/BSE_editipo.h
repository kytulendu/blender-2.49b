/**
 * $Id: BSE_editipo.h 16519 2008-09-14 12:41:42Z aligorith $
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

#ifndef BSE_EDITIPO_H
#define BSE_EDITIPO_H

struct TransVert;
struct IpoCurve;
struct BezTriple;
struct Ipo;
struct EditIpo;
struct ID;
struct ListBase;
struct Object;
struct IpoKey;
struct TransOb;
struct Tex;
struct TransInfo;

void remake_object_ipos(struct Object *ob);
char *getname_ac_ei(int nr);
char *getname_co_ei(int nr);
char *getname_ob_ei(int nr, int colipo);
char *getname_mtex_ei(int nr);
char *getname_tex_ei(int nr);
char *getname_mat_ei(int nr);
char *getname_world_ei(int nr);
char *getname_seq_ei(int nr);
char *getname_cu_ei(int nr);
char *getname_la_ei(int nr);
char *getname_cam_ei(int nr);
char *getname_snd_ei(int nr);
char *getname_fluidsim_ei(int nr);
char *getname_part_ei(int nr);

char *getname_ipocurve(struct IpoCurve *icu, struct Object *ob);
int geticon_ipo_blocktype(short blocktype);

struct EditIpo *get_active_editipo(void);

void boundbox_ipocurve(struct IpoCurve *icu, int selectedonly);
void boundbox_ipo(struct Ipo *ipo, struct rctf *bb, int selectedonly);
void editipo_changed(struct SpaceIpo *si, int doredraw);
void scale_editipo(void);

unsigned int ipo_rainbow(int cur, int tot);

void test_editipo(int doit);
void get_status_editipo(void);
void update_editipo_flags(void);
void set_editflag_editipo(void);
void ipo_toggle_showkey(void);
void swap_selectall_editipo(void);
void swap_visible_editipo(void);
void deselectall_editipo(void);

void move_to_frame(void);
void do_ipowin_buts(short event);
void do_ipo_selectbuttons(void);


/* gets ipo curve, creates if needed */
struct IpoCurve *verify_ipocurve(struct ID *, short, char *, char *, char *, int, short);
struct Ipo *verify_ipo(struct ID *, short, char *, char *, char *, short);
int texchannel_to_adrcode(int channel);


void add_duplicate_editipo(void);
void remove_doubles_ipo(void);
void clean_ipo(void);
void clean_ipo_curve(struct IpoCurve *icu);
void smooth_ipo(void);
void join_ipo_menu(void);
void join_ipo(int mode);
void ipo_snap_menu(void);
void ipo_snap(short event);
void ipo_mirror_menu(void);
void ipo_mirror(short event);
void mouse_select_ipo(void);
void sethandles_ipo(int code);
void select_ipo_bezier_keys(struct Ipo *ipo, int selectmode);
void select_icu_bezier_keys(struct IpoCurve *icu, int selectmode);
void set_ipotype(void);
void set_ipoextend(void);
void borderselect_ipo(void);
void del_ipo(int need_check);
void del_ipoCurve ( struct IpoCurve * icu );
void free_ipocopybuf(void);
void copy_editipo(void);
void paste_editipo(void);

void set_exprap_ipo(int mode);

void set_speed_editipo(float speed);
void insertkey_editipo(void);
void add_vert_ipo(void);
void free_ipokey(struct ListBase *lb);
void add_to_ipokey(struct ListBase *lb, struct BezTriple *bezt, int nr, int len);
void make_ipokey(void);
void make_ipokey_spec(struct ListBase *lb, struct Ipo *ipo);
void make_ipokey_transform(struct Object *ob, struct ListBase *lb, int sel);
void update_ipokey_val(void);
void set_tob_old(float *old, float *poin);
void set_ipo_pointers_transob(struct IpoKey *ik, struct TransOb *tob);
void nextkey(struct ListBase *elems, int dir);
void movekey_ipo(int dir);
void movekey_obipo(int dir);
void nextkey_ipo(int dir);
void nextkey_obipo(int dir);
void filter_sampledata(float *data, int sfra, int efra);
void sampledata_to_ipocurve(float *data, int sfra, int efra, struct IpoCurve *icu);
void ipo_record(void); 

void make_ipo_transdata(struct TransInfo *t);
void remake_ipo_transdata(struct TransInfo *t);
void transform_ipo(int mode);   

void actstrip_map_ipo_keys(struct Object *ob, struct Ipo *ipo, short restore, short only_keys);

void sethandles_ipo_keys(struct Ipo *ipo, int code);
void snap_cfra_ipo_keys(struct Ipo *ipo, short mode);
void snap_ipo_keys(struct Ipo *ipo, short snaptype);
void mirror_ipo_keys(struct Ipo *ipo, short mirror_mode);
void setipotype_ipo(struct Ipo *ipo, int code);
void set_ipo_key_selection(struct Ipo *ipo, int sel);
int is_ipo_key_selected(struct Ipo *ipo);
void delete_icu_key(struct IpoCurve *icu, int index, short do_recalc);
void delete_ipo_keys(struct Ipo *ipo);
int fullselect_ipo_keys(struct Ipo *ipo);
int add_trans_ipo_keys(struct Ipo *ipo, struct TransVert *tv, int tvtot);
void duplicate_ipo_keys(struct Ipo *ipo);
void borderselect_ipo_key(struct Ipo *ipo, float xmin, float xmax, int val);
void borderselect_icu_key(struct IpoCurve *icu, float xmin, float xmax, 
						  int (*select_function)(struct BezTriple *));
void select_ipo_key(struct Ipo *ipo, float selx, int sel);
void select_icu_key(struct IpoCurve *icu, float selx, int selectmode);
void setexprap_ipoloop(struct Ipo *ipo, int code);

/* callbacks */
int select_bezier_add(struct BezTriple *bezt);
int select_bezier_subtract(struct BezTriple *bezt);
int select_bezier_invert(struct BezTriple *bezt);

#endif /*  BSE_EDITIPO_H */

