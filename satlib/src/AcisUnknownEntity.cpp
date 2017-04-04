// AcisUnknownEntity.cpp: implementation of the AcisEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tchar.h>
#include <AcisUnknownEntity.h>

ACISLIB_IMPLEMENT_FUNC(AcisUnknownEntity , AcisEntity , TYPELIST({_T("unknown") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisUnknownEntity::AcisUnknownEntity(const TCHAR* pType , const long& lIndex) : AcisEntity(pType , lIndex)
{
}

AcisUnknownEntity::~AcisUnknownEntity()
{
	try
	{
	}
	catch(...)
	{
	}
}

/**	
	@brief	The AcisUnknownEntity::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisUnknownEntity::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		bRet = true;
	}

	return bRet;
}
