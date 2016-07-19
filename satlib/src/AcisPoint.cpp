// AcisPoint.cpp: implementation of the AcisPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisPoint.h>

ACISLIB_IMPLEMENT_FUNC(AcisPoint , AcisEntity , TYPELIST({_T("point") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AcisPoint::AcisPoint(const TCHAR* pType,const long& nIndex) : AcisEntity(pType,nIndex)
{
}

AcisPoint::~AcisPoint()
{

}

/**	
	@brief	The AcisPoint::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisPoint::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ /// ACAD 2004 , ACAD 2005
			m_pt.Set(ATOF_T(oResult[4].c_str()) , ATOF_T(oResult[5].c_str()) , ATOF_T(oResult[6].c_str()));
		}
		else
		{
			m_pt.Set(ATOF_T(oResult[2].c_str()) , ATOF_T(oResult[3].c_str()) , ATOF_T(oResult[4].c_str()));
		}

		bRet = true;
	}

	return bRet;
}

/**	
	@brief	The AcisPoint::GetPoint function
	@author	humkyung
	@date	
	@return	POINT_T	
*/
CPoint3d AcisPoint::GetPoint() const
{
	return m_pt;
}