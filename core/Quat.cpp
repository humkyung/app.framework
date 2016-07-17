#include "StdAfx.h"
#include <math.h>
#include <assert.h>
#include "BaseTools.h"
#include "Vect3d.h"
#include "Quat.h"
#include "Matrix4d.h"

#include <exception>
using namespace std;
using namespace AppFramework;
//////////////////////////////////////////////////////////////////////////

CQuat::CQuat() : m_x(0) , m_y(0) , m_z(0) , m_w(0)
{
}

CQuat::CQuat(const double& x , const double& y , const double& z , const double& w)
: m_x(x) , m_y(y) , m_z(z) , m_w(w)
{

}

CQuat::CQuat(const CQuat& quat)
{
	m_x = quat.m_x;
	m_y = quat.m_y;
	m_z = quat.m_z;
	m_w = quat.m_w;
}

/**
	@brief	
	@author	HumKyung.BAEK
	@date	????.??.??
	@return
*/
CQuat::CQuat(CVect3d norm, const double &theta) : m_x(0) , m_y(0) , m_z(0) , m_w(0)
{
	try
	{
		norm.Normalize();
		
		const double rad = theta * 0.5;
		const double sv = sin(rad);
		m_x = norm.dx() * sv;
		m_y = norm.dy() * sv;
		m_z = norm.dz() * sv;
		m_w = cos(rad);
	}
	catch(...)
	{
	}
}

/**	\brief	The * function

	\param	quat1	a parameter of type CQuat
	\param	quat2	a parameter of type CQuat

	\return	CQuat operator	
*/
/*
CQuat operator *(CQuat quat1,CQuat quat2)
{
	CQuat ret;

	ret.w() = quat1.w()*quat2.w() - quat1.x()*quat2.x() + (quat1.y()*quat2.y() + quat1.z()*quat2.z());
	ret.x() = quat1.w()*quat2.x() + quat2.w()*quat1.x() + (quat1.y()*quat2.z() - quat1.z()*quat2.y());
	ret.y() = quat1.w()*quat2.y() + quat2.w()*quat1.y() + (-quat1.x()*quat2.z()+ quat1.z()*quat2.x());
	ret.z() = quat1.w()*quat2.z() + quat2.w()*quat1.z() + (quat1.x()*quat2.y() - quat1.y()*quat2.x());

	return ret;
}
*/

/**	\brief	The = function

	\param	vec	a parameter of type const CVect3d&

	\return	CQuat operator	
*/
CQuat GetQuaternion(CVect3d vec)
{
	CQuat ret;
	
	double magnitude= sqrt((double)vec.dx()*vec.dx() + (double)vec.dy()*vec.dy() + (double)vec.dz()*vec.dz());
	CVect3d vecAxis=vec;
	if(magnitude > 0.)
	{
		const double dfactor = 1.0 / magnitude;

		vecAxis *= dfactor;
	}else	return ret;
	
	double alpha=0.,beta=0.;
	vecAxis.GetRotatedAngleOfAxis(alpha,beta);
	CQuat quat1,quat2;
	
	quat1.Set(cos(-beta*0.5) , 
		  sin(-beta*0.5)*0.f , sin(-beta*0.5)*1.f , sin(-beta*0.5)*0.f);
	quat2.Set(cos(-alpha*0.5) , 
		sin(-alpha*0.5)*1.f , sin(-alpha*0.5)*0.f , sin(-alpha*0.5)*0.f);
	
	ret   = quat1*quat2;
	
	return ret;
}

/**
 * Copy:
 *
 * @param pQuat 
 * @return void 
 */
void CQuat::Copy(CQuat *pQuat)
{
	assert(pQuat && "pQuat is NULL");

	if(pQuat)
	{
		m_w = pQuat->m_w;
		m_x = pQuat->m_x;
		m_y = pQuat->m_y;
		m_z = pQuat->m_z;
	}
}

/**
 * Clone:
 *
 * @return CQuat* 
 */
CQuat* CQuat::Clone()
{
	CQuat* pQuat = new CQuat;
	if(pQuat) pQuat->Copy(this);
	return pQuat;
}

/**
 * Inverse:
 *
 * @return CQuat 
 */
CQuat CQuat::Inverse() const
{
	CQuat ret;
	
	ret.m_w = m_w;
	ret.m_x = -m_x;
	ret.m_y = -m_y;
	ret.m_z = -m_z;
	const double nMagnitude = Length();
	if(nMagnitude > 0.)
	{
		ret.m_w /= nMagnitude;
		ret.m_x /= nMagnitude;
		ret.m_y /= nMagnitude;
		ret.m_z /= nMagnitude;
	}else	throw exception("magnitude error!!!");
	
	return ret;
}

double CQuat::w() const
{
	return m_w;
}

double CQuat::x() const
{
	return m_x;
}

double CQuat::y() const
{
	return m_y;
}

double CQuat::z() const
{
	return m_z;
}

/**
 * operator*:
 *
 * @param quat 
 * @return CQuat 
 */
CQuat CQuat::operator *(CQuat quat) const
{
	CQuat ret;

	ret.Set(
		m_w*quat.w() - m_x*quat.x() + (m_y*quat.y() + m_z*quat.z()) ,
		m_w*quat.x() + quat.w()*m_x + (m_y*quat.z() - m_z*quat.y()) ,
		m_w*quat.y() + quat.w()*m_y + (-m_x*quat.z()+ m_z*quat.x()) ,
		m_w*quat.z() + quat.w()*m_z + (m_x*quat.y() - m_y*quat.x()));

	return ret;
}


double CQuat::Length() const
{
	return (m_w*m_w + m_x*m_x + m_y*m_y + m_z*m_z);
}

void CQuat::Set(const double &w , const double &x , const double &y , const double &z)
{
	m_w = w;
	m_x = x;
	m_y = y;
	m_z = z;
}

/**
	@brief	convert quaternion to matrix 4d
	@author	BHK
	@date	2009.11.25
	@param
	@return
*/
CMatrix4d CQuat::ToMatrix() const
{
	const double x2 = x() * x();
	const double y2 = y() * y();
	const double z2 = z() * z();
	const double xy = x() * y();
	const double xz = x() * z();
	const double yz = y() * z();
	const double wx = w() * x();
	const double wy = w() * y();
	const double wz = w() * z();
	
	double ret[][4] = 
	{
		{(1.0f - 2.0f * (y2 + z2)), (2.0f * (xy + wz)),        (2.0f * (xz - wy)),        0.0f},
		{(2.0f * (xy - wz)),        (1.0f - 2.0f * (x2 + z2)), (2.0f * (yz + wx)),        0.0f},
		{(2.0f * (xz + wy)),        (2.0f * (yz - wx)),        (1.0f - 2.0f * (x2 + y2)), 0.0f},
		{0.0f,                      0.0f,                      0.0f,                      1.0f}
	};

	CMatrix4d mat4d(ret);
	return mat4d;
}

/**
	@brief	Return the rotation in the form of an axis-of-rotation and a rotation angle.

	@author	

	@date	2010.09.05

	@return
*/
void CQuat::GetValue(CVect3d& a_axis, double & a_degree) const
{
	if((m_w >= -1.0) && (m_w <= 1.0))
	{
		a_degree = (std::acos(m_w)) * 2.0f;

		const double scale = (double)std::sin(DEG2RAD(a_degree) / 2.0f);
		if(scale != 0.0f)
		{
			a_axis.SetDX(m_x / scale);
			a_axis.SetDY(m_y / scale);
			a_axis.SetDZ(m_z / scale);

			return;
		}
	}

	// Quat can't be converted to axis and rotation angle, so we just
	// set up values to indicate this.
	a_axis.Set(0.0, 0.0, 1.0);
	a_degree = 0.0f;
}

/**
	@brief	Euler-to-quaternion conversion

	@author	HumKyung.BAEK

	@date	2010.09.05

	@return
*/
void CQuat::SetValue(double yaw, double pitch, double roll)
{
	// Gainer, 1972
	// calculate trig identities
	yaw     = DEG2RAD(yaw)*(double)0.5;
	pitch   = DEG2RAD(pitch)*(double)0.5;
	roll    = DEG2RAD(roll)*(double)0.5;

	double c1 = std::cos(roll);
	double c2 = std::cos(yaw);
	double c3 = std::cos(pitch);

	double s1 = std::sin(roll);
	double s2 = std::sin(yaw);
	double s3 = std::sin(pitch);

	double c2c1 = c2 * c1;
	double s2s1 = s2 * s1;

	m_x = s3 * c2c1 - c3 * s2s1;
	m_y = c3 * s2 * c1 + s3 * c2 * s1;
	m_z = c3 * c2 * s1 - s3 * s2 * c1;
	m_w = c3 * c2c1 + s3 * s2s1;
}

/**
	@brief	

	@author	HumKyung.BAEK

	@date	2010.09.05

	@return
*/
void CQuat::GetValue(double & yaw, double & pitch, double & roll) const
{
	double q12 = m_x*m_x;
	double q22 = m_y*m_y;
	double q32 = m_z*m_z;
	double q42 = m_w*m_w;

	yaw   = RAD2DEG(std::asin(-2.0*(m_x*m_z-m_w*m_y)));
	pitch = RAD2DEG(std::atan(2.0*(m_w*m_x+m_y*m_z)/ (q42 - q12 - q22+ q32)));
	roll  = RAD2DEG(std::atan(2.0*(m_x*m_y+m_w*m_z)/ (q42 + q12 - q22- q32)));
}