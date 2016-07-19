#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"

class ON_EXT_CLASS AcisFace : public AcisEntity  
{
public:
	AcisFace(const TCHAR*,const long& nIndex);
	virtual ~AcisFace();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	
	const long GetNextIndex() const;
	long GetSurfIndex() const;
	long GetShellIndex() const;
	long GetLoopIndex() const;
	AcisSense sense() const;

	ACISLIB_DECLARE_FUNC(AcisFace)
public:
	const static TCHAR* szDir[2];
private:
	long m_lAttributeIndex;
	long m_lNextIndex;
	long m_lLoopIndex;
	long m_lShellIndex;
	long m_lSurfIndex;
	AcisSense m_eSense;
};