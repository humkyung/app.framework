#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisSurf.h"

class ON_EXT_CLASS AcisSphereSurf : public AcisSurf
{
public:
	AcisSphereSurf(const TCHAR*,const long& nIndex);
	virtual ~AcisSphereSurf();
public:
	bool Parse(ifstream& file);
	bool Parse(AcisDoc*,const TCHAR*);

	ACISLIB_DECLARE_FUNC(AcisSphereSurf)
private:
	double m_nRadius;
};