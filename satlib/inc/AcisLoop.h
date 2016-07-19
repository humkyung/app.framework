#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"

class ON_EXT_CLASS AcisLoop : public AcisEntity  
{
public:
	AcisLoop(const TCHAR*,const long& nIndex);
	virtual ~AcisLoop();
public:
	bool Parse(ifstream& file);
	bool Parse(AcisDoc*,const TCHAR*);
	
	const long GetNextIndex() const;
	long GetCoEdgeIndex() const;
	
	ACISLIB_DECLARE_FUNC(AcisLoop)
private:
	long m_nNextIndex;
	long m_nCoEdgeIndex;
};