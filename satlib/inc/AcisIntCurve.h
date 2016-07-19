#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisCurve.h"

class ON_EXT_CLASS AcisIntCurve : public AcisCurve
{
	typedef enum curv_type
	{
		undef = 0,
		surfintcur= 1,
		exactcur  = 2	
	};
public:
	AcisIntCurve(const TCHAR*,const long& nIndex);
	virtual ~AcisIntCurve();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	AcisIntCurve::curv_type type() const{
		return m_type;
	};

	ACISLIB_DECLARE_FUNC(AcisIntCurve)
private:
	AcisIntCurve::curv_type m_type;
};