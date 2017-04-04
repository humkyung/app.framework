#include "stdafx.h"
#include <assert.h>
#include <tokenizer.h>
#include <IsString.h>
#include <AcisLib.h>
#include <AcisDoc.h>
#include "AcisSurfIntCurv.h"
#include <AcisRefEntity.h>

ACISLIB_IMPLEMENT_FUNC(AcisSurfIntCurv , AcisCurve , TYPELIST({_T("surfintcur") , NULL}))

AcisSurfIntCurv::AcisSurfIntCurv(const TCHAR* pType,const long& lIndex) : AcisCurve(pType,lIndex)
{
	m_iDegree = m_iKnots = 0;
	m_eType = OPEN;
	m_pKnots = new vector<AcisCurve::Knot>;
	m_pPoles = new vector<AcisCurve::Pole>;
}


AcisSurfIntCurv::~AcisSurfIntCurv(void)
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
	@brief	return true if bspline type is open
	@author	humkyung
	@date	2014.11.02
	@return	int
*/
bool AcisSurfIntCurv::IsOpen() const
{
	return (OPEN == m_eType);
}

/**
	@brief	return number of poles
	@author	humkyung
	@date	2014.11.02
	@return	int
*/
int AcisSurfIntCurv::poles() const
{
	return m_pPoles->size();
}

/**
	@brief	return degree
	@author	humkyung
	@date	2014.11.02
	@return	int
*/
int AcisSurfIntCurv::degree() const
{
	return m_iDegree;
}

/**
	@brief	return number of knot
	@author	humkyung
	@date	2014.11.02
	@return	int
*/
int AcisSurfIntCurv::knots() const
{
	return m_iKnots;
}

/**
	@brief	parse given buf
	@author	humkyung
	@date	2014.10.23
	@return	bool
*/
bool AcisSurfIntCurv::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or szBuf is NULL");
	bool res = false;

	if((NULL != pDoc) && (NULL != psz))
	{
		int iLineIndex = 0;

		vector<STRING_T> oLines , oResult;
		CTokenizer<CIsFromString>::Tokenize(oLines , psz , CIsFromString(_T("\r\n")));
		if(!oLines.empty())
		{
			CTokenizer<CIsFromString>::Tokenize(oResult , oLines[iLineIndex] , CIsFromString(_T(" \t")));
			if(700 == pDoc->GetVer())
			{
				if((_T("nubs") == oResult[3]) || (_T("nurbs") == oResult[3]))	/// used as part of B-spline curve definition
				{
					m_iDegree = ATOI_T(oResult[4].c_str());
					m_eType = (_T("open") == oResult[5]) ? OPEN : PERIODIC;
					m_iKnots  = ATOI_T(oResult[6].c_str());
				}
			}else if(400 == pDoc->GetVer())
			{
				if((_T("nubs") == oResult[2]) || (_T("nurbs") == oResult[2]))	/// used as part of B-spline curve definition
				{
					m_iDegree = ATOI_T(oResult[3].c_str());
					m_eType = (_T("open") == oResult[4]) ? OPEN : PERIODIC;
					m_iKnots  = ATOI_T(oResult[5].c_str());
				}
			}

			STRING_T aLine;
			int i = 0 , num_knots = 0;
			while(int(m_pKnots->size()) < m_iKnots)
			{
				aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				AcisCurve::Knot knot;
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				for(vector<STRING_T>::iterator itr = oResult.begin();itr != oResult.end();++itr)
				{
					knot.value = ATOF_T(itr->c_str());
					++itr;
					knot.multiplicity = ATOI_T(itr->c_str());
					//if(OPEN == m_eType)
					{
						if((0 == m_pKnots->size()) || ((m_iKnots - 1) == m_pKnots->size()))
						{
							knot.multiplicity = m_iDegree + 1;
						}
					}
					/*else
					{
						if((0 == m_pKnots->size()) || ((m_iKnots - 1) == m_pKnots->size()))
						{
							knot.multiplicity -= 1;
						}
					}*/
					num_knots += knot.multiplicity;
					m_pKnots->push_back(knot);
				}
			}

			const int iPoles = /*(OPEN == m_eType) ? */num_knots - m_iDegree - 1;/// : num_knots;
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
	}

	return res;
}
