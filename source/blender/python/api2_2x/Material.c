/* 
 * $Id: Material.c 22742 2009-08-24 10:37:39Z campbellbarton $
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
 * This is a new part of Blender.
 *
 * Contributor(s): Willian P. Germano, Michel Selten, Alex Mole,
 * Alexander Szakaly, Campbell Barton, Ken Hughes
 *
 * ***** END GPL LICENSE BLOCK *****
*/

#include "Material.h" /*This must come first*/

#include "DNA_space_types.h"
#include "DNA_material_types.h"
#include "DNA_userdef_types.h"
#include "BKE_main.h"
#include "BKE_global.h"
#include "BKE_library.h"
#include "BKE_material.h"
#include "BKE_texture.h"
#include "BKE_node.h"
#include "BKE_idprop.h"
#include "BKE_utildefines.h" /* for CLAMP */
#include "MEM_guardedalloc.h"
#include "BLI_blenlib.h"
#include "BSE_editipo.h"
#include "BIF_keyframing.h"
#include "BIF_space.h"
#include "mydevice.h"
#include "constant.h"
#include "MTex.h"
#include "Texture.h"
#include "Ipo.h"
#include "Group.h"
#include "gen_utils.h"
#include "gen_library.h"
#include "IDProp.h"

/*****************************************************************************/
/* Python BPy_Material defaults: */
/*****************************************************************************/
/* Material MIN, MAX values */
#define EXPP_MAT_ADD_MIN			 0.0f
#define EXPP_MAT_ADD_MAX			 1.0f
#define EXPP_MAT_ALPHA_MIN	   0.0f
#define EXPP_MAT_ALPHA_MAX		 1.0f
#define EXPP_MAT_AMB_MIN			 0.0f
#define EXPP_MAT_AMB_MAX			 1.0f
#define EXPP_MAT_COL_MIN			 0.0f /* min/max for all ... */
#define EXPP_MAT_COL_MAX			 1.0f /* ... color triplets  */
#define EXPP_MAT_EMIT_MIN			 0.0f
#define EXPP_MAT_EMIT_MAX			 1.0f
#define EXPP_MAT_REF_MIN			 0.0f
#define EXPP_MAT_REF_MAX			 1.0f
#define EXPP_MAT_SPEC_MIN			 0.0f
#define EXPP_MAT_SPEC_MAX			 2.0f
#define EXPP_MAT_SPECTRA_MIN	 0.0f
#define EXPP_MAT_SPECTRA_MAX	 1.0f

/* Shader specific settings */

#define EXPP_MAT_ROUGHNESS_MIN			 0.0f
#define EXPP_MAT_ROUGHNESS_MAX			 3.140f
#define EXPP_MAT_SPECSIZE_MIN			 0.0f
#define EXPP_MAT_SPECSIZE_MAX			 1.530f
#define EXPP_MAT_DIFFUSESIZE_MIN		 0.0f
#define EXPP_MAT_DIFFUSESIZE_MAX			 3.140f
#define EXPP_MAT_SPECSMOOTH_MIN			 0.0f
#define EXPP_MAT_SPECSMOOTH_MAX			 1.0f
#define EXPP_MAT_DIFFUSESMOOTH_MIN			 0.0f
#define EXPP_MAT_DIFFUSESMOOTH_MAX			 1.0f
#define EXPP_MAT_DIFFUSE_DARKNESS_MIN			 0.0f
#define EXPP_MAT_DIFFUSE_DARKNESS_MAX			 2.0f
#define EXPP_MAT_REFRACINDEX_MIN			 1.0f
#define EXPP_MAT_REFRACINDEX_MAX			 10.0f
#define EXPP_MAT_RMS_MIN			 0.0f
#define EXPP_MAT_RMS_MAX			 0.4f
/* End shader settings */

#define EXPP_MAT_ZOFFS_MIN			 0.0
#define EXPP_MAT_ZOFFS_MAX			10.0
#define EXPP_MAT_HALOSIZE_MIN			 0.0
#define EXPP_MAT_HALOSIZE_MAX		 100.0
#define EXPP_MAT_FLARESIZE_MIN		 0.1f
#define EXPP_MAT_FLARESIZE_MAX		25.0
#define EXPP_MAT_FLAREBOOST_MIN		 0.1f
#define EXPP_MAT_FLAREBOOST_MAX		10.0
#define EXPP_MAT_SUBSIZE_MIN			 0.1f
#define EXPP_MAT_SUBSIZE_MAX			25.0

#define EXPP_MAT_HARD_MIN				 1
#define EXPP_MAT_HARD_MAX		 511	/* 127 with MODE HALO ON */
#define EXPP_MAT_HALOSEED_MIN		 0
#define EXPP_MAT_HALOSEED_MAX    255
#define EXPP_MAT_NFLARES_MIN		 1
#define EXPP_MAT_NFLARES_MAX		32
#define EXPP_MAT_FLARESEED_MIN	 0
#define EXPP_MAT_FLARESEED_MAX 255
#define EXPP_MAT_NSTARS_MIN			 3
#define EXPP_MAT_NSTARS_MAX			50
#define EXPP_MAT_NLINES_MIN			 0
#define EXPP_MAT_NLINES_MAX		 250
#define EXPP_MAT_NRINGS_MIN			 0
#define EXPP_MAT_NRINGS_MAX			24

#define EXPP_MAT_RAYMIRR_MIN			 0.0
#define EXPP_MAT_RAYMIRR_MAX			 1.0
#define EXPP_MAT_MIRRDEPTH_MIN			 0
#define EXPP_MAT_MIRRDEPTH_MAX			 10
#define EXPP_MAT_FRESNELMIRR_MIN			0.0
#define EXPP_MAT_FRESNELMIRR_MAX			5.0
#define EXPP_MAT_FRESNELMIRRFAC_MIN			1.0
#define EXPP_MAT_FRESNELMIRRFAC_MAX			5.0
#define EXPP_MAT_RAYMIRRGLOSS_MIN			 0.0
#define EXPP_MAT_RAYMIRRGLOSS_MAX			 1.0
#define EXPP_MAT_RAYMIRRGLOSSSAMPLES_MIN	 0
#define EXPP_MAT_RAYMIRRGLOSSSAMPLES_MAX	 1024
#define EXPP_MAT_RAYTRANSPGLOSS_MIN			 0.0
#define EXPP_MAT_RAYTRANSPGLOSS_MAX			 1.0
#define EXPP_MAT_RAYTRANSPGLOSSSAMPLES_MIN	 0
#define EXPP_MAT_RAYTRANSPGLOSSSAMPLES_MAX	 1024
#define EXPP_MAT_ANISO_GLOSS_MIR_MIN			0.0
#define EXPP_MAT_ANISO_GLOSS_MIR_MAX			1.0
#define EXPP_MAT_ADAPT_THRESH_MIR_MIN			0.0
#define EXPP_MAT_ADAPT_THRESH_MIR_MAX			1.0
#define EXPP_MAT_ADAPT_THRESH_TRA_MIN			0.0
#define EXPP_MAT_ADAPT_THRESH_TRA_MAX			1.0
#define EXPP_MAT_FILTER_MIN			0.0
#define EXPP_MAT_FILTER_MAX			1.0
#define EXPP_MAT_TRANSLUCENCY_MIN			0.0
#define EXPP_MAT_TRANSLUCENCY_MAX			1.0
#define EXPP_MAT_ZOFFS_MIN				0.0
#define EXPP_MAT_ZOFFS_MAX				10.0
#define EXPP_MAT_IOR_MIN				1.0
#define EXPP_MAT_IOR_MAX				3.0
#define EXPP_MAT_TRANSDEPTH_MIN				0
#define EXPP_MAT_TRANSDEPTH_MAX				10
#define EXPP_MAT_FRESNELTRANS_MIN			0.0
#define EXPP_MAT_FRESNELTRANS_MAX			5.0
#define EXPP_MAT_FRESNELTRANSFAC_MIN			1.0
#define EXPP_MAT_FRESNELTRANSFAC_MAX			5.0
#define EXPP_MAT_SPECTRANS_MIN				0.0
#define EXPP_MAT_SPECTRANS_MAX				1.0
#define EXPP_MAT_MIRRTRANSADD_MIN			0.0
#define EXPP_MAT_MIRRTRANSADD_MAX			1.0
#define EXPP_MAT_COLORBAND_FACTOR_MIN		0.0
#define EXPP_MAT_COLORBAND_FACTOR_MAX		1.0

/* closure values for getColorComponent()/setColorComponent() */

#define	EXPP_MAT_COMP_R		0
#define	EXPP_MAT_COMP_G		1
#define	EXPP_MAT_COMP_B		2
#define	EXPP_MAT_COMP_SPECR	3
#define	EXPP_MAT_COMP_SPECG	4
#define	EXPP_MAT_COMP_SPECB	5
#define	EXPP_MAT_COMP_MIRR	6
#define	EXPP_MAT_COMP_MIRG	7
#define	EXPP_MAT_COMP_MIRB	8
#define	EXPP_MAT_COMP_SSSR	9
#define	EXPP_MAT_COMP_SSSG	10
#define	EXPP_MAT_COMP_SSSB	11


#define IPOKEY_RGB          0
#define IPOKEY_ALPHA        1 
#define IPOKEY_HALOSIZE     2 
#define IPOKEY_MODE         3
#define IPOKEY_ALLCOLOR     10
#define IPOKEY_ALLMIRROR    14
#define IPOKEY_OFS          12
#define IPOKEY_SIZE         13
#define IPOKEY_ALLMAPPING   11

/* SSS Settings */
#define EXPP_MAT_SSS_SCALE_MIN			0.001
#define EXPP_MAT_SSS_SCALE_MAX			1000.0
#define EXPP_MAT_SSS_RADIUS_MIN			0.0
#define EXPP_MAT_SSS_RADIUS_MAX			10000.0
#define EXPP_MAT_SSS_IOR_MIN			0.1
#define EXPP_MAT_SSS_IOR_MAX			2.0
#define EXPP_MAT_SSS_ERROR_MIN			0.0
#define EXPP_MAT_SSS_ERROR_MAX			1.0
#define EXPP_MAT_SSS_FRONT_MIN			0.0
#define EXPP_MAT_SSS_FRONT_MAX			2.0
#define EXPP_MAT_SSS_BACK_MIN			0.0
#define EXPP_MAT_SSS_BACK_MAX			10.0


/*****************************************************************************/
/* Python API function prototypes for the Material module.                   */
/*****************************************************************************/
static PyObject *M_Material_New( PyObject * self, PyObject * args,
				 PyObject * keywords );
static PyObject *M_Material_Get( PyObject * self, PyObject * args );

/*****************************************************************************/
/* The following string definitions are used for documentation strings.  In  */
/* Python these will be written to the console when doing a                  */
/* Blender.Material.__doc__                                                  */
/*****************************************************************************/
static char M_Material_doc[] = "The Blender Material module";

static char M_Material_New_doc[] =
	"(name) - return a new material called 'name'\n\
() - return a new material called 'Mat'";

static char M_Material_Get_doc[] =
	"(name) - return the material called 'name', None if not found.\n\
() - return a list of all materials in the current scene.";

/*****************************************************************************/
/* Python method structure definition for Blender.Material module:           */
/*****************************************************************************/
struct PyMethodDef M_Material_methods[] = {
	{"New", ( PyCFunction ) M_Material_New, METH_VARARGS | METH_KEYWORDS,
	 M_Material_New_doc},
	{"Get", M_Material_Get, METH_VARARGS, M_Material_Get_doc},
	{"get", M_Material_Get, METH_VARARGS, M_Material_Get_doc},
	{NULL, NULL, 0, NULL}
};

/*****************************************************************************/
/* Function:	M_Material_New                                               */
/* Python equivalent:		Blender.Material.New                             */
/*****************************************************************************/
static PyObject *M_Material_New( PyObject * self, PyObject * args,
				 PyObject * keywords )
{
	char *name = "Mat";
	static char *kwlist[] = { "name", NULL };
	BPy_Material *pymat; /* for Material Data object wrapper in Python */
	Material *blmat; /* for actual Material Data we create in Blender */
	char buf[21];

	if( !PyArg_ParseTupleAndKeywords
	    ( args, keywords, "|s", kwlist, &name ) )
		return ( EXPP_ReturnPyObjError
			 ( PyExc_AttributeError,
			   "expected string or nothing as argument" ) );

	if( strcmp( name, "Mat" ) != 0 )	/* use gave us a name ? */
		PyOS_snprintf( buf, sizeof( buf ), "%s", name );

	blmat = add_material( name );	/* first create the Material Data in Blender */

	if( blmat )		/* now create the wrapper obj in Python */
		pymat = ( BPy_Material * ) Material_CreatePyObject( blmat );
	else
		return ( EXPP_ReturnPyObjError( PyExc_RuntimeError,
						"couldn't create Material Data in Blender" ) );

	blmat->id.us = 0;	/* was incref'ed by add_material() above */

	if( pymat == NULL )
		return ( EXPP_ReturnPyObjError( PyExc_MemoryError,
						"couldn't create Material Data object" ) );

	return ( PyObject * ) pymat;
}

/*****************************************************************************/
/* Function:	M_Material_Get	 */
/* Python equivalent:	Blender.Material.Get */
/* Description:		Receives a string and returns the material whose */
/*			name matches the string.	If no argument is */
/*			passed in, a list with all materials in the	 */
/*			current scene is returned.			 */
/*****************************************************************************/
static PyObject *M_Material_Get( PyObject * self, PyObject * args )
{
	char *name = NULL;
	Material *mat_iter;

	if( !PyArg_ParseTuple( args, "|s", &name ) )
		return ( EXPP_ReturnPyObjError( PyExc_TypeError,
						"expected string argument (or nothing)" ) );

	if( name ) {		/* (name) - Search material by name */

		mat_iter = ( Material * ) GetIdFromList( &( G.main->mat ), name );

		if( mat_iter == NULL ) { /* Requested material doesn't exist */
			char error_msg[64];
			PyOS_snprintf( error_msg, sizeof( error_msg ),
				       "Material \"%s\" not found", name );
			return EXPP_ReturnPyObjError( PyExc_NameError,
						      error_msg );
		}

		return Material_CreatePyObject( mat_iter );
	}

	else {			/* () - return a list with all materials in the scene */
		int index = 0;
		PyObject *matlist, *pyobj;
	
		matlist = PyList_New( BLI_countlist( &( G.main->mat ) ) );

		if( !matlist )
			return ( EXPP_ReturnPyObjError( PyExc_MemoryError,
							"couldn't create PyList" ) );
		
		mat_iter = G.main->mat.first;
		while( mat_iter ) {
			pyobj = Material_CreatePyObject( mat_iter );

			if( !pyobj ) {
				Py_DECREF(matlist);
				return ( EXPP_ReturnPyObjError
					 ( PyExc_MemoryError,
					   "couldn't create PyObject" ) );
			}
			PyList_SET_ITEM( matlist, index, pyobj );

			mat_iter = mat_iter->id.next;
			index++;
		}

		return matlist;
	}
}

static PyObject *Material_ShadeModesDict( void )
{
	PyObject *ShadeModes = PyConstant_New(  );
	
	if( ShadeModes ) {
		BPy_constant *c = ( BPy_constant * ) ShadeModes;
		
		PyConstant_Insert(c, "CUBIC",   PyInt_FromLong(MA_CUBIC));
		PyConstant_Insert(c, "OBCOLOR", PyInt_FromLong(MA_OBCOLOR));
	}
	
	return ShadeModes;
}

static PyObject *Material_ModesDict( void )
{
	PyObject *Modes = PyConstant_New(  );

	if( Modes ) {
		BPy_constant *c = ( BPy_constant * ) Modes;

		PyConstant_Insert(c, "TRACEABLE", PyInt_FromLong(MA_TRACEBLE));
		PyConstant_Insert(c, "SHADOW", PyInt_FromLong(MA_SHADOW));
		PyConstant_Insert(c, "SHADOWBUF", PyInt_FromLong(MA_SHADBUF));
		PyConstant_Insert(c, "TANGENTSTR", PyInt_FromLong(MA_TANGENT_STR));
		PyConstant_Insert(c, "FULLOSA", PyInt_FromLong(MA_FULL_OSA));
		PyConstant_Insert(c, "RAYBIAS", PyInt_FromLong(MA_RAYBIAS));
		PyConstant_Insert(c, "TRANSPSHADOW", PyInt_FromLong(MA_SHADOW_TRA));
		PyConstant_Insert(c, "RAMPCOL", PyInt_FromLong(MA_RAMP_COL));
		PyConstant_Insert(c, "RAMPSPEC", PyInt_FromLong(MA_RAMP_SPEC));
		PyConstant_Insert(c, "SHADELESS", PyInt_FromLong(MA_SHLESS));
		PyConstant_Insert(c, "WIRE", PyInt_FromLong(MA_WIRE));
		PyConstant_Insert(c, "VCOL_LIGHT", PyInt_FromLong(MA_VERTEXCOL));
		PyConstant_Insert(c, "HALO", PyInt_FromLong(MA_HALO));
		PyConstant_Insert(c, "ZTRANSP", PyInt_FromLong(MA_ZTRA));
		PyConstant_Insert(c, "VCOL_PAINT", PyInt_FromLong(MA_VERTEXCOLP));
		PyConstant_Insert(c, "ZINVERT", PyInt_FromLong(MA_ZINV));
		PyConstant_Insert(c, "HALORINGS", PyInt_FromLong(MA_HALO_RINGS));
		PyConstant_Insert(c, "ENV", PyInt_FromLong(MA_ENV));
		PyConstant_Insert(c, "HALOLINES", PyInt_FromLong(MA_HALO_LINES));
		PyConstant_Insert(c, "ONLYSHADOW", PyInt_FromLong(MA_ONLYSHADOW));
		PyConstant_Insert(c, "HALOXALPHA", PyInt_FromLong(MA_HALO_XALPHA));
		PyConstant_Insert(c, "HALOSTAR", PyInt_FromLong(MA_STAR));
		PyConstant_Insert(c, "TEXFACE", PyInt_FromLong(MA_FACETEXTURE));
		PyConstant_Insert(c, "HALOTEX", PyInt_FromLong(MA_HALOTEX));
		PyConstant_Insert(c, "HALOPUNO", PyInt_FromLong(MA_HALOPUNO));
		PyConstant_Insert(c, "NOMIST", PyInt_FromLong(MA_NOMIST));
		PyConstant_Insert(c, "HALOSHADE", PyInt_FromLong(MA_HALO_SHADE));
		PyConstant_Insert(c, "HALOFLARE", PyInt_FromLong(MA_HALO_FLARE));
		PyConstant_Insert(c, "RADIO", PyInt_FromLong(MA_RADIO));
		PyConstant_Insert(c, "RAYMIRROR", PyInt_FromLong(MA_RAYMIRROR));
		PyConstant_Insert(c, "ZTRA", PyInt_FromLong(MA_ZTRA));
		PyConstant_Insert(c, "RAYTRANSP", PyInt_FromLong(MA_RAYTRANSP));
		PyConstant_Insert(c, "TANGENT_V", PyInt_FromLong(MA_TANGENT_V));
		PyConstant_Insert(c, "NMAP_TS", PyInt_FromLong(MA_NORMAP_TANG));
		PyConstant_Insert(c, "GROUP_EXCLUSIVE", PyInt_FromLong(MA_GROUP_NOLAY));
		PyConstant_Insert(c, "TEXFACE_ALPHA", PyInt_FromLong(MA_FACETEXTURE_ALPHA));
		
	}

	return Modes;
}


static PyObject *Material_ShadersDict( void )
{
	PyObject *Shaders = PyConstant_New(  );

	if( Shaders ) {
		BPy_constant *c = ( BPy_constant * ) Shaders;

		PyConstant_Insert(c, "DIFFUSE_LAMBERT", PyInt_FromLong(MA_DIFF_LAMBERT));
		PyConstant_Insert(c, "DIFFUSE_ORENNAYAR", PyInt_FromLong(MA_DIFF_ORENNAYAR));
		PyConstant_Insert(c, "DIFFUSE_TOON", PyInt_FromLong(MA_DIFF_TOON));
		PyConstant_Insert(c, "DIFFUSE_MINNAERT", PyInt_FromLong(MA_DIFF_MINNAERT));
		PyConstant_Insert(c, "SPEC_COOKTORR", PyInt_FromLong(MA_SPEC_COOKTORR));
		PyConstant_Insert(c, "SPEC_PHONG", PyInt_FromLong(MA_SPEC_PHONG));
		PyConstant_Insert(c, "SPEC_BLINN", PyInt_FromLong(MA_SPEC_BLINN));
		PyConstant_Insert(c, "SPEC_TOON", PyInt_FromLong(MA_SPEC_TOON));
		PyConstant_Insert(c, "SPEC_WARDISO", PyInt_FromLong(MA_SPEC_WARDISO));

	}

	return Shaders;
}

static PyObject *Material_ColorRampMethodsDict( void )
{
	PyObject *Methods = PyConstant_New(  );
	if( Methods ) {
		BPy_constant *c = (BPy_constant * ) Methods;

		PyConstant_Insert(c, "BLEND", PyInt_FromLong(MA_RAMP_BLEND));
		PyConstant_Insert(c, "MIX", PyInt_FromLong(MA_RAMP_BLEND)); /* This one is added to solve confusion between Blend-Mix name. */
		PyConstant_Insert(c, "ADD", PyInt_FromLong(MA_RAMP_ADD));
		PyConstant_Insert(c, "MULT", PyInt_FromLong(MA_RAMP_MULT));
		PyConstant_Insert(c, "SUB", PyInt_FromLong(MA_RAMP_SUB));
		PyConstant_Insert(c, "SCREEN", PyInt_FromLong(MA_RAMP_SCREEN));
		PyConstant_Insert(c, "DIV", PyInt_FromLong(MA_RAMP_DIV));
		PyConstant_Insert(c, "DIFF", PyInt_FromLong(MA_RAMP_DIFF));
		PyConstant_Insert(c, "DARK", PyInt_FromLong(MA_RAMP_DARK));
		PyConstant_Insert(c, "LIGHT", PyInt_FromLong(MA_RAMP_LIGHT));
		PyConstant_Insert(c, "OVERLAY", PyInt_FromLong(MA_RAMP_OVERLAY));
		PyConstant_Insert(c, "DODGE", PyInt_FromLong(MA_RAMP_DODGE));
		PyConstant_Insert(c, "BURN", PyInt_FromLong(MA_RAMP_BURN));
		PyConstant_Insert(c, "HUE", PyInt_FromLong(MA_RAMP_HUE));
		PyConstant_Insert(c, "SAT", PyInt_FromLong(MA_RAMP_SAT));
		PyConstant_Insert(c, "VAL", PyInt_FromLong(MA_RAMP_VAL));
		PyConstant_Insert(c, "COLOR", PyInt_FromLong(MA_RAMP_COLOR));

	}
	return Methods;
}

static PyObject *Material_ColorRampInputDict( void )
{
	PyObject *Inputs = PyConstant_New(  );
	if( Inputs ) {
		BPy_constant *c = (BPy_constant * ) Inputs;

		PyConstant_Insert(c, "SHADER", PyInt_FromLong(MA_RAMP_IN_SHADER));
		PyConstant_Insert(c, "ENERGY", PyInt_FromLong(MA_RAMP_IN_ENERGY));
		PyConstant_Insert(c, "NORMAL", PyInt_FromLong(MA_RAMP_IN_NOR));
		PyConstant_Insert(c, "RESULT", PyInt_FromLong(MA_RAMP_IN_RESULT));
	}
	return Inputs;
}

/*****************************************************************************/
/* Function:	Material_Init */
/*****************************************************************************/
PyObject *Material_Init( void )
{
	PyObject *submodule, *Modes, *ShadeModes, *Shaders, *ColorbandInput, *ColorbandMethod;

	if( PyType_Ready( &Material_Type ) < 0)
		return NULL;

	Modes = Material_ModesDict(  );
	ShadeModes = Material_ShadeModesDict(  );
	Shaders = Material_ShadersDict(  );
	ColorbandMethod = Material_ColorRampMethodsDict(  );
	ColorbandInput = Material_ColorRampInputDict(  );

	submodule = Py_InitModule3( "Blender.Material",
				    M_Material_methods, M_Material_doc );

	if( Modes )
		PyModule_AddObject( submodule, "Modes", Modes );
	if( ShadeModes )
		PyModule_AddObject( submodule, "ShadeModes", ShadeModes );
	if( Shaders )
		PyModule_AddObject( submodule, "Shaders", Shaders );
	if( ColorbandMethod )
		PyModule_AddObject( submodule, "ColorbandMethod", ColorbandMethod );
	if( ColorbandInput )
		PyModule_AddObject( submodule, "ColorbandInput", ColorbandInput );
	
	PyModule_AddIntConstant( submodule, "RGB", IPOKEY_RGB );
	PyModule_AddIntConstant( submodule, "ALPHA", IPOKEY_ALPHA );
	PyModule_AddIntConstant( submodule, "HALOSIZE", IPOKEY_HALOSIZE );
	PyModule_AddIntConstant( submodule, "MODE", IPOKEY_MODE );
	PyModule_AddIntConstant( submodule, "ALLCOLOR", IPOKEY_ALLCOLOR );
	PyModule_AddIntConstant( submodule, "ALLMIRROR", IPOKEY_ALLMIRROR );
	PyModule_AddIntConstant( submodule, "OFS", IPOKEY_OFS );
	PyModule_AddIntConstant( submodule, "SIZE", IPOKEY_SIZE );
	PyModule_AddIntConstant( submodule, "ALLMAPPING", IPOKEY_ALLMAPPING );

	return ( submodule );
}

/***************************/
/*** The Material PyType ***/
/***************************/

static PyObject *Matr_oldsetAdd( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetAlpha( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetAmb( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetEmit( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetFilter( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetFlareBoost( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetFlareSeed( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetFlareSize( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetFresnelMirr( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetFresnelMirrFac( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetFresnelTrans( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetFresnelTransFac( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetHaloSeed( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetHaloSize( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetHardness( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetIOR( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetNFlares( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetNLines( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetNRings( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetNStars( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetRayMirr( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetMirrDepth( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetRef( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetSpec( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetSpecTransp( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetSubSize( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetTransDepth( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetZOffset( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetMode( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetIpo( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetRGBCol( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetSpecCol( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetSpecShader( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetMirCol( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetDiffuseShader( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetRoughness( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetSpecSize( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetDiffuseSize( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetSpecSmooth( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetDiffuseSmooth( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetDiffuseDarkness( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetRefracIndex( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetRms( BPy_Material * self, PyObject * args );
static PyObject *Matr_oldsetTranslucency( BPy_Material * self, PyObject * args );

static int Material_setIpo( BPy_Material * self, PyObject * value );

static int Material_setMode( BPy_Material * self, PyObject * value );
static int Material_setShadeMode( BPy_Material * self, PyObject * value );
static int Material_setRGBCol( BPy_Material * self, PyObject * value );
static int Material_setSpecCol( BPy_Material * self, PyObject * value );
static int Material_setMirCol( BPy_Material * self, PyObject * value );
static int Material_setSssCol( BPy_Material * self, PyObject * value );
static int Material_setColorComponent( BPy_Material * self, PyObject * value,
							void * closure );
static int Material_setAmb( BPy_Material * self, PyObject * value );
static int Material_setEmit( BPy_Material * self, PyObject * value );
static int Material_setSpecTransp( BPy_Material * self, PyObject * value );
static int Material_setAlpha( BPy_Material * self, PyObject * value );
static int Material_setShadAlpha( BPy_Material * self, PyObject * value );
static int Material_setRef( BPy_Material * self, PyObject * value );
static int Material_setSpec( BPy_Material * self, PyObject * value );
static int Material_setZOffset( BPy_Material * self, PyObject * value );
static int Material_setLightGroup( BPy_Material * self, PyObject * value );
static int Material_setAdd( BPy_Material * self, PyObject * value );
static int Material_setHaloSize( BPy_Material * self, PyObject * value );
static int Material_setFlareSize( BPy_Material * self, PyObject * value );
static int Material_setFlareBoost( BPy_Material * self, PyObject * value );
static int Material_setSubSize( BPy_Material * self, PyObject * value );
static int Material_setHaloSeed( BPy_Material * self, PyObject * value );
static int Material_setFlareSeed( BPy_Material * self, PyObject * value );
static int Material_setHardness( BPy_Material * self, PyObject * value );
static int Material_setNFlares( BPy_Material * self, PyObject * value );
static int Material_setNStars( BPy_Material * self, PyObject * value );
static int Material_setNLines( BPy_Material * self, PyObject * value );
static int Material_setNRings( BPy_Material * self, PyObject * value );
static int Material_setRayMirr( BPy_Material * self, PyObject * value );
static int Material_setMirrDepth( BPy_Material * self, PyObject * value );
static int Material_setFresnelMirr( BPy_Material * self, PyObject * value );
static int Material_setFresnelMirrFac( BPy_Material * self, PyObject * value );
static int Material_setIOR( BPy_Material * self, PyObject * value );
static int Material_setTransDepth( BPy_Material * self, PyObject * value );
static int Material_setFresnelTrans( BPy_Material * self, PyObject * value );
static int Material_setFresnelTransFac( BPy_Material * self, PyObject * value );
static int Material_setGlossMirr( BPy_Material * self, PyObject * value );
static int Material_setGlossMirrSamples( BPy_Material * self, PyObject * value );
static int Material_setGlossTrans( BPy_Material * self, PyObject * value );
static int Material_setGlossTransSamples( BPy_Material * self, PyObject * value );
static int Material_setAniso( BPy_Material * self, PyObject * value );
static int Material_setThreshMirr( BPy_Material * self, PyObject * value );
static int Material_setThreshTrans( BPy_Material * self, PyObject * value );
static int Material_setRigidBodyFriction( BPy_Material * self, PyObject * value );
static int Material_setRigidBodyRestitution( BPy_Material * self, PyObject * value );

static int Material_setSpecShader( BPy_Material * self, PyObject * value );
static int Material_setDiffuseShader( BPy_Material * self, PyObject * value );
static int Material_setRoughness( BPy_Material * self, PyObject * value );
static int Material_setSpecSize( BPy_Material * self, PyObject * value );
static int Material_setDiffuseSize( BPy_Material * self, PyObject * value );
static int Material_setSpecSmooth( BPy_Material * self, PyObject * value );
static int Material_setDiffuseSmooth( BPy_Material * self, PyObject * value );
static int Material_setDiffuseDarkness( BPy_Material * self, PyObject * value );
static int Material_setRefracIndex( BPy_Material * self, PyObject * value );
static int Material_setRms( BPy_Material * self, PyObject * value );
static int Material_setFilter( BPy_Material * self, PyObject * value );
static int Material_setTranslucency( BPy_Material * self, PyObject * value );

static int Material_setSssEnable( BPy_Material * self, PyObject * value );
static int Material_setSssScale( BPy_Material * self, PyObject * value );
static int Material_setSssRadius( BPy_Material * self, PyObject * value, void * type );
static int Material_setSssIOR( BPy_Material * self, PyObject * value );
static int Material_setSssError( BPy_Material * self, PyObject * value );
static int Material_setSssColorBlend( BPy_Material * self, PyObject * value );
static int Material_setSssTexScatter( BPy_Material * self, PyObject * value );
static int Material_setSssFront( BPy_Material * self, PyObject * value );
static int Material_setSssBack( BPy_Material * self, PyObject * value );
static int Material_setSssBack( BPy_Material * self, PyObject * value );
static int Material_setTexChannel( BPy_Material * self, PyObject * value );
static int Material_setTextures( BPy_Material * self, PyObject * value );

static PyObject *Material_getColorComponent( BPy_Material * self,
							void * closure );

/*static int Material_setSeptex( BPy_Material * self, PyObject * value );
  static PyObject *Material_getSeptex( BPy_Material * self );*/

/*****************************************************************************/
/* Python BPy_Material methods declarations: */
/*****************************************************************************/
static PyObject *Material_getIpo( BPy_Material * self );
static PyObject *Material_getMode( BPy_Material * self );
static PyObject *Material_getShadeMode( BPy_Material * self );
static PyObject *Material_getRGBCol( BPy_Material * self );
/*static PyObject *Material_getAmbCol(BPy_Material *self);*/
static PyObject *Material_getSpecCol( BPy_Material * self );
static PyObject *Material_getMirCol( BPy_Material * self );
static PyObject *Material_getSssCol( BPy_Material * self );
static PyObject *Material_getAmb( BPy_Material * self );
static PyObject *Material_getEmit( BPy_Material * self );
static PyObject *Material_getAlpha( BPy_Material * self );
static PyObject *Material_getShadAlpha( BPy_Material * self );
static PyObject *Material_getRef( BPy_Material * self );
static PyObject *Material_getSpec( BPy_Material * self );
static PyObject *Material_getSpecTransp( BPy_Material * self );
static PyObject *Material_getAdd( BPy_Material * self );
static PyObject *Material_getZOffset( BPy_Material * self );
static PyObject *Material_getLightGroup( BPy_Material * self );
static PyObject *Material_getHaloSize( BPy_Material * self );
static PyObject *Material_getHaloSeed( BPy_Material * self );
static PyObject *Material_getFlareSize( BPy_Material * self );
static PyObject *Material_getFlareSeed( BPy_Material * self );
static PyObject *Material_getFlareBoost( BPy_Material * self );
static PyObject *Material_getSubSize( BPy_Material * self );
static PyObject *Material_getHardness( BPy_Material * self );
static PyObject *Material_getNFlares( BPy_Material * self );
static PyObject *Material_getNStars( BPy_Material * self );
static PyObject *Material_getNLines( BPy_Material * self );
static PyObject *Material_getNRings( BPy_Material * self );
/* Shader settings */
static PyObject *Material_getSpecShader( BPy_Material * self );
static PyObject *Material_getDiffuseShader( BPy_Material * self );
static PyObject *Material_getRoughness( BPy_Material * self );
static PyObject *Material_getSpecSize( BPy_Material * self );
static PyObject *Material_getDiffuseSize( BPy_Material * self );
static PyObject *Material_getSpecSmooth( BPy_Material * self );
static PyObject *Material_getDiffuseSmooth( BPy_Material * self );
static PyObject *Material_getDiffuseDarkness( BPy_Material * self );
static PyObject *Material_getRefracIndex( BPy_Material * self );
static PyObject *Material_getRms( BPy_Material * self );

static PyObject *Material_getRayMirr( BPy_Material * self );
static PyObject *Material_getMirrDepth( BPy_Material * self );
static PyObject *Material_getFresnelMirr( BPy_Material * self );
static PyObject *Material_getFresnelMirrFac( BPy_Material * self );
static PyObject *Material_getIOR( BPy_Material * self );
static PyObject *Material_getTransDepth( BPy_Material * self );
static PyObject *Material_getFresnelTrans( BPy_Material * self );
static PyObject *Material_getFresnelTransFac( BPy_Material * self );
static PyObject *Material_getGlossMirr( BPy_Material * self );
static PyObject *Material_getGlossMirrSamples( BPy_Material * self );
static PyObject *Material_getGlossTrans( BPy_Material * self );
static PyObject *Material_getGlossTransSamples( BPy_Material * self );
static PyObject *Material_getAniso( BPy_Material * self );
static PyObject *Material_getThreshMirr( BPy_Material * self );
static PyObject *Material_getThreshTrans( BPy_Material * self );
static PyObject *Material_getRigidBodyFriction( BPy_Material * self );
static PyObject *Material_getRigidBodyRestitution( BPy_Material * self );

static PyObject *Material_getSssEnable( BPy_Material * self );
static PyObject *Material_getSssScale( BPy_Material * self );
static PyObject *Material_getSssRadius( BPy_Material * self, void * type );
static PyObject *Material_getSssIOR( BPy_Material * self );
static PyObject *Material_getSssError( BPy_Material * self );
static PyObject *Material_getSssColorBlend( BPy_Material * self );
static PyObject *Material_getSssTexScatter( BPy_Material * self );
static PyObject *Material_getSssFront( BPy_Material * self );
static PyObject *Material_getSssBack( BPy_Material * self );
static PyObject *Material_getSssBack( BPy_Material * self );

static PyObject *Material_getFilter( BPy_Material * self );
static PyObject *Material_getTranslucency( BPy_Material * self );
static PyObject *Material_getTextures( BPy_Material * self );
static PyObject *Material_getTexChannel( BPy_Material * self );
static PyObject *Material_clearIpo( BPy_Material * self );

static PyObject *Material_setTexture( BPy_Material * self, PyObject * args );
static PyObject *Material_clearTexture( BPy_Material * self, PyObject * value );

static PyObject *Material_getScriptLinks(BPy_Material *self, PyObject * value );
static PyObject *Material_addScriptLink(BPy_Material * self, PyObject * args );
static PyObject *Material_clearScriptLinks(BPy_Material *self, PyObject *args);

static PyObject *Material_insertIpoKey( BPy_Material * self, PyObject * args );
static PyObject *Material_getColorband( BPy_Material * self, void * type);
static int Material_setColorband( BPy_Material * self, PyObject * value, void * type);
static PyObject *Material_copy( BPy_Material * self );
static PyObject *Material_freeNodes( BPy_Material * self );

static PyObject *Material_getColorbandDiffuseFactor( BPy_Material * self );
static PyObject *Material_getColorbandSpecularFactor( BPy_Material * self );
static int Material_setColorbandDiffuseFactor ( BPy_Material * self, PyObject * value );
static int Material_setColorbandSpecularFactor ( BPy_Material * self, PyObject * value );
static PyObject *Material_getColorbandDiffuseMethod( BPy_Material * self );
static PyObject *Material_getColorbandSpecularMethod ( BPy_Material * self );
static int Material_setColorbandDiffuseMethod ( BPy_Material * self, PyObject * value);
static int Material_setColorbandSpecularMethod ( BPy_Material * self, PyObject * value);
static PyObject *Material_getColorbandDiffuseInput( BPy_Material * self );
static PyObject *Material_getColorbandSpecularInput( BPy_Material * self );
static int Material_setColorbandDiffuseInput ( BPy_Material * self, PyObject * value);
static int Material_setColorbandSpecularInput ( BPy_Material * self, PyObject * value);

static PyObject *Material_getStrandTangentShad( BPy_Material * self );
static int Material_setStrandTangentShad( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandSurfDiff( BPy_Material * self );
static int Material_setStrandSurfDiff( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandDist( BPy_Material * self );
static int Material_setStrandDist( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandBlendUnit( BPy_Material * self );
static int Material_setStrandBlendUnit( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandStart( BPy_Material * self );
static int Material_setStrandStart( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandEnd( BPy_Material * self );
static int Material_setStrandEnd( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandMin( BPy_Material * self );
static int Material_setStrandMin( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandShape( BPy_Material * self );
static int Material_setStrandShape( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandWidthFad( BPy_Material * self );
static int Material_setStrandWidthFad( BPy_Material * self, PyObject * value);
static PyObject *Material_getStrandUV( BPy_Material * self );
static int Material_setStrandUV( BPy_Material * self, PyObject * value);


/*****************************************************************************/
/* Python BPy_Material methods table: */
/*****************************************************************************/
static PyMethodDef BPy_Material_methods[] = {
	/* name, method, flags, doc */
	{"getName", ( PyCFunction ) GenericLib_getName, METH_NOARGS,
	 "() - Return Material's name"},
	{"getIpo", ( PyCFunction ) Material_getIpo, METH_NOARGS,
	 "() - Return Material's ipo or None if not found"},
	{"getMode", ( PyCFunction ) Material_getMode, METH_NOARGS,
	 "() - Return Material's mode flags"},
	{"getRGBCol", ( PyCFunction ) Material_getRGBCol, METH_NOARGS,
	 "() - Return Material's rgb color triplet"},
/*	{"getAmbCol", (PyCFunction)Material_getAmbCol, METH_NOARGS,
			"() - Return Material's ambient color"},*/
	{"getSpecCol", ( PyCFunction ) Material_getSpecCol, METH_NOARGS,
	 "() - Return Material's specular color"},
	{"getMirCol", ( PyCFunction ) Material_getMirCol, METH_NOARGS,
	 "() - Return Material's mirror color"},
	{"getAmb", ( PyCFunction ) Material_getAmb, METH_NOARGS,
	 "() - Return Material's ambient color blend factor"},
	{"getEmit", ( PyCFunction ) Material_getEmit, METH_NOARGS,
	 "() - Return Material's emitting light intensity"},
	{"getAlpha", ( PyCFunction ) Material_getAlpha, METH_NOARGS,
	 "() - Return Material's alpha (transparency) value"},
	{"getRef", ( PyCFunction ) Material_getRef, METH_NOARGS,
	 "() - Return Material's reflectivity"},
	{"getSpec", ( PyCFunction ) Material_getSpec, METH_NOARGS,
	 "() - Return Material's specularity"},
	/* Shader specific settings */
	{"getSpecShader", ( PyCFunction ) Material_getSpecShader, METH_NOARGS,
	 "() - Returns Material's specular shader" },
	{"getDiffuseShader", ( PyCFunction ) Material_getDiffuseShader, METH_NOARGS,
	 "() - Returns Material's diffuse shader" },
	 {"getRoughness", ( PyCFunction ) Material_getRoughness, METH_NOARGS,
	 "() - Returns Material's Roughness (applies to the \"Oren Nayar\" Diffuse Shader only)" },
	{"getSpecSize", ( PyCFunction ) Material_getSpecSize, METH_NOARGS,
	 "() - Returns Material's size of specular area (applies to the \"Toon\" Specular Shader only)" },
	{"getDiffuseSize", ( PyCFunction ) Material_getDiffuseSize, METH_NOARGS,
	 "() - Returns Material's size of diffuse area (applies to the \"Toon\" Diffuse Shader only)" },
	{"getSpecSmooth", ( PyCFunction ) Material_getSpecSmooth, METH_NOARGS,
	 "() - Returns Material's smoothing of specular area (applies to the \"Toon\" Diffuse Shader only)" },
	{"getDiffuseSmooth", ( PyCFunction ) Material_getDiffuseSmooth, METH_NOARGS,
	 "() - Returns Material's smoothing of diffuse area (applies to the \"Toon\" Diffuse Shader only)" },
	{"getDiffuseDarkness", ( PyCFunction ) Material_getDiffuseDarkness, METH_NOARGS,
	 "() - Returns Material's diffuse darkness (applies to the \"Minnaert\" Diffuse Shader only)" },
	{"getRefracIndex", ( PyCFunction ) Material_getRefracIndex, METH_NOARGS,
	 "() - Returns Material's Index of Refraction (applies to the \"Blinn\" Specular Shader only)" },	 
	{"getRms", ( PyCFunction ) Material_getRms, METH_NOARGS,
	 "() - Returns Material's standard deviation of surface slope (applies to the \"WardIso\" Specular Shader only)" },
	/* End shader settings */
	{"getSpecTransp", ( PyCFunction ) Material_getSpecTransp, METH_NOARGS,
	 "() - Return Material's specular transparency"},
	{"getAdd", ( PyCFunction ) Material_getAdd, METH_NOARGS,
	 "() - Return Material's glow factor"},
	{"getZOffset", ( PyCFunction ) Material_getZOffset, METH_NOARGS,
	 "() - Return Material's artificial offset for faces"},
	{"getHaloSize", ( PyCFunction ) Material_getHaloSize, METH_NOARGS,
	 "() - Return Material's halo size"},
	{"getHaloSeed", ( PyCFunction ) Material_getHaloSeed, METH_NOARGS,
	 "() - Return Material's seed for random ring dimension and line "
	 "location in halos"},
	{"getFlareSize", ( PyCFunction ) Material_getFlareSize, METH_NOARGS,
	 "() - Return Material's (flare size)/(halo size) factor"},
	{"getFlareSeed", ( PyCFunction ) Material_getFlareSeed, METH_NOARGS,
	 "() - Return Material's flare offset in the seed table"},
	{"getFlareBoost", ( PyCFunction ) Material_getFlareBoost, METH_NOARGS,
	 "() - Return Material's flare boost"},
	{"getSubSize", ( PyCFunction ) Material_getSubSize, METH_NOARGS,
	 "() - Return Material's dimension of subflare, dots and circles"},
	{"getHardness", ( PyCFunction ) Material_getHardness, METH_NOARGS,
	 "() - Return Material's specular hardness"},
	{"getNFlares", ( PyCFunction ) Material_getNFlares, METH_NOARGS,
	 "() - Return Material's number of flares in halo"},
	{"getNStars", ( PyCFunction ) Material_getNStars, METH_NOARGS,
	 "() - Return Material's number of points in the halo stars"},
	{"getNLines", ( PyCFunction ) Material_getNLines, METH_NOARGS,
	 "() - Return Material's number of lines in halo"},
	{"getNRings", ( PyCFunction ) Material_getNRings, METH_NOARGS,
	 "() - Return Material's number of rings in halo"},
	{"getRayMirr", ( PyCFunction ) Material_getRayMirr, METH_NOARGS,
	 "() - Return mount mirror"},
	{"getMirrDepth", ( PyCFunction ) Material_getMirrDepth, METH_NOARGS,
	 "() - Return amount mirror depth"},
	{"getFresnelMirr", ( PyCFunction ) Material_getFresnelMirr, METH_NOARGS,
	 "() - Return fresnel power for refractions"},
	{"getFresnelMirrFac", ( PyCFunction ) Material_getFresnelMirrFac, METH_NOARGS,
	 "() - Return fresnel power for refractions factor"},
	{"getRayTransGloss", ( PyCFunction ) Material_getGlossTrans, METH_NOARGS,
	 "() - Return amount refraction glossiness"},
	{"getRayTransGlossSamples", ( PyCFunction ) Material_getGlossTransSamples, METH_NOARGS,
	 "() - Return number of sampels for transparent glossiness"},
	{"getRayMirrGlossSamples", ( PyCFunction ) Material_getGlossMirrSamples, METH_NOARGS,
	 "() - Return number of sampels for mirror glossiness"},
	{"getFilter", ( PyCFunction ) Material_getFilter, METH_NOARGS,
	 "() - Return the amount of filtering when transparent raytrace is enabled"},
	{"getTranslucency", ( PyCFunction ) Material_getTranslucency, METH_NOARGS,
	 "() - Return the Translucency, the amount of diffuse shading of the back side"},
	{"getIOR", ( PyCFunction ) Material_getIOR, METH_NOARGS,
	 "() - Return IOR"},
	{"getTransDepth", ( PyCFunction ) Material_getTransDepth, METH_NOARGS,
	 "() - Return amount inter-refractions"},
	{"getFresnelTrans", ( PyCFunction ) Material_getFresnelTrans, METH_NOARGS,
	 "() - Return fresnel power for refractions"},
	{"getFresnelTransFac", ( PyCFunction ) Material_getFresnelTransFac, METH_NOARGS,
	 "() - Return fresnel power for refractions factor"},

	{"getTextures", ( PyCFunction ) Material_getTextures, METH_NOARGS,
	 "() - Return Material's texture list as a tuple"},
	{"setName", ( PyCFunction ) GenericLib_setName_with_method, METH_VARARGS,
	 "(s) - Change Material's name"},
	{"setIpo", ( PyCFunction ) Matr_oldsetIpo, METH_VARARGS,
	 "(Blender Ipo) - Change Material's Ipo"},
	{"clearIpo", ( PyCFunction ) Material_clearIpo, METH_NOARGS,
	 "(Blender Ipo) - Unlink Ipo from this Material"},
	{"insertIpoKey", ( PyCFunction ) Material_insertIpoKey, METH_VARARGS,
	 "(Material Ipo Constant) - Insert IPO Key at current frame"},	 
	{"setMode", ( PyCFunction ) Matr_oldsetMode, METH_VARARGS,
	 "([s[,s]]) - Set Material's mode flag(s)"},
	{"setRGBCol", ( PyCFunction ) Matr_oldsetRGBCol, METH_VARARGS,
	 "(f,f,f or [f,f,f]) - Set Material's rgb color triplet"},
/*	{"setAmbCol", (PyCFunction)Matr_oldsetAmbCol, METH_VARARGS,
			"(f,f,f or [f,f,f]) - Set Material's ambient color"},*/
	{"setSpecCol", ( PyCFunction ) Matr_oldsetSpecCol, METH_VARARGS,
	 "(f,f,f or [f,f,f]) - Set Material's specular color"},
	 
	/* Shader spesific settings */
	{"setSpecShader", ( PyCFunction ) Matr_oldsetSpecShader, METH_VARARGS,
	 "(i) - Set the Material's specular shader" },
	{"setDiffuseShader", ( PyCFunction ) Matr_oldsetDiffuseShader, METH_VARARGS,
	 "(i) - Set the Material's diffuse shader" },
	 {"setRoughness", ( PyCFunction ) Matr_oldsetRoughness, METH_VARARGS,
	 "(f) - Set the Material's Roughness (applies to the \"Oren Nayar\" Diffuse Shader only)" },
	{"setSpecSize", ( PyCFunction ) Matr_oldsetSpecSize, METH_VARARGS,
	 "(f) - Set the Material's size of specular area (applies to the \"Toon\" Specular Shader only)" },
	{"setDiffuseSize", ( PyCFunction ) Matr_oldsetDiffuseSize, METH_VARARGS,
	 "(f) - Set the Material's size of diffuse area (applies to the \"Toon\" Diffuse Shader only)" },
	{"setSpecSmooth", ( PyCFunction ) Matr_oldsetSpecSmooth, METH_VARARGS,
	 "(f) - Set the Material's smoothing of specular area (applies to the \"Toon\" Specular Shader only)" },
	{"setDiffuseSmooth", ( PyCFunction ) Matr_oldsetDiffuseSmooth, METH_VARARGS,
	 "(f) - Set the Material's smoothing of diffuse area (applies to the \"Toon\" Diffuse Shader only)" },
	{"setDiffuseDarkness", ( PyCFunction ) Matr_oldsetDiffuseDarkness, METH_VARARGS,
	 "(f) - Set the Material's diffuse darkness (applies to the \"Minnaert\" Diffuse Shader only)" },
	{"setRefracIndex", ( PyCFunction ) Matr_oldsetRefracIndex, METH_VARARGS,
	 "(f) - Set the Material's Index of Refraction (applies to the \"Blinn\" Specular Shader only)" },	 
	{"setRms", ( PyCFunction ) Matr_oldsetRms, METH_VARARGS,
	 "(f) - Set the Material's standard deviation of surface slope (applies to the \"WardIso\" Specular Shader only)" },
	/* End shader settings */
	 
	{"setMirCol", ( PyCFunction ) Matr_oldsetMirCol, METH_VARARGS,
	 "(f,f,f or [f,f,f]) - Set Material's mirror color"},
	{"setAmb", ( PyCFunction ) Matr_oldsetAmb, METH_VARARGS,
	 "(f) - Set how much the Material's color is affected"
	 " by \nthe global ambient colors - [0.0, 1.0]"},
	{"setEmit", ( PyCFunction ) Matr_oldsetEmit, METH_VARARGS,
	 "(f) - Set Material's emitting light intensity - [0.0, 1.0]"},
	{"setAlpha", ( PyCFunction ) Matr_oldsetAlpha, METH_VARARGS,
	 "(f) - Set Material's alpha (transparency) - [0.0, 1.0]"},
	{"setRef", ( PyCFunction ) Matr_oldsetRef, METH_VARARGS,
	 "(f) - Set Material's reflectivity - [0.0, 1.0]"},
	{"setSpec", ( PyCFunction ) Matr_oldsetSpec, METH_VARARGS,
	 "(f) - Set Material's specularity - [0.0, 2.0]"},
	{"setSpecTransp", ( PyCFunction ) Matr_oldsetSpecTransp, METH_VARARGS,
	 "(f) - Set Material's specular transparency - [0.0, 1.0]"},
	{"setAdd", ( PyCFunction ) Matr_oldsetAdd, METH_VARARGS,
	 "(f) - Set Material's glow factor - [0.0, 1.0]"},
	{"setZOffset", ( PyCFunction ) Matr_oldsetZOffset, METH_VARARGS,
	 "(f) - Set Material's artificial offset - [0.0, 10.0]"},
	{"setHaloSize", ( PyCFunction ) Matr_oldsetHaloSize, METH_VARARGS,
	 "(f) - Set Material's halo size - [0.0, 100.0]"},
	{"setHaloSeed", ( PyCFunction ) Matr_oldsetHaloSeed, METH_VARARGS,
	 "(i) - Set Material's halo seed - [0, 255]"},
	{"setFlareSize", ( PyCFunction ) Matr_oldsetFlareSize, METH_VARARGS,
	 "(f) - Set Material's factor: (flare size)/(halo size) - [0.1, 25.0]"},
	{"setFlareSeed", ( PyCFunction ) Matr_oldsetFlareSeed, METH_VARARGS,
	 "(i) - Set Material's flare seed - [0, 255]"},
	{"setFlareBoost", ( PyCFunction ) Matr_oldsetFlareBoost, METH_VARARGS,
	 "(f) - Set Material's flare boost - [0.1, 10.0]"},
	{"setSubSize", ( PyCFunction ) Matr_oldsetSubSize, METH_VARARGS,
	 "(f) - Set Material's dimension of subflare,"
	 " dots and circles - [0.1, 25.0]"},
	{"setHardness", ( PyCFunction ) Matr_oldsetHardness, METH_VARARGS,
	 "(i) - Set Material's hardness - [1, 255 (127 if halo mode is ON)]"},
	{"setNFlares", ( PyCFunction ) Matr_oldsetNFlares, METH_VARARGS,
	 "(i) - Set Material's number of flares in halo - [1, 32]"},
	{"setNStars", ( PyCFunction ) Matr_oldsetNStars, METH_VARARGS,
	 "(i) - Set Material's number of stars in halo - [3, 50]"},
	{"setNLines", ( PyCFunction ) Matr_oldsetNLines, METH_VARARGS,
	 "(i) - Set Material's number of lines in halo - [0, 250]"},
	{"setNRings", ( PyCFunction ) Matr_oldsetNRings, METH_VARARGS,
	 "(i) - Set Material's number of rings in halo - [0, 24]"},
	{"setRayMirr", ( PyCFunction ) Matr_oldsetRayMirr, METH_VARARGS,
	 "(f) - Set amount mirror - [0.0, 1.0]"},
	{"setMirrDepth", ( PyCFunction ) Matr_oldsetMirrDepth, METH_VARARGS,
	 "(i) - Set amount inter-reflections - [0, 10]"},
	{"setFresnelMirr", ( PyCFunction ) Matr_oldsetFresnelMirr, METH_VARARGS,
	 "(f) - Set fresnel power for mirror - [0.0, 5.0]"},
	{"setFresnelMirrFac", ( PyCFunction ) Matr_oldsetFresnelMirrFac, METH_VARARGS,
	 "(f) - Set blend fac for mirror fresnel - [1.0, 5.0]"},
	{"setRayTransGloss", ( PyCFunction ) Material_setGlossTrans, METH_VARARGS,
	 "(f) - Set amount refraction glossiness - [0.0, 1.0]"},
	{"setRayTransGlossSamples", ( PyCFunction ) Material_setGlossTransSamples, METH_VARARGS,
	 "(i) - Set number transparent gloss samples - [1, 1024]"},
	{"setRayMirrGlossSamples", ( PyCFunction ) Material_setGlossMirrSamples, METH_VARARGS,
	 "(i) - Set number mirror gloss samples - [1, 1024]"},
	{"setFilter", ( PyCFunction ) Matr_oldsetFilter, METH_VARARGS,
	 "(f) - Set the amount of filtering when transparent raytrace is enabled"},
	{"setTranslucency", ( PyCFunction ) Matr_oldsetTranslucency, METH_VARARGS,
	 "(f) - Set the Translucency, the amount of diffuse shading of the back side"},
	{"setIOR", ( PyCFunction ) Matr_oldsetIOR, METH_VARARGS,
	 "(f) - Set IOR - [1.0, 3.0]"},
	{"setTransDepth", ( PyCFunction ) Matr_oldsetTransDepth, METH_VARARGS,
	 "(i) - Set amount inter-refractions - [0, 10]"},
	{"setFresnelTrans", ( PyCFunction ) Matr_oldsetFresnelTrans, METH_VARARGS,
	 "(f) - Set fresnel power for refractions - [0.0, 5.0]"},
	{"setFresnelTransFac", ( PyCFunction ) Matr_oldsetFresnelTransFac, METH_VARARGS,
	 "(f) - Set fresnel power for refractions factor- [0.0, 5.0]"},
	{"setTexture", ( PyCFunction ) Material_setTexture, METH_VARARGS,
	 "(n,tex,texco=0,mapto=0) - Set numbered texture to tex"},
	{"clearTexture", ( PyCFunction ) Material_clearTexture, METH_O,
	 "(n) - Remove texture from numbered slot"},
	{"getScriptLinks", ( PyCFunction ) Material_getScriptLinks, METH_O,
	 "(eventname) - Get a list of this material's scriptlinks (Text names) "
	 "of the given type\n"
	 "(eventname) - string: FrameChanged, Redraw or Render."},
	{"addScriptLink", ( PyCFunction ) Material_addScriptLink, METH_VARARGS,
	 "(text, evt) - Add a new material scriptlink.\n"
	 "(text) - string: an existing Blender Text name;\n"
	 "(evt) string: FrameChanged, Redraw or Render."},
	{"clearScriptLinks", ( PyCFunction ) Material_clearScriptLinks, METH_VARARGS,
	 "() - Delete all scriptlinks from this material.\n"
	 "([s1<,s2,s3...>]) - Delete specified scriptlinks from this material."},
	{"__copy__", ( PyCFunction ) Material_copy, METH_NOARGS,
	 "() - Return a copy of the material."},
	{"copy", ( PyCFunction ) Material_copy, METH_NOARGS,
	 "() - Return a copy of the material."},
	{"freeNodes", ( PyCFunction ) Material_freeNodes, METH_NOARGS,
	 "() - Free this materials nodes."},
	{NULL, NULL, 0, NULL}
};

/*****************************************************************************/
/* Python attributes get/set structure:                                      */
/*****************************************************************************/

static PyGetSetDef BPy_Material_getseters[] = {
	GENERIC_LIB_GETSETATTR,
	{"add",
	 (getter)Material_getAdd, (setter)Material_setAdd,
	 "Strength of the add effect",
	 NULL},
	{"alpha",
	 (getter)Material_getAlpha, (setter)Material_setAlpha,
	 "Alpha setting ",
	 NULL},
	{"shadAlpha",
	 (getter)Material_getShadAlpha, (setter)Material_setShadAlpha,
	 "Shadow Alpha setting",
	 NULL},
	{"amb",
	 (getter)Material_getAmb, (setter)Material_setAmb,
	 "Amount of global ambient color material receives",
	 NULL},
	{"diffuseDarkness",
	 (getter)Material_getDiffuseDarkness, (setter)Material_setDiffuseDarkness,
	 "Material's diffuse darkness (\"Minnaert\" diffuse shader only)",
	 NULL},
	{"diffuseShader",
	 (getter)Material_getDiffuseShader, (setter)Material_setDiffuseShader,
	 "Diffuse shader type",
	 NULL},
	{"diffuseSize",
	 (getter)Material_getDiffuseSize, (setter)Material_setDiffuseSize,
	 "Material's diffuse area size (\"Toon\" diffuse shader only)",
	 NULL},
	{"diffuseSmooth",
	 (getter)Material_getDiffuseSmooth, (setter)Material_setDiffuseSmooth,
	 "Material's diffuse area smoothing (\"Toon\" diffuse shader only)",
	 NULL},
	{"emit",
	 (getter)Material_getEmit, (setter)Material_setEmit,
	 "Amount of light the material emits",
	 NULL},
	{"filter",
	 (getter)Material_getFilter, (setter)Material_setFilter,
	 "Amount of filtering when transparent raytrace is enabled",
	 NULL},
	{"flareBoost",
	 (getter)Material_getFlareBoost, (setter)Material_setFlareBoost,
	 "Flare's extra strength",
	 NULL},
	{"flareSeed",
	 (getter)Material_getFlareSeed, (setter)Material_setFlareSeed,
	 "Offset in the flare seed table",
	 NULL},
	{"flareSize",
	 (getter)Material_getFlareSize, (setter)Material_setFlareSize,
	 "Ratio of flare size to halo size",
	 NULL},
	{"fresnelDepth",
	 (getter)Material_getFresnelMirr, (setter)Material_setFresnelMirr,
	 "Power of Fresnel for mirror reflection",
	 NULL},
	{"fresnelDepthFac",
	 (getter)Material_getFresnelMirrFac, (setter)Material_setFresnelMirrFac,
	 "Blending factor for Fresnel mirror",
	 NULL},
	{"fresnelTrans",
	 (getter)Material_getFresnelTrans, (setter)Material_setFresnelTrans,
	 "Power of Fresnel for transparency",
	 NULL},
	{"fresnelTransFac",
	 (getter)Material_getFresnelTransFac, (setter)Material_setFresnelTransFac,
	 "Blending factor for Fresnel transparency",
	 NULL},
	 {"rbFriction",
	 (getter)Material_getRigidBodyFriction, (setter)Material_setRigidBodyFriction,
	 "Rigid Body Friction coefficient",
	 NULL},
	 {"rbRestitution",
	 (getter)Material_getRigidBodyRestitution, (setter)Material_setRigidBodyRestitution,
	 "Rigid Body Restitution coefficient",
	 NULL},

	{"haloSeed",
	 (getter)Material_getHaloSeed, (setter)Material_setHaloSeed,
	 "Randomizes halo ring dimension and line location",
	 NULL},
	{"haloSize",
	 (getter)Material_getHaloSize, (setter)Material_setHaloSize,
	 "Dimension of the halo",
	 NULL},
	{"hard",
	 (getter)Material_getHardness, (setter)Material_setHardness,
	 "Specularity hardness",
	 NULL},
	{"IOR",
	 (getter)Material_getIOR, (setter)Material_setIOR,
	 "Angular index of refraction for raytrace",
	 NULL},
	{"ipo",
	 (getter)Material_getIpo, (setter)Material_setIpo,
	 "Material Ipo data",
	 NULL},
	{"mirCol",
	 (getter)Material_getMirCol, (setter)Material_setMirCol,
	 "Mirror RGB color triplet",
	 NULL},
	{"mirR",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Mirror color red component",
	 (void *) EXPP_MAT_COMP_MIRR },
	{"mirG",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Mirror color green component",
	 (void *) EXPP_MAT_COMP_MIRG },
	{"mirB",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Mirror color blue component",
	 (void *) EXPP_MAT_COMP_MIRB },
	{"sssCol",
	 (getter)Material_getSssCol, (setter)Material_setSssCol,
	 "Sss RGB color triplet",
	 NULL},
	{"sssR",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "SSS color red component",
	 (void *) EXPP_MAT_COMP_SSSR },
	{"sssG",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "SSS color green component",
	 (void *) EXPP_MAT_COMP_SSSG },
	{"sssB",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "SSS color blue component",
	 (void *) EXPP_MAT_COMP_SSSB },
	{"mode",
	 (getter)Material_getMode, (setter)Material_setMode,
	 "Material mode bitmask",
	 NULL},
	{"shadeMode",
	 (getter)Material_getShadeMode, (setter)Material_setShadeMode,
	 "Material shade mode bitmask",
	 NULL},
	{"nFlares",
	 (getter)Material_getNFlares, (setter)Material_setNFlares,
	 "Number of subflares with halo",
	 NULL},
	{"nLines",
	 (getter)Material_getNLines, (setter)Material_setNLines,
	 "Number of star-shaped lines with halo",
	 NULL},
	{"nRings",
	 (getter)Material_getNRings, (setter)Material_setNRings,
	 "Number of rings with halo",
	 NULL},
	{"nStars",
	 (getter)Material_getNStars, (setter)Material_setNStars,
	 "Number of star points with halo",
	 NULL},
	{"rayMirr",
	 (getter)Material_getRayMirr, (setter)Material_setRayMirr,
	 "Mirror reflection amount for raytrace",
	 NULL},
	{"rayMirrDepth",
	 (getter)Material_getMirrDepth, (setter)Material_setMirrDepth,
	 "Amount of raytrace inter-reflections",
	 NULL},
	{"ref",
	 (getter)Material_getRef, (setter)Material_setRef,
	 "Amount of reflections (for shader)",
	 NULL},
	{"refracIndex",
	 (getter)Material_getRefracIndex, (setter)Material_setRefracIndex,
	 "Material's Index of Refraction (applies to the \"Blinn\" Specular Shader only",
	 NULL},
 	{"glossMir",
	 (getter)Material_getGlossMirr, (setter)Material_setGlossMirr,
	 "Reflection glossiness",
	 NULL},
	{"sampGlossMir",
	 (getter)Material_getGlossMirrSamples, (setter)Material_setGlossMirrSamples,
	 "Reflection glossiness",
	 NULL},
	{"glossTra",
	 (getter)Material_getGlossTrans, (setter)Material_setGlossTrans,
	 "Refraction glossiness",
	 NULL},
	{"sampGlossTra",
	 (getter)Material_getGlossMirrSamples, (setter)Material_setGlossMirrSamples,
	 "Refraction glossiness",
	 NULL},
	{"anisotropy",
	 (getter)Material_getAniso, (setter)Material_setAniso,
	 "Anisotropy",
	 NULL},
	{"threshMir",
	 (getter)Material_getThreshMirr, (setter)Material_setThreshMirr,
	 "Reflections threshold",
	 NULL},
	{"threshTra",
	 (getter)Material_getThreshTrans, (setter)Material_setThreshTrans,
	 "Refractions threshold",
	 NULL},
	{"rgbCol",
	 (getter)Material_getRGBCol, (setter)Material_setRGBCol,
	 "Diffuse RGB color triplet",
	 NULL},
	{"rms",
	 (getter)Material_getRms, (setter)Material_setRms,
	 "Material's surface slope standard deviation (\"WardIso\" specular shader only)",
	 NULL},
	{"roughness",
	 (getter)Material_getRoughness, (setter)Material_setRoughness,
	 "Material's roughness (\"Oren Nayar\" diffuse shader only)",
	 NULL},
	{"spec",
	 (getter)Material_getSpec, (setter)Material_setSpec,
	 "Degree of specularity",
	 NULL},
	{"specCol",
	 (getter)Material_getSpecCol, (setter)Material_setSpecCol,
	 "Specular RGB color triplet",
	 NULL},
	{"specR",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Specular color red component",
	 (void *) EXPP_MAT_COMP_SPECR },
	{"specG",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Specular color green component",
	 (void *) EXPP_MAT_COMP_SPECG },
	{"specB",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Specular color blue component",
	 (void *) EXPP_MAT_COMP_SPECB },
	{"specTransp",
	 (getter)Material_getSpecTransp, (setter)Material_setSpecTransp,
	 "Makes specular areas opaque on transparent materials",
	 NULL},
	{"specShader",
	 (getter)Material_getSpecShader, (setter)Material_setSpecShader,
	 "Specular shader type",
	 NULL},
	{"specSize",
	 (getter)Material_getSpecSize, (setter)Material_setSpecSize,
	 "Material's specular area size (\"Toon\" specular shader only)",
	 NULL},
	{"specSmooth",
	 (getter)Material_getSpecSmooth, (setter)Material_setSpecSmooth,
	 "Sets the smoothness of specular toon area",
	 NULL},
	{"subSize",
	 (getter)Material_getSubSize, (setter)Material_setSubSize,
	 "Dimension of subflares, dots and circles",
	 NULL},
	{"transDepth",
	 (getter)Material_getTransDepth, (setter)Material_setTransDepth,
	 "Amount of refractions for raytrace",
	 NULL},
	{"translucency",
	 (getter)Material_getTranslucency, (setter)Material_setTranslucency,
	 "Amount of diffuse shading of the back side",
	 NULL},
	{"zOffset",
	 (getter)Material_getZOffset, (setter)Material_setZOffset,
	 "Artificial offset in the Z buffer (for Ztransp option)",
	 NULL},
	{"lightGroup",
	 (getter)Material_getLightGroup, (setter)Material_setLightGroup,
	 "The light group for this material",
	 NULL},
	{"enabledTextures",
	 (getter)Material_getTexChannel, (setter)Material_setTexChannel,
	 "Enabled texture channels for this material",
	 NULL},
	{"R",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Diffuse color red component",
	 (void *) EXPP_MAT_COMP_R },
	{"G",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Diffuse color green component",
	 (void *) EXPP_MAT_COMP_G },
	{"B",
	 (getter)Material_getColorComponent, (setter)Material_setColorComponent,
	 "Diffuse color blue component",
	 (void *) EXPP_MAT_COMP_B },
	{"colorbandDiffuse",
	 (getter)Material_getColorband, (setter)Material_setColorband,
	 "The diffuse colorband for this material",
	 (void *) 0},
	{"colorbandSpecular",
	 (getter)Material_getColorband, (setter)Material_setColorband,
	 "The specular colorband for this material",
	 (void *) 1},
	{"textures",
	 (getter)Material_getTextures, (setter)Material_setTextures,
	 "The Material's texture list as a tuple",
	 NULL},
	{"colorbandSpecularFactor",
	 (getter)Material_getColorbandSpecularFactor, (setter)Material_setColorbandSpecularFactor,
	 "The specular colorband factor for this material",
	 NULL},
	{"colorbandSpecularMethod",
	 (getter)Material_getColorbandSpecularMethod, (setter)Material_setColorbandSpecularMethod,
	 "The specular colorband method for this material",
	 NULL},
	{"colorbandSpecularInput",
	 (getter)Material_getColorbandSpecularInput, (setter)Material_setColorbandSpecularInput,
	 "The specular colorband input for this material",
	 NULL},
	{"colorbandDiffuseFactor",
	 (getter)Material_getColorbandDiffuseFactor, (setter)Material_setColorbandDiffuseFactor,
	 "The diffuse colorband factor for this material",
	 NULL},
	{"colorbandDiffuseMethod",
	 (getter)Material_getColorbandDiffuseMethod, (setter)Material_setColorbandDiffuseMethod,
	 "The diffuse colorband method for this material",
	 NULL},
	{"colorbandDiffuseInput",
	 (getter)Material_getColorbandDiffuseInput, (setter)Material_setColorbandDiffuseInput,
	 "The diffuse colorband input for this material",
	 NULL},
	{"strandTanShad",
	 (getter)Material_getStrandTangentShad, (setter)Material_setStrandTangentShad,
	 "Uses direction of strands as normal for tangent-shading",
	 NULL},
	{"strandSurfDiff",
	 (getter)Material_getStrandSurfDiff, (setter)Material_setStrandSurfDiff,
	 "Make diffuse shading more similar to shading the surface",
	 NULL},
	{"strandDist",
	 (getter)Material_getStrandDist, (setter)Material_setStrandDist,
	 "Distance in Blender units over which to blend in the surface normal",
	 NULL},
	{"strandBlendUnit",
	 (getter)Material_getStrandBlendUnit, (setter)Material_setStrandBlendUnit,
	 "Use actual Blender units for widths instead of pixels",
	 NULL},
	{"strandStart",
	 (getter)Material_getStrandStart, (setter)Material_setStrandStart,
	 "Start size of strands",
	 NULL},
	{"strandEnd",
	 (getter)Material_getStrandEnd, (setter)Material_setStrandEnd,
	 "End size of strands",
	 NULL},
	{"strandMin",
	 (getter)Material_getStrandMin, (setter)Material_setStrandMin,
	 "Minimum size of strands in pixels",
	 NULL},
	{"strandShape",
	 (getter)Material_getStrandShape, (setter)Material_setStrandShape,
	 "Shape of strands, positive value makes it rounder, negative makes it spiky",
	 NULL},
	{"strandFade",
	 (getter)Material_getStrandWidthFad, (setter)Material_setStrandWidthFad,
	 "Transparency along the width of the strand",
	 NULL},
	{"strandUV",
	 (getter)Material_getStrandUV, (setter)Material_setStrandUV,
	 "Set name of UV layer to override",
	 NULL},

	/* SSS settings */
	{"enableSSS",
	 (getter)Material_getSssEnable, (setter)Material_setSssEnable,
	 "if true, SSS will be rendered for this material",
	 NULL},
	{"sssScale",
	 (getter)Material_getSssScale, (setter)Material_setSssScale,
	 "object scale for sss",
	 NULL},
	{"sssRadiusRed",
	 (getter)Material_getSssRadius, (setter)Material_setSssRadius,
	 "Mean red scattering path length",
	 (void *) 0},
	{"sssRadiusGreen",
	 (getter)Material_getSssRadius, (setter)Material_setSssRadius,
	 "Mean red scattering path length",
	 (void *) 1},
	{"sssRadiusBlue",
	 (getter)Material_getSssRadius, (setter)Material_setSssRadius,
	 "Mean red scattering path length",
	 (void *) 2},
	{"sssIOR",
	 (getter)Material_getSssIOR, (setter)Material_setSssIOR,
	 "index of refraction",
	 NULL},
	{"sssError",
	 (getter)Material_getSssError, (setter)Material_setSssError,
	 "Error",
	 NULL},
	{"sssColorBlend",
	 (getter)Material_getSssColorBlend, (setter)Material_setSssColorBlend,
	 "Blend factor for SSS Colors",
	 NULL},
	{"sssTextureScatter",
	 (getter)Material_getSssTexScatter, (setter)Material_setSssTexScatter,
	 "Texture scattering factor",
	 NULL},
	{"sssFront",
	 (getter)Material_getSssFront, (setter)Material_setSssFront,
	 "Front scattering weight",
	 NULL},
	{"sssBack",
	 (getter)Material_getSssBack, (setter)Material_setSssBack,
	 "Back scattering weight",
	 NULL},
	{NULL,NULL,NULL,NULL,NULL}  /* Sentinel */
};

/*****************************************************************************/
/* Python Material_Type callback function prototypes: */
/*****************************************************************************/
static void Material_dealloc( BPy_Material * self );
static int Material_compare( BPy_Material * a, BPy_Material * b);
static PyObject *Material_repr( BPy_Material * self );

/*****************************************************************************/
/* Python Material_Type structure definition:                                */
/*****************************************************************************/
PyTypeObject Material_Type = {
	PyObject_HEAD_INIT( NULL )  /* required py macro */
	0,                          /* ob_size */
	/*  For printing, in format "<module>.<name>" */
	"Blender Material",         /* char *tp_name; */
	sizeof( BPy_Material ),     /* int tp_basicsize; */
	0,                          /* tp_itemsize;  For allocation */

	/* Methods to implement standard operations */

	( destructor ) Material_dealloc,/* destructor tp_dealloc; */
	NULL,                       /* printfunc tp_print; */
	NULL,                       /* getattrfunc tp_getattr; */
	NULL,                       /* setattrfunc tp_setattr; */
	( cmpfunc ) Material_compare,/* cmpfunc tp_compare; */
	( reprfunc ) Material_repr, /* reprfunc tp_repr; */

	/* Method suites for standard classes */

	NULL,                       /* PyNumberMethods *tp_as_number; */
	NULL,                       /* PySequenceMethods *tp_as_sequence; */
	NULL,                       /* PyMappingMethods *tp_as_mapping; */

	/* More standard operations (here for binary compatibility) */

	( hashfunc ) GenericLib_hash,	/* hashfunc tp_hash; */
	NULL,                       /* ternaryfunc tp_call; */
	NULL,                       /* reprfunc tp_str; */
	NULL,                       /* getattrofunc tp_getattro; */
	NULL,                       /* setattrofunc tp_setattro; */

	/* Functions to access object as input/output buffer */
	NULL,                       /* PyBufferProcs *tp_as_buffer; */

  /*** Flags to define presence of optional/expanded features ***/
	Py_TPFLAGS_DEFAULT,         /* long tp_flags; */

	NULL,                       /*  char *tp_doc;  Documentation string */
  /*** Assigned meaning in release 2.0 ***/
	/* call function for all accessible objects */
	NULL,                       /* traverseproc tp_traverse; */

	/* delete references to contained objects */
	NULL,                       /* inquiry tp_clear; */

  /***  Assigned meaning in release 2.1 ***/
  /*** rich comparisons ***/
	NULL,                       /* richcmpfunc tp_richcompare; */

  /***  weak reference enabler ***/
	0,                          /* long tp_weaklistoffset; */

  /*** Added in release 2.2 ***/
	/*   Iterators */
	NULL,                       /* getiterfunc tp_iter; */
	NULL,                       /* iternextfunc tp_iternext; */

  /*** Attribute descriptor and subclassing stuff ***/
	BPy_Material_methods,       /* struct PyMethodDef *tp_methods; */
	NULL,                       /* struct PyMemberDef *tp_members; */
	BPy_Material_getseters,     /* struct PyGetSetDef *tp_getset; */
	NULL,                       /* struct _typeobject *tp_base; */
	NULL,                       /* PyObject *tp_dict; */
	NULL,                       /* descrgetfunc tp_descr_get; */
	NULL,                       /* descrsetfunc tp_descr_set; */
	0,                          /* long tp_dictoffset; */
	NULL,                       /* initproc tp_init; */
	NULL,                       /* allocfunc tp_alloc; */
	NULL,                       /* newfunc tp_new; */
	/*  Low-level free-memory routine */
	NULL,                       /* freefunc tp_free;  */
	/* For PyObject_IS_GC */
	NULL,                       /* inquiry tp_is_gc;  */
	NULL,                       /* PyObject *tp_bases; */
	/* method resolution order */
	NULL,                       /* PyObject *tp_mro;  */
	NULL,                       /* PyObject *tp_cache; */
	NULL,                       /* PyObject *tp_subclasses; */
	NULL,                       /* PyObject *tp_weaklist; */
	NULL
};

/*****************************************************************************/
/* Function:	Material_dealloc          */
/* Description: This is a callback function for the BPy_Material type. It is */
/*		the destructor function.				 */
/*****************************************************************************/
static void Material_dealloc( BPy_Material * self )
{
	Py_DECREF( self->col );
	Py_DECREF( self->amb );
	Py_DECREF( self->spec );
	Py_DECREF( self->mir );
	Py_DECREF( self->sss );
	PyObject_DEL( self );
}

/*****************************************************************************/
/* Function:	Material_CreatePyObject		*/
/* Description: Create a new BPy_Material from an  existing */
/*		 Blender material structure.	 */
/*****************************************************************************/
PyObject *Material_CreatePyObject( struct Material *mat )
{
	BPy_Material *pymat;
	float *col[3], *amb[3], *spec[3], *mir[3], *sss[3];

	pymat = ( BPy_Material * ) PyObject_NEW( BPy_Material,
						 &Material_Type );

	if( !pymat )
		return EXPP_ReturnPyObjError( PyExc_MemoryError,
					      "couldn't create BPy_Material object" );

	pymat->material = mat;

	col[0] = &mat->r;
	col[1] = &mat->g;
	col[2] = &mat->b;

	amb[0] = &mat->ambr;
	amb[1] = &mat->ambg;
	amb[2] = &mat->ambb;

	spec[0] = &mat->specr;
	spec[1] = &mat->specg;
	spec[2] = &mat->specb;

	mir[0] = &mat->mirr;
	mir[1] = &mat->mirg;
	mir[2] = &mat->mirb;
	
	sss[0] = &mat->sss_col[0];
	sss[1] = &mat->sss_col[1];
	sss[2] = &mat->sss_col[2];

	pymat->col = ( BPy_rgbTuple * ) rgbTuple_New( col );
	pymat->amb = ( BPy_rgbTuple * ) rgbTuple_New( amb );
	pymat->spec = ( BPy_rgbTuple * ) rgbTuple_New( spec );
	pymat->mir = ( BPy_rgbTuple * ) rgbTuple_New( mir );
	pymat->sss = ( BPy_rgbTuple * ) rgbTuple_New( sss );

	return ( PyObject * ) pymat;
}

/*****************************************************************************/
/* Function:		Material_FromPyObject	 */
/* Description: This function returns the Blender material from the given */
/*		PyObject.	 */
/*****************************************************************************/
Material *Material_FromPyObject( PyObject * pyobj )
{
	return ( ( BPy_Material * ) pyobj )->material;
}

static PyObject *Material_getIpo( BPy_Material * self )
{
	Ipo *ipo = self->material->ipo;

	if( !ipo )
		Py_RETURN_NONE;

	return Ipo_CreatePyObject( ipo );
}

static PyObject *Material_getMode( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->mode );
}

static PyObject *Material_getShadeMode( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->shade_flag );
}

static PyObject *Material_getRGBCol( BPy_Material * self )
{
	return rgbTuple_getCol( self->col );
}

/*
static PyObject *Material_getAmbCol(BPy_Material *self)
{
	return rgbTuple_getCol(self->amb);
}
*/
static PyObject *Material_getSpecCol( BPy_Material * self )
{
	return rgbTuple_getCol( self->spec );
}

static PyObject *Material_getMirCol( BPy_Material * self )
{
	return rgbTuple_getCol( self->mir );
}

static PyObject *Material_getSssCol( BPy_Material * self )
{
	return rgbTuple_getCol( self->sss );
}

static PyObject *Material_getSpecShader( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->spec_shader );
}

static PyObject *Material_getDiffuseShader( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->diff_shader );
}

static PyObject *Material_getRoughness( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->roughness );
}

static PyObject *Material_getSpecSize( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->param[2] );
}

static PyObject *Material_getDiffuseSize( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->param[0] );
}

static PyObject *Material_getSpecSmooth( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->param[3] );
}

static PyObject *Material_getDiffuseSmooth( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->param[1] );
}

static PyObject *Material_getDiffuseDarkness( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->darkness );
}

static PyObject *Material_getRefracIndex( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->refrac );
}
	
static PyObject *Material_getRms( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->rms );
}

static PyObject *Material_getAmb( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->amb );
}

static PyObject *Material_getEmit( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->emit );
}

static PyObject *Material_getAlpha( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->alpha );
}

static PyObject *Material_getShadAlpha( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->shad_alpha );
}

static PyObject *Material_getRef( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->ref );
}

static PyObject *Material_getSpec( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->spec );
}

static PyObject *Material_getSpecTransp( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->spectra );
}

static PyObject *Material_getAdd( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->add );
}

static PyObject *Material_getZOffset( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->zoffs );
}

static PyObject *Material_getLightGroup( BPy_Material * self )
{
	return Group_CreatePyObject( self->material->group );
}

static PyObject *Material_getTexChannel( BPy_Material * self )
{
	int i;
    short mask = 1;
	PyObject *list = PyList_New(0);
	if( !list )
		return EXPP_ReturnPyObjError( PyExc_MemoryError,
				"PyList_New() failed" );

	for( i = 0, mask = 1; i < MAX_MTEX ; ++i, mask <<= 1 ) {
		if( self->material->mtex[i] && (mask & self->material->septex) == 0 ) {
			PyObject * val = PyInt_FromLong(i);
			if( !val ) {
				Py_DECREF( list );
				return EXPP_ReturnPyObjError( PyExc_MemoryError,
						"PyInt_FromLong() failed" );
			}
			if( PyList_Append( list, val ) < 0 ) {
				Py_DECREF( val );
				Py_DECREF( list );
				return EXPP_ReturnPyObjError( PyExc_RuntimeError,
						"PyList_Append() failed" );
			}
			Py_DECREF( val );
		}
	}

	return list;
}

static PyObject *Material_getHaloSize( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->hasize );
}

static PyObject *Material_getFlareSize( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->flaresize );
}

static PyObject *Material_getFlareBoost( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->flareboost );
}

static PyObject *Material_getSubSize( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->subsize );
}

static PyObject *Material_getHaloSeed( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->seed1 );
}

static PyObject *Material_getFlareSeed( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->seed2 );
}

static PyObject *Material_getHardness( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->har );
}

static PyObject *Material_getNFlares( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->flarec );
}

static PyObject *Material_getNStars( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->starc );
}

static PyObject *Material_getNLines( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->linec );
}

static PyObject *Material_getNRings( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->ringc );
}

static PyObject *Material_getRayMirr( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->ray_mirror );
}

static PyObject *Material_getMirrDepth( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->ray_depth );
}

static PyObject *Material_getFresnelMirr( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->fresnel_mir );
}

static PyObject *Material_getFresnelMirrFac( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->fresnel_mir_i );
}

static PyObject *Material_getFilter( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->filter );
}

static PyObject *Material_getTranslucency( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->translucency );
}

static PyObject *Material_getIOR( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->ang );
}

static PyObject *Material_getTransDepth( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->ray_depth_tra );
}

static PyObject *Material_getFresnelTrans( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->fresnel_tra );
}

static PyObject *Material_getFresnelTransFac( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->fresnel_tra_i );
}

static PyObject *Material_getGlossMirr( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->gloss_mir );
}

static PyObject *Material_getGlossMirrSamples( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->samp_gloss_mir );
}

static PyObject *Material_getGlossTrans( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->gloss_tra );
}

static PyObject *Material_getGlossTransSamples( BPy_Material * self )
{
	return PyInt_FromLong( ( long ) self->material->samp_gloss_tra );
}

static PyObject *Material_getAniso( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->aniso_gloss_mir );
}

static PyObject *Material_getThreshMirr( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->adapt_thresh_mir );
}

static PyObject *Material_getThreshTrans( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->adapt_thresh_tra );
}

static PyObject* Material_getRigidBodyFriction( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->friction );
}

static PyObject* Material_getRigidBodyRestitution( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->reflect );
}

/* SSS */
static PyObject* Material_getSssEnable( BPy_Material * self )
{
	return EXPP_getBitfield( &self->material->sss_flag, MA_DIFF_SSS, 'h' );
}

static PyObject* Material_getSssScale( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->sss_scale );
}

static PyObject* Material_getSssRadius( BPy_Material * self, void * type )
{
	return PyFloat_FromDouble( ( double ) (self->material->sss_radius[GET_INT_FROM_POINTER(type)]) );
}

static PyObject* Material_getSssIOR( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->sss_ior);
}

static PyObject* Material_getSssError( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->sss_error);
}

static PyObject* Material_getSssColorBlend( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->sss_colfac);
}

static PyObject* Material_getSssTexScatter( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->sss_texfac);
}

static PyObject* Material_getSssFront( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->sss_front);
}

static PyObject* Material_getSssBack( BPy_Material * self )
{
	return PyFloat_FromDouble( ( double ) self->material->sss_back);
}

static PyObject *Material_getTextures( BPy_Material * self )
{
	int i;
	PyObject *tuple;

	/* build a texture list */
	tuple = PyTuple_New( MAX_MTEX );
	if( !tuple )
		return EXPP_ReturnPyObjError( PyExc_MemoryError,
					      "couldn't create PyTuple" );

	for( i = 0; i < MAX_MTEX; ++i ) {
		struct MTex *mtex = self->material->mtex[i];
		if( mtex ) {
			PyTuple_SET_ITEM( tuple, i, MTex_CreatePyObject( mtex, ID_MA ) );
		} else {
			Py_INCREF( Py_None );
			PyTuple_SET_ITEM( tuple, i, Py_None );
		}
	}

	return tuple;
}

/*
 * this should accept a Py_None argument and just delete the Ipo link
 * (as Lamp_clearIpo() does)
 */

static int Material_setIpo( BPy_Material * self, PyObject * value )
{
	return GenericLib_assignData(value, (void **) &self->material->ipo, 0, 1, ID_IP, ID_MA);
}


/* 
 *  Material_insertIpoKey( key )
 *   inserts Material IPO key at current frame
 */

static PyObject *Material_insertIpoKey( BPy_Material * self, PyObject * args )
{
    int key = 0, flag = 0, map;
    
	if( !PyArg_ParseTuple( args, "i", &( key ) ) )
		return ( EXPP_ReturnPyObjError( PyExc_AttributeError,
						"expected int argument" ) ); 
    				
	map = texchannel_to_adrcode(self->material->texact);
	
	/* flag should be initialised with the 'autokeying' flags like for normal keying */
	if (IS_AUTOKEY_FLAG(INSERTNEEDED)) flag |= INSERTKEY_NEEDED;
	
	if(key==IPOKEY_RGB || key==IPOKEY_ALLCOLOR) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_COL_R, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_COL_G, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_COL_B, flag);
	}
	if(key==IPOKEY_ALPHA || key==IPOKEY_ALLCOLOR) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_ALPHA, flag);
	}
	if(key==IPOKEY_HALOSIZE || key==IPOKEY_ALLCOLOR) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_HASIZE, flag);
	}
	if(key==IPOKEY_MODE || key==IPOKEY_ALLCOLOR) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_MODE, flag);
	}
	if(key==IPOKEY_ALLCOLOR) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_SPEC_R, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_SPEC_G, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_SPEC_B, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_REF, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_EMIT, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_AMB, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_SPEC, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_HARD, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_MODE, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_TRANSLU, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_ADD, flag);
	}
	if(key==IPOKEY_ALLMIRROR) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_RAYM, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_FRESMIR, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_FRESMIRI, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_FRESTRA, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, MA_FRESTRAI, flag);
	}
	if(key==IPOKEY_OFS || key==IPOKEY_ALLMAPPING) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_OFS_X, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_OFS_Y, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_OFS_Z, flag);
	}
	if(key==IPOKEY_SIZE || key==IPOKEY_ALLMAPPING) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_SIZE_X, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_SIZE_Y, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_SIZE_Z, flag);
	}
	if(key==IPOKEY_ALLMAPPING) {
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_R, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_G, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_B, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_DVAR, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_COLF, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_NORF, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_VARF, flag);
		insertkey((ID *)self->material, ID_MA, NULL, NULL, map+MAP_DISP, flag);
	}

	allspace(REMAKEIPO, 0);
	EXPP_allqueue(REDRAWIPO, 0);
	EXPP_allqueue(REDRAWVIEW3D, 0);
	EXPP_allqueue(REDRAWACTION, 0);
	EXPP_allqueue(REDRAWNLA, 0);

	Py_RETURN_NONE;
}

static int Material_setMode( BPy_Material * self, PyObject * value )
{
	int param;

	if( !PyInt_Check( value ) ) {
		char errstr[128];
		sprintf ( errstr , "expected int bitmask of 0x%08x", MA_MODE_MASK );
		return EXPP_ReturnIntError( PyExc_TypeError, errstr );
	}
	param = PyInt_AS_LONG ( value );

	if ( ( param & MA_MODE_MASK ) != param )
		return EXPP_ReturnIntError( PyExc_ValueError,
						"invalid bit(s) set in mask" );

	self->material->mode &= ( MA_RAMP_COL | MA_RAMP_SPEC );
	self->material->mode |= param & ~( MA_RAMP_COL | MA_RAMP_SPEC );

	return 0;
}

static int Material_setShadeMode( BPy_Material * self, PyObject * value )
{
	int param;

	if( !PyInt_Check( value ) ) {
		char errstr[128];
		sprintf ( errstr , "expected int bitmask of 0x%08x", (MA_CUBIC | MA_OBCOLOR) );
		return EXPP_ReturnIntError( PyExc_TypeError, errstr );
	}
	param = PyInt_AS_LONG ( value );
	if ( ( param & (MA_CUBIC | MA_OBCOLOR) ) != param )
		return EXPP_ReturnIntError( PyExc_ValueError,
						"invalid bit(s) set in mask" );
	self->material->shade_flag |= param;

	return 0;
}

static int Material_setRGBCol( BPy_Material * self, PyObject * value )
{
	return rgbTuple_setCol( self->col, value );
}

/*
static PyObject *Material_setAmbCol (BPy_Material *self, PyObject * value )
{
	return rgbTuple_setCol(self->amb, value);
}
*/

static int Material_setSpecCol( BPy_Material * self, PyObject * value )
{
	return rgbTuple_setCol( self->spec, value );
}

static int Material_setMirCol( BPy_Material * self, PyObject * value )
{
	return rgbTuple_setCol( self->mir, value );
}

static int Material_setSssCol( BPy_Material * self, PyObject * value )
{
	return rgbTuple_setCol( self->sss, value );
}

static int Material_setColorComponent( BPy_Material * self, PyObject * value,
							void * closure )
{
	float param;

	if( !PyNumber_Check ( value ) )
		return EXPP_ReturnIntError( PyExc_TypeError,
						"expected float argument in [0.0,1.0]" );

	param = (float)PyFloat_AsDouble( value );
	param = EXPP_ClampFloat( param, EXPP_MAT_COL_MIN, EXPP_MAT_COL_MAX );

	switch ( GET_INT_FROM_POINTER(closure) ) {
	case EXPP_MAT_COMP_R:
		self->material->r = param;
		return 0;
	case EXPP_MAT_COMP_G:
		self->material->g = param;
		return 0;
	case EXPP_MAT_COMP_B:
		self->material->b = param;
		return 0;
	case EXPP_MAT_COMP_SPECR:
		self->material->specr = param;
		return 0;
	case EXPP_MAT_COMP_SPECG:
		self->material->specg = param;
		return 0;
	case EXPP_MAT_COMP_SPECB:
		self->material->specb = param;
		return 0;
	case EXPP_MAT_COMP_MIRR:
		self->material->mirr = param;
		return 0;
	case EXPP_MAT_COMP_MIRG:
		self->material->mirg = param;
		return 0;
	case EXPP_MAT_COMP_MIRB:
		self->material->mirb = param;
		return 0;
	case EXPP_MAT_COMP_SSSR:
		self->material->sss_col[0] = param;
		return 0;
	case EXPP_MAT_COMP_SSSG:
		self->material->sss_col[1] = param;
		return 0;
	case EXPP_MAT_COMP_SSSB:
		self->material->sss_col[2] = param;
		return 0;
	}
	return EXPP_ReturnIntError( PyExc_RuntimeError,
				"unknown color component specified" );
}

/*#define setFloatWrapper(val, min, max) {return EXPP_setFloatClamped ( value, &self->material->#val, #min, #max}*/

static int Material_setAmb( BPy_Material * self, PyObject * value )
{ 
	return EXPP_setFloatClamped ( value, &self->material->amb,
								EXPP_MAT_AMB_MIN,
					       		EXPP_MAT_AMB_MAX );
}

static int Material_setEmit( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->emit,
								EXPP_MAT_EMIT_MIN,
								EXPP_MAT_EMIT_MAX );
}

static int Material_setSpecTransp( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->spectra,
								EXPP_MAT_SPECTRA_MIN,
								EXPP_MAT_SPECTRA_MAX );
}

static int Material_setAlpha( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->alpha,
								EXPP_MAT_ALPHA_MIN,
								EXPP_MAT_ALPHA_MAX );
}

static int Material_setShadAlpha( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->shad_alpha,
								EXPP_MAT_ALPHA_MIN,
								EXPP_MAT_ALPHA_MAX );
}

static int Material_setRef( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->ref,
								EXPP_MAT_REF_MIN,
								EXPP_MAT_REF_MAX );
}

static int Material_setSpec( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->spec,
								EXPP_MAT_SPEC_MIN,
								EXPP_MAT_SPEC_MAX );
}

static int Material_setZOffset( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->zoffs,
		   						EXPP_MAT_ZOFFS_MIN,
								EXPP_MAT_ZOFFS_MAX );
}

static int Material_setLightGroup( BPy_Material * self, PyObject * value )
{
	return GenericLib_assignData(value, (void **) &self->material->group, NULL, 1, ID_GR, 0);
}

static int Material_setTexChannel( BPy_Material * self, PyObject * value )
{
	int i, mask;
	short septex = 0;
	int result = 1;

	/* fail if input is not a standard sequence */
	if( !PyList_Check( value ) && !PyTuple_Check( value ) )
		return EXPP_ReturnIntError( PyExc_TypeError,
						"expected tuple or list of integers" );

	/* get a fast sequence; in Python 2.5, this just return the original
	 * list or tuple and INCREFs it, so we must DECREF */
	value = PySequence_Fast( value, "" );

	/* set the disable bit for each existing texture */
	for( i= 0, mask= 1; i < MAX_MTEX; ++i, mask <<= 1 )
		if( self->material->mtex[i] != NULL )
			septex |= mask;

	/* check the list, and build new septex value */
	for( i= PySequence_Size(value)-1; i >= 0; --i ) {
		long ival;
		PyObject *item = PySequence_Fast_GET_ITEM( value, i );
		if( !PyInt_Check( item ) ) {
			PyErr_SetString ( PyExc_TypeError,
					"expected tuple or list of integers" );
			goto exit;
		}
		ival= PyInt_AsLong( item );
		if(ival < 0 || ival > MAX_MTEX) {
			PyErr_SetString( PyExc_ValueError,
							"channel value out of range" );
			goto exit;
		}
		ival&= (1<<MAX_MTEX)-1;
		if( self->material->mtex[(int)ival] == NULL ) {
			PyErr_SetString( PyExc_ValueError,
							"channels must have a texture assigned" );
			goto exit;
		}
		septex&= ~(1<<ival);
	}
	self->material->septex= septex;
	result = 0;

exit:
	Py_DECREF(value);
	return result;
}

static int Material_setAdd( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->add,
								EXPP_MAT_ADD_MIN,
								EXPP_MAT_ADD_MAX );
}

static int Material_setHaloSize( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->hasize,
		   						EXPP_MAT_HALOSIZE_MIN,
								EXPP_MAT_HALOSIZE_MAX );
}

static int Material_setFlareSize( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->flaresize,
								EXPP_MAT_FLARESIZE_MIN,
								EXPP_MAT_FLARESIZE_MAX );
}

static int Material_setFlareBoost( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->flareboost,
								EXPP_MAT_FLAREBOOST_MIN,
								EXPP_MAT_FLAREBOOST_MAX );
}

static int Material_setSubSize( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->subsize,
								EXPP_MAT_SUBSIZE_MIN,
								EXPP_MAT_SUBSIZE_MAX );
}

static int Material_setHaloSeed( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->seed1,
								EXPP_MAT_HALOSEED_MIN,
								EXPP_MAT_HALOSEED_MAX, 'b' );
}

static int Material_setFlareSeed( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->seed2,
								EXPP_MAT_FLARESEED_MIN,
								EXPP_MAT_FLARESEED_MAX, 'b' );
}

static int Material_setHardness( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->har,
		   						EXPP_MAT_HARD_MIN,
								EXPP_MAT_HARD_MAX, 'h' );
}

static int Material_setNFlares( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->flarec,
								EXPP_MAT_NFLARES_MIN,
								EXPP_MAT_NFLARES_MAX, 'h' );
}

static int Material_setNStars( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->starc,
								EXPP_MAT_NSTARS_MIN,
								EXPP_MAT_NSTARS_MAX, 'h' );
}

static int Material_setNLines( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->linec,
								EXPP_MAT_NLINES_MIN,
								EXPP_MAT_NLINES_MAX, 'h' );
}

static int Material_setNRings( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->ringc,
		   						EXPP_MAT_NRINGS_MIN,
								EXPP_MAT_NRINGS_MAX, 'h' );
}

static int Material_setRayMirr( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->ray_mirror,
								EXPP_MAT_RAYMIRR_MIN,
								EXPP_MAT_RAYMIRR_MAX );
}

static int Material_setMirrDepth( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->ray_depth,
								EXPP_MAT_MIRRDEPTH_MIN,
								EXPP_MAT_MIRRDEPTH_MAX, 'h' );
}

static int Material_setFresnelMirr( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->fresnel_mir,
								EXPP_MAT_FRESNELMIRR_MIN,
								EXPP_MAT_FRESNELMIRR_MAX );
}

static int Material_setFresnelMirrFac( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->fresnel_mir_i,
								EXPP_MAT_FRESNELMIRRFAC_MIN,
								EXPP_MAT_FRESNELMIRRFAC_MAX );
}

static int Material_setIOR( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->ang,
								EXPP_MAT_IOR_MIN,
								EXPP_MAT_IOR_MAX );
}

static int Material_setTransDepth( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->ray_depth_tra,
								EXPP_MAT_TRANSDEPTH_MIN,
								EXPP_MAT_TRANSDEPTH_MAX, 'h' );
}

static int Material_setFresnelTrans( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->fresnel_tra,
								EXPP_MAT_FRESNELTRANS_MIN,
								EXPP_MAT_FRESNELTRANS_MAX );
}

static int Material_setFresnelTransFac( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->fresnel_tra_i,
								EXPP_MAT_FRESNELTRANSFAC_MIN,
								EXPP_MAT_FRESNELTRANSFAC_MAX );
}

static int Material_setGlossMirr( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->gloss_mir,
								EXPP_MAT_RAYMIRRGLOSS_MIN,
								EXPP_MAT_RAYMIRRGLOSS_MAX );
}

static int Material_setGlossMirrSamples( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->samp_gloss_mir,
								EXPP_MAT_RAYMIRRGLOSSSAMPLES_MIN,
								EXPP_MAT_RAYMIRRGLOSSSAMPLES_MAX, 'h' );
}

static int Material_setGlossTrans( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->gloss_tra,
								EXPP_MAT_RAYTRANSPGLOSS_MIN,
								EXPP_MAT_RAYTRANSPGLOSS_MAX );
}

static int Material_setGlossTransSamples( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueClamped ( value, &self->material->samp_gloss_tra,
								EXPP_MAT_RAYTRANSPGLOSSSAMPLES_MIN,
								EXPP_MAT_RAYTRANSPGLOSSSAMPLES_MAX, 'h' );
}

static int Material_setAniso( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->aniso_gloss_mir,
								EXPP_MAT_ANISO_GLOSS_MIR_MIN,
								EXPP_MAT_ANISO_GLOSS_MIR_MAX );
}

static int Material_setThreshMirr( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->adapt_thresh_mir,
								EXPP_MAT_ADAPT_THRESH_MIR_MIN,
								EXPP_MAT_ADAPT_THRESH_MIR_MAX );
}

static int Material_setThreshTrans( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->adapt_thresh_tra,
								EXPP_MAT_ADAPT_THRESH_TRA_MIN,
								EXPP_MAT_ADAPT_THRESH_TRA_MAX );
}

static int Material_setRigidBodyFriction( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->friction,
								0.f,
								100.f );
}

static int Material_setRigidBodyRestitution( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->reflect,
								0.f,
								1.f );
}




static int Material_setSpecShader( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueRange( value, &self->material->spec_shader,
								MA_SPEC_COOKTORR,
								MA_SPEC_WARDISO, 'h' );
}

static int Material_setDiffuseShader( BPy_Material * self, PyObject * value )
{
	return EXPP_setIValueRange( value, &self->material->diff_shader,
								MA_DIFF_LAMBERT,
								MA_DIFF_MINNAERT, 'h' );
}

static int Material_setRoughness( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->roughness,
								EXPP_MAT_ROUGHNESS_MIN,
								EXPP_MAT_ROUGHNESS_MAX );
}

static int Material_setSpecSize( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->param[2],
								EXPP_MAT_SPECSIZE_MIN,
								EXPP_MAT_SPECSIZE_MAX );
}

static int Material_setDiffuseSize( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->param[0],
								EXPP_MAT_DIFFUSESIZE_MIN,
								EXPP_MAT_DIFFUSESIZE_MAX );
}

static int Material_setSpecSmooth( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->param[3],
								EXPP_MAT_SPECSMOOTH_MIN,
								EXPP_MAT_SPECSMOOTH_MAX );
}

static int Material_setDiffuseSmooth( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->param[1],
								EXPP_MAT_DIFFUSESMOOTH_MIN,
								EXPP_MAT_DIFFUSESMOOTH_MAX );
}

static int Material_setDiffuseDarkness( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->darkness,
								EXPP_MAT_DIFFUSE_DARKNESS_MIN,
								EXPP_MAT_DIFFUSE_DARKNESS_MAX );
}

static int Material_setRefracIndex( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->refrac,
								EXPP_MAT_REFRACINDEX_MIN,
								EXPP_MAT_REFRACINDEX_MAX );
}

static int Material_setRms( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->rms,
								EXPP_MAT_RMS_MIN,
								EXPP_MAT_RMS_MAX );
}

static int Material_setFilter( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->filter,
								EXPP_MAT_FILTER_MIN,
								EXPP_MAT_FILTER_MAX );
}

static int Material_setTranslucency( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->translucency,
								EXPP_MAT_TRANSLUCENCY_MIN,
								EXPP_MAT_TRANSLUCENCY_MAX );
}

/* SSS */
static int Material_setSssEnable( BPy_Material * self, PyObject * value )
{
	return EXPP_setBitfield( value, &self->material->sss_flag, MA_DIFF_SSS, 'h' );
}

static int Material_setSssScale( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->sss_scale,
								EXPP_MAT_SSS_SCALE_MIN,
								EXPP_MAT_SSS_SCALE_MAX);
}

static int Material_setSssRadius( BPy_Material * self, PyObject * value, void *type )
{
	return EXPP_setFloatClamped ( value, &self->material->sss_radius[GET_INT_FROM_POINTER(type)],
								EXPP_MAT_SSS_RADIUS_MIN,
								EXPP_MAT_SSS_RADIUS_MAX);
}

static int Material_setSssIOR( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->sss_ior,
								EXPP_MAT_SSS_IOR_MIN,
								EXPP_MAT_SSS_IOR_MAX);
}

static int Material_setSssError( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->sss_error,
								EXPP_MAT_SSS_IOR_MIN,
								EXPP_MAT_SSS_IOR_MAX);
}

static int Material_setSssColorBlend( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->sss_colfac,
								0.0,
								1.0);
}

static int Material_setSssTexScatter( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->sss_texfac,
								0.0,
								1.0);
}

static int Material_setSssFront( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->sss_front,
								EXPP_MAT_SSS_FRONT_MIN,
								EXPP_MAT_SSS_FRONT_MAX);
}

static int Material_setSssBack( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped ( value, &self->material->sss_back,
								EXPP_MAT_SSS_BACK_MIN,
								EXPP_MAT_SSS_BACK_MAX);
}

static PyObject *Material_setTexture( BPy_Material * self, PyObject * args )
{
	int texnum;
	PyObject *pytex;
	Tex *bltex;
	int texco = TEXCO_ORCO, mapto = MAP_COL;

	if( !PyArg_ParseTuple( args, "iO!|ii", &texnum, &Texture_Type, &pytex,
			       &texco, &mapto ) )
		return EXPP_ReturnPyObjError( PyExc_TypeError,
					      "expected int in [0,17] and Texture" );
	if( ( texnum < 0 ) || ( texnum >= MAX_MTEX ) )
		return EXPP_ReturnPyObjError( PyExc_TypeError,
					      "expected int in [0,17] and Texture" );

	bltex = Texture_FromPyObject( pytex );

	if( !self->material->mtex[texnum] ) {
		/* there isn't an mtex for this slot so we need to make one */
		self->material->mtex[texnum] = add_mtex(  );
	} else {
		/* we already had a texture here so deal with the old one first */
		self->material->mtex[texnum]->tex->id.us--;
	}

	self->material->mtex[texnum]->tex = bltex;
	id_us_plus( &bltex->id );
	self->material->mtex[texnum]->texco = (short)texco;
	self->material->mtex[texnum]->mapto = (short)mapto;

	Py_RETURN_NONE;
}

static int Material_setTextures( BPy_Material * self, PyObject * value )
{
	int i;

	if( !PyList_Check( value ) && !PyTuple_Check( value ) )
		return EXPP_ReturnIntError( PyExc_TypeError,
						"expected tuple or list of integers" );

	/* don't allow more than MAX_MTEX items */
	if( PySequence_Size(value) > MAX_MTEX )
		return EXPP_ReturnIntError( PyExc_AttributeError,
						"size of sequence greater than number of allowed textures" );

	/* get a fast sequence; in Python 2.5, this just return the original
	 * list or tuple and INCREFs it, so we must DECREF */
	value = PySequence_Fast( value, "" );

	/* check the list for valid entries */
	for( i= 0; i < PySequence_Size(value) ; ++i ) {
		PyObject *item = PySequence_Fast_GET_ITEM( value, i );
		if( item == Py_None || ( BPy_MTex_Check( item ) &&
						((BPy_MTex *)item)->type == ID_MA ) ) {
			continue;
		} else {
			Py_DECREF(value);
			return EXPP_ReturnIntError( PyExc_TypeError,
					"expected tuple or list containing material MTex objects and NONE" );
		}
	}

	/* for each MTex object, copy to this structure */
	for( i= 0; i < PySequence_Size(value) ; ++i ) {
		PyObject *item = PySequence_Fast_GET_ITEM( value, i );
		struct MTex *mtex = self->material->mtex[i];
		if( item != Py_None ) {
			BPy_MTex *obj = (BPy_MTex *)item;

			/* if MTex is already at this location, just skip it */
			if( obj->mtex == mtex )	continue;

			/* create a new entry if needed, otherwise update reference count
			 * for texture that is being replaced */
			if( !mtex )
				mtex = self->material->mtex[i] = add_mtex(  );
			else
				mtex->tex->id.us--;

			/* copy the data */
			mtex->tex = obj->mtex->tex;
			id_us_plus( &mtex->tex->id );
			mtex->texco = obj->mtex->texco;
			mtex->mapto = obj->mtex->mapto;
		}
	}

	/* now go back and free any entries now marked as None */
	for( i= 0; i < PySequence_Size(value) ; ++i ) {
		PyObject *item = PySequence_Fast_GET_ITEM( value, i );
		struct MTex *mtex = self->material->mtex[i];
		if( item == Py_None && mtex ) {
			mtex->tex->id.us--;
			MEM_freeN( mtex );
			self->material->mtex[i] = NULL;
		} 
	}

	Py_DECREF(value);
	return 0;
}

static PyObject *Material_clearTexture( BPy_Material * self, PyObject * value )
{
	int texnum = (int)PyInt_AsLong(value);
	struct MTex *mtex;
	/* non ints will be -1 */
	if( ( texnum < 0 ) || ( texnum >= MAX_MTEX ) ) {
		char errstr[64];
		sprintf( errstr, "expected int in [0,%d]", MAX_MTEX );
		return EXPP_ReturnPyObjError( PyExc_TypeError, errstr );
	}

	mtex = self->material->mtex[texnum];
	if( mtex ) {
		if( mtex->tex )
			mtex->tex->id.us--;
		MEM_freeN( mtex );
		self->material->mtex[texnum] = NULL;
	}

	Py_RETURN_NONE;
}

/* mat.addScriptLink */
static PyObject *Material_addScriptLink( BPy_Material * self, PyObject * args )
{
	Material *mat = self->material;
	ScriptLink *slink = NULL;

	slink = &( mat )->scriptlink;

	return EXPP_addScriptLink( slink, args, 0 );
}

/* mat.clearScriptLinks */
static PyObject *Material_clearScriptLinks(BPy_Material *self, PyObject *args )
{
	Material *mat = self->material;
	ScriptLink *slink = NULL;

	slink = &( mat )->scriptlink;

	return EXPP_clearScriptLinks( slink, args );
}

/* mat.getScriptLinks */
static PyObject *Material_getScriptLinks( BPy_Material * self,
					  PyObject * value )
{
	Material *mat = self->material;
	ScriptLink *slink = NULL;
	PyObject *ret = NULL;

	slink = &( mat )->scriptlink;

	/* can't this just return?  EXP_getScriptLinks() returns a PyObject*
	 * or NULL anyway */

	ret = EXPP_getScriptLinks( slink, value, 0 );

	if( ret )
		return ret;
	else
		return NULL;
}

/* mat.__copy__ */
static PyObject *Material_copy( BPy_Material * self )
{
	BPy_Material *pymat; /* for Material Data object wrapper in Python */
	Material *blmat; /* for actual Material Data we create in Blender */
	
	blmat = copy_material( self->material );	/* first copy the Material Data in Blender */

	if( blmat )		/* now create the wrapper obj in Python */
		pymat = ( BPy_Material * ) Material_CreatePyObject( blmat );
	else
		return ( EXPP_ReturnPyObjError( PyExc_RuntimeError,
						"couldn't create Material Data in Blender" ) );

	blmat->id.us = 0;	/* was incref'ed by add_material() above */

	if( pymat == NULL )
		return ( EXPP_ReturnPyObjError( PyExc_MemoryError,
						"couldn't create Material Data object" ) );

	return ( PyObject * ) pymat;
}

/* mat.freeNodes() */
static PyObject *Material_freeNodes( BPy_Material * self )
{
	if (self->material->nodetree) {
		if(self->material->nodetree) {
			ntreeFreeTree(self->material->nodetree);
			MEM_freeN(self->material->nodetree);
		}
		self->material->nodetree = NULL;
		self->material->use_nodes = 0;
		Py_RETURN_TRUE;
	} else {
		Py_RETURN_FALSE;
	}
}

/* mat_a==mat_b or mat_a!=mat_b*/
static int Material_compare( BPy_Material * a, BPy_Material * b )
{
	return ( a->material == b->material) ? 0 : -1;
}

/*****************************************************************************/
/* Function:	Material_repr	 */
/* Description: This is a callback function for the BPy_Material type. It  */
/*		 builds a meaninful string to represent material objects.   */
/*****************************************************************************/
static PyObject *Material_repr( BPy_Material * self )
{
	return PyString_FromFormat( "[Material \"%s\"]",
				    self->material->id.name + 2 );
}

/*****************************************************************************/
/* These functions are used here and in in Texture.c						*/
/*****************************************************************************/
PyObject *EXPP_PyList_fromColorband( ColorBand *coba )
{
	short i;
	PyObject *cbls;
	PyObject *colls;
	
	if (!coba)
		return PyList_New( 0 );
	
	cbls = PyList_New( coba->tot );
	
	for (i=0; i < coba->tot; i++) {
		colls = PyList_New( 5 );
		PyList_SET_ITEM( colls, 0, PyFloat_FromDouble(coba->data[i].r) );
		PyList_SET_ITEM( colls, 1, PyFloat_FromDouble(coba->data[i].g) );
		PyList_SET_ITEM( colls, 2, PyFloat_FromDouble(coba->data[i].b) );
		PyList_SET_ITEM( colls, 3, PyFloat_FromDouble(coba->data[i].a) );
		PyList_SET_ITEM( colls, 4, PyFloat_FromDouble(coba->data[i].pos) );
		PyList_SET_ITEM(cbls, i, colls);
	}
	return cbls;
}

/* make sure you coba is not none before calling this */
int EXPP_Colorband_fromPyList( ColorBand **coba, PyObject * value )
{
	short totcol, i;
	PyObject *colseq;
	PyObject *pyflt;
	float f;
	
	if ( !PySequence_Check( value )  )
		return ( EXPP_ReturnIntError( PyExc_TypeError,
				"Colorband must be a sequence" ) );
	
	totcol = PySequence_Size(value);
	if ( totcol > 31)
		return ( EXPP_ReturnIntError( PyExc_ValueError,
				"Colorband must be between 1 and 31 in length" ) );
	
	if (totcol==0) {
		MEM_freeN(*coba);
		*coba = NULL;
		return 0;
	}
	
	if (!*coba)
		*coba = MEM_callocN( sizeof(ColorBand), "colorband");
	
	for (i=0; i<totcol; i++) {
		colseq = PySequence_GetItem( value, i );
		if ( !PySequence_Check( colseq ) || PySequence_Size( colseq ) != 5) {
			Py_DECREF ( colseq );
			return ( EXPP_ReturnIntError( PyExc_ValueError,
				"Colorband colors must be sequences of 5 floats" ) );
		}
		for (i=0; i<5; i++) {
			pyflt = PySequence_GetItem( colseq, i );
			if (!PyNumber_Check(pyflt)) {
				Py_DECREF ( pyflt );
				Py_DECREF ( colseq );
				return ( EXPP_ReturnIntError( PyExc_ValueError,
					"Colorband colors must be sequences of 5 floats" ) );
			}
			Py_DECREF ( pyflt );
		}
		Py_DECREF ( colseq );
	}
	
	/* ok, continue - should check for 5 floats, will ignore non floats for now */
	(*coba)->tot = totcol;
	for (i=0; i<totcol; i++) {
		colseq = PySequence_GetItem( value, i );
		
		pyflt = PySequence_GetItem( colseq, 0 ); 
		f = (float)PyFloat_AsDouble( pyflt );
		CLAMP(f, 0.0, 1.0);
		(*coba)->data[i].r = f;
		Py_DECREF ( pyflt );
		
		pyflt = PySequence_GetItem( colseq, 1 ); 
		f = (float)PyFloat_AsDouble( pyflt );
		CLAMP(f, 0.0, 1.0);
		(*coba)->data[i].g = f;
		Py_DECREF ( pyflt );
		
		pyflt = PySequence_GetItem( colseq, 2 ); 
		f = (float)PyFloat_AsDouble( pyflt );
		CLAMP(f, 0.0, 1.0);
		(*coba)->data[i].b = f;
		Py_DECREF ( pyflt );
		
		pyflt = PySequence_GetItem( colseq, 3 ); 
		f = (float)PyFloat_AsDouble( pyflt );
		CLAMP(f, 0.0, 1.0);
		(*coba)->data[i].a = f;
		Py_DECREF ( pyflt );
		
		pyflt = PySequence_GetItem( colseq, 4 ); 
		f = (float)PyFloat_AsDouble( pyflt );
		CLAMP(f, 0.0, 1.0);
		(*coba)->data[i].pos = f;
		Py_DECREF ( pyflt );
		
		Py_DECREF ( colseq );
	}
	return 0;
}


/*****************************************************************************/
/* These functions are used in NMesh.c and Object.c	 */
/*****************************************************************************/
PyObject *EXPP_PyList_fromMaterialList( Material ** matlist, int len, int all )
{
	PyObject *list;
	int i;

	list = PyList_New( 0 );
	if( !matlist )
		return list;

	for( i = 0; i < len; i++ ) {
		Material *mat = matlist[i];
		PyObject *ob;

		if( mat ) {
			ob = Material_CreatePyObject( mat );
			PyList_Append( list, ob );
			Py_DECREF( ob );	/* because Append increfs */
		} else if( all ) {	/* return NULL mats (empty slots) as Py_None */
			PyList_Append( list, Py_None );
		}
	}

	return list;
}

Material **EXPP_newMaterialList_fromPyList( PyObject * list )
{
	int i, len;
	BPy_Material *pymat = 0;
	Material *mat;
	Material **matlist;

	len = PySequence_Length( list );
	if( len > 16 )
		len = 16;
	else if( len <= 0 )
		return NULL;

	matlist = EXPP_newMaterialList( len );

	for( i = 0; i < len; i++ ) {

		pymat = ( BPy_Material * ) PySequence_GetItem( list, i );

		if( BPy_Material_Check( ( PyObject * ) pymat ) ) {
			mat = pymat->material;
			matlist[i] = mat;
		} else if( ( PyObject * ) pymat == Py_None ) {
			matlist[i] = NULL;
		} else {	/* error; illegal type in material list */
			Py_DECREF( pymat );
			MEM_freeN( matlist );
			return NULL;
		}

		Py_DECREF( pymat );
	}

	return matlist;
}

Material **EXPP_newMaterialList( int len )
{
	Material **matlist =
		( Material ** ) MEM_mallocN( len * sizeof( Material * ),
					     "MaterialList" );

	return matlist;
}

int EXPP_releaseMaterialList( Material ** matlist, int len )
{
	int i;
	Material *mat;

	if( ( len < 0 ) || ( len > MAXMAT ) ) {
		printf( "illegal matindex!\n" );
		return 0;
	}

	for( i = 0; i < len; i++ ) {
		mat = matlist[i];
		if( mat ) {
			if( ( ( ID * ) mat )->us > 0 )
				( ( ID * ) mat )->us--;
			else
				printf( "FATAL: material usage=0: %s",
					( ( ID * ) mat )->name );
		}
	}
	MEM_freeN( matlist );

	return 1;
}

/** expands pointer array of length 'oldsize' to length 'newsize'.
	* A pointer to the (void *) array must be passed as first argument 
	* The array pointer content can be NULL, in this case a new array of length
	* 'newsize' is created.
	*/

static int expandPtrArray( void **p, int oldsize, int newsize )
{
	void *newarray;

	if( newsize < oldsize ) {
		return 0;
	}
	newarray = MEM_callocN( sizeof( void * ) * newsize, "PtrArray" );
	if( *p ) {
		memcpy( newarray, *p, sizeof( void * ) * oldsize );
		MEM_freeN( *p );
	}
	*p = newarray;
	return 1;
}

int EXPP_synchronizeMaterialLists( Object * object )
{
	Material ***p_dataMaterials = give_matarar( object );
	short *nmaterials = give_totcolp( object );
	int result = 0;

	if( object->totcol > *nmaterials ) {
		/* More object mats than data mats */
		result = expandPtrArray( ( void * ) p_dataMaterials,
					 *nmaterials, object->totcol );
		*nmaterials = object->totcol;
	} else {
		if( object->totcol < *nmaterials ) {
			/* More data mats than object mats */
			result = expandPtrArray( ( void * ) &object->mat,
						 object->totcol, *nmaterials );
			object->totcol = (char)*nmaterials;
		}
	}			/* else no synchronization needed, they are of equal length */

	return result;		/* 1 if changed, 0 otherwise */
}

void EXPP_incr_mats_us( Material ** matlist, int len )
{
	int i;
	Material *mat;

	if( len <= 0 )
		return;

	for( i = 0; i < len; i++ ) {
		mat = matlist[i];
		if( mat )
			mat->id.us++;
	}

	return;
}

static PyObject *Material_getColorComponent( BPy_Material * self, 
							void * closure )
{
	switch ( GET_INT_FROM_POINTER(closure) ) {
	case EXPP_MAT_COMP_R:
		return PyFloat_FromDouble( ( double ) self->material->r );
	case EXPP_MAT_COMP_G:
		return PyFloat_FromDouble( ( double ) self->material->g );
	case EXPP_MAT_COMP_B:
		return PyFloat_FromDouble( ( double ) self->material->b );
	case EXPP_MAT_COMP_SPECR:
		return PyFloat_FromDouble( ( double ) self->material->specr );
	case EXPP_MAT_COMP_SPECG:
		return PyFloat_FromDouble( ( double ) self->material->specg );
	case EXPP_MAT_COMP_SPECB:
		return PyFloat_FromDouble( ( double ) self->material->specb );
	case EXPP_MAT_COMP_MIRR:
		return PyFloat_FromDouble( ( double ) self->material->mirr );
	case EXPP_MAT_COMP_MIRG:
		return PyFloat_FromDouble( ( double ) self->material->mirg );
	case EXPP_MAT_COMP_MIRB:
		return PyFloat_FromDouble( ( double ) self->material->mirb );
	case EXPP_MAT_COMP_SSSR:
		return PyFloat_FromDouble( ( double ) self->material->sss_col[0] );
	case EXPP_MAT_COMP_SSSG:
		return PyFloat_FromDouble( ( double ) self->material->sss_col[1] );
	case EXPP_MAT_COMP_SSSB:
		return PyFloat_FromDouble( ( double ) self->material->sss_col[2] );
	default:
		return EXPP_ReturnPyObjError( PyExc_RuntimeError,
					"unknown color component specified" );
	}
}

static PyObject *Material_getColorband( BPy_Material * self, void * type)
{
	switch( (long)type ) {
    case 0:	/* these are backwards, but that how it works */
		return EXPP_PyList_fromColorband( self->material->ramp_col );
    case 1:
		return EXPP_PyList_fromColorband( self->material->ramp_spec );
	}
	Py_RETURN_NONE;
}

static int Material_setColorband( BPy_Material * self, PyObject * value, void * type)
{
	switch( (long)type ) {
    case 0:	/* these are backwards, but that how it works */
		return EXPP_Colorband_fromPyList( &self->material->ramp_col, value );
    case 1:
		return EXPP_Colorband_fromPyList( &self->material->ramp_spec, value );
	}
	return 0;
}

/* #####DEPRECATED###### */

static PyObject *Matr_oldsetAdd( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setAdd );
}

static PyObject *Matr_oldsetAlpha( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setAlpha );
}

static PyObject *Matr_oldsetAmb( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setAmb );
}

static PyObject *Matr_oldsetDiffuseDarkness( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setDiffuseDarkness );
}

static PyObject *Matr_oldsetDiffuseShader( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setDiffuseShader );
}

static PyObject *Matr_oldsetDiffuseSize( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setDiffuseSize );
}

static PyObject *Matr_oldsetDiffuseSmooth( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setDiffuseSmooth );
}

static PyObject *Matr_oldsetEmit( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setEmit );
}

static PyObject *Matr_oldsetFilter( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setFilter );
}

static PyObject *Matr_oldsetFlareBoost( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setFlareBoost );
}

static PyObject *Matr_oldsetFlareSeed( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setFlareSeed );
}

static PyObject *Matr_oldsetFlareSize( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setFlareSize );
}

static PyObject *Matr_oldsetFresnelMirr( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setFresnelMirr );
}

static PyObject *Matr_oldsetFresnelMirrFac( BPy_Material * self,
					     PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setFresnelMirrFac );
}

static PyObject *Matr_oldsetFresnelTrans( BPy_Material * self,
					   PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setFresnelTrans );
}

static PyObject *Matr_oldsetFresnelTransFac( BPy_Material * self,
					      PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setFresnelTransFac );
}

static PyObject *Matr_oldsetHaloSeed( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setHaloSeed );
}

static PyObject *Matr_oldsetHaloSize( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setHaloSize );
}

static PyObject *Matr_oldsetHardness( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setHardness );
}

static PyObject *Matr_oldsetIOR( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setIOR );
}

static PyObject *Matr_oldsetNFlares( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setNFlares );
}

static PyObject *Matr_oldsetNLines( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setNLines );
}

static PyObject *Matr_oldsetNRings( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setNRings );
}

static PyObject *Matr_oldsetNStars( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setNStars );
}

static PyObject *Matr_oldsetRayMirr( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setRayMirr );
}

static PyObject *Matr_oldsetRoughness( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setRoughness );
}

static PyObject *Matr_oldsetMirrDepth( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setMirrDepth );
}

static PyObject *Matr_oldsetRef( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setRef );
}

static PyObject *Matr_oldsetRefracIndex( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setRefracIndex );
}

static PyObject *Matr_oldsetRms( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setRms );
}

static PyObject *Matr_oldsetSpec( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setSpec );
}

static PyObject *Matr_oldsetSpecShader( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setSpecShader );
}

static PyObject *Matr_oldsetSpecSize( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setSpecSize );
}

static PyObject *Matr_oldsetSpecSmooth( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setSpecSmooth );
}

static PyObject *Matr_oldsetSpecTransp( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setSpecTransp );
}

static PyObject *Matr_oldsetSubSize( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setSubSize );
}

static PyObject *Matr_oldsetTranslucency( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setTranslucency );
}

static PyObject *Matr_oldsetTransDepth( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setTransDepth );
}

static PyObject *Matr_oldsetZOffset( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setZOffset );
}

static PyObject *Matr_oldsetRGBCol( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapperTuple( (void *)self, args,
			(setter)Material_setRGBCol );
}

static PyObject *Matr_oldsetSpecCol( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapperTuple( (void *)self, args,
			(setter)Material_setSpecCol );
}

static PyObject *Matr_oldsetMirCol( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapperTuple( (void *)self, args,
			(setter)Material_setMirCol );
}


/* Possible modes are traceable, shadow, shadeless, wire, vcolLight,
 * vcolPaint, halo, ztransp, zinvert, haloRings, env, haloLines,
 * onlyShadow, xalpha, star, faceTexture, haloTex, haloPuno, noMist,
 * haloShaded, haloFlare */

static PyObject *Matr_oldsetMode( BPy_Material * self, PyObject * args )
{
	unsigned int i, flag = 0, ok = 0;
	PyObject *value, *error;
	char *m[28] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL
	};

	/* 
	 * check for a single integer argument; do a quick check for now
	 * that the value is not larger than double the highest flag bit
	 */

	if ( (PySequence_Size( args ) == 1)
		    && PyInt_Check ( PyTuple_GET_ITEM ( args , 0 ) )
		    && PyArg_ParseTuple( args, "i", &flag ) 
			&& (flag & MA_MODE_MASK ) == flag ) {
			ok = 1;

	/*
	 * check for either an empty argument list, or up to 28 strings
	 */

	} else if( PyArg_ParseTuple( args, "|ssssssssssssssssssssssssssss",
			       &m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6],
			       &m[7], &m[8], &m[9], &m[10], &m[11], &m[12],
			       &m[13], &m[14], &m[15], &m[16], &m[17], &m[18],
			       &m[19], &m[20], &m[21], &m[22], &m[23], &m[24],
			       &m[25], &m[26], &m[27] ) ) {
		for( i = 0; i < 28; i++ ) {
			if( m[i] == NULL )
				break;
			if( strcmp( m[i], "Traceable" ) == 0 )
				flag |= MA_TRACEBLE;
			else if( strcmp( m[i], "Shadow" ) == 0 )
				flag |= MA_SHADOW;
			else if( strcmp( m[i], "Shadeless" ) == 0 )
				flag |= MA_SHLESS;
			else if( strcmp( m[i], "Wire" ) == 0 )
				flag |= MA_WIRE;
			else if( strcmp( m[i], "VColLight" ) == 0 )
				flag |= MA_VERTEXCOL;
			else if( strcmp( m[i], "VColPaint" ) == 0 )
				flag |= MA_VERTEXCOLP;
			else if( strcmp( m[i], "Halo" ) == 0 )
				flag |= MA_HALO;
			else if( strcmp( m[i], "ZTransp" ) == 0 )
				flag |= MA_ZTRA;
			else if( strcmp( m[i], "ZInvert" ) == 0 )
				flag |= MA_ZINV;
			else if( strcmp( m[i], "HaloRings" ) == 0 )
				flag |= MA_HALO_RINGS;
			else if( strcmp( m[i], "HaloLines" ) == 0 )
				flag |= MA_HALO_LINES;
			else if( strcmp( m[i], "OnlyShadow" ) == 0 )
				flag |= MA_ONLYSHADOW;
			else if( strcmp( m[i], "HaloXAlpha" ) == 0 )
				flag |= MA_HALO_XALPHA;
			else if( strcmp( m[i], "HaloStar" ) == 0 )
				flag |= MA_STAR;
			else if( strcmp( m[i], "TexFace" ) == 0 )
				flag |= MA_FACETEXTURE;
			else if( strcmp( m[i], "HaloTex" ) == 0 )
				flag |= MA_HALOTEX;
			else if( strcmp( m[i], "HaloPuno" ) == 0 )
				flag |= MA_HALOPUNO;
			else if( strcmp( m[i], "NoMist" ) == 0 )
				flag |= MA_NOMIST;
			else if( strcmp( m[i], "HaloShaded" ) == 0 )
				flag |= MA_HALO_SHADE;
			else if( strcmp( m[i], "HaloFlare" ) == 0 )
				flag |= MA_HALO_FLARE;
			else if( strcmp( m[i], "Radio" ) == 0 )
				flag |= MA_RADIO;
			/* ** Mirror ** */
			else if( strcmp( m[i], "RayMirr" ) == 0 )
				flag |= MA_RAYMIRROR;
			else if( strcmp( m[i], "ZTransp" ) == 0 )
				flag |= MA_ZTRA;
			else if( strcmp( m[i], "RayTransp" ) == 0 )
				flag |= MA_RAYTRANSP;
			else if( strcmp( m[i], "OnlyShadow" ) == 0 )
				flag |= MA_ONLYSHADOW;
			else if( strcmp( m[i], "NoMist" ) == 0 )
				flag |= MA_NOMIST;
			else if( strcmp( m[i], "Env" ) == 0 )
				flag |= MA_ENV;
			else
				return ( EXPP_ReturnPyObjError( PyExc_AttributeError,
								"unknown Material mode argument" ) );
		}
		ok = 1;
	}

	/* if neither input method worked, then throw an exception */

	if ( ok == 0 )
		return ( EXPP_ReturnPyObjError
			 ( PyExc_AttributeError,
			   "expected nothing, an integer or up to 22 string argument(s)" ) );
	/* build tuple, call wrapper */

	value = Py_BuildValue("(i)", flag);
	error = EXPP_setterWrapper( (void *)self, value, (setter)Material_setMode );
	Py_DECREF ( value );
	return error;
}

static PyObject *Matr_oldsetIpo( BPy_Material * self, PyObject * args )
{
	return EXPP_setterWrapper( (void *)self, args, (setter)Material_setIpo );
}

/*
 * clearIpo() returns True/False depending on whether material has an Ipo
 */

static PyObject *Material_clearIpo( BPy_Material * self )
{
	/* if Ipo defined, delete it and return true */

	if( self->material->ipo ) {
		PyObject *value = Py_BuildValue( "(O)", Py_None );
		EXPP_setterWrapper( (void *)self, value, (setter)Material_setIpo );
		Py_DECREF ( value );
		return EXPP_incr_ret_True();
	}
	return EXPP_incr_ret_False(); /* no ipo found */
}

/* RampCol Factor */

static PyObject *Material_getColorbandDiffuseFactor( BPy_Material * self )
{
	return PyFloat_FromDouble( (double) self->material->rampfac_col);
}

static PyObject *Material_getColorbandSpecularFactor( BPy_Material * self )
{
	return PyFloat_FromDouble( (double) self->material->rampfac_spec);
}

static int Material_setColorbandDiffuseFactor ( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped(value, &self->material->rampfac_col,
			EXPP_MAT_COLORBAND_FACTOR_MIN, EXPP_MAT_COLORBAND_FACTOR_MAX);
}

static int Material_setColorbandSpecularFactor ( BPy_Material * self, PyObject * value )
{
	return EXPP_setFloatClamped(value, &self->material->rampfac_spec,
			EXPP_MAT_COLORBAND_FACTOR_MIN, EXPP_MAT_COLORBAND_FACTOR_MAX);
}

/* RampCol Method */

static PyObject *Material_getColorbandDiffuseMethod( BPy_Material * self )
{
	return PyInt_FromLong( (long) self->material->rampblend_col);
}

static PyObject *Material_getColorbandSpecularMethod ( BPy_Material * self )
{
	return PyInt_FromLong( (long) self->material->rampblend_spec);
}

static int Material_setColorbandDiffuseMethod ( BPy_Material * self, PyObject * value)
{
	return EXPP_setIValueClamped(value, &self->material->rampblend_col,
			MA_RAMP_BLEND, MA_RAMP_COLOR, 'b');
}

static int Material_setColorbandSpecularMethod ( BPy_Material * self, PyObject * value)
{
	return EXPP_setIValueClamped(value, &self->material->rampblend_spec,
			MA_RAMP_BLEND, MA_RAMP_COLOR, 'b');
}

/* RampCol Input */

static PyObject *Material_getColorbandDiffuseInput( BPy_Material * self )
{
	return PyInt_FromLong( (long) self->material->rampin_col);
}

static PyObject *Material_getColorbandSpecularInput( BPy_Material * self )
{
	return PyInt_FromLong( (long) self->material->rampin_spec);
}

static int Material_setColorbandDiffuseInput ( BPy_Material * self, PyObject * value)
{
	return EXPP_setIValueClamped(value, &self->material->rampin_col,
			MA_RAMP_IN_SHADER, MA_RAMP_IN_RESULT, 'b');
}

static int Material_setColorbandSpecularInput ( BPy_Material * self, PyObject * value)
{
	return EXPP_setIValueClamped(value, &self->material->rampin_spec,
			MA_RAMP_IN_SHADER, MA_RAMP_IN_RESULT, 'b');
}

/* Strand */

static PyObject *Material_getStrandTangentShad( BPy_Material * self )
{
	return PyInt_FromLong( ((long)( self->material->mode & MA_TANGENT_STR )) > 0 );
}

static int Material_setStrandTangentShad( BPy_Material * self, PyObject * value)
{
	int number;

	if( !PyInt_Check( value ) )
		return EXPP_ReturnIntError( PyExc_TypeError, "expected int argument" );

	number = PyInt_AS_LONG( value );

	if (number){
		self->material->mode |= MA_TANGENT_STR;
	}else{
		self->material->mode &= ~MA_TANGENT_STR;
	}

	return 0;
}

static PyObject *Material_getStrandSurfDiff( BPy_Material * self )
{
	return PyInt_FromLong( ((long)( self->material->mode & MA_STR_SURFDIFF )) > 0 );
}

static int Material_setStrandSurfDiff( BPy_Material * self, PyObject * value)
{
	int number;

	if( !PyInt_Check( value ) )
		return EXPP_ReturnIntError( PyExc_TypeError, "expected int argument" );

	number = PyInt_AS_LONG( value );

	if (number){
		self->material->mode |= MA_STR_SURFDIFF;
	}else{
		self->material->mode &= ~MA_STR_SURFDIFF;
	}

	return 0;
}

static PyObject *Material_getStrandDist( BPy_Material * self )
{
	return PyFloat_FromDouble( ((float)( self->material->strand_surfnor )) );
}

static int Material_setStrandDist( BPy_Material * self, PyObject * value)
{
	return EXPP_setFloatRange( value, &self->material->strand_surfnor,	0.0, 10.0 );
}

static PyObject *Material_getStrandBlendUnit( BPy_Material * self )
{
	return PyInt_FromLong( ((long)( self->material->mode & MA_STR_B_UNITS )) > 0 );
}

static int Material_setStrandBlendUnit( BPy_Material * self, PyObject * value)
{
	int number;

	if( !PyInt_Check( value ) )
		return EXPP_ReturnIntError( PyExc_TypeError, "expected int argument" );

	number = PyInt_AS_LONG( value );

	if (number){
		self->material->mode |= MA_STR_B_UNITS;
	}else{
		self->material->mode &= ~MA_STR_B_UNITS;
	}

	return 0;
}

static PyObject *Material_getStrandStart( BPy_Material * self )
{
	return PyFloat_FromDouble( ((float)( self->material->strand_sta )) );
}

static int Material_setStrandStart( BPy_Material * self, PyObject * value)
{
	return EXPP_setFloatRange( value, &self->material->strand_sta,	0.0001, 2.0 );
}

static PyObject *Material_getStrandEnd( BPy_Material * self )
{
	return PyFloat_FromDouble( ((float)( self->material->strand_end )) );
}

static int Material_setStrandEnd( BPy_Material * self, PyObject * value)
{
	return EXPP_setFloatRange( value, &self->material->strand_end,	0.0001, 1.0 );
}

static PyObject *Material_getStrandMin( BPy_Material * self )
{
	return PyFloat_FromDouble( ((float)( self->material->strand_min )) );
}

static int Material_setStrandMin( BPy_Material * self, PyObject * value)
{
	return EXPP_setFloatRange( value, &self->material->strand_min,	0.0001, 10.0 );
}

static PyObject *Material_getStrandShape( BPy_Material * self )
{
	return PyFloat_FromDouble( ((float)( self->material->strand_ease )) );
}

static int Material_setStrandShape( BPy_Material * self, PyObject * value)
{
	return EXPP_setFloatRange( value, &self->material->strand_ease,	-0.9, 0.9 );
}

static PyObject *Material_getStrandWidthFad( BPy_Material * self )
{
	return PyFloat_FromDouble( ((float)( self->material->strand_widthfade )) );
}

static int Material_setStrandWidthFad( BPy_Material * self, PyObject * value)
{
	return EXPP_setFloatRange( value, &self->material->strand_widthfade,	0.0, 2.0 );
}

static PyObject *Material_getStrandUV( BPy_Material * self )
{
	return EXPP_ReturnPyObjError( PyExc_NotImplementedError,
		"Material.strandUV not implemented" );
}

static int Material_setStrandUV( BPy_Material * self, PyObject * value)
{
	return EXPP_ReturnPyObjError( PyExc_NotImplementedError,
		"Material.strandUV not implemented" );
}
