#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Point3d.h>
#include "AcisEntity.h"

using namespace AppFramework;

class ON_EXT_CLASS AcisPoint : public AcisEntity  
{
public:
	AcisPoint(const TCHAR*,const long& nIndex);
	virtual ~AcisPoint();
public:
	bool Parse(ifstream& file);
	bool Parse(AcisDoc*,const TCHAR*);
	AppFramework::CPoint3d GetPoint() const;
	ACISLIB_DECLARE_FUNC(AcisPoint)
private:
	CPoint3d m_pt;
};