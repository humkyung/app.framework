#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"

class ON_EXT_CLASS AcisTransform : public AcisEntity
{
public:
	AcisTransform(const TCHAR*,const long& lIndex);
	virtual ~AcisTransform();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	ACISLIB_DECLARE_FUNC(AcisEntity)
protected:
};