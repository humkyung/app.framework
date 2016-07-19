#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisCurve.h"

class ON_EXT_CLASS AcisStraightCurv : public AcisCurve
{
public:
	AcisStraightCurv(const TCHAR*,const long& nIndex);
	virtual ~AcisStraightCurv();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	ACISLIB_DECLARE_FUNC(AcisStraightCurv)
private:
};
