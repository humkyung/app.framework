// AcisRefEntity.cpp: implementation of the AcisRefEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <Tokenizer.h>
#include <IsString.h>
#include <AcisRefEntity.h>

ACISLIB_IMPLEMENT_FUNC(AcisRefEntity , AcisEntity , TYPELIST({_T("ref") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
@brief
*/
AcisRefEntity::AcisRefEntity(const TCHAR* pType,const long& lIndex) : AcisEntity(pType , lIndex)
{
}

AcisRefEntity::~AcisRefEntity()
{
	try
	{
	}
	catch(...)
	{
	}
}

/**	
	@brief	parse ref entity
	@author	humkyung
	@date	2014.10.23
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisRefEntity::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult , psz , CIsFromString(_T(" \t")));
		SubTypeRefIndex() = ATOI_T(oResult[2].c_str());
		return true;
	}

	return false;
}