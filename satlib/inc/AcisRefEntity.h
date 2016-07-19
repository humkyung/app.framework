#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <BaseTools.h>
#include <fstream>
#include <AcisEntity.h>
using namespace std;

class ON_EXT_CLASS AcisRefEntity : public AcisEntity
{
public:
	AcisRefEntity(const TCHAR*,const long& lIndex);
	virtual ~AcisRefEntity();
public:
	bool Parse(AcisDoc*,const TCHAR*);

	ACISLIB_DECLARE_FUNC(AcisRefEntity)
};
