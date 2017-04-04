// AcisDisplayAttribute.cpp: implementation of the AcisEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tchar.h>
#include <AcisDisplayAttribute.h>

ACISLIB_IMPLEMENT_FUNC(AcisDisplayAttribute , AcisEntity , TYPELIST({_T("display_attribute-st-attrib") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	\brief
*/
AcisDisplayAttribute::AcisDisplayAttribute(const TCHAR* pType , const long& lIndex) : AcisEntity(pType , lIndex)
{
}

AcisDisplayAttribute::~AcisDisplayAttribute()
{
	try
	{
	}
	catch(...)
	{
	}
}

/**	
	@brief	The AcisDisplayAttribute::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisDisplayAttribute::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		bRet = true;
	}

	return bRet;
}