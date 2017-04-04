// AcisStraightCurv.cpp: implementation of the AcisStraightCurv class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisStraightCurv.h>

ACISLIB_IMPLEMENT_FUNC(AcisStraightCurv , AcisCurve , TYPELIST({_T("straight-curve") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	\brief
*/
AcisStraightCurv::AcisStraightCurv(const TCHAR* pType,const long& nIndex) : AcisCurve(pType,nIndex)
{
	//m_nId = ENM_SAT_STRAIGHT_CRV;
}

AcisStraightCurv::~AcisStraightCurv()
{

}

/**	
	@brief	The AcisStraightCurv::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisStraightCurv::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if(NULL != psz)
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,AcisLib::m_szLine,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ /// ACAD 2004 , ACAD 2005
		}
		else
		{
		}
		bRet = true;
	}

	return bRet;
}
