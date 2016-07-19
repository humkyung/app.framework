// AcisPCurve.cpp: implementation of the AcisPCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <tchar.h>
#include <Tokenizer.h>
#include <IsString.h>
#include <BaseTools.h>
#include <AcisLib.h>
#include <AcisPCurve.h>
#include <AcisSplineSurf.h>
#include <AcisExppcCurv.h>
#include <AcisEntityFactory.h>

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

ACISLIB_IMPLEMENT_FUNC(AcisPCurve , AcisCurve , TYPELIST({_T("pcurve") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AcisPCurve::AcisPCurve(const TCHAR* pType,const long& lIndex) : AcisCurve(pType,lIndex)
{
	m_lAttributeIndex = -1;
	m_type = AcisPCurve::undef;
}

AcisPCurve::~AcisPCurve()
{

}

/**	
	@brief	parse pcurve
	@author	humkyung
	@date	2014.10.21
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisPCurve::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	if((NULL != pDoc) && (NULL != psz))
	{
		int iLineIndex = 0;

		vector<STRING_T> oLines , oResult;
		CTokenizer<CIsFromString>::Tokenize(oLines , psz , CIsFromString(_T("\r\n")));
		if(700 == pDoc->GetVer())
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
				}
			}
		}
		else
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
				}
			}
		}

		return true;
	}

	return false;
}