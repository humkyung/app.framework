#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisSurf.h"

#include <list>
using namespace std;
using namespace AppFramework;

class ON_EXT_CLASS AcisExactSurf : public AcisSurf
{
public:
	typedef struct tagKnot
	{
		double value;
		int    multiplicity;
	}Knot;

	typedef struct tagPole
	{
		CPoint3d pt;
		double weight;
	}Pole;

	AcisExactSurf(const TCHAR*,const long& nIndex);
	virtual ~AcisExactSurf();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	int u_degree() const;
	int v_degree() const;
	int u_knots() const;
	int v_knots() const;

	typedef vector<Knot>::const_iterator knot_iterator;
	knot_iterator uknot_begin() { return m_pUKnots->begin();	}
	knot_iterator uknot_end() { return m_pUKnots->end();	}
	knot_iterator vknot_begin() { return m_pVKnots->begin();	}
	knot_iterator vknot_end() { return m_pVKnots->end();	}
	typedef vector<Pole>::const_iterator iterator;
	iterator begin() { return m_pPoles->begin(); }
	iterator end() { return m_pPoles->end(); }

	ACISLIB_DECLARE_FUNC(AcisExactSurf)
private:
	int GetCurvDefIndex(const vector<STRING_T>&) const;

	int m_iUDegree , m_iVDegree;
	int m_iUKnots , m_iVKnots;

	vector<Knot>* m_pUKnots;
	vector<Knot>* m_pVKnots;
	vector<Pole>* m_pPoles;
};