#pragma once

#include "BaseEntity.h"
#include "Quat.h"

namespace AppFramework
{
class CPoint3d;
class ON_EXT_CLASS CVect3d : public CBaseEntity
{
public:
	CVect3d();
	CVect3d(const double& dx,const double& dy,const double& dz);
	CVect3d(const CVect3d& vec);
	CVect3d& operator=(const CVect3d& vec);
	CVect3d(CPoint3d pt);
public:
	const double AngleTo(const CVect3d& rhs) const;	/// return angle in radian between two vectors - 2013.06.20 added by humkyung
	bool IsParallelTo( const CVect3d& rhs );
	bool IsPerpendicularTo( const CVect3d& rhs );
	CVect3d Rotate(const CQuat& quat);
	CVect3d RotateAboutZAxis(const double& theta);
	CVect3d RotateAboutYXAxis(const double& beta,const double& alpha);
	CVect3d RotateAboutXYAxis(const double& alpha,const double& beta) const;
	CVect3d RotateOnXYPlane(const double nDeg);
	void GetRotatedAngleOfAxis(double& alpha,double& beta) const;
	const double GetRotatedAngleInXYPlane();
	
	const double dz() const;
	const double dy() const;
	const double dx() const;
	double& dz();
	double& dy();
	double& dx();

	void Set(const double& dx,const double& dy,const double& dz);
	void SetDX( const double& dx ){ m_dx = dx; }
	void SetDY( const double& dy ){ m_dy = dy; }
	void SetDZ( const double& dz ){ m_dz = dz; }
	bool   IsValid() const;
	double Length() const;
	double LengthSquared() const;
	void   Flatten();
	CVect3d  Perpendicular();
	CVect3d& Normalize();
	CVect3d UnitVector() const;
	
	CVect3d CrossCrossed(const CVect3d &V1, const CVect3d &V2);
	void CrossCross(const CVect3d &V1, const CVect3d &V2);

	double operator [](const int &at) const;
	CVect3d operator+(const CVect3d& v) const { return CVect3d(m_dx + v.m_dx, m_dy + v.m_dy, m_dz + v.m_dz); }
	CVect3d operator-(const CVect3d& v) const { return CVect3d(m_dx - v.m_dx , m_dy - v.m_dy , m_dz - v.m_dz); }
	CVect3d operator-() const { return CVect3d(-m_dx , -m_dy , -m_dz); }
	CVect3d operator *(const CVect3d& vect) const;	/// cross product
	void operator +=(const CVect3d& vec);
	void operator -=(const CVect3d& vec);
	bool operator==( const CVect3d& rhs ) const;

	//void operator =(const CVect3d& vec);
	void operator =(CPoint3d pt);
	
	CVect3d operator *(const double& real) const;
	void operator *=(const double& d);
	void operator *=(const CVect3d& vec);
	const double DotProduct(const CVect3d& vec) const;

	friend CVect3d operator *(const double& real , const CVect3d& vec);
	static const double Dot(CVect3d& vect1,CVect3d& vect2);

	ON_DECLARE_FUNC(CVect3d)
public:
	void Zero();
	double m_dx;
	double m_dy;
	double m_dz;	/// dx,dy,dz
};

CVect3d operator -(CVect3d& vect1,CVect3d& vect2);
double ON_DotProduct( const CVect3d&, const CVect3d&  );
CVect3d ON_CrossProduct( const CVect3d&, const CVect3d& );
};
