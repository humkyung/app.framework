#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEnum.h"
#include "AcisEntity.h"

class ON_EXT_CLASS AcisEdge : public AcisEntity  
{
public:
	AcisEdge(const TCHAR*,const long& nIndex);
	virtual ~AcisEdge();
public:
	bool Parse(ifstream& file);
	bool Parse(AcisDoc*,const TCHAR*);
	
	long GetStartIndex() const;
	long GetEndIndex() const;
	const long GetCurveIndex() const;
	double* params();
	AcisSense sense() const;

	ACISLIB_DECLARE_FUNC(AcisEdge)
private:
	long m_lStartIndex;
	long m_lEndIndex;
	long m_nCoEdgeIndex;
	double m_params[2];
	long m_nCurveIndex;
	AcisSense m_eSense;
};