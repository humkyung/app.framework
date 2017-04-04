#pragma once
#include <Aciscurve.h>

class ON_EXT_CLASS AcisExppcCurv : public AcisCurve
{
public:
	AcisExppcCurv(const TCHAR*,const long& nIndex);
	~AcisExppcCurv(void);

	int degree() const;
	int knots() const;
	int params() const;

	bool Parse(AcisDoc*,const TCHAR*);
	AcisEntity* subtype();

	typedef vector<AcisCurve::Knot>::const_iterator knot_iterator;
	knot_iterator knot_begin() { return m_pKnots->begin();	}
	knot_iterator knot_end() { return m_pKnots->end();	}
	typedef vector<AcisCurve::Param>::const_iterator param_iterator;
	param_iterator begin() { return m_pParams->begin(); }
	param_iterator end() { return m_pParams->end(); }

	ACISLIB_DECLARE_FUNC(AcisExppcCurv)
private:
	int m_iDegree , m_iKnots;
	vector<AcisCurve::Knot>* m_pKnots;
	vector<AcisCurve::Param>* m_pParams;
	AcisEntity* m_pSubType;
};

