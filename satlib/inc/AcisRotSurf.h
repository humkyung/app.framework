#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisSurf.h"

#include <list>
using namespace std;

class ON_EXT_CLASS AcisRotSurf : public AcisSurf
{
public:
	AcisRotSurf(const TCHAR*,const long& nIndex);
	virtual ~AcisRotSurf();
public:
	bool Parse(AcisDoc*,const TCHAR*);

	ACISLIB_DECLARE_FUNC(AcisRotSurf)
private:
};