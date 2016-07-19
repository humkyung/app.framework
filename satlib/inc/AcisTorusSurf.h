#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Vect3d.h>
#include "AcisSurf.h"

using namespace AppFramework;

class ON_EXT_CLASS AcisTorusSurf : public AcisSurf  
{
public:
	AcisTorusSurf(const TCHAR*,const long& nIndex);
	virtual ~AcisTorusSurf();
public:
	bool Parse(ifstream& file);
	bool Parse(AcisDoc*,const TCHAR*);

	CPoint3d origin() const;
	CVect3d norm() const;
	CVect3d Vx() const;
	const double GetTorusRadius() const;
	const double GetTubeRadius() const;

	ACISLIB_DECLARE_FUNC(AcisTorusSurf)
private:
	CPoint3d m_ptOrigin;
	CVect3d m_vecNorm;
	double m_dTorusRadius;
	double m_dTubeRadius;
	CVect3d m_vecStart;
	double m_bReversed;
};