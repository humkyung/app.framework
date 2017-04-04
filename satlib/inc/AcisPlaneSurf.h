#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Vect3d.h>
#include "AcisSurf.h"

using namespace AppFramework;

class ON_EXT_CLASS AcisPlaneSurf : public AcisSurf
{
public:
	AcisPlaneSurf(const TCHAR* pType,const long& nIndex);
	virtual ~AcisPlaneSurf();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	
	CPoint3d origin() const;
	CVect3d norm() const;
	//PSQPRIMITIVE CreateSurf();
	ACISLIB_DECLARE_FUNC(AcisPlaneSurf)
private:
	CPoint3d m_ptOrigin;
	CVect3d m_vecNorm;
};