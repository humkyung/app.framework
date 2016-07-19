#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Point3d.h>
#include "AcisEntity.h"

class ON_EXT_CLASS AcisCurve : public AcisEntity  
{
public:
	typedef struct tagKnot
	{
		double value;
		int    multiplicity;
	}Knot;

	typedef struct tagPole
	{
		AppFramework::CPoint3d pt;
		double weight;
	}Pole;

	typedef struct tagParam
	{
		double u,v;
	}Param;

	AcisCurve(const TCHAR*,const long& lIndex);
	virtual ~AcisCurve();

	ACISLIB_DECLARE_FUNC(AcisCurve)
public:
	//virtual PSQPRIMITIVE CreateCurve()=0;
};