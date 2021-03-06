#ifndef KX_BULLET2PHYSICS_CONTROLLER
#define KX_BULLET2PHYSICS_CONTROLLER


#include "KX_IPhysicsController.h"
#include "CcdPhysicsController.h"

class KX_BulletPhysicsController : public KX_IPhysicsController ,public CcdPhysicsController
{
private:
	int m_savedCollisionFlags;
	int m_savedActivationState;
	short int m_savedCollisionFilterGroup;
	short int m_savedCollisionFilterMask;
	MT_Scalar m_savedMass;
	bool m_savedDyna;
	bool m_suspended;
	btCollisionShape* m_bulletChildShape;

public:

	KX_BulletPhysicsController (const CcdConstructionInfo& ci, bool dyna, bool sensor, bool compound);
	virtual ~KX_BulletPhysicsController ();

	///////////////////////////////////
	//	KX_IPhysicsController interface
	////////////////////////////////////

	virtual void	applyImpulse(const MT_Point3& attach, const MT_Vector3& impulse);
	virtual void	SetObject (SG_IObject* object);
	virtual void	setMargin (float collisionMargin);
	virtual void	RelativeTranslate(const MT_Vector3& dloc,bool local);
	virtual void	RelativeRotate(const MT_Matrix3x3& drot,bool local);
	virtual void	ApplyTorque(const MT_Vector3& torque,bool local);
	virtual void	ApplyForce(const MT_Vector3& force,bool local);
	virtual MT_Vector3 GetLinearVelocity();
	virtual MT_Vector3 GetAngularVelocity();
	virtual MT_Vector3 GetVelocity(const MT_Point3& pos);
	virtual void	SetAngularVelocity(const MT_Vector3& ang_vel,bool local);
	virtual void	SetLinearVelocity(const MT_Vector3& lin_vel,bool local);
	virtual	void	getOrientation(MT_Quaternion& orn);
	virtual	void setOrientation(const MT_Matrix3x3& orn);
	virtual	void setPosition(const MT_Point3& pos);
	virtual	void setScaling(const MT_Vector3& scaling);
	virtual void SetTransform();
	virtual	MT_Scalar	GetMass();
	virtual	void	SetMass(MT_Scalar newmass);
	virtual	MT_Vector3	GetLocalInertia();
	virtual	MT_Vector3	getReactionForce();
	virtual void	setRigidBody(bool rigid);
	virtual void    AddCompoundChild(KX_IPhysicsController* child);
	virtual void    RemoveCompoundChild(KX_IPhysicsController* child);

	virtual void	resolveCombinedVelocities(float linvelX,float linvelY,float linvelZ,float angVelX,float angVelY,float angVelZ);

	virtual void	SuspendDynamics(bool ghost);
	virtual void	RestoreDynamics();

	virtual	SG_Controller*	GetReplica(class SG_Node* destnode);

	virtual MT_Scalar GetRadius();
	
	virtual float GetLinVelocityMin();
	virtual void  SetLinVelocityMin(float val);
	virtual float GetLinVelocityMax();
	virtual void  SetLinVelocityMax(float val);

	virtual void	SetSumoTransform(bool nondynaonly);
	// todo: remove next line !
	virtual void	SetSimulatedTime(double time);
	
	// call from scene graph to update
	virtual bool Update(double time);
	void*	GetUserData() { return m_userdata;}
	
	void
	SetOption(
		int option,
		int value
	){
		// intentionally empty
	};

};

#endif //KX_BULLET2PHYSICS_CONTROLLER

