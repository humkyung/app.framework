// AcisRotSurf.cpp: implementation of the AcisRotSurf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Tokenizer.h>
#include <IsString.h>
#include <AcisLib.h>
#include <AcisEllipseCurv.h>
#include <AcisRotSurf.h>

ACISLIB_IMPLEMENT_FUNC(AcisRotSurf , AcisSurf , TYPELIST({_T("rotsur") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisRotSurf::AcisRotSurf(const TCHAR* pType,const long& nIndex) : AcisSurf(pType,nIndex)
{
}

/**	
	@brief
*/
AcisRotSurf::~AcisRotSurf()
{
	try
	{
		
	}
	catch(...)
	{
	}
}

/**
	@brief	parse rotation surf
	@author	humkyung
	@date	2014.10.24
	@return	bool
*/
bool AcisRotSurf::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");

	if((NULL != pDoc) && (NULL != psz))
	{
		return true;
	}

	return false;
}