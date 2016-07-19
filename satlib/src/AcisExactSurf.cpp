// AcisExactSurf.cpp: implementation of the AcisExactSurf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Tokenizer.h>
#include <IsString.h>
#include <AcisLib.h>
#include <AcisEllipseCurv.h>
#include <AcisExactSurf.h>

ACISLIB_IMPLEMENT_FUNC(AcisExactSurf , AcisSurf , TYPELIST({_T("exactsur") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisExactSurf::AcisExactSurf(const TCHAR* pType,const long& nIndex) : AcisSurf(pType,nIndex)
{
	m_iUDegree = -1;
	m_iVDegree = -1;
	m_iUKnots = -1;
	m_iVKnots = -1;
	m_pUKnots = new vector<AcisExactSurf::Knot>;
	m_pVKnots = new vector<AcisExactSurf::Knot>;
	m_pPoles = new vector<AcisExactSurf::Pole>;
}

/**	
	@brief
*/
AcisExactSurf::~AcisExactSurf()
{
	try
	{
		SAFE_DELETE(m_pUKnots);
		SAFE_DELETE(m_pVKnots);
		SAFE_DELETE(m_pPoles);
	}
	catch(...)
	{
	}
}

/**
	@brief	get curve definition index
	@author	humkyung
	@date	2016.07.07
	@return	int
*/
int AcisExactSurf::GetCurvDefIndex(const vector<STRING_T>& oResult) const
{
	int res = 0;

	for(vector<STRING_T>::const_iterator itr = oResult.begin();itr != oResult.end();++itr,++res)
	{
		if((_T("nubs") == *itr) || (_T("nurbs") == *itr)) return res;
	}

	return -1;
}

/**
	@brief	parse spline exact surf
	@author	humkyung
	@date	2014.10.22
	@return	bool
*/
bool AcisExactSurf::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");

	if((NULL != pDoc) && (NULL != psz))
	{
		int iLineIndex = 0;

		vector<STRING_T> oLines , oResult;
		CTokenizer<CIsFromString>::Tokenize(oLines , psz , CIsFromString(_T("\r\n")));
		{
			vector<STRING_T> oResult;
			CTokenizer<CIsFromString>::Tokenize(oResult , oLines[iLineIndex] , CIsFromString(_T(" \t")));
			const int iCurvDefIndex = this->GetCurvDefIndex(oResult);
			const STRING_T sCurveDef = oResult[iCurvDefIndex];
			if(_T("nubs") == sCurveDef)	/// used as part of B-spline curve definition
			{
				m_iUDegree = ATOI_T(oResult[iCurvDefIndex+1].c_str());
				m_iVDegree = ATOI_T(oResult[iCurvDefIndex+2].c_str());
				/// u-closure
				/// v-closure
				/// u-singularity
				/// v-singularity
				m_iUKnots = ATOI_T(oResult[oResult.size()-2].c_str());
				m_iVKnots = ATOI_T(oResult[oResult.size()-1].c_str());

				int KnotNums[2] = {0,0};
				STRING_T aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				AcisExactSurf::Knot knot;
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				for(int i = 0;i < m_iUKnots;++i)
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
					KnotNums[0] += knot.multiplicity;
					m_pUKnots->push_back(knot);
				}

				aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				for(int i = 0;i < m_iVKnots;++i)
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
					KnotNums[1] += knot.multiplicity;
					m_pVKnots->push_back(knot);
				}

				const int iCtrlPoints = (KnotNums[0]-m_iUDegree+1)*(KnotNums[1]-m_iVDegree+1);
				Pole aPole;
				for(int i = 0;i < iCtrlPoints;++i)
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
			}
			else if(_T("nurbs") == sCurveDef)	/// used as part of B-spline curve definition
			{
				m_iUDegree = ATOI_T(oResult[iCurvDefIndex+1].c_str());
				m_iVDegree = ATOI_T(oResult[iCurvDefIndex+2].c_str());
				/// u-closure
				/// v-closure
				/// u-singularity
				/// v-singularity
				m_iUKnots = ATOI_T(oResult[oResult.size()-2].c_str());
				m_iVKnots = ATOI_T(oResult[oResult.size()-1].c_str());

				int KnotNums[2] = {0,0};
				STRING_T aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				AcisExactSurf::Knot knot;
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				for(int i = 0;i < m_iUKnots;++i)
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
					KnotNums[0] += knot.multiplicity;
					m_pUKnots->push_back(knot);
				}

				aLine = oLines[++iLineIndex];
				IsString::TrimWhiteSpace(aLine);
				CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
				for(int i = 0;i < m_iVKnots;++i)
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
					KnotNums[1] += knot.multiplicity;
					m_pVKnots->push_back(knot);
				}

				const int iCtrlPoints = (KnotNums[0]-m_iUDegree+1)*(KnotNums[1]-m_iVDegree+1);
				Pole aPole;
				for(int i = 0;i < iCtrlPoints;++i)
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
			}
		}

		return true;
	}
	
	return false;
}

int AcisExactSurf::u_degree() const
{
	return m_iUDegree;
}

int AcisExactSurf::v_degree() const
{
	return m_iVDegree;
}

int AcisExactSurf::u_knots() const
{
	return m_iUKnots;
}

int AcisExactSurf::v_knots() const
{
	return m_iVKnots;
}