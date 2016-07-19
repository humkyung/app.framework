#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"

class ON_EXT_CLASS AcisCoEdge : public AcisEntity  
{
public:
	AcisCoEdge(const TCHAR*,const long& nIndex);
	virtual ~AcisCoEdge();
public:
	const long GetLoopIndex() const;
	bool Parse(AcisDoc*,const TCHAR*);
	const long GetNextIndex() const;
	long GetEdgeIndex() const;
	AcisSense sense() const;
	const long pcurve() const;

	ACISLIB_DECLARE_FUNC(AcisCoEdge)
private:
	long m_lForwardNextIndex , m_lReversedNextIndex;
	long m_nEdgeIndex;
	AcisSense m_eSense;
	long m_nLoopIndex;
	long m_lPCurveIndex;
};