// AcisShell.cpp: implementation of the AcisShell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisDoc.h>
#include <AcisShell.h>

ACISLIB_IMPLEMENT_FUNC(AcisShell , AcisEntity , TYPELIST({_T("shell") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisShell::AcisShell(const TCHAR* pType,const long& nIndex) : AcisEntity(pType,nIndex)
{
	m_lFaceIndex = -1;
	m_lLumpIndex = -1;
}

AcisShell::~AcisShell()
{

}

/**	
	@brief	The CSATBody::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisShell::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ // ACAD 2004 , ACAD 2005
			//CSATEntity::tokenizer.SetTokenString((char*)psz);
			//CSATEntity::tokenizer.SetDelimiter(AcisLib::szDelimiter);
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// "shell" 
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); ///
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// face index
			m_lFaceIndex=ATOI_T(oResult[6].c_str() + 1);
		}
		else
		{
			const bool is = _T("shell") == oResult[0];
			/// ???
			/// ???
			/// ???
			m_lFaceIndex = ATOI_T(oResult[4].c_str() + 1);
			/// ???
			m_lLumpIndex = ATOI_T(oResult[6].c_str() + 1);
		}
		bRet = true;
	}

	return bRet;
}

/**	
	@brief	return face index
	@author	humkyung
	@return	long	
*/
long AcisShell::GetFaceIndex() const
{
	return m_lFaceIndex;
}

/**	
	@brief	return lump index
	@author	humkyung
	@return	long	
*/
long AcisShell::GetLumpIndex() const
{
	return m_lLumpIndex;
}