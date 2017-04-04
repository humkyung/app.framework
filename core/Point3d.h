#pragma once

#include "BaseEntity.h"
#include "Quat.h"

namespace AppFramework
{
class CVect3d;
class ON_EXT_CLASS CPoint3d : public CBaseEntity
{
public:
	CPoint3d();
	CPoint3d(const CPoint3d& pt);
	CPoint3d(const double& _x,const double& _y,const double& _z);
	CPoint3d(CVect3d vect);
	CPoint3d& operator =(const CPoint3d& rhs);
	bool operator =( const CVect3d& rhs);
	virtual ~CPoint3d();
public:
	CPoint3d RotateAboutZAxis(const double& theta);
	CPoint3d RotateAboutYXAxis(const double& beta,const double& alpha);
	CPoint3d Rotate(const CQuat quat);
	CPoint3d RotateAboutXYAxis(const double& alpha,const double& beta);
	const double GetRotatedAngleInXYPlane();
	static const long TypeId();

	const double x() const;
	const double y() const;
	const double z() const;
	double& x();
	double& y();
	double& z();
	// index operators mimic double[3] behavior
	double& operator[](const int&);
	double operator[](const int&) const;

	const double DistanceTo(const CPoint3d& pt) const;

	CPoint3d operator *(const double& m) const;
	CPoint3d operator /(const double& m);
	CPoint3d& operator /=(const double& m);
	bool operator !=(const CPoint3d& pt);
	bool operator ==(const CPoint3d& pt) const;
	CPoint3d operator +(const CPoint3d &pt);
	bool operator +=(const CPoint3d &pt);
	CVect3d operator -(const CPoint3d &pt) const;
	bool operator -=(const CPoint3d &pt);
	
	ON_DECLARE_FUNC(CPoint3d)
public:
	double Length() const;
	void Set(const double& x , const double& y , const double& z);
	void SetX( const double& x){ m_x = x; }
	void SetY( const double& y){ m_y = y; }
	void SetZ( const double& z){ m_z = z; }
	double m_x,m_y,m_z;
};

CPoint3d operator +(const CPoint3d& pt1 , const CPoint3d& pt2);
CPoint3d operator *(const double& m , const CPoint3d& pt);
};