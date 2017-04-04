#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"

class ON_EXT_CLASS AcisVertex : public AcisEntity  
{
public:
	AcisVertex(const TCHAR*,const long& nIndex);
	virtual ~AcisVertex();
public:
	bool Parse(IFSTREAM_T& file);
	bool Parse(AcisDoc*,const TCHAR*);
	long GetEdgeIndex() const;
	long GetPointIndex() const;
	ACISLIB_DECLARE_FUNC(AcisVertex)
private:
	long m_nEdgeIndex;
	long m_nPointIndex;
};