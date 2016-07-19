// AcisEdge.cpp: implementation of the AcisEdge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisEdge.h>

ACISLIB_IMPLEMENT_FUNC(AcisEdge , AcisEntity , TYPELIST({_T("edge") , _T("tedge-edge") ,  NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisEdge::AcisEdge(const TCHAR* pType,const long& nIndex) : AcisEntity(pType,nIndex)
{
	m_nCoEdgeIndex = -1L;
	m_params[0] = m_params[1] = DBL_MAX;
	m_eSense = UNKNOWN;
}

/**	
	@brief
*/
AcisEdge::~AcisEdge()
{
}

/**	
	@brief	The AcisEdge::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisEdge::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ /// ACAD 2004
			m_lStartIndex = ATOI_T(oResult[4].c_str() + 1);
			m_params[0] = ATOF_T(oResult[5].c_str());
			m_lEndIndex = ATOI_T(oResult[6].c_str() + 1);
			m_params[1] = ATOF_T(oResult[7].c_str());
			m_nCoEdgeIndex = ATOI_T(oResult[8].c_str() + 1);
			m_nCurveIndex = ATOI_T(oResult[9].c_str() + 1);
			m_eSense = (0 == STRNCMP_T(oResult[10].c_str(),AcisLib::szDir[0],7)) ? FORWARD : REVERSED;
		}
		else
		{
			int at=2;
			m_lStartIndex = ATOI_T(oResult[at++].c_str() + 1);
			if(!AcisEntity::IsIndexString(oResult[at]))
			{
				m_params[0] = ATOF_T(oResult[at++].c_str()); 
			}
			m_lEndIndex = ATOI_T(oResult[at++].c_str() + 1);
			if(!AcisEntity::IsIndexString(oResult[at]))
			{
				m_params[1] = ATOF_T(oResult[at++].c_str()); 
			}
			m_nCoEdgeIndex = ATOI_T(oResult[at++].c_str() + 1);
			m_nCurveIndex = ATOI_T(oResult[at++].c_str() + 1);
			m_eSense = (0 == STRNCMP_T(oResult[at++].c_str(),AcisLib::szDir[0],7)) ? FORWARD : REVERSED;
		}
		bRet = true;
	}

	return bRet;
}

/**	
	@brief	The AcisEdge::GetStart function
	@author	humkyung
	@return	long	
*/
long AcisEdge::GetStartIndex() const
{
	return m_lStartIndex;
}

/**	
	@brief	The AcisEdge::GetEnd function
	@author	humkyung
	@return	long	
*/
long AcisEdge::GetEndIndex() const
{
	return m_lEndIndex;
}

/**	
	@brief	return params
	@author	humkyung
	@date	2014.11.06
	@return	double*	
*/
double* AcisEdge::params()
{
	return m_params;
}

/**	
	@brief	The AcisEdge::GetCurveIndex function
	@author	humkyung
	@return	long	
*/
const long AcisEdge::GetCurveIndex() const
{
	return m_nCurveIndex;
}

/**	
	@brief	return the sense of edge
	@author	humkyung
	@return	AcisSense
*/
AcisSense AcisEdge::sense() const
{
	return m_eSense;
}