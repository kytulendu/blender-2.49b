/*
 * $Id: KX_GameObject.h 22205 2009-08-04 05:14:10Z campbellbarton $
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
 * General KX game object.
 */

#ifndef __KX_GAMEOBJECT
#define __KX_GAMEOBJECT

#ifdef WIN32
// get rid of this stupid "warning 'this' used in initialiser list", generated by VC when including Solid/Sumo
#pragma warning (disable : 4355) 
#endif 


#include "ListValue.h"
#include "SCA_IObject.h"
#include "SG_Node.h"
#include "MT_Transform.h"
#include "MT_CmMatrix4x4.h"
#include "GEN_Map.h"
#include "GEN_HashedPtr.h"
#include "KX_Scene.h"
#include "KX_KetsjiEngine.h" /* for m_anim_framerate */
#include "KX_IPhysicsController.h" /* for suspend/resume */
#include "DNA_object_types.h"
#include "SCA_LogicManager.h" /* for ConvertPythonToGameObject to search object names */
#define KX_OB_DYNAMIC 1

//Forward declarations.
struct KX_ClientObjectInfo;
class KX_RayCast;
class RAS_MeshObject;
class KX_IPhysicsController;
class PHY_IGraphicController;
class PHY_IPhysicsEnvironment;
struct Object;

/* utility conversion function */
bool ConvertPythonToGameObject(PyObject * value, KX_GameObject **object, bool py_none_ok, const char *error_prefix);

/**
 * KX_GameObject is the main class for dynamic objects.
 */
class KX_GameObject : public SCA_IObject
{
	Py_Header;
protected:

	bool								m_bDyna;
	KX_ClientObjectInfo*				m_pClient_info;
	STR_String							m_name;
	STR_String							m_text;
	int									m_layer;
	std::vector<RAS_MeshObject*>		m_meshes;
	SG_QList							m_meshSlots;	// head of mesh slots of this 
	struct Object*						m_pBlenderObject;
	struct Object*						m_pBlenderGroupObject;
	
	bool								m_bSuspendDynamics;
	bool								m_bUseObjectColor;
	bool								m_bIsNegativeScaling;
	MT_Vector4							m_objectColor;

	// visible = user setting
	// culled = while rendering, depending on camera
	bool       							m_bVisible; 
	bool       							m_bCulled; 
	bool								m_bOccluder;

	KX_IPhysicsController*				m_pPhysicsController1;
	PHY_IGraphicController*				m_pGraphicController;
	STR_String							m_testPropName;
	bool								m_xray;
	KX_GameObject*						m_pHitObject;

	SG_Node*							m_pSGNode;

	MT_CmMatrix4x4						m_OpenGL_4x4Matrix;
	
public:
	bool								m_isDeformable;

	/**
	 * Helper function for modules that can't include KX_ClientObjectInfo.h
	 */
	static KX_GameObject* GetClientObject(KX_ClientObjectInfo* info);

	// Python attributes that wont convert into CValue
	// 
	// there are 2 places attributes can be stored, in the CValue,
	// where attributes are converted into BGE's CValue types
	// these can be used with property actuators
	//
	// For the python API, For types that cannot be converted into CValues (lists, dicts, GameObjects)
	// these will be put into "m_attr_dict", logic bricks cannot access them.
	// 
	// rules for setting attributes.
	// 
	// * there should NEVER be a CValue and a m_attr_dict attribute with matching names. get/sets make sure of this.
	// * if CValue conversion fails, use a PyObject in "m_attr_dict"
	// * when assigning a value, first see if it can be a CValue, if it can remove the "m_attr_dict" and set the CValue
	// 
	PyObject*							m_attr_dict; 

	virtual void	/* This function should be virtual - derived classed override it */
	Relink(
		GEN_Map<GEN_HashedPtr, void*> *map
	);

	/**
	 * Compute an OpenGl compatable 4x4 matrix. Has the
	 * side effect of storing the result internally. The
	 * memory for the matrix remains the property of this class.
	 */ 
		double*						
	GetOpenGLMatrix(
	);

	/**
	 * Return a pointer to a MT_CmMatrix4x4 storing the 
	 * opengl transformation for this object. This is updated
	 * by a call to GetOpenGLMatrix(). This class owns the 
	 * memory for the returned matrix.
	 */

		MT_CmMatrix4x4*				
	GetOpenGLMatrixPtr(
	) { 
		return &m_OpenGL_4x4Matrix;
	};

	/** 
	 * Get a pointer to the game object that is the parent of 
	 * this object. Or NULL if there is no parent. The returned
	 * object is part of a reference counting scheme. Calling
	 * this function ups the reference count on the returned 
	 * object. It is the responsibility of the caller to decrement
	 * the reference count when you have finished with it.
	 */
		KX_GameObject*				
	GetParent(
	);

	/** 
	 * Sets the parent of this object to a game object
	 */			
	void SetParent(KX_Scene *scene, KX_GameObject *obj, bool addToCompound=true, bool ghost=true);

	/** 
	 * Removes the parent of this object to a game object
	 */			
	void RemoveParent(KX_Scene *scene);

	/**
	 * Construct a game object. This class also inherits the 
	 * default constructors - use those with care!
	 */

	KX_GameObject(
		void* sgReplicationInfo,
		SG_Callbacks callbacks,
		PyTypeObject* T=&Type
	);

	virtual 
	~KX_GameObject(
	);

	/** 
	 * @section Stuff which is here due to poor design.
	 * Inherited from CValue and needs an implementation. 
	 * Do not expect these functions do to anything sensible.
	 */

	/**
	 * Inherited from CValue -- does nothing!
	 */
		CValue*				
	Calc(
		VALUE_OPERATOR op,
		CValue *val
	);

	/**
	 * Inherited from CValue -- does nothing!
	 */
		CValue*				
	CalcFinal(
		VALUE_DATA_TYPE dtype,
		VALUE_OPERATOR op,
		CValue *val
	);

	/**
	 * Inherited from CValue -- does nothing!
	 */
	const 
		STR_String &	
	GetText(
	);

	/**
	 * Inherited from CValue -- does nothing!
	 */
		double
	GetNumber(
	);

	/**
	 * @section Inherited from CValue. These are the useful
	 * part of the CValue interface that this class implements. 
	 */

	/**
	 * Inherited from CValue -- returns the name of this object.
	 */
		STR_String&			
	GetName(
	);

	/**
	 * Inherited from CValue -- set the name of this object.
	 */
		void				
	SetName(
		const char *name
	);

	/** 
	 * Inherited from CValue -- return a new copy of this
	 * instance allocated on the heap. Ownership of the new 
	 * object belongs with the caller.
	 */
	virtual	CValue*				
	GetReplica(
	);
	
	/**
	 * Inherited from CValue -- Makes sure any internal 
	 * data owned by this class is deep copied. Called internally
	 */
	virtual	void				
	ProcessReplica();

	/** 
	 * Return the linear velocity of the game object.
	 */
		MT_Vector3 
	GetLinearVelocity(
		bool local=false
	);

	/** 
	 * Return the linear velocity of a given point in world coordinate
	 * but relative to center of object ([0,0,0]=center of object)
	 */
		MT_Vector3 
	GetVelocity(
		const MT_Point3& position
	);

	/**
	 * Return the mass of the object
	 */
		MT_Scalar	
	GetMass();

	/**
	 * Return the local inertia vector of the object
	 */
		MT_Vector3
	GetLocalInertia();

	/** 
	 * Return the angular velocity of the game object.
	 */
		MT_Vector3 
	GetAngularVelocity(
		bool local=false
	);

	/** 
	 * Align the object to a given normal.
	 */
		void 
	AlignAxisToVect(
		const MT_Vector3& vect,
		int axis = 2,
		float fac = 1.0
	);

	/** 
	 * Quick'n'dirty obcolor ipo stuff
	 */

		void				
	SetObjectColor(
		const MT_Vector4& rgbavec
	);


		void 
	ResolveCombinedVelocities(
		const MT_Vector3 & lin_vel,
		const MT_Vector3 & ang_vel,
		bool lin_vel_local,
		bool ang_vel_local
	);

	/**
	 * @return a pointer to the physics controller owned by this class.
	 */

	KX_IPhysicsController* GetPhysicsController() ;

	void	SetPhysicsController(KX_IPhysicsController*	physicscontroller,bool isDynamic) 
	{ 
		m_bDyna = isDynamic;
		m_pPhysicsController1 = physicscontroller;
	}

	virtual class RAS_Deformer* GetDeformer()
	{
		return 0;
	}
	virtual void	SetDeformer(class RAS_Deformer* deformer)
	{

	}

	/**
	 * @return a pointer to the graphic controller owner by this class 
	 */
	PHY_IGraphicController* GetGraphicController()
	{
		return m_pGraphicController;
	}

	void SetGraphicController(PHY_IGraphicController* graphiccontroller) 
	{ 
		m_pGraphicController = graphiccontroller;
	}
	/*
	 * @add/remove the graphic controller to the physic system
	 */
	void ActivateGraphicController(bool recurse);

	/**
	 * @section Coordinate system manipulation functions
	 */

	void	NodeSetLocalPosition(const MT_Point3& trans	);

	void	NodeSetLocalOrientation(const MT_Matrix3x3& rot	);

	void	NodeSetLocalScale(	const MT_Vector3& scale	);

	void	NodeSetRelativeScale(	const MT_Vector3& scale	);

	// adapt local position so that world position is set to desired position
	void	NodeSetWorldPosition(const MT_Point3& trans);

		void						
	NodeUpdateGS(
		double time
	);

	const 
		MT_Matrix3x3&			
	NodeGetWorldOrientation(
	) const;

	const 
		MT_Vector3&			
	NodeGetWorldScaling(
	) const;

	const 
		MT_Point3&			
	NodeGetWorldPosition(
	) const;


	/**
	 * @section scene graph node accessor functions.
	 */

	SG_Node*	GetSGNode(	) 
	{ 
		return m_pSGNode;
	}

	const 	SG_Node* GetSGNode(	) const	
	{ 
		return m_pSGNode;
	}

	/**
	 * @section blender object accessor functions.
	 */

	struct Object* GetBlenderObject( )
	{
		return m_pBlenderObject;
	}

	void SetBlenderObject( struct Object* obj)
	{
		m_pBlenderObject = obj;
	}

	struct Object* GetBlenderGroupObject( )
	{
		return m_pBlenderGroupObject;
	}

	void SetBlenderGroupObject( struct Object* obj)
	{
		m_pBlenderGroupObject = obj;
	}
	
	bool IsDupliGroup()
	{ 
		return (m_pBlenderObject &&
				(m_pBlenderObject->transflag & OB_DUPLIGROUP) &&
				m_pBlenderObject->dup_group != NULL) ? true : false;
	}

	/**
	 * Set the Scene graph node for this game object.
	 * warning - it is your responsibility to make sure
	 * all controllers look at this new node. You must
	 * also take care of the memory associated with the
	 * old node. This class takes ownership of the new
	 * node.
	 */
		void	SetSGNode(SG_Node* node	)
		{ 
			m_pSGNode = node; 
		}
	
	//Is it a dynamic/physics object ?
	bool	IsDynamic() const 
	{ 
		return m_bDyna; 
	}

	/**
	 * Check if this object has a vertex parent relationship
	 */
	bool IsVertexParent( )
	{
		return (m_pSGNode && m_pSGNode->GetSGParent() && m_pSGNode->GetSGParent()->IsVertexParent());
	}

	bool RayHit(KX_ClientObjectInfo* client, KX_RayCast* result, void * const data);
	bool NeedRayCast(KX_ClientObjectInfo* client);


	/**
	 * @section Physics accessors for this node.
	 *
	 * All these calls get passed directly to the physics controller 
	 * owned by this object.
	 * This is real interface bloat. Why not just use the physics controller
	 * directly? I think this is because the python interface is in the wrong
	 * place.
	 */

		void						
	ApplyForce(
		const MT_Vector3& force,	bool local
	);

		void						
	ApplyTorque(
		const MT_Vector3& torque,
		bool local
	);

		void						
	ApplyRotation(
		const MT_Vector3& drot,
		bool local
	);

		void						
	ApplyMovement(
		const MT_Vector3& dloc,
		bool local
	);

		void						
	addLinearVelocity(
		const MT_Vector3& lin_vel,
		bool local
	);

		void						
	setLinearVelocity(
		const MT_Vector3& lin_vel,
		bool local
	);

		void						
	setAngularVelocity(
		const MT_Vector3& ang_vel,
		bool local
	);

	/**	
	 * Update the physics object transform based upon the current SG_Node
	 * position.
	 */
		void
	UpdateTransform(
	);

	static void UpdateTransformFunc(SG_IObject* node, void* gameobj, void* scene);

	/**
	 * only used for sensor objects
	 */
	void SynchronizeTransform();

	static void SynchronizeTransformFunc(SG_IObject* node, void* gameobj, void* scene);

	/**
	 * Function to set IPO option at start of IPO
	 */ 
		void	
	InitIPO(
		bool ipo_as_force,
		bool ipo_add,
		bool ipo_local
	);

	/**
	 * Odd function to update an ipo. ???
	 */ 
		void	
	UpdateIPO(
		float curframetime,
		bool recurse
	);
	/**
	 * Updates Material Ipo data 
	 */
		void 
	UpdateMaterialData(
		dword matname_hash,
		MT_Vector4 rgba,
		MT_Vector3 specrgb,
		MT_Scalar hard,
		MT_Scalar spec,
		MT_Scalar ref,
		MT_Scalar emit,
		MT_Scalar alpha
	);

	/**
	 * @section Mesh accessor functions.
	 */

	/**	
	 * Update buckets to indicate that there is a new
	 * user of this object's meshes.
	 */
		void						
	AddMeshUser(
	);
	
	/**	
	 * Update buckets with data about the mesh after
	 * creating or duplicating the object, changing
	 * visibility, object color, .. .
	 */
		void						
	UpdateBuckets(
		bool recursive
	);

	/**
	 * Clear the meshes associated with this class
	 * and remove from the bucketing system.
	 * Don't think this actually deletes any of the meshes.
	 */
		void						
	RemoveMeshes(
	);

	/**
	 * Add a mesh to the set of meshes associated with this
	 * node. Meshes added in this way are not deleted by this class.
	 * Make sure you call RemoveMeshes() before deleting the
	 * mesh though,
	 */
		void						
	AddMesh(
		RAS_MeshObject* mesh
	){ 
		m_meshes.push_back(mesh);
	}

	/**
	 * Pick out a mesh associated with the integer 'num'.
	 */
		RAS_MeshObject*				
	GetMesh(
		int num
	) const { 
		return m_meshes[num]; 
	}

	/**
	 * Return the number of meshes currently associated with this
	 * game object.
	 */
		int							
	GetMeshCount(
	) const { 
		return m_meshes.size(); 
	}
	
	/**	
	 * Set the debug color of the meshes associated with this
	 * class. Does this still work?
	 */
		void						
	SetDebugColor(
		unsigned int bgra
	);

	/** 
	 * Reset the debug color of meshes associated with this class.
	 */
		void						
	ResetDebugColor(
	);

	/**
	 * Was this object marked visible? (only for the explicit
	 * visibility system).
	 */
		bool
	GetVisible(
		void
	);

	/**
	 * Set visibility flag of this object
	 */
		void
	SetVisible(
		bool b,
		bool recursive
	);

	/**
	 * Was this object culled?
	 */
	inline bool
	GetCulled(
		void
	) { return m_bCulled; }

	/**
	 * Set culled flag of this object
	 */
	inline void
	SetCulled(
		bool c
	) { m_bCulled = c; }
	
	/**
	 * Is this object an occluder?
	 */
	inline bool
	GetOccluder(
		void
	) { return m_bOccluder; }

	/**
	 * Set occluder flag of this object
	 */
	void
	SetOccluder(
		bool v,
		bool recursive
	);
	
	/**
	 * Change the layer of the object (when it is added in another layer
	 * than the original layer)
	 */
		void
	SetLayer(
		int l
	);

	/**
	 * Get the object layer
	 */
		int
	GetLayer(
		void
	);
		
	/**
	 * Get the negative scaling state
	 */
		bool
	IsNegativeScaling(
		void
	) { return m_bIsNegativeScaling; }

	/**
	 * Is this a light?
	 */
		virtual bool
	IsLight(
		void
	) { return false; }

	/**
	 * @section Logic bubbling methods.
	 */

	/**
	 * Stop making progress
	 */
	void Suspend(void);

	/**
	 * Resume making progress
	 */
	void Resume(void);
	
	void SuspendDynamics(void) {
		if (m_bSuspendDynamics)
		{
			return;
		}
	
		if (m_pPhysicsController1)
		{
			m_pPhysicsController1->SuspendDynamics();
		}
		m_bSuspendDynamics = true;
	}
	
	void RestoreDynamics(void) {	
		if (!m_bSuspendDynamics)
		{
			return;
		}
	
		if (m_pPhysicsController1)
		{
			m_pPhysicsController1->RestoreDynamics();
		}
		m_bSuspendDynamics = false;
	}
	
	KX_ClientObjectInfo* getClientInfo() { return m_pClient_info; }
	
	CListValue* GetChildren();
	CListValue* GetChildrenRecursive();
	
	/**
	 * @section Python interface functions.
	 */
	
	virtual PyObject* py_getattro(PyObject *attr);
	virtual PyObject* py_getattro_dict();
	virtual int py_setattro(PyObject *attr, PyObject *value);		// py_setattro method
	virtual int				py_delattro(PyObject *attr);
	virtual PyObject* py_repr(void)
	{
		return PyString_FromString(GetName().ReadPtr());
	}
	
	
	/* quite annoying that we need these but the bloody 
	 * py_getattro_up and py_setattro_up macro's have a returns in them! */
	PyObject* py_getattro__internal(PyObject *attr);
	int py_setattro__internal(PyObject *attr, PyObject *value);		// py_setattro method
	
		
	KX_PYMETHOD_NOARGS(KX_GameObject,GetPosition);
	KX_PYMETHOD_O(KX_GameObject,SetPosition);
	KX_PYMETHOD_O(KX_GameObject,SetWorldPosition);
	KX_PYMETHOD_VARARGS(KX_GameObject, ApplyForce);
	KX_PYMETHOD_VARARGS(KX_GameObject, ApplyTorque);
	KX_PYMETHOD_VARARGS(KX_GameObject, ApplyRotation);
	KX_PYMETHOD_VARARGS(KX_GameObject, ApplyMovement);
	KX_PYMETHOD_VARARGS(KX_GameObject,GetLinearVelocity);
	KX_PYMETHOD_VARARGS(KX_GameObject,SetLinearVelocity);
	KX_PYMETHOD_VARARGS(KX_GameObject,GetAngularVelocity);
	KX_PYMETHOD_VARARGS(KX_GameObject,SetAngularVelocity);
	KX_PYMETHOD_VARARGS(KX_GameObject,GetVelocity);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetMass);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetReactionForce);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetOrientation);
	KX_PYMETHOD_O(KX_GameObject,SetOrientation);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetVisible);
	KX_PYMETHOD_VARARGS(KX_GameObject,SetVisible);
	KX_PYMETHOD_VARARGS(KX_GameObject,SetOcclusion);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetState);
	KX_PYMETHOD_O(KX_GameObject,SetState);
	KX_PYMETHOD_VARARGS(KX_GameObject,AlignAxisToVect);
	KX_PYMETHOD_O(KX_GameObject,GetAxisVect);
	KX_PYMETHOD_NOARGS(KX_GameObject,SuspendDynamics);
	KX_PYMETHOD_NOARGS(KX_GameObject,RestoreDynamics);
	KX_PYMETHOD_NOARGS(KX_GameObject,EnableRigidBody);
	KX_PYMETHOD_NOARGS(KX_GameObject,DisableRigidBody);
	KX_PYMETHOD_VARARGS(KX_GameObject,ApplyImpulse);
	KX_PYMETHOD_O(KX_GameObject,SetCollisionMargin);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetParent);
	KX_PYMETHOD_VARARGS(KX_GameObject,SetParent);
	KX_PYMETHOD_NOARGS(KX_GameObject,RemoveParent);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetChildren);	
	KX_PYMETHOD_NOARGS(KX_GameObject,GetChildrenRecursive);
	KX_PYMETHOD_VARARGS(KX_GameObject,GetMesh);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetPhysicsId);
	KX_PYMETHOD_NOARGS(KX_GameObject,GetPropertyNames);
	KX_PYMETHOD_VARARGS(KX_GameObject,ReplaceMesh);
	KX_PYMETHOD_NOARGS(KX_GameObject,EndObject);
	KX_PYMETHOD_DOC(KX_GameObject,rayCastTo);
	KX_PYMETHOD_DOC(KX_GameObject,rayCast);
	KX_PYMETHOD_DOC_O(KX_GameObject,getDistanceTo);
	KX_PYMETHOD_DOC_O(KX_GameObject,getVectTo);
	KX_PYMETHOD_DOC_VARARGS(KX_GameObject, sendMessage);
	KX_PYMETHOD_VARARGS(KX_GameObject, ReinstancePhysicsMesh);
	
	/* Dict access */
	KX_PYMETHOD_VARARGS(KX_GameObject,get);
	KX_PYMETHOD_O(KX_GameObject,has_key);
	
	/* attributes */
	static PyObject*	pyattr_get_name(void* self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_parent(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);

	static PyObject*	pyattr_get_mass(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_mass(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_lin_vel_min(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_lin_vel_min(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_lin_vel_max(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_lin_vel_max(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_visible(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_visible(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_worldPosition(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_worldPosition(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_localPosition(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_localPosition(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_localInertia(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_localInertia(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_worldOrientation(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_worldOrientation(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_localOrientation(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_localOrientation(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_worldScaling(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_localScaling(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_localScaling(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_timeOffset(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_timeOffset(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_state(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static int			pyattr_set_state(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef, PyObject *value);
	static PyObject*	pyattr_get_meshes(void* self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_children(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_children_recursive(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_attrDict(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	
	/* Experemental! */
	static PyObject*	pyattr_get_sensors(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_controllers(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	static PyObject*	pyattr_get_actuators(void *self_v, const KX_PYATTRIBUTE_DEF *attrdef);
	
	/* getitem/setitem */
	static PyMappingMethods	Mapping;
	static PySequenceMethods	Sequence;
	
private :

	/**	
	 * Random internal function to convert python function arguments
	 * to 2 vectors.
	 * @return true if conversion was possible.
	 */

		bool						
	ConvertPythonVectorArgs(
		PyObject* args,
		MT_Vector3& pos,
		MT_Vector3& pos2
	);	

};



#endif //__KX_GAMEOBJECT

