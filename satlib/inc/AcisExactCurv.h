#pragma once
#include <AcisCurve.h>

class ON_EXT_CLASS AcisExactCurv : public AcisCurve
{
public:
	AcisExactCurv(const TCHAR*,const long& nIndex);
	~AcisExactCurv(void);

	bool Parse(AcisDoc*,const TCHAR*);

	int poles() const;
	int degree() const;
	int knots() const;

	typedef vector<AcisCurve::Knot>::const_iterator knot_iterator;
	knot_iterator knot_begin() { return m_pKnots->begin();	}
	knot_iterator knot_end() { return m_pKnots->end();	}
	typedef vector<Pole>::const_iterator pole_iterator;
	pole_iterator begin() { return m_pPoles->begin(); }
	pole_iterator end() { return m_pPoles->end(); }

	ACISLIB_DECLARE_FUNC(AcisExactCurv)
private:
	int m_iDegree , m_iKnots;
	vector<AcisCurve::Knot>* m_pKnots;
	vector<AcisCurve::Pole>* m_pPoles;
};

