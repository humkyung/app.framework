#include "stdafx.h"
#include <assert.h>
#include <tokenizer.h>
#include <isstring.h>
#include <AcisLib.h>
#include <AcisDoc.h>
#include "AcisExactCurv.h"
#include <AcisRefEntity.h>

ACISLIB_IMPLEMENT_FUNC(AcisExactCurv , AcisCurve , TYPELIST({_T("exactcur") , NULL}))

AcisExactCurv::AcisExactCurv(const TCHAR* pType,const long& lIndex) : AcisCurve(pType,lIndex)
{
	m_iDegree = m_iKnots = -1;
	m_pKnots = new vector<AcisExactCurv::Knot>;
	m_pPoles = new vector<AcisExactCurv::Pole>;
}


AcisExactCurv::~AcisExactCurv(void)
{
	try
	{
		SAFE_DELETE(m_pKnots);
		SAFE_DELETE(m_pPoles);
	}
	catch(...)
	{
	}
}

/**
	@brief	return number of poles
	@author	humkyung
	@date	2014.10.28
	@return	int
*/
int AcisExactCurv::poles() const
{
	return m_pPoles->size();
}

/**
	@brief	return degree
	@author	humkyung
	@date	2014.10.28
	@return	int
*/
int AcisExactCurv::degree() const
{
	return m_iDegree;
}

/**
	@brief	return number of knot
	@author	humkyung
	@date	2014.10.28
	@return	int
*/
int AcisExactCurv::knots() const
{
	return m_iKnots;
}

/**
	@brief	parse given buf
	@author	humkyung
	@date	2014.10.23
	@return	bool
*/
bool AcisExactCurv::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or szBuf is NULL");
	bool res = false;

	if((NULL != pDoc) && (NULL != psz))
	{
		int iLineIndex = 0;

		vector<STRING_T> oLines , oResult;
		CTokenizer<CIsFromString>::Tokenize(oLines , psz , CIsFromString(_T("\r\n")));
		if(700 == pDoc->GetVer())
		{
			CTokenizer<CIsFromString>::Tokenize(oResult , oLines[iLineIndex] , CIsFromString(_T(" \t")));
			if((_T("nubs") == oResult[3]) || (_T("nurbs") == oResult[3]))	/// used as part of B-spline curve definition
			{
				m_iDegree = ATOI_T(oResult[4].c_str());
				m_iKnots  = ATOI_T(oResult[6].c_str());
			}
		}
		else if(400 == pDoc->GetVer())
		{
			CTokenizer<CIsFromString>::Tokenize(oResult , oLines[iLineIndex] , CIsFromString(_T(" \t")));
			if((_T("nubs") == oResult[2]) || (_T("nurbs") == oResult[2]))	/// used as part of B-spline curve definition
			{
				m_iDegree = ATOI_T(oResult[3].c_str());
				m_iKnots  = ATOI_T(oResult[5].c_str());
			}
		}

		STRING_T aLine = oLines[++iLineIndex];
		IsString::TrimWhiteSpace(aLine);
		int num_knots = 0;
		AcisExactCurv::Knot knot;
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
		Pole aPole;
		for(int i = 0;i < iPoles;++i)
		{
			aLine = oLines[++iLineIndex];
			IsString::TrimWhiteSpace(aLine);
			CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
			aPole.pt.Set(ATOF_T(oResult[0].c_str()) , ATOF_T(oResult[1].c_str()) , ATOF_T(oResult[2].c_str()));

			aPole.weight = 1.0;
			if(4 == oResult.size())
			{
				aPole.weight = ATOF_T(oResult[3].c_str());
			}
			m_pPoles->push_back(aPole);
		}

		STRING_T::size_type at;
		do
		{
			aLine = oLines[++iLineIndex];
			at = aLine.find(ACIS_END_OF_SUBTYPE);
		}while(STRING_T::npos == at);

		res = true;
	}

	return res;
}
