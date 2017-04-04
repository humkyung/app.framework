#include "StdAfx.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "BaseTools.h"
#include "Point3d.h"
#include "Vect3d.h"

#include <exception>
using namespace std;
using namespace AppFramework;

ON_IMPLEMENT_FUNC(CPoint3d , CBaseEntity , "POINT3D")

/**	
	@brief
*/
CPoint3d::CPoint3d() : m_x(0) , m_y(0) , m_z(0)
{
}

/**	\brief
*/
CPoint3d::CPoint3d(const double& _x,const double& _y,const double& _z)
{
	m_x = _x;m_y = _y;m_z = _z;
}

/**	\brief
*/
CPoint3d::CPoint3d(const CPoint3d& pt)
{
	m_x = pt.m_x;m_y = pt.m_y;m_z = pt.m_z;
}

/**	\brief
*/
CPoint3d::CPoint3d(CVect3d vect)
{
	m_x = vect.dx();
	m_y = vect.dy();
	m_z = vect.dz();
}

/**	\brief
*/
CPoint3d::~CPoint3d()
{
}

/**	\brief	The CPoint3d::x function


	\return	double&
*/
const double CPoint3d::x() const
{
	return m_x;
}

/**	\brief	The CPoint3d::y function


	\return	double&
*/
const double CPoint3d::y() const
{
	return m_y;
}

/**	\brief	The CPoint3d::z function


	\return	double&
*/
const double CPoint3d::z() const
{
	return m_z;
}

/**	\brief	The CPoint3d::x function


	\return	double&
*/
double& CPoint3d::x()
{
	return m_x;
}

/**	\brief	The CPoint3d::y function


	\return	double&
*/
double& CPoint3d::y()
{
	return m_y;
}

/**	\brief	The CPoint3d::z function


	\return	double&
*/
double& CPoint3d::z()
{
	return m_z;
}

/**
	@brief	
	@author	BHK
	@date	2009.11.09
	@param
	@return
*/
double CPoint3d::operator[](const int& i) const
{
	return ( (i<=0)?m_x:((i>=2)?m_z:m_y) );
}

/**
	@brief	
	@author	BHK
	@date	2009.11.09
	@param
	@return
*/
double& CPoint3d::operator[](const int& i)
{
	double* pd = (i<=0)? &m_x : ( (i>=2) ?  &m_z : &m_y);
	return (*pd);
}

/**	\brief	The CPoint3d::DistanceTo function
	\param	pt	a parameter of type const POINT_T&
	\return	const double	
*/
const double CPoint3d::DistanceTo(const CPoint3d& pt) const
{
	double dx = m_x - pt.m_x;
	double dy = m_y - pt.m_y;
	double dz = m_z - pt.m_z;
	
	return sqrt(dx*dx + dy*dy + dz*dz);
}

/**	
	@brief	대입 연산자

	@param	pt	a parameter of type const CPoint3d&

	@return	bool CPoint3d::operator	
*/
CPoint3d& CPoint3d::operator =(const CPoint3d& rhs)
{
	if(this != &rhs)
	{
		CBaseEntity::operator =( rhs );
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_z = rhs.m_z;
	}

	return (*this);
}

/**
 * operator=:
 *
 * @param vt 
 * @return bool 
 */
bool CPoint3d::operator =( const CVect3d& vt)
{
	m_x = vt.dx();
	m_y = vt.dy();
	m_z = vt.dz();

	return true;
}

/**
 * operator==:
 *
 * @param pt 
 * @return bool 
 */
bool CPoint3d::operator ==(const CPoint3d& pt) const
{
	const double dx = m_x - pt.m_x;
	const double dy = m_y - pt.m_y;
	const double dz = m_z - pt.m_z;
	return ((dx * dx + dy * dy + dz * dz) < (IS_TOLER * IS_TOLER));
}

/**
 * operator!=:
 *
 * @param pt 
 * @return bool 
 */
bool CPoint3d::operator !=(const CPoint3d& pt)
{
	return ((*this) == pt) ? false : true;
}

/**
 * operator+=:
 *
 * @param pt 
 * @return bool 
 */
bool CPoint3d::operator +=(const CPoint3d &pt)
{
	m_x += pt.m_x;
	m_y += pt.m_y;
	m_z += pt.m_z;

	return true;
}

/**
	@brief	
	@author	BHK
	@date	2009.11.05
	@param	
	@return
*/
CPoint3d CPoint3d::operator +(const CPoint3d &pt)
{
	CPoint3d tmp(m_x+pt.x() , m_y+pt.y() , m_z+pt.z());
	return tmp;
}

/**
 * operator-:
 *
 * @param pt 
 * @return CPoint3d 
 */
CVect3d CPoint3d::operator -(const CPoint3d &pt) const
{
	CPoint3d ret(m_x - pt.m_x , m_y - pt.m_y , m_z - pt.m_z);

	return ret;
}

/**
 * operator-=:
 *
 * @param pt 
 * @return bool 
 */
bool CPoint3d::operator -=(const CPoint3d &rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	m_z -= rhs.m_z;

	return true;
}

const double CPoint3d::GetRotatedAngleInXYPlane()
{
	const double l = sqrt(m_x*m_x + m_y*m_y);
	double theta=0.f;
	
	if(l > 0)
	{
		theta = acos(m_x / l);
		
		if((m_x > 0.) && (0. == m_y))
		{
			theta = 0.;
		}
		else if((m_x >= 0.) && (m_y <= 0.))
		{
			theta = 2*PI - theta;
		}
		else if((m_x <= 0.) && (m_y <= 0.))
		{
			theta = 2*PI - theta;
		}
	}
	
	return theta;
}

/**
 * RotateAboutXYAxis:
 * first, rotate about x axis by alpha angle,\n
 * then rotate about y axis by beta angle.\n
 * rotating matrix=\n
 *	| 1      0           0    | | cos(beta) 0 -sin(beta)|\n
 *	|x y z|*| 0 cos(alpha)  sin(alpha)|*|     0     1     0     |\n
 *	| 0 -sin(alpha) cos(alpha)| | sin(beta) 0 cos(beta) |
 * @param alpha 
 * @param beta 
 * @return CPoint3d 
 */
CPoint3d CPoint3d::RotateAboutXYAxis(const double &alpha, const double &beta)
{
	CPoint3d ptRet;

	double cos_alpha=cos(alpha);
	double cos_beta=cos(beta);
	double sin_alpha=sin(alpha);
	double sin_beta=sin(beta);
	if((fabs(cos_alpha) < 0.0000000001)) cos_alpha = 0.;
	if((fabs(cos_beta) < 0.0000000001)) cos_beta = 0.;
	if((fabs(sin_alpha) < 0.0000000001)) sin_alpha = 0.;
	if((fabs(sin_beta) < 0.0000000001)) sin_beta = 0.;
	
	ptRet.Set(
		m_x*cos_beta + m_y*sin_alpha*sin_beta + m_z*cos_alpha*sin_beta ,
		m_y*cos_alpha- m_z*sin_alpha ,
		-m_x*sin_beta + m_y*sin_alpha*cos_beta + m_z*cos_alpha*cos_beta
		);
	
	return ptRet;
}

/**
 * Rotate:
 *
 * @param quat 
 * @return CPoint3d 
 */
CPoint3d CPoint3d::Rotate(const CQuat quat)
{
	CPoint3d ret;

	CQuat tmp;
	tmp.Set(0 , m_x , m_y , m_z);

	CQuat inverse = quat.Inverse();
	tmp = (quat*tmp)*inverse;

	ret.Set( tmp.x() , tmp.y() , tmp.z() );

	return ret;
}

/**
 * RotateAboutYXAxis:
 * first rotate about y axis by beta angle,\n
 * rotate about x axis by alpha angle.\n
 *	| cos(beta) 0 -sin(beta)| | 1      0          0     |\n
 *	|      x    y     z     |*| 0      1          0     |*| 0 cos(alpha)  sin(alpha)|\n
 *	| sin(beta) 0 cos(beta) | | 0 -sin(alpha) cos(alpah)|  
 * @param beta 
 * @param alpha 
 * @return CPoint3d 
 */
CPoint3d CPoint3d::RotateAboutYXAxis(const double &beta, const double &alpha)
{
	CPoint3d ptRet;
	
	ptRet.Set(
		m_x*cos(beta) + m_z*sin(beta) , 
		m_x*sin(alpha)*sin(beta) + m_y*cos(alpha) - m_z*sin(alpha)*cos(beta) ,
		-m_x*cos(alpha)*sin(beta)+ m_y*sin(alpha) + m_z*cos(alpha)*cos(beta)
		);
	
	return ptRet;
}

/**
 * RotateAboutZAxis:
 * rotating matrix=\n
 *	| cos(theta) -sin(theta)  0 | |x|\n
 *	| sin(theta)  cos(theta)  0 |*|y|\n
 *	|      0          0       1 | |z|
 *
 * @param theta 
 * @return CPoint3d 
 */
CPoint3d CPoint3d::RotateAboutZAxis(const double &theta)
{
	CPoint3d ptRet;
	
	const double s=sin(theta);
	const double c=cos(theta);
	ptRet.Set( m_x*c - m_y*s , m_x*s + m_y*c , m_z );
	
	return ptRet;
}

CPoint3d operator +(const CPoint3d& pt1 , const CPoint3d& pt2)
{
	CPoint3d ret(	pt1.m_x + pt2.m_x , 
			pt1.m_y + pt2.m_y , 
			pt1.m_z + pt2.m_z);

	return ret;
}

/**
	@brief	

	@author	BHK

	@date	2009.11.05

	@param	

	@return
*/
CPoint3d operator *(const double& m , const CPoint3d& pt)
{
	return (pt*m);
}

void CPoint3d::Set(const double &x, const double &y, const double &z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

/**
	@brief	

	@author	BHK

	@date	2009.11.05

	@param	

	@return
*/
CPoint3d CPoint3d::operator *(const double& m) const
{
	CPoint3d tmp(m_x*m , m_y*m , m_z*m);

	return tmp;
}

/**
	@brief	

	@author	BHK

	@date	2009.11.05

	@param	

	@return
*/
CPoint3d CPoint3d::operator /(const double& m)
{
	if(0.f != m)
	{
		CPoint3d tmp(m_x/m , m_y/m , m_z/m);

		return tmp;
	}

	throw exception("CPoint3d : divide by zero");
}

/**
	@brief	

	@author	BHK

	@date	2009.11.05

	@param	

	@return
*/
CPoint3d& CPoint3d::operator /=(const double& m)
{
	if(0.f != m)
	{
		m_x /= m;
		m_y /= m;
		m_z /= m;
	}

	return (*this);
}

/**
	@brief	

	@author	HumKyung.BAEK

	@date	2010.09.05

	@param	

	@return
*/
double CPoint3d::Length() const
{
	return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}