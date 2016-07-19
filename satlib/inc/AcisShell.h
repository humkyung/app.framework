#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"

class ON_EXT_CLASS AcisShell : public AcisEntity  
{
public:
	AcisShell(const TCHAR*,const long& nIndex);
	virtual ~AcisShell();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	long GetFaceIndex() const;
	long GetLumpIndex() const;

	ACISLIB_DECLARE_FUNC(AcisShell)
private:
	long m_lFaceIndex;
	long m_lLumpIndex;
};
