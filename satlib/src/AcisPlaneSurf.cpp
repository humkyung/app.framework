// AcisPlaneSurf.cpp: implementation of the AcisPlaneSurf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisPlaneSurf.h>

ACISLIB_IMPLEMENT_FUNC(AcisPlaneSurf , AcisSurf , TYPELIST({_T("plane-surface") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	\brief
*/
AcisPlaneSurf::AcisPlaneSurf(const TCHAR* pType,const long& nIndex) : AcisSurf(pType,nIndex)
{
}

AcisPlaneSurf::~AcisPlaneSurf()
{

}

CPoint3d AcisPlaneSurf::origin() const
{
	return m_ptOrigin;
}

CVect3d AcisPlaneSurf::norm() const
{
	return m_vecNorm;
}

/**	
	@brief	The AcisPlaneSurf::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisPlaneSurf::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ // ACAD 2004 , ACAD 2005
			m_ptOrigin.SetX(ATOF_T(oResult[4].c_str()));
			m_ptOrigin.SetY(ATOF_T(oResult[5].c_str()));
			m_ptOrigin.SetZ(ATOF_T(oResult[6].c_str()));
			m_vecNorm.dx() = ATOF_T(oResult[7].c_str());
			m_vecNorm.dy() = ATOF_T(oResult[8].c_str());
			m_vecNorm.dz() = ATOF_T(oResult[9].c_str());
		}
		else
		{
			m_ptOrigin.SetX(ATOF_T(oResult[2].c_str()));
			m_ptOrigin.SetY(ATOF_T(oResult[3].c_str()));
			m_ptOrigin.SetZ(ATOF_T(oResult[4].c_str()));
			m_vecNorm.dx() = ATOF_T(oResult[5].c_str());
			m_vecNorm.dy() = ATOF_T(oResult[6].c_str());
			m_vecNorm.dz() = ATOF_T(oResult[7].c_str());
		}
		bRet = true;
	}

	return bRet;
}

/**	\brief	The AcisPlaneSurf::CreateSurf function


	\return	PSQPRIMITIVE	
*/
//PSQPRIMITIVE AcisPlaneSurf::CreateSurf()
//{
//	PSQPRIMITIVE pRet=NULL;
//	
//	if(pRet = AcisLib::AllocPrimitive())
//	{
//		pRet->hdr.id = SQ_PLANESURFACE;
//		pRet->hdr.attr.f = 1;
//		pRet->hdr.attr.d = 3;
//		
//		if(pRet->body.pPlaneSurf = AcisLib::AllocPlaneSurf())
//		{
//			pRet->body.pPlaneSurf->ptOrigin = m_ptOrigin;
//			pRet->body.pPlaneSurf->vecNorm = m_vecNorm;
//		}
//	}
//
//	return pRet;
//}