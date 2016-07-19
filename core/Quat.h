/********************************************************************
	created:	2003/08/09
	created:	9:8:2003   13:03
	file base:	quat
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/

#pragma once

namespace AppFramework
{
class CMatrix4d;
class CVect3d;
// q = w + xi + yj + zk
class ON_EXT_CLASS CQuat
{
public:
	CQuat(const CQuat& quat);
	CQuat(CVect3d norm , const double& theta);
	CQuat(const double& x , const double& y , const double& z , const double& w);
	CQuat();
public:
	void GetValue(double & yaw, double & pitch, double & roll) const;
	void SetValue(double yaw, double pitch, double roll);
	void GetValue(CVect3d& a_axis, double & a_degree) const;
	CMatrix4d ToMatrix() const;
	void Set(const double &w , const double &x, const double &y, const double &z);
	double Length() const;
	
	CQuat operator *(CQuat quat) const;
	double z() const;
	double y() const;
	double x() const;
	double w() const;
	CQuat Inverse() const;
	virtual CQuat* Clone();
	void Copy(CQuat* pQuat);
private:
	double m_w;	// imaginary part
	double m_x;	// real part
	double m_y;	
	double m_z;
};

CQuat GetQuaternion(CVect3d vec);
};