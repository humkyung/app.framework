// AcisCoEdge.cpp: implementation of the AcisCoEdge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tokenizer.h"
#include <AcisLib.h>
#include <AcisCoEdge.h>

ACISLIB_IMPLEMENT_FUNC(AcisCoEdge , AcisEntity , TYPELIST({_T("coedge") , _T("tcoedge-coedge") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisCoEdge::AcisCoEdge(const TCHAR* pType,const long& nIndex) : AcisEntity(pType,nIndex)
{
	m_lForwardNextIndex = m_lReversedNextIndex = -1L;
	m_nEdgeIndex = 0L;
	m_eSense = UNKNOWN;
	m_nLoopIndex = -1L;
	m_lPCurveIndex = -1L;
}

AcisCoEdge::~AcisCoEdge()
{

}

/**	
	@brief	The AcisCoEdge::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisCoEdge::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ /// ACAD 2004 , ACAD2005
			m_lForwardNextIndex = ATOL_T(oResult[4].c_str() + 1);
			m_lReversedNextIndex = ATOL_T(oResult[5].c_str() + 1);
			m_nEdgeIndex = ATOL_T(oResult[7].c_str() + 1);
			m_eSense = (0 == STRNCMP_T(oResult[8].c_str(),AcisLib::szDir[0],7)) ? FORWARD : REVERSED;
			m_nLoopIndex = ATOL_T(oResult[9].c_str() + 1);
			m_lPCurveIndex = ATOL_T(oResult[10].c_str() + 1);
		}
		else
		{
			m_lForwardNextIndex = ATOL_T(oResult[2].c_str() + 1);
			m_lReversedNextIndex = ATOL_T(oResult[3].c_str() + 1);
			m_nEdgeIndex = ATOL_T(oResult[5].c_str() + 1);
			m_eSense = (0 == STRNCMP_T(oResult[6].c_str(),AcisLib::szDir[0],7)) ? FORWARD : REVERSED;
			m_nLoopIndex = ATOL_T(oResult[7].c_str() + 1);
			m_lPCurveIndex = ATOL_T(oResult[8].c_str() + 1);
		}
		bRet = true;
	}

	return bRet;
}

/**	
	@brief	The AcisCoEdge::GetNextIndex function
	@author	humkyung
	@return	const long	
*/
const long AcisCoEdge::GetNextIndex() const
{
	return m_lForwardNextIndex;///(FORWARD == m_eSense) ? m_lForwardNextIndex : m_lReversedNextIndex;
}

/**	
	@brief	The AcisCoEdge::GetEdgeIndex function
	@author	humkyung
	@return	long	
*/
long AcisCoEdge::GetEdgeIndex() const {return m_nEdgeIndex;}

/**	
	@brief	return the sense of co-edge
	@author	humkyung
	@return	bool	
*/
AcisSense AcisCoEdge::sense() const {return m_eSense;}

const long AcisCoEdge::GetLoopIndex() const
{
	return m_nLoopIndex;
}

/**	
	@brief	return pcurve index
	@author	humkyung
	@date	2014.10.29
	@return	long
*/
const long AcisCoEdge::pcurve() const
{
	return m_lPCurveIndex;
}