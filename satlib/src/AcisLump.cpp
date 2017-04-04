// SATLump.cpp: implementation of the AcisLump class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisDoc.h>
#include <AcisLump.h>

ACISLIB_IMPLEMENT_FUNC(AcisLump , AcisEntity , TYPELIST({_T("lump") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisLump::AcisLump(const TCHAR* pType,const long& nIndex) : AcisEntity(pType,nIndex)
{
	m_lAttributeIndex = -1;
	m_lNextIndex = -1L;
	m_lShellIndex = -1L;
}

AcisLump::~AcisLump()
{

}

/**	
	@brief	The AcisLump::Parse function
	@author	humkyung
	@param	psz
	@return	bool	
*/
bool AcisLump::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ // ACAD 2004 , ACAD 2005
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// expected "lump
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// attribute
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); ///
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// next lump index
			m_lNextIndex = ATOI_T(oResult[4].c_str() + 1);
			m_lShellIndex=ATOI_T(oResult[5].c_str() + 1);
		}
		else
		{
			const bool is = _T("lump") == oResult[0]; /// expected "lump
			m_lAttributeIndex = ATOI_T(oResult[1].c_str() + 1); /// attribute
			m_lNextIndex = ATOI_T(oResult[2].c_str() + 1);
			m_lShellIndex = ATOI_T(oResult[3].c_str() + 1);
			m_lBodyIndex = ATOI_T(oResult[4].c_str() + 1);
		}
		bRet = true;
	}

	return bRet;
}

/**	
	@brief	The AcisLump::GetNextIndex function
	@author	humkyung
	@return	long	
*/
long AcisLump::GetNextIndex() const
{
	return m_lNextIndex;
}

/**	
	@brief	The AcisLump::GetShellIndex function
	@author	humkyung
	@return	long	
*/
long AcisLump::GetShellIndex() const
{
	return m_lShellIndex;
}

/**	
	@brief	return attribute index
	@date	2014.10.22
	@author	humkyung
	@return	long	
*/
long AcisLump::GetAttributeIndex() const
{
	return m_lAttributeIndex;
}

/**	
	@brief	return body index
	@date	2014.10.22
	@author	humkyung
	@return	long	
*/
long AcisLump::GetBodyIndex() const
{
	return m_lBodyIndex;
}