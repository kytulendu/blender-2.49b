////////////////////////////////////////////////////////////////
// Copied from the ActiveX SDK
// This code is used to register and unregister a
// control as safe for initialization and safe for scripting
/**
 * $Id: SafeControl.h 15444 2008-07-05 17:05:05Z lukep $
 */


#include "comcat.h"
#include "objsafe.h"

HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid);

