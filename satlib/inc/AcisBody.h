#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"

class ON_EXT_CLASS AcisBody : public AcisEntity  
{
public:
	AcisBody(const TCHAR*,const long& nIndex);
	virtual ~AcisBody();
public:
	bool Parse(AcisDoc*,const TCHAR* psz);
	long GetLumpIndex() const;
	long GetWireIndex() const;
	long GetTransformIndex() const;

	ACISLIB_DECLARE_FUNC(AcisBody)
private:
	long m_lLumpIndex;
	long m_lWireIndex;
	long m_lTransformIndex;
};