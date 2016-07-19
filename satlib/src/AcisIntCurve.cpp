// AcisIntCurve.cpp: implementation of the AcisIntCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include <Tokenizer.h>
#include <IsString.h>
#include <AcisLib.h>
#include <AcisIntCurve.h>
#include <AcisExactCurv.h>
#include <AcisEntityFactory.h>

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

ACISLIB_IMPLEMENT_FUNC(AcisIntCurve , AcisCurve , TYPELIST({_T("intcurve-curve") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisIntCurve::AcisIntCurve(const TCHAR* pType,const long& nIndex) : AcisCurve(pType,nIndex)
{
}

/**	
	@brief
*/
AcisIntCurve::~AcisIntCurve()
{
	try
	{
	}
	catch(...)
	{
	}
}

/**	
	@brief	The AcisIntCurve::Parse function
	@author	humkyung
	@date	?
	@param	psz	a parameter of type const char*
	@remarks\n
	;2004.03.30 - read curve id('surfintcur' , 'exactcur')
	;2004.12.16 - fix code segement when curve is is 'exactcur'
	@return	bool	
*/
bool AcisIntCurve::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	if((NULL != pDoc) && (NULL != psz))
	{
		int iLineIndex = 0;
		STRING_T aLine;
		vector<STRING_T> oLines , oResult;
		CTokenizer<CIsFromString>::Tokenize(oLines , psz , CIsFromString(_T("\r\n")));
		if(700 == pDoc->GetVer())
		{
			aLine = oLines[iLineIndex];
			CTokenizer<CIsFromString>::Tokenize(oResult,aLine,CIsFromString(_T(" \t")));
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
				}
			}
			/*m_nNumOfPoints = ATOI_T(oResult[9].c_str())*2;
			
			STRING_T aLine = oLines[++iLineIndex];
			IsString::TrimWhiteSpace(aLine);
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));

			for(int i = 0;i < m_nNumOfPoints;++i)
			{
				aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				if(3 == oResult.size())
				{
					m_ppts->push_back(CIsPoint3d(ATOF_T(oResult[0].c_str()) , ATOF_T(oResult[1].c_str()) , ATOF_T(oResult[2].c_str())));
				}
			}

			STRING_T::size_type at = aLine.find(ACIS_END_OF_SUBTYPE);
			do
			{
				aLine = oLines[++iLineIndex];
				at = aLine.find(ACIS_END_OF_SUBTYPE);
			}while(at == STRING_T::npos);
			IsString::TrimWhiteSpace(aLine);
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));*/
		}
		else
		{
			aLine = oLines[iLineIndex];
			CTokenizer<CIsFromString>::Tokenize(oResult,aLine,CIsFromString(_T(" \t")));
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
				}	
			}
		}

		return true;
	}

	return false;
}

/**	\brief	The AcisIntCurve::CreateCurve function


	\return	PSQPRIMITIVE	
*/
//PSQPRIMITIVE AcisIntCurve::CreateCurve()
//{
//	PSQPRIMITIVE pRet=NULL;
//
//	if((0L != m_nNumOfPoints) && (pRet = AcisLib::AllocPrimitive()))
//	{
//		pRet->hdr.id = SQ_INTCURVE;
//		pRet->body.intcurve.nPoints = m_nNumOfPoints;
//		pRet->body.intcurve.ppt = m_ppt;
//
//		VECTOR_T u={0,},v={0,};
//		u.dx = pRet->body.intcurve.ppt[1].x - pRet->body.intcurve.ppt[0].x;
//		u.dy = pRet->body.intcurve.ppt[1].y - pRet->body.intcurve.ppt[0].y;
//		u.dz = pRet->body.intcurve.ppt[1].z - pRet->body.intcurve.ppt[0].z;
//		v.dx = pRet->body.intcurve.ppt[2].x - pRet->body.intcurve.ppt[0].x;
//		v.dy = pRet->body.intcurve.ppt[2].y - pRet->body.intcurve.ppt[0].y;
//		v.dz = pRet->body.intcurve.ppt[2].z - pRet->body.intcurve.ppt[0].z;
//		pRet->body.intcurve.vecNorm.dx = u.dy*v.dz - u.dz*v.dy;
//		pRet->body.intcurve.vecNorm.dy = u.dz*v.dx - u.dx*v.dz;
//		pRet->body.intcurve.vecNorm.dz = u.dx*v.dy - u.dy*v.dx;
//		double l=
//			(pRet->body.intcurve.vecNorm.dx)*(pRet->body.intcurve.vecNorm.dx)+
//			(pRet->body.intcurve.vecNorm.dy)*(pRet->body.intcurve.vecNorm.dy)+
//			(pRet->body.intcurve.vecNorm.dz)*(pRet->body.intcurve.vecNorm.dz);
//		l = sqrt(l);
//		pRet->body.intcurve.vecNorm.dx /= l;
//		pRet->body.intcurve.vecNorm.dy /= l;
//		pRet->body.intcurve.vecNorm.dz /= l;
//	}
//
//	return pRet;
//}