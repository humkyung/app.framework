// AcisColorAdeskAttrib.cpp: implementation of the AcisEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tchar.h>
#include <AcisColorAdeskAttrib.h>

ACISLIB_IMPLEMENT_FUNC(AcisColorAdeskAttrib , AcisEntity , TYPELIST({_T("color-adesk-attrib") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	\brief
*/
AcisColorAdeskAttrib::AcisColorAdeskAttrib(const TCHAR* pType , const long& lIndex) : AcisEntity(pType , lIndex)
{
}

AcisColorAdeskAttrib::~AcisColorAdeskAttrib()
{
	try
	{
	}
	catch(...)
	{
	}
}

/**	
	@brief	The AcisColorAdeskAttrib::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisColorAdeskAttrib::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		bRet = true;
	}

	return bRet;
}
