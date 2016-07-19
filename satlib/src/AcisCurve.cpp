// AcisCurve.cpp: implementation of the AcisCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <AcisCurve.h>

ACISLIB_IMPLEMENT_FUNC(AcisCurve , AcisEntity , TYPELIST({NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AcisCurve::AcisCurve(const TCHAR* pType,const long& lIndex) : AcisEntity(pType,lIndex)
{

}

AcisCurve::~AcisCurve()
{

}
