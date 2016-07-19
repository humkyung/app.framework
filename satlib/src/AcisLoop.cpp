// AcisLoop.cpp: implementation of the AcisLoop class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisLoop.h>

ACISLIB_IMPLEMENT_FUNC(AcisLoop , AcisEntity , TYPELIST({_T("loop") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisLoop::AcisLoop(const TCHAR* pType,const long& nIndex) : AcisEntity(pType,nIndex)
{
	m_nNextIndex = -1L;
	m_nCoEdgeIndex = -1;
}

AcisLoop::~AcisLoop()
{

}

/**	
	@brief	The AcisLoop::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisLoop::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ /// ACAD 2004 , ACAD 2005
			m_nNextIndex = ATOI_T(oResult[4].c_str() + 1);
			m_nCoEdgeIndex = ATOI_T(oResult[5].c_str() + 1);
		}
		else
		{
			m_nNextIndex = ATOI_T(oResult[2].c_str() + 1);
			m_nCoEdgeIndex = ATOI_T(oResult[3].c_str() + 1);
		}
		bRet = true;
	}

	return bRet;
}

/**	
	@brief	The AcisLoop::GetNextIndex function
	@author	humkyung
	@return	const long	
*/
const long AcisLoop::GetNextIndex() const
{
	return m_nNextIndex;
}

/**	
	@brief	The AcisLoop::GetCoEdgeIndex function
	@author	humkyung
	@return	long	
*/
long AcisLoop::GetCoEdgeIndex() const
{
	return m_nCoEdgeIndex;
}
