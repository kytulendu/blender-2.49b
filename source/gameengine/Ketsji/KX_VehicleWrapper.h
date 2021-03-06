#ifndef KX_VEHICLE_WRAPPER
#define KX_VEHICLE_WRAPPER

#include "Value.h"
#include "PHY_DynamicTypes.h"
class PHY_IVehicle;
class PHY_IMotionState;

#include <vector>

///Python interface to physics vehicles (primarily 4-wheel cars and 2wheel bikes)
class	KX_VehicleWrapper : public PyObjectPlus
{
	Py_Header;
	virtual PyObject*		py_getattro(PyObject *attr);
	virtual PyObject*		py_getattro_dict();
	virtual int 			py_setattro(PyObject *attr, PyObject *value);

	std::vector<PHY_IMotionState*> m_motionStates;

public:
	KX_VehicleWrapper(PHY_IVehicle* vehicle,class PHY_IPhysicsEnvironment* physenv,PyTypeObject *T = &Type);
	virtual ~KX_VehicleWrapper ();
	int			getConstraintId();
	
	
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,AddWheel);
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,GetNumWheels);
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,GetWheelOrientationQuaternion);
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,GetWheelRotation);
	
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,GetWheelPosition);
	
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,GetConstraintId);
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,GetConstraintType);

	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,SetSteeringValue);

	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,ApplyEngineForce);

	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,ApplyBraking);

	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,SetTyreFriction);

	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,SetSuspensionStiffness);
	
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,SetSuspensionDamping);
	
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,SetSuspensionCompression);
	
	KX_PYMETHOD_VARARGS(KX_VehicleWrapper,SetRollInfluence);
	

private:
	PHY_IVehicle*			 m_vehicle;
	PHY_IPhysicsEnvironment* m_physenv;
};

#endif //KX_VEHICLE_WRAPPER
