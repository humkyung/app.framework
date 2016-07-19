#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"
class ON_EXT_CLASS AcisSurf : public AcisEntity
{
public:
	AcisSurf(const TCHAR*,const long& lIndex);
	virtual ~AcisSurf();

	bool Parse(AcisDoc*,const TCHAR*);
	ACISLIB_DECLARE_FUNC(AcisSurf)
public:
};