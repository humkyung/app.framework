// SATFace.cpp: implementation of the AcisFace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisDoc.h>
#include <AcisFace.h>

ACISLIB_IMPLEMENT_FUNC(AcisFace , AcisEntity , TYPELIST({_T("face") , NULL}))

const TCHAR* AcisFace::szDir[2] = {_T("forward"),_T("reversed")};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisFace::AcisFace(const TCHAR* pType,const long& nIndex) : AcisEntity(pType,nIndex)
{
	m_lAttributeIndex = -1L;
	m_lNextIndex = -1L;
	m_lLoopIndex = -1L;
	m_lShellIndex= -1L;
	m_lSurfIndex = -1L;
	m_eSense = UNKNOWN;
}

AcisFace::~AcisFace()
{

}

/**	
	@brief	The CSATBody::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisFace::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ /// ACAD 2004 , ACAD 2005
			m_lAttributeIndex = ATOI_T(oResult[1].c_str() + 1);
			/// ???
			/// ???
			m_lNextIndex = ATOI_T(oResult[4].c_str() + 1);
			m_lLoopIndex = ATOI_T(oResult[5].c_str() + 1);
			m_lShellIndex = ATOI_T(oResult[6].c_str() + 1);
			m_lSurfIndex = ATOI_T(oResult[8].c_str() + 1);
			m_eSense = (0 == STRNCMP_T(oResult[9].c_str(),AcisFace::szDir[0],7)) ? FORWARD : REVERSED;
		}
		else
		{
			m_lAttributeIndex = ATOI_T(oResult[1].c_str() + 1);
			m_lNextIndex = ATOI_T(oResult[2].c_str() + 1);
			m_lLoopIndex = ATOI_T(oResult[3].c_str() + 1);
			m_lShellIndex = ATOI_T(oResult[4].c_str() + 1);
			/// ???
			m_lSurfIndex = ATOI_T(oResult[6].c_str() + 1);
			m_eSense = (0 == STRNCMP_T(oResult[7].c_str(),AcisFace::szDir[0],7)) ? FORWARD : REVERSED;
		}
		bRet = true;
	}

	return bRet;
}

/**	
	@brief	The AcisFace::GetNextIndex function
	@author	humkyung
	@return	const long	
*/
const long AcisFace::GetNextIndex() const{return m_lNextIndex;}

/**	
	@brief	The CSATBody::GetLumpIndex function
	@author	humkyung
	@return	long	
*/
long AcisFace::GetSurfIndex() const {return m_lSurfIndex;}

/**	
	@brief	The AcisFace::GetLoopIndex function
	@author	humkyung
	@return	long	
*/
long AcisFace::GetLoopIndex() const {return m_lLoopIndex;}

/**	
	@brief	return shell index
	@author	humkyung
	@return	long	
*/
long AcisFace::GetShellIndex() const {return m_lShellIndex;}

/**	
	@brief	The AcisFace::GetForwardFlag function
	@author	humkyung
	@return	AcisSense
*/
AcisSense AcisFace::sense() const {return m_eSense;}