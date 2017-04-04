// AcisVertex.cpp: implementation of the AcisVertex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "../app.framework/Tokenizer.h"
#include <AcisLib.h>
#include <AcisVertex.h>

ACISLIB_IMPLEMENT_FUNC(AcisVertex , AcisEntity , TYPELIST({_T("vertex") , _T("tvertex-vertex") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisVertex::AcisVertex(const TCHAR* pType , const long& nIndex) : AcisEntity(pType,nIndex)
{
	m_nEdgeIndex = -1L;
	m_nPointIndex = 0L;
}

/**	\brief
*/
AcisVertex::~AcisVertex()
{

}

/**	
	@brief	The AcisVertex::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisVertex::Parse(IFSTREAM_T& file)
{
	return Parse(NULL,AcisLib::m_szLine);
}

/**	
	@brief	The AcisVertex::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisVertex::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ /// ACAD 2004 , ACAD 2005
			m_nPointIndex = ATOI_T(oResult[5].c_str() + 1);
		}
		else
		{
			m_nEdgeIndex = ATOI_T(oResult[2].c_str() + 1);
			m_nPointIndex = ATOI_T(oResult[3].c_str() + 1);
		}

		bRet = true;
	}

	return bRet;
}

/**	
	@brief	The AcisVertex::GetPointIndex function
	@author	humkyung
	@return	long	
*/
long AcisVertex::GetPointIndex() const
{
	return m_nPointIndex;
}

/**	
	@brief	The AcisVertex::GetEdgeIndex function
	@author	humkyung
	@return	long	
*/
long AcisVertex::GetEdgeIndex() const
{
	return m_nEdgeIndex;
}