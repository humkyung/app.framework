// SATBody.cpp: implementation of the AcisBody class.
//
//////////////////////////////////////////////////////////////////////

///#include "stdafx.h"
#include <assert.h>
#include <Tokenizer.h>
#include <AcisLib.h>
#include <AcisDoc.h>
#include <AcisBody.h>

ACISLIB_IMPLEMENT_FUNC(AcisBody , AcisEntity , TYPELIST({_T("body") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
	@brief
*/
AcisBody::AcisBody(const TCHAR* pType,const long& nIndex) : AcisEntity(pType,nIndex)
{
	m_lLumpIndex = -1;
	m_lWireIndex = -1;
	m_lTransformIndex = -1;
}

/**
	@brief
*/
AcisBody::~AcisBody()
{
}

/**
	@brief	parse given string
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool
*/
bool AcisBody::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult , psz , CIsFromString(AcisLib::szDelimiter));
		if(700 == pDoc->GetVer())	/// ACAD 2004
		{
			//AcisEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// expected "body"
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); // attribute
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
			//CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
			m_lLumpIndex = ATOI_T(oResult[4].c_str() + 1); /// lump index(skip '$')
		}
		else
		{
			_T("body") == oResult[0]; /// expected "body"
			/// attribute
			m_lLumpIndex = ATOI_T(oResult[2].c_str() + 1); /// lump index(skip '$')
			m_lWireIndex = ATOI_T(oResult[3].c_str() + 1);
			m_lTransformIndex = ATOI_T(oResult[4].c_str() + 1);
		}
		bRet = true;
	}

	return bRet;
}

/**
	@brief	The AcisBody::GetLumpIndex function
	@author	humkyung
	@return	long
*/
long AcisBody::GetLumpIndex() const {return m_lLumpIndex;}

/**
	@brief	return wire index
	@date	2014.10.22
	@author	humkyung
	@return	long
*/
long AcisBody::GetWireIndex() const
{
	return m_lWireIndex;
}

/**
	@brief	return transform index
	@date	2014.10.22
	@author	humkyung
	@return	long
*/
long AcisBody::GetTransformIndex() const
{
	return m_lTransformIndex;
}
