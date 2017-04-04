#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Vect3d.h>
#include "AcisSurf.h"

using namespace AppFramework;

class ON_EXT_CLASS AcisConeSurf : public AcisSurf
{
public:
	typedef struct
	{
		double a,b;
	}ratio_;

	AcisConeSurf(const TCHAR*,const long& nIndex);
	virtual ~AcisConeSurf();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	
	CPoint3d origin() const;
	CVect3d axis() const;
	CVect3d Vx() const;
	const double delta() const;
	const ratio_ ratio() const;
	const double radius() const;
	ACISLIB_DECLARE_FUNC(AcisConeSurf)
private:
	CPoint3d m_ptOrigin;
	CVect3d m_vecAxis;  
	double m_dDelta; /// ???
	CVect3d m_vecStart;
	ratio_ m_varRatio;
	double m_dRadius;
};