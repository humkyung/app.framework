#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisCurve.h"

class ON_EXT_CLASS AcisPCurve : public AcisCurve
{
public:
	typedef enum curv_type
	{
		undef , 
		exppc	
	};

	AcisPCurve(const TCHAR*,const long& lIndex);
	virtual ~AcisPCurve();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	ACISLIB_DECLARE_FUNC(AcisPCurve)
private:
	AcisPCurve::curv_type m_type;
	long m_lAttributeIndex;
	int m_iDegree;
	int m_iKnots;
};