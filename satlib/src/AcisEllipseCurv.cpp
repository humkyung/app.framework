// AcisEllipseCurv.cpp: implementation of the AcisEllipseCurv class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include <Tokenizer.h>
#include <AcisLib.h>
#include <AcisEllipseCurv.h>

ACISLIB_IMPLEMENT_FUNC(AcisEllipseCurv , AcisCurve , TYPELIST({_T("ellipse-curve") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisEllipseCurv::AcisEllipseCurv(const TCHAR* pType,const long& nIndex) : AcisCurve(pType,nIndex) , m_type(ellipse_type)
{
	m_dRadius = 0;
	m_dRatio = 1;
}

/**	
	@brief
*/
AcisEllipseCurv::~AcisEllipseCurv()
{

}

/**	
	@brief	The CSATConeSurf::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisEllipseCurv::Parse(AcisDoc* pDoc,const TCHAR* psz)
{
	assert(pDoc && psz && "pDoc or psz is NULL");
	bool bRet=false;

	if((NULL != pDoc) && (NULL != psz))
	{
		vector<STRING_T> oResult;
		CTokenizer<CIsFromString>::Tokenize(oResult,psz,CIsFromString(_T(" \t")));
		if(700 == pDoc->GetVer())
		{ // ACAD 2004 , ACAD2005
			m_ptOrigin.SetX(ATOF_T(oResult[4].c_str()));
			m_ptOrigin.SetY(ATOF_T(oResult[5].c_str()));
			m_ptOrigin.SetZ(ATOF_T(oResult[6].c_str()));
			
			/// get normal vector of plane
			m_vecNorm.dx() = ATOF_T(oResult[7].c_str());
			m_vecNorm.dy() = ATOF_T(oResult[8].c_str());
			m_vecNorm.dz() = ATOF_T(oResult[9].c_str());
			
			/// get delta 
			m_vecDelta.dx() = ATOF_T(oResult[10].c_str());
			m_vecDelta.dy() = ATOF_T(oResult[11].c_str());
			m_vecDelta.dz() = ATOF_T(oResult[12].c_str());

			/// ratio
			m_dRatio = 1. / ATOF_T(oResult[13].c_str());

			m_type = (oResult[14] == _T("I")) ? ellipse_type : arc_type;
		}
		else
		{
			// get origion of arc
			m_ptOrigin.SetX(ATOF_T(oResult[2].c_str()));
			m_ptOrigin.SetY(ATOF_T(oResult[3].c_str()));
			m_ptOrigin.SetZ(ATOF_T(oResult[4].c_str()));
			
			// get normal vector of plane
			m_vecNorm.dx() = ATOF_T(oResult[5].c_str());
			m_vecNorm.dy() = ATOF_T(oResult[6].c_str());
			m_vecNorm.dz() = ATOF_T(oResult[7].c_str());
			
			// get delta 
			m_vecDelta.dx() = ATOF_T(oResult[8].c_str());
			m_vecDelta.dy() = ATOF_T(oResult[9].c_str());
			m_vecDelta.dz() = ATOF_T(oResult[10].c_str());

			/// ratio
			m_dRatio = 1. / ATOF_T(oResult[11].c_str());

			m_type = (oResult[12] == _T("I")) ? ellipse_type : arc_type;
		}
		m_dRadius = m_vecDelta.Length();

		bRet = true;
	}

	return bRet;
}

/**	\brief	The AcisEllipseCurv::SetOriginPos function

	\param	ptOrigin	a parameter of type const POINT_T&

	\return	void	
*/
//void AcisEllipseCurv::SetOriginPos(const POINT_T& ptOrigin)
//{
//	m_ptOrigin = ptOrigin;
//}

/**	
	@brief	The AcisEllipseCurv::GetOriginPos function
	@author	humkyung
	@return	POINT_T	
*/
CPoint3d AcisEllipseCurv::origin() const
{
	return m_ptOrigin;
}

/**	\brief	The AcisEllipseCurv::SetStartPoint function

	\param	ptStart	a parameter of type const POINT_T&

	\return	void	
*/
//void AcisEllipseCurv::SetStartPos(const POINT_T& ptStart)
//{
//	m_ptStart = ptStart;
//}

/**	
	@brief	The AcisEllipseCurv::GetStartPos function
	@author	humkyung
	@return	POINT_T	
*/
CPoint3d AcisEllipseCurv::GetStartPos() const
{
	return m_ptStart;
}

/**	\brief	The AcisEllipseCurv::SetEndPoint function

	\param	ptEnd	a parameter of type const POINT_T&

	\return	void	
*/
//void AcisEllipseCurv::SetEndPos(const POINT_T& ptEnd)
//{
//	m_ptEnd = ptEnd;
//}

/**	\brief	The AcisEllipseCurv::SetNormVector function

	\param	vecNorm	a parameter of type const VECTOR_T&

	\return	void
*/
//void AcisEllipseCurv::SetNormVector(const VECTOR_T& vecNorm)
//{
//	m_vecNorm = vecNorm;
//}

/**	
	@brief	The AcisEllipseCurv::GetNormVector function
	@author	humkyung
	@return	CIsVect3d
*/
CVect3d AcisEllipseCurv::norm() const
{
	return m_vecNorm;
}

/**	
	@brief	return delta vector indicates start point of ellipse
	@author	humkyung
	@return	CIsVect3d	
*/
CVect3d AcisEllipseCurv::delta() const
{
	return m_vecDelta;
}

/**	
	@brief	return radius
	@author	humkyung
	@return	double	
*/
double AcisEllipseCurv::radius() const
{
	return m_dRadius;
}

/**	
	@brief	return ratio
	@author	humkyung
	@return	double	
*/
double AcisEllipseCurv::ratio() const
{
	return m_dRatio;
}