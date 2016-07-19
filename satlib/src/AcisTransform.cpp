// AcisTransform.cpp: implementation of the AcisEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tchar.h>
#include <AcisTransform.h>

ACISLIB_IMPLEMENT_FUNC(AcisTransform , AcisEntity , TYPELIST({_T("transform") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	\brief
*/
AcisTransform::AcisTransform(const TCHAR* pType , const long& lIndex) : AcisEntity(pType , lIndex)
{
}

AcisTransform::~AcisTransform()
{
	try
	{
	}
	catch(...)
	{
	}
}

/**	
	@brief	The AcisTransform::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisTransform::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		bRet = true;
	}

	return bRet;
}