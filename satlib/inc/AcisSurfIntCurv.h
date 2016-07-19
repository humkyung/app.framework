#pragma once
#include <Aciscurve.h>

class ON_EXT_CLASS AcisSurfIntCurv : public AcisCurve
{
public:
	AcisSurfIntCurv(const TCHAR*,const long& nIndex);
	~AcisSurfIntCurv(void);

	bool Parse(AcisDoc*,const TCHAR*);

	bool IsOpen() const;

	int poles() const;
	int degree() const;
	int knots() const;

	typedef vector<AcisCurve::Knot>::const_iterator knot_iterator;
	knot_iterator knot_begin() { return m_pKnots->begin();	}
	knot_iterator knot_end() { return m_pKnots->end();	}
	typedef vector<AcisCurve::Pole>::const_iterator pole_iterator;
	pole_iterator pole_begin() { return m_pPoles->begin(); }
	pole_iterator pole_end() { return m_pPoles->end(); }

	ACISLIB_DECLARE_FUNC(AcisSurfIntCurv)
private:
	int m_iDegree , m_iKnots;
	AcisBsplineType m_eType;
	vector<AcisCurve::Knot>* m_pKnots;
	vector<AcisCurve::Pole>* m_pPoles;
};

