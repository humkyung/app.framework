#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisSurf.h"

#include <list>
using namespace std;

class ON_EXT_CLASS AcisSplineSurf : public AcisSurf
{
public:
	typedef enum surf_type
	{
		undef , 
		rotsur ,
		exactsur
	};

	AcisSplineSurf(const TCHAR*,const long& nIndex);
	virtual ~AcisSplineSurf();
public:
	bool Parse(ifstream& file);
	bool Parse(AcisDoc*,const TCHAR*);

	//PSQPRIMITIVE CreateSurf();
	AcisSplineSurf::surf_type type() const
	{
		return m_type;
	}
	AcisSurf* GetSubSurf();

	ACISLIB_DECLARE_FUNC(AcisSplineSurf)
private:
	void ParseEllipse();
	void RegisterBoundaryCurve(AcisEntity* pEntity);
private:
	long m_lAttributeIndex;
	AcisSplineSurf::surf_type m_type;
	AcisSurf* m_pSubSurf;

	/*POINT_T m_ptOrigin;
	VECTOR_T m_vecNorm;
	list<CSATEntity*>* m_plstBoundayCurve;*/
};