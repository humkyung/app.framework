// AcisRefVTEyeAttrib.cpp: implementation of the AcisEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tchar.h>
#include <AcisRefVTEyeAttrib.h>

ACISLIB_IMPLEMENT_FUNC(AcisRefVTEyeAttrib , AcisEntity , TYPELIST({_T("ref_vt-eye-attrib") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisRefVTEyeAttrib::AcisRefVTEyeAttrib(const TCHAR* pType , const long& lIndex) : AcisEntity(pType , lIndex)
{
}

AcisRefVTEyeAttrib::~AcisRefVTEyeAttrib()
{
	try
	{
	}
	catch(...)
	{
	}
}

/**	
	@brief	The AcisRefVTEyeAttrib::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisRefVTEyeAttrib::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		bRet = true;
	}

	return bRet;
}
