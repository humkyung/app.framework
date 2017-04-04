// AcisSphereSurf.cpp: implementation of the AcisSphereSurf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisSphereSurf.h>

ACISLIB_IMPLEMENT_FUNC(AcisSphereSurf , AcisSurf , TYPELIST({_T("sphere-surface") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	\brief
*/
AcisSphereSurf::AcisSphereSurf(const TCHAR* pType,const long& nIndex) : AcisSurf(pType,nIndex)
{
	//m_nId = ENM_SAT_SPHERE_SURF;
	m_nRadius = 0.;
}

AcisSphereSurf::~AcisSphereSurf()
{

}

/**	\brief	The AcisSphereSurf::Parse function

	\param	psz	a parameter of type const char*

	\return	bool	
*/
bool AcisSphereSurf::Parse(ifstream& file)
{
	return Parse(NULL,AcisLib::m_szLine);
}

/**	
	@brief	The AcisSphereSurf::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisSphereSurf::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ // ACAD 2004 , ACAD 2005
			/*m_ptOrigin.x = atof(oResult[4].c_str());
			m_ptOrigin.y = atof(oResult[5].c_str());
			m_ptOrigin.z = atof(oResult[6].c_str());
			m_nRadius = atof(oResult[7].c_str());
			m_vecNorm.dx = atof(oResult[8].c_str());
			m_vecNorm.dy = atof(oResult[9].c_str());
			m_vecNorm.dz = atof(oResult[10].c_str());*/
		}
		else
		{
			/*m_ptOrigin.x = atof(oResult[3].c_str());
			m_ptOrigin.y = atof(oResult[4].c_str());
			m_ptOrigin.z = atof(oResult[5].c_str());
			m_nRadius = atof(oResult[6].c_str());
			m_vecNorm.dx = atof(oResult[7].c_str());
			m_vecNorm.dy = atof(oResult[8].c_str());
			m_vecNorm.dz = atof(oResult[9].c_str());*/
		}

		bRet = true;
	}
	return bRet;
}

/**	\brief	The AcisSphereSurf::CreateSurf function


	\return	PSQPRIMITIVE	
*/
//PSQPRIMITIVE AcisSphereSurf::CreateSurf()
//{
//	PSQPRIMITIVE pRet=NULL;
//	
//	if(pRet = AcisLib::AllocPrimitive())
//	{
//		pRet->hdr.id = SQ_SPHERESURFACE;
//		pRet->hdr.attr.f = 1;
//		pRet->hdr.attr.d = 3;
//		
//		if(pRet->body.pSphereSurf = AcisLib::AllocSphereSurf())
//		{
//			pRet->body.pSphereSurf->ptOrigin = m_ptOrigin;
//			pRet->body.pSphereSurf->nRadius = m_nRadius;
//			pRet->body.pSphereSurf->vecNorm = m_vecNorm;
//		}
//	}
//
//	return pRet;
//}