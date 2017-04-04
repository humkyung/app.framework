// AcisSplineSurf.cpp: implementation of the AcisSplineSurf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Tokenizer.h>
#include <IsString.h>
#include <AcisLib.h>
#include <AcisEllipseCurv.h>
#include <AcisSplineSurf.h>
#include <AcisExactSurf.h>
#include <AcisRefEntity.h>
#include <AcisEntityFactory.h>

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

ACISLIB_IMPLEMENT_FUNC(AcisSplineSurf , AcisSurf , TYPELIST({_T("spline-surface") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisSplineSurf::AcisSplineSurf(const TCHAR* pType,const long& nIndex) : AcisSurf(pType,nIndex) , m_type(AcisSplineSurf::undef)
{
	m_lAttributeIndex = -1;
	m_pSubSurf = NULL;
}

/**	
	@brief
*/
AcisSplineSurf::~AcisSplineSurf()
{
	try
	{
		SAFE_DELETE(m_pSubSurf);
	}
	catch(...)
	{
	}
}

/**	
	@brief	spline-surface의 항목을 파싱한다.
	@author	humkyung
	@date	?
	@param	file	현재 작업하는 파일 레퍼런스
	@return	bool	
*/
bool AcisSplineSurf::Parse(ifstream& file)
{
	bool bRet=false;

	//if(file.good())
	//{
	//	AcisLib* pSATLib=AcisLib::GetInstance();
	//	AcisDoc* pAcisDoc=pSATLib->GetDoc();

	//	vector<string> oResult;
	//	CTokenizer<CIsFromString>::Tokenize(oResult,AcisLib::m_szLine,CIsFromString(" \t"));
	//	if(700 == pAcisDoc->GetVer())
	//	{ //! ACAD 2004 , ACAD 2005
	//		if("rotsur" == oResult[6])
	//		{
	//			file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ);
	//			CTokenizer<CIsFromString>::Tokenize(oResult,AcisLib::m_szLine,CIsFromString(" \t"));
	//			if("ellipse" == oResult[0]){}
	//			file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ);
	//			CTokenizer<CIsFromString>::Tokenize(oResult,AcisLib::m_szLine,CIsFromString(" \t"));
	//			/*m_ptOrigin.x = ATOF_T(oResult[0].c_str());
	//			m_ptOrigin.y = ATOF_T(oResult[1].c_str());
	//			m_ptOrigin.z = ATOF_T(oResult[2].c_str());
	//			m_vecNorm.dx = ATOF_T(oResult[3].c_str());
	//			m_vecNorm.dy = ATOF_T(oResult[4].c_str());
	//			m_vecNorm.dz = ATOF_T(oResult[5].c_str());*/
	//			file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ);
	//			CTokenizer<CIsFromString>::Tokenize(oResult,AcisLib::m_szLine,CIsFromString(" \t"));
	//			double nStartRad=ATOF_T(oResult[6].c_str());	/// start angle
	//			double nEndRad=ATOF_T(oResult[8].c_str());	/// end angle
	//			for(;NULL == strchr(AcisLib::m_szLine,ACIS_END_MARK);file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ));

	//			m_type = AcisSplineSurf::rotsur;
	//			bRet = true;
	//		}
	//		else if("exactsur" == oResult[6])
	//		{
	//			//! 무시한다.
	//			for(;NULL == strchr(AcisLib::m_szLine,ACIS_END_MARK);file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ));

	//			m_type = AcisSplineSurf::exactsur;
	//			bRet = true;
	//		}
	//		else
	//		{
	//			//! 무시한다.
	//			for(;NULL == strchr(AcisLib::m_szLine,ACIS_END_MARK);file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ));

	//			m_type = AcisSplineSurf::undef;
	//			bRet = true;
	//		}
	//	}
	//	else
	//	{ // ACAD2000 or 2002
	//		if("rotsur" == oResult[4])
	//		{
	//			file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ);
	//			CTokenizer<CIsFromString>::Tokenize(oResult,AcisLib::m_szLine,CIsFromString(" \t"));
	//			if(0 == strcmp(AcisEntity::szToken,"ellipse"))
	//			{
	//				bRet = true;
	//			}

	//			m_type = AcisSplineSurf::rotsur;
	//		}
	//		else if("exactsur" == oResult[6])
	//		{
	//			//! 무시한다.
	//			for(;NULL == strchr(AcisLib::m_szLine,ACIS_END_MARK);file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ));

	//			m_type = AcisSplineSurf::exactsur;
	//			bRet = true;
	//		}
	//		else
	//		{
	//			//! 무시한다.
	//			for(;NULL == strchr(AcisLib::m_szLine,ACIS_END_MARK);file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ));

	//			m_type = AcisSplineSurf::undef;
	//			bRet = true;
	//		}
	//	}
	//}

	return bRet;
}

/**	
	@brief	spline-surface의 항목을 파싱한다.
	@author	humkyung	
	@date	?
	@param	file	현재 작업하는 파일 레퍼런스
	@return	bool	
*/
bool AcisSplineSurf::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		int iLineIndex = 0;

		vector<STRING_T> oLines , oResult;
		CTokenizer<CIsFromString>::Tokenize(oLines , psz , CIsFromString(_T("\r\n")));
		//if(700 == pDoc->GetVer())
		{
			STRING_T aLine = oLines[iLineIndex];
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
			m_lAttributeIndex = ATOI_T(oResult[1].c_str() + 1);
			vector<STRING_T>::iterator where = find(oResult.begin() , oResult.end() , ACIS_START_OF_SUBTYPE);
			if(where != oResult.end())
			{
				AcisEntity* pAcisEnt = AcisEntityFactory::CreateEntity((where+1)->c_str() , -1);
				if(NULL != pAcisEnt)
				{
					SubTypeRefIndex() = pDoc->RegisterSubType(pAcisEnt);

					OSTRINGSTREAM_T stream;
#ifdef	_UNICODE
					std::copy(where , oResult.end(), std::ostream_iterator<STRING_T,wchar_t>(stream , _T(" ")));
#else
					std::copy(where , oResult.end(), std::ostream_iterator<STRING_T>(stream , _T(" ")));
#endif
					aLine = stream.str();
					STRING_T str = GetStringOfSubType(aLine , iLineIndex , oLines);

					pAcisEnt->Parse(pDoc , str.c_str());
					if(AcisRefEntity::TypeOf(pAcisEnt->GetTypeString()))
					{
						AcisRefEntity* pAcisRef = static_cast<AcisRefEntity*>(pAcisEnt);
						SubTypeRefIndex() = pAcisRef->SubTypeRefIndex();
						SAFE_DELETE(pAcisEnt);
					}
				}
			}
		}
		/*else
		{
			STRING_T aLine = oLines[iLineIndex];
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
			m_lAttributeIndex = ATOI_T(oResult[1].c_str() + 1);
			vector<STRING_T>::iterator where = find(oResult.begin() , oResult.end() , ACIS_START_OF_SUBTYPE);
			if(where != oResult.end())
			{
				AcisEntity* pAcisEnt = AcisEntityFactory::CreateEntity((where+1)->c_str() , -1);
				if(NULL != pAcisEnt)
				{
					SubTypeRefIndex() = pDoc->RegisterSubType(pAcisEnt);

					OSTRINGSTREAM_T stream;
					std::copy(where , oResult.end(), std::ostream_iterator<STRING_T>(stream , _T(" ")));
					aLine = stream.str();
					STRING_T str = GetStringOfSubType(aLine , iLineIndex , oLines);

					pAcisEnt->Parse(pDoc , str.c_str());
				}
			}
		}*/

		return true;
	}

	return false;
}

/**
	@brief	return subsurf
	@author	humkyung
	@date	2014.10.22
	@return	AcisSurf*
*/
AcisSurf* AcisSplineSurf::GetSubSurf()
{
	return m_pSubSurf;
}

/**	
	@brief	The AcisSplineSurf::ParseEllipse function


	@return	void	
*/
void AcisSplineSurf::ParseEllipse()
{
	//CSATEllipse* pEllipse=new CSATEllipse(-1);
	//if(pEllipse){
		/*POINT_T pt={0,};

		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		pt.x = ATOF_T(CSATEntity::szToken);
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		pt.y = ATOF_T(CSATEntity::szToken);
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		pt.z = ATOF_T(CSATEntity::szToken);*/
		//pEllipse->SetOriginPos(pt);

		/*VECTOR_T vec={0,};
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		vec.dx = ATOF_T(CSATEntity::szToken);
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		vec.dy = ATOF_T(CSATEntity::szToken);
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		vec.dz = ATOF_T(CSATEntity::szToken);*/
		//pEllipse->SetNormVector(vec);

		/*CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		vec.dx = ATOF_T(CSATEntity::szToken);
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		vec.dy = ATOF_T(CSATEntity::szToken);
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken);
		vec.dz = ATOF_T(CSATEntity::szToken);*/
		//pEllipse->SetDelta(vec);
		//pt.x += vec.dx;pt.y += vec.dy;pt.z += vec.dz;
		//pEllipse->SetStartPos(pt);

		/*CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ratio
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// sweep angle
		double nSweep=atoi(CSATEntity::szToken);
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???
		CSATEntity::tokenizer.GetNextToken(CSATEntity::szToken); /// ???*/

		double alpha=0.,beta=0.;
		//CGeometry::GetRotatedAngleOfAxis(pEllipse->GetNormVector(),alpha,beta);
		/*pt.x = vec.dx;pt.y = vec.dy;pt.z = vec.dz;
		pt = CGeometry::RotateAboutXYAxis(pt,alpha,beta);
		pt.z = 0.;
		pt = CGeometry::RotateAboutZAxis(pt,nSweep);
		pt = CGeometry::RotateAboutYXAxis(pt,-beta,-alpha);*/
		
		//POINT_T ptOrigin=pEllipse->GetOriginPos();
		//ptOrigin.x += pt.x;ptOrigin.z += pt.z;ptOrigin.z += pt.z;
		//pEllipse->SetEndPos(ptOrigin);

		//RegisterBoundaryCurve(pEllipse);
	//}

}

/**	
	@brief	The AcisSplineSurf::CreateSurf function

	@author	BHK

	@return	PSQPRIMITIVE	
*/
//PSQPRIMITIVE AcisSplineSurf::CreateSurf()
//{
//	PSQPRIMITIVE pRet = NULL;
//	
//	if(AcisSplineSurf::rotsur == m_type)
//	{
//		pRet = AcisLib::AllocPrimitive();
//
//		pRet->hdr.id = SQ_SURFACE;
//		pRet->hdr.attr.f = 1;
//		pRet->hdr.attr.d = 3;
//
//		pRet->body.pSurface = AcisLib::AllocSurf();
//		if(pRet->body.pSurface)
//		{
//			pRet->body.pSurface->nType = SURF_OF_REVOLUTION;
//		}
//	}
//
//	return pRet;
//}

/**	\brief	The AcisSplineSurf::RegisterBoundaryCurve function

	\param	pEntity	a parameter of type CSATEntity*

	\return	void	
*/
void AcisSplineSurf::RegisterBoundaryCurve(AcisEntity* pEntity)
{
	assert(pEntity && "pEntity is NULL");

	if(pEntity)
	{
		//if(NULL == m_plstBoundayCurve) m_plstBoundayCurve = new list<CSATEntity*>;
		//if(m_plstBoundayCurve) m_plstBoundayCurve->push_back(pEntity);
	}
}