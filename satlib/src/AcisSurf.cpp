// AcisSurf.cpp: implementation of the AcisSurf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <AcisSurf.h>

ACISLIB_IMPLEMENT_FUNC(AcisSurf , AcisEntity , TYPELIST({NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AcisSurf::AcisSurf(const TCHAR* pType,const long& lIndex) : AcisEntity(pType,lIndex)
{

}

AcisSurf::~AcisSurf()
{
}

/**	
	@brief	The AcisTransform::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisSurf::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		bRet = true;
	}

	return bRet;
}