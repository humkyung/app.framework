#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Vect3d.h>
#include "AcisCurve.h"

using namespace AppFramework;

class ON_EXT_CLASS AcisEllipseCurv : public AcisCurve
{
	typedef enum
	{
		ellipse_type = 0x00,
		arc_type     = 0x01
	}type_e;
public:
	AcisEllipseCurv(const TCHAR*,const long& nIndex);
	virtual ~AcisEllipseCurv();
public:
	bool Parse(AcisDoc*,const TCHAR*);

	//PSQPRIMITIVE CreateCurve();
	//void SetOriginPos(const POINT_T& ptOrigin);
	CPoint3d origin() const;
	CPoint3d GetStartPos() const;
	//void SetStartPos(const POINT_T& ptStart);
	//void SetEndPos(const POINT_T& ptEnd);
	//void SetNormVector(const VECTOR_T& vecNorm);
	CVect3d norm() const;
	CVect3d delta() const;
	double radius() const;
	double ratio() const;
	
	ACISLIB_DECLARE_FUNC(AcisEllipseCurv)
private:
	type_e m_type;

	CPoint3d m_ptOrigin;
	CVect3d m_vecNorm;
	CVect3d m_vecDelta;
	CPoint3d m_ptStart;
	CPoint3d m_ptEnd;
	double m_dRadius , m_dRatio;
};
