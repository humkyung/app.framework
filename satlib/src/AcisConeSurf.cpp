// AcisConeSurf.cpp: implementation of the AcisConeSurf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisConeSurf.h>

ACISLIB_IMPLEMENT_FUNC(AcisConeSurf , AcisSurf , TYPELIST({_T("cone-surface") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisConeSurf::AcisConeSurf(const TCHAR* pType,const long& nIndex) : AcisSurf(pType,nIndex)
{
	m_dDelta = 0;
}

/**	
	@brief
*/
AcisConeSurf::~AcisConeSurf()
{

}

/**	
	@brief	The AcisConeSurf::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisConeSurf::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ /// ACAD 2004 , ACAD 2005
			m_ptOrigin.SetX(ATOF_T(oResult[4].c_str()));
			m_ptOrigin.SetY(ATOF_T(oResult[5].c_str()));
			m_ptOrigin.SetZ(ATOF_T(oResult[6].c_str()));
			m_vecAxis.dx() = ATOF_T(oResult[7].c_str());
			m_vecAxis.dy() = ATOF_T(oResult[8].c_str());
			m_vecAxis.dz() = ATOF_T(oResult[9].c_str());
			m_vecStart.dx() = ATOF_T(oResult[10].c_str());
			m_vecStart.dy() = ATOF_T(oResult[11].c_str());
			m_vecStart.dz() = ATOF_T(oResult[12].c_str());
			m_dDelta = ATOF_T(oResult[13].c_str()); /// 1 == straight , others not
			m_varRatio.a = ATOF_T(oResult[16].c_str());
			m_varRatio.b = ATOF_T(oResult[17].c_str());
			m_dRadius = ATOF_T(oResult[18].c_str());
		}
		else
		{
			m_ptOrigin.SetX(ATOF_T(oResult[2].c_str()));
			m_ptOrigin.SetY(ATOF_T(oResult[3].c_str()));
			m_ptOrigin.SetZ(ATOF_T(oResult[4].c_str()));
			m_vecAxis.dx() = ATOF_T(oResult[5].c_str());
			m_vecAxis.dy() = ATOF_T(oResult[6].c_str());
			m_vecAxis.dz() = ATOF_T(oResult[7].c_str());
			m_vecStart.dx() = ATOF_T(oResult[8].c_str());
			m_vecStart.dy() = ATOF_T(oResult[9].c_str());
			m_vecStart.dz() = ATOF_T(oResult[10].c_str());
			m_dDelta = ATOF_T(oResult[11].c_str()); /// 1 == straight , others not
			m_varRatio.a = ATOF_T(oResult[14].c_str());
			m_varRatio.b = ATOF_T(oResult[15].c_str());
			m_dRadius = ATOF_T(oResult[16].c_str());
		}
		bRet = true;
	}

	return bRet;
}

/**	\brief	The AcisConeSurf::CreateSurf function


	\return	PSQPRIMITIVE	
*/
//PSQPRIMITIVE AcisConeSurf::CreateSurf()
//{
//	PSQPRIMITIVE pRet=NULL;
//
//	if(pRet = AcisLib::AllocPrimitive())
//	{
//		pRet->hdr.attr.f = 1;
//		pRet->hdr.attr.d = 3;
//		pRet->hdr.id = SQ_CONESURFACE;
//		
//		if(pRet->body.pConeSurf = AcisLib::AllocConeSurf())
//		{
//			memset(pRet->body.pConeSurf,0,sizeof(CONESURF_T));
//			
//			pRet->body.pConeSurf->ptOrigin = m_ptOrigin;
//			pRet->body.pConeSurf->vecAxis = m_vecAxis;
//			pRet->body.pConeSurf->vecStart = m_vecStart;
//			pRet->body.pConeSurf->ratio.a = m_varRatio.a;
//			pRet->body.pConeSurf->ratio.b = m_varRatio.b;
//			pRet->body.pConeSurf->nRadius = m_nRadius;
//		}
//	}
//
//	return pRet;
//}

/**	
	@brief	The AcisConeSurf::GetDelta function
	@author	humkyung
	@return	const double	
*/
const double AcisConeSurf::delta() const
{
	return m_dDelta;
}

CPoint3d AcisConeSurf::origin() const
{
	return m_ptOrigin;
}

CVect3d AcisConeSurf::axis() const
{
	return m_vecAxis;
}

CVect3d AcisConeSurf::Vx() const
{
	return m_vecStart;
}

const AcisConeSurf::ratio_ AcisConeSurf::ratio() const
{
	return m_varRatio;
}

const double AcisConeSurf::radius() const
{
	return m_dRadius;
}