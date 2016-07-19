// AcisTorusSurf.cpp: implementation of the AcisTorusSurf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <tokenizer.h>
#include <AcisLib.h>
#include <AcisTorusSurf.h>

ACISLIB_IMPLEMENT_FUNC(AcisTorusSurf , AcisSurf , TYPELIST({_T("torus-surface") , NULL}))
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisTorusSurf::AcisTorusSurf(const TCHAR* pType,const long& nIndex) : AcisSurf(pType,nIndex)
{
	m_bReversed = false;
}

AcisTorusSurf::~AcisTorusSurf()
{

}

/**	
	@brief	return origin of torus
	@author	humkyung
	@date	2014.11.06
	@return	CPoint3d
*/
CPoint3d AcisTorusSurf::origin() const
{
	return m_ptOrigin;
}

/**	
	@brief	return normal vector of torus
	@author	humkyung
	@date	2014.11.06
	@return	CVect3d
*/
CVect3d AcisTorusSurf::norm() const
{
	return m_vecNorm;
}

/**	
	@brief	return axis vector of torus
	@author	humkyung
	@date	2014.11.06
	@return	CVect3d
*/
CVect3d AcisTorusSurf::Vx() const
{
	return m_vecStart;
}

/**	
	@brief	return torus radius of torus
	@author	humkyung
	@date	2014.11.06
	@return	double	
*/
const double AcisTorusSurf::GetTorusRadius() const
{
	return m_dTorusRadius;
}

/**	
	@brief	return tube radius of torus
	@author	humkyung
	@date	2014.11.06
	@return	double	
*/
const double AcisTorusSurf::GetTubeRadius() const
{
	return m_dTubeRadius;
}

/**	
	@brief	The AcisTorusSurf::Parse function
	@author	humkyung
	@param	psz	a parameter of type const char*
	@return	bool	
*/
bool AcisTorusSurf::Parse(AcisDoc* pDoc,const TCHAR* psz)
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
			m_vecNorm.dx()=ATOF_T(oResult[7].c_str());
			m_vecNorm.dy()=ATOF_T(oResult[8].c_str());
			m_vecNorm.dz()=ATOF_T(oResult[9].c_str());
			m_dTorusRadius = ATOF_T(oResult[10].c_str());
			m_dTubeRadius = ATOF_T(oResult[11].c_str());
			m_vecStart.dx()=ATOF_T(oResult[12].c_str());
			m_vecStart.dy()=ATOF_T(oResult[13].c_str());
			m_vecStart.dz()=ATOF_T(oResult[14].c_str());
			if(m_dTubeRadius < 0.) m_bReversed = !m_bReversed;
		}
		else
		{
			m_ptOrigin.SetX(ATOF_T(oResult[2].c_str()));
			m_ptOrigin.SetY(ATOF_T(oResult[3].c_str()));
			m_ptOrigin.SetZ(ATOF_T(oResult[4].c_str()));
			m_vecNorm.dx() = ATOF_T(oResult[5].c_str());
			m_vecNorm.dy() = ATOF_T(oResult[6].c_str());
			m_vecNorm.dz() = ATOF_T(oResult[7].c_str());
			m_dTorusRadius = ATOF_T(oResult[8].c_str());
			m_dTubeRadius = ATOF_T(oResult[9].c_str());
			m_vecStart.dx()=ATOF_T(oResult[10].c_str());
			m_vecStart.dy()=ATOF_T(oResult[11].c_str());
			m_vecStart.dz()=ATOF_T(oResult[12].c_str());
			if(m_dTubeRadius < 0.) m_bReversed = !m_bReversed;
		}

		bRet = true;
	}

	return bRet;
}