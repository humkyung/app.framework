#include "stdafx.h"
#include <assert.h>
#include <tokenizer.h>
#include <isstring.h>
#include <AcisLib.h>
#include <AcisDoc.h>
#include "AcisExppcCurv.h"
#include <AcisRefEntity.h>
#include <AcisEntityFactory.h>

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

ACISLIB_IMPLEMENT_FUNC(AcisExppcCurv , AcisCurve , TYPELIST({_T("exppc") , NULL}))

AcisExppcCurv::AcisExppcCurv(const TCHAR* pType,const long& lIndex) : AcisCurve(pType,lIndex)
{
	m_iDegree = m_iKnots = -1;
	m_pKnots = new vector<AcisCurve::Knot>; 
	m_pParams = new vector<AcisCurve::Param>; 
	m_pSubType = NULL;
}


AcisExppcCurv::~AcisExppcCurv(void)
{
	try
	{
		SAFE_DELETE(m_pKnots);
		SAFE_DELETE(m_pParams);
		//SAFE_DELETE(m_pSubType);
	}
	catch(...)
	{
	}
}

/**
	@brief	return degree
	@author	humkyung
	@date	2014.10.29
	@return	bool
*/
int AcisExppcCurv::degree() const
{
	return m_iDegree;
}

/**
	@brief	return number of knots
	@author	humkyung
	@date	2014.10.29
	@return	bool
*/
int AcisExppcCurv::knots() const
{
	return m_iKnots;
}

/**
	@brief	return number of params 
	@author	humkyung
	@date	2014.10.29
	@return	bool
*/
int AcisExppcCurv::params() const
{
	return m_pParams->size();
}

/**
	@brief	parse given buf
	@author	humkyung
	@date	2014.10.23
	@return	bool
*/
bool AcisExppcCurv::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or szBuf is NULL");
	bool res = false;

	if((NULL != pDoc) && (NULL != psz))
	{
		int iLineIndex = 0;

		vector<STRING_T> oLines , oResult;
		CTokenizer<CIsFromString>::Tokenize(oLines , psz , CIsFromString(_T("\r\n")));
		//if(700 == pDoc->GetVer())
		{
			STRING_T aLine = oLines[iLineIndex];
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
			m_iDegree = ATOI_T(oResult[3].c_str());
			m_iKnots = ATOI_T(oResult[5].c_str());

			aLine = oLines[++iLineIndex];
			IsString::TrimWhiteSpace(aLine);
			int num_knots = 0;
			AcisCurve::Knot knot;
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
			for(int i = 0;i < m_iKnots;++i)
			{
				if(oResult.size() <= i*2)
				{
					aLine = oLines[++iLineIndex];
					IsString::TrimWhiteSpace(aLine);
					vector<STRING_T> tmp;
					CTokenizer<CIsFromString>::Tokenize(tmp, aLine , CIsFromString(_T(" \t")));
					oResult.insert(oResult.end(),tmp.begin(),tmp.end());
				}
				knot.value = ATOF_T(oResult[i*2].c_str());
				knot.multiplicity = ATOI_T(oResult[i*2+1].c_str());
				if((0 == i) || ((m_iKnots - 1) == i))
				{
					knot.multiplicity = m_iDegree + 1;
				}
				num_knots += knot.multiplicity;
				m_pKnots->push_back(knot);
			}

			const int iPoles = num_knots - m_iDegree - 1;
			AcisCurve::Param aParam;
			for(int i = 0;i < iPoles;++i)
			{
				aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				aParam.u = ATOF_T(oResult[0].c_str());
				aParam.v = ATOF_T(oResult[1].c_str());
				m_pParams->push_back(aParam);
			}

			aLine = oLines[++iLineIndex];
			aLine = oLines[++iLineIndex];
			IsString::TrimWhiteSpace(aLine);
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
			vector<STRING_T>::iterator where = find(oResult.begin() , oResult.end() , ACIS_START_OF_SUBTYPE);
			if((_T("spline") == oResult[0]) && (where != oResult.end()))
			{
				m_pSubType = AcisEntityFactory::CreateEntity((where+1)->c_str() , -1);
				if(NULL != m_pSubType)
				{
					SubTypeRefIndex() = pDoc->RegisterSubType(m_pSubType);

					OSTRINGSTREAM_T stream;
#ifdef	_UNICODE
					std::copy(where , oResult.end(), std::ostream_iterator<STRING_T,wchar_t>(stream , _T(" ")));
#else
					std::copy(where , oResult.end(), std::ostream_iterator<STRING_T>(stream , _T(" ")));
#endif
					aLine = stream.str();
					STRING_T str = GetStringOfSubType(aLine , iLineIndex , oLines);

					m_pSubType->Parse(pDoc , str.c_str());
				}
			}
		}
		/*else if(400 == pDoc->GetVer())
		{
			STRING_T aLine = oLines[iLineIndex];
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
			if((_T("nubs") == oResult[2]) || (_T("nurbs") == oResult[2]))	/// used as part of B-spline curve definition
			{
				m_iDegree = ATOI_T(oResult[3].c_str());
				m_iKnots = ATOI_T(oResult[5].c_str());

				STRING_T aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				int num_knots = 0;
				AcisCurve::Knot knot;
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				for(int i = 0;i < m_iKnots;++i)
				{
					knot.value = ATOF_T(oResult[i*2].c_str());
					knot.multiplicity = ATOI_T(oResult[i*2+1].c_str());
					if((0 == i) || ((m_iKnots - 1) == i))
					{
						knot.multiplicity = m_iDegree + 1;
					}
					num_knots += knot.multiplicity;
					m_pKnots->push_back(knot);
				}

				const int iPoles = num_knots - m_iDegree - 1;
				AcisCurve::Param aParam;
				for(int i = 0;i < iPoles;++i)
				{
					aLine = oLines[++iLineIndex];
					IsString::TrimWhiteSpace(aLine);
					CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
					aParam.u = ATOF_T(oResult[0].c_str());
					aParam.v = ATOF_T(oResult[1].c_str());
					m_pParams->push_back(aParam);
				}

				aLine = oLines[++iLineIndex];
				aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				vector<STRING_T>::iterator where = find(oResult.begin() , oResult.end() , ACIS_START_OF_SUBTYPE);
				if((_T("spline") == oResult[0]) && (where != oResult.end()))
				{
					m_pSubType = AcisEntityFactory::CreateEntity((where+1)->c_str() , -1);
					if(NULL != m_pSubType)
					{
						OSTRINGSTREAM_T stream;
						std::copy(where , oResult.end(), std::ostream_iterator<STRING_T>(stream , _T(" ")));
						aLine = stream.str();
						STRING_T str = GetStringOfSubType(aLine , iLineIndex , oLines);

						m_pSubType->Parse(pDoc , str.c_str());
					}
				}
			}
		}*/
	}

	return res;
}

/**
	@brief	return subtype
	@author	humkyung
	@date	2014.10.29
	@return	AcisEntity*	
*/
AcisEntity* AcisExppcCurv::subtype()
{
	return m_pSubType;
}