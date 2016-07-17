#include "StdAfx.h"
#include <math.h>
#include <assert.h>
#include "BaseTools.h"
#include "Vect3d.h"
#include "Point3d.h"

using namespace AppFramework;

ON_IMPLEMENT_FUNC(CVect3d , CBaseEntity , "CVect3d")
//////////////////////////////////////////////////////////////////////////

CVect3d::CVect3d()
{
	m_dx=0;
	m_dy=0;
	m_dz=1.;
}

CVect3d::CVect3d(const double& dx,const double& dy,const double& dz)
{
	m_dx=dx;
	m_dy=dy;
	m_dz=dz;
}

CVect3d::CVect3d(const CVect3d& vec)
{
	(*this) = vec;
}

CVect3d& CVect3d::operator=(const CVect3d& vec)
{
	if(this != &vec)
	{
		m_dx=vec.m_dx;
		m_dy=vec.m_dy;
		m_dz=vec.m_dz;
	}

	return (*this);
}

/**
 * CVect3d:
 *
 * @param pt 
 * @return  
 */
CVect3d::CVect3d(CPoint3d pt)
{
	m_dx = pt.x();
	m_dy = pt.y();
	m_dz = pt.z();
}

/**	
	@brief	The CVect3d::IsValid function

	@author	humkyung

	@return	bool	
*/
bool CVect3d::IsValid() const
{
	return ((m_dx*m_dx + m_dy*m_dy + m_dz*m_dz) > 0.);
}

/**	
	@brief	The CVect3d::Length function

	@author	humkyung

	@return	double	
*/
double CVect3d::Length() const
{
    	return sqrt(m_dx*m_dx + m_dy*m_dy + m_dz*m_dz);
}

/**
	@brief	
	@author	BHK
	@date	2009.11.09
	@param
	@return
*/
double CVect3d::LengthSquared() const
{
  return (m_dx*m_dx + m_dy*m_dy + m_dz*m_dz);
}

/**	
	@brief	The CVect3d::Flatten function

	@author	humkyung

	@return	void	
*/
void CVect3d::Flatten()
{
    	m_dz = 0.;
}

/**	
	@brief	The CVect3d::Perpendicular function

	@author	humkyung

	@return	CVect3d	
*/
CVect3d CVect3d::Perpendicular()
{
    	CVect3d ret;
	
	CVect3d flat(m_dx,m_dy,0),z(0,0,1);
	ret = z * flat;

	return ret;
}

/**	
	@brief	The CVect3d::Normalize function

	@author	humkyung

	@return	CVect3d&	
*/
CVect3d& CVect3d::Normalize()
{
	if(IsValid())
	{
		double nFactor = 1./ Length();
		m_dx *= nFactor;
		m_dy *= nFactor;
		m_dz *= nFactor;
	}

	return (*this);
}

/**
	@brief	The CVect3d::DotProduct function

	@author	BHK

	@date	?

	@param	vec	a parameter of type const CVect3d&

	@return	const double	
*/
const double CVect3d::DotProduct(const CVect3d& vec) const
{
	return (m_dx*vec.m_dx + m_dy*vec.m_dy + m_dz*vec.m_dz);
}

///**	\brief	The = function
//
//	\param	vec	a parameter of type const CVect3d&
//
//	\return	void CVect3d::operator	
//*/
//void CVect3d::operator =(const CVect3d& vec)
//{
//	m_dx = vec.m_dx;
//	m_dy = vec.m_dy;
//	m_dz = vec.m_dz;
//}

/**
 * operator=:
 *
 * @param pt 
 * @return void 
 */
void CVect3d::operator =(CPoint3d pt)
{
	m_dx = pt.x();
	m_dy = pt.y();
	m_dz = pt.z();
}

/**	\brief	The += function

	\param	vec	a parameter of type const CVect3d&

	\return	void CVect3d::operator	
*/
void CVect3d::operator +=(const CVect3d& vec)
{
    	m_dx += vec.m_dx;
	m_dy += vec.m_dy;
	m_dz += vec.m_dz;
}

/**	\brief	The -= function

	\param	vec	a parameter of type const CVect3d&

	\return	void CVect3d::operator	
*/
void CVect3d::operator -=(const CVect3d& vec)
{
    	m_dx -= vec.m_dx;
	m_dy -= vec.m_dy;
	m_dz -= vec.m_dz;
}

/**
 * operator*=:
 *
 * @param d 
 * @return void 
 */
void CVect3d::operator *=(const double& d)
{
	m_dx *= d;
	m_dy *= d;
	m_dz *= d;
}

/**	\brief	The *= function

	\param	vec	a parameter of type const CVect3d&

	\return	void CVect3d::operator	
*/
void CVect3d::operator *=(const CVect3d& vec)
{
    	CVect3d tmp=*this;
	
	m_dx = tmp.m_dy*vec.m_dz - vec.m_dy*tmp.m_dz;
	m_dy = vec.m_dx*tmp.m_dz - tmp.m_dx*vec.m_dz;
	m_dz = tmp.m_dx*vec.m_dy - vec.m_dx*tmp.m_dy;
}

/**	
	@brief	The - function
	
	@author	BHK

	@date	?

	@param	vec1	a parameter of type CVect3d&
	@param	vec2	a parameter of type CVect3d&

	@return	CVect3d CVect3d::operator	
*/
CVect3d operator -(CVect3d& vec1,CVect3d& vec2)
{
    	CVect3d ret(vec1.m_dx - vec2.m_dx,
		vec1.m_dy - vec2.m_dy,
		vec1.m_dz - vec2.m_dz);

	return ret;
}

/**	
	@brief	ON_DotProduct
	
	@author	BHK

	@date	2009.11.09

	@param	lhs	a parameter of type CVect3d&
	@param	rhs	a parameter of type CVect3d&

	@return	double
*/
double ON_DotProduct( const CVect3d& lhs, const CVect3d& rhs)
{
	return lhs.DotProduct(rhs);
}

/**	
	@brief	ON_CrossProduct
	
	@author	BHK

	@date	2009.11.09

	@param	lhs	a parameter of type CVect3d&
	@param	rhs	a parameter of type CVect3d&

	@return	double
*/
CVect3d ON_CrossProduct( const CVect3d& lhs, const CVect3d& rhs)
{
	return (lhs*rhs);
}

/**	\brief	The * function

	\param	real	a parameter of type const double&

	\return	CVect3d CVect3d::operator

	
*/
CVect3d CVect3d::operator *(const double& real) const
{
	CVect3d ret(m_dx * real , m_dy * real , m_dz * real);
	return ret;
}

/**
 * operator*:
 *
 * @param vec 
 * @return CVect3d 
 */
CVect3d CVect3d::operator *(const CVect3d& vec) const
{
	CVect3d ret;
	
    	ret.m_dx = m_dy*vec.m_dz - vec.m_dy*m_dz;
	ret.m_dy = vec.m_dx*m_dz - m_dx*vec.m_dz;
	ret.m_dz = m_dx*vec.m_dy - vec.m_dx*m_dy;

	return ret;
} 

/**
 * Copy:
 *
 * @param pVect 
 * @return void 
 */
//void CVect3d::Copy(CVect3d *pVect)
//{
//	assert(pVect && "pVect is NULL");
//
//	if(pVect)
//	{
//		m_dx = pVect->m_dx;
//		m_dy = pVect->m_dy;
//		m_dz = pVect->m_dz;
//	}
//}

/**
 * Clone:
 *
 * @return CVect3d* 
 */
//CVect3d* CVect3d::Clone()
//{
//	CVect3d* pVect = new CVect3d;
//	if(pVect) pVect->Copy(this);
//	return pVect;
//}

/**
 * Set:
 *
 * @param dx 
 * @param dy 
 * @param dz 
 * @return void 
 */
void CVect3d::Set(const double &dx, const double &dy, const double &dz)
{
	m_dx = dx;
	m_dy = dy;
	m_dz = dz;
}

/**
 * dx:
 *
 * @return double& 
 */
const double CVect3d::dx() const
{
	return m_dx;
}

/**
 * dy:
 *
 * @return double& 
 */
const double CVect3d::dy() const
{
	return m_dy;
}

/**
 * dz:
 *
 * @return double& 
 */
const double CVect3d::dz() const
{
	return m_dz;
}

/**
 * dx:
 *
 * @return double& 
 */
double& CVect3d::dx()
{
	return m_dx;
}

/**
 * dy:
 *
 * @return double& 
 */
double& CVect3d::dy()
{
	return m_dy;
}

/**
 * dz:
 *
 * @return double& 
 */
double& CVect3d::dz()
{
	return m_dz;
}
/**
 * GetRotatedAngleInXYPlane:
 *
 * @return const double 
 */
const double CVect3d::GetRotatedAngleInXYPlane()
{
	const double l = sqrt(m_dx*m_dx + m_dy*m_dy);
	double theta=0.f;
	
	if(l > 0)
	{
		theta=acos(m_dx / l);
		
		if((m_dx >= 0.) && (m_dy <= 0.))
		{
			theta = 2*PI - theta;
		}
		else if((m_dx <= 0.) && (m_dy <= 0.))
		{
			theta = 2*PI - theta;
		}
	}
	
	return theta;
}

/**
 * GetRotatedAngleOfAxis:
 * get rotated angle of x-axis,y-axis about z-axis(<0,0,1>).
 *
 * @param alpha 
 * @param beta 
 * @return void 
 */
void CVect3d::GetRotatedAngleOfAxis(double &alpha, double &beta) const
{
	#define G_TOLERANCE 0.000001
	CVect3d axis = (*this);
       	
	axis.Normalize();
	if(fabs(axis.dx()) < G_TOLERANCE) axis.Set( 0.f , axis.dy() , axis.dz ());
	if(fabs(axis.dy()) < G_TOLERANCE) axis.Set( axis.dx() , 0.f , axis.dz() );
	if(fabs(axis.dz()) < G_TOLERANCE) axis.Set( axis.dx() , axis.dy() , 0.f );
	
	double d=sqrt(axis.dy()*axis.dy() + axis.dz()*axis.dz());
	if((axis.dy() != 0.) || (axis.dz() != 0.))
	{
		if((1. == axis.dy()) && (0. == axis.dz()))
		{
			alpha = PI*0.5;
			beta  = 0.;
		}
		else if((-1 == axis.dy()) && (0. == axis.dz()))
		{
			alpha = PI + PI*0.5;
			beta  = 0.;
		}
		else if((axis.dx() >= 0.) && (axis.dy() >= 0.) && (axis.dz() < 0.))
		{
			if((0. == axis.dx()) && (0. == axis.dy()) && (axis.dz() < 0.))
			{
				alpha = PI;
				beta = 0.;
			}
			else
			{
				alpha = acos(-axis.dz() / d);
				alpha = PI - alpha;
				if(fabs(d - 1.) >= G_TOLERANCE)
					beta = -acos(d);
				else	beta = 0.;
			}
		}
		else if((axis.dx() >= 0.) && (axis.dy() < 0.) && (axis.dz() >= 0.))
		{
			alpha = 2*PI -acos(axis.dz()/d);
			beta  = (fabs(d - 1.0) < 0.00001) ? 0 : -acos(d);
		}
		else if((axis.dx() >= 0.) && (axis.dy() < 0.) && (axis.dz() < 0.))
		{
			alpha = acos(-axis.dz()/d);
			alpha+= PI;
			beta  = (0. == axis.dx()) ? 0. : -acos(d);
		}
		else if((axis.dx() < 0.) && (axis.dy() >= 0.) && (axis.dz() >= 0.))
		{
			alpha = acos(axis.dz() / d);
			beta  = acos(d);
		}
		else if((axis.dx() < 0.) && (axis.dy() >= 0.) && (axis.dz() < 0.))
		{
			alpha = acos(-axis.dz() / d);
			alpha = PI - alpha;
			beta  = acos(d);
		}
		else if((axis.dx() < 0.) && (axis.dy() < 0.) && (axis.dz() >= 0.))
		{
			alpha = acos(axis.dz()/d);
			alpha = 2*PI - alpha;
			beta  = acos(d);
		}
		else if((axis.dx() < 0.) && (axis.dy() < 0.) && (axis.dz() < 0.))
		{
			alpha = acos(-axis.dz() / d);
			alpha+= PI;
			beta  = acos(d);
		}
		else if((axis.dx() < 0.) && (axis.dy() >= 0.) && (axis.dz() < 0.))
		{
			alpha = acos(-axis.dz()/d);
			alpha = PI - alpha;
			beta  = acos(d);
		}
		else if(0. == axis.dx() )
		{
			alpha = acos(axis.dz()/d);
			beta  = 0.;
		}
		else
		{
			alpha = acos(axis.dz()/d);
			beta  = -acos(d);
		}
	}
	else if(axis.dx() > 0.)
	{
		alpha = 0.;
		beta = PI + PI*0.5;
	}
	else if(axis.dx() < 0.)
	{
		alpha = 0.;
		beta = PI*0.5;
	}
}

/**
 * RotateOnXYPlane:
 *
 * @param nDeg 
 * @return CVect3d 
 */
CVect3d CVect3d::RotateOnXYPlane(const double nDeg)
{
	CVect3d vecRet;
	
	const double nRad=DEG2RAD(nDeg);
	vecRet.Set( m_dx*cos(nRad) - m_dy*sin(nRad) , m_dx*sin(nRad) + m_dy*cos(nRad) , m_dz );
	
	return vecRet;
}

/**
 * RotateAboutXYAxis:
 * first, rotate about x axis by alpha angle,\n
 * then rotate about y axis by beta angle.\n
 * rotating matrix=\n
 *	| 1      0         0      | | cos(beta) 0 -sin(beta)|\n
 *	|x y z|*| 0  cos(alpha) sin(alpha)|*|     0     1     0     |\n
 *	| 0 -sin(alpha) cos(alpha)| | sin(beta) 0 cos(beta) |
 * @param alpha 
 * @param beta 
 * @return CVect3d 
 */
CVect3d CVect3d::RotateAboutXYAxis(const double &alpha, const double &beta) const 
{
	CVect3d vecRet;
	
	vecRet.Set(
		m_dx*cos(beta) + m_dy*sin(beta)*sin(alpha) + m_dz*sin(beta)*cos(alpha) , 
		m_dy*cos(alpha)- m_dz*sin(alpha) , 
		-m_dx*sin(beta)+ m_dy*sin(alpha)*cos(beta) + m_dz*cos(alpha)*cos(beta)
		);
	
	return vecRet;
}

/**
 * RotateAboutYXAxis:
 * first rotate about y axis by beta angle,\n
 * rotate about x axis by alpha angle.\n
 *	| cos(beta)  0 sin(beta)| | 1     0           0     |\n
 *	|x y z|*|    0       1     0    |*| 0 cos(alpha)  sin(alpha)|\n
 *	| -sin(beta) 0 cos(beta)| | 0 -sin(alpha) cos(alpah)|
 * @param beta 
 * @param alpha 
 * @return CVect3d 
 */
CVect3d CVect3d::RotateAboutYXAxis(const double &beta, const double &alpha)
{
	CVect3d vecRet;
	
	vecRet.Set( 
		m_dx*cos(beta) + m_dz*sin(beta) ,
		m_dx*sin(alpha)*sin(beta) + m_dy*cos(alpha) - m_dz*sin(alpha)*cos(beta) ,
		-m_dx*cos(alpha)*sin(beta)+ m_dy*sin(alpha) + m_dz*cos(alpha)*cos(beta)
		);
	
	return vecRet;
}

/**
 * RotateAboutZAxis:
 * rotate about z axis by theta.\n
 * rotating matrix=\n
 *	| cos(theta) -sin(theta)  0 | |x|\n
 *	| sin(theta)  cos(theta)  0 |*|y|\n
 *	|      0          0       1 | |z|
 * @param theta 
 * @return CVect3d 
 */
CVect3d CVect3d::RotateAboutZAxis(const double &theta)
{
	CVect3d vecRet;
	
	const double s=sin(theta);
	const double c=cos(theta);
	vecRet.Set( m_dx*c - m_dy*s , m_dx*s + m_dy*c , m_dz );
	
	return vecRet;
}

/**
 * Rotate:
 *
 * @param quat 
 * @return CVect3d 
 */
CVect3d CVect3d::Rotate(const CQuat &quat)
{
	CVect3d ret;
	
	CQuat tmp;
	tmp.Set(0 , m_dx , m_dy , m_dz);
	
	CQuat inverse=quat.Inverse();
	tmp = (quat*tmp)*inverse;
	
	ret.Set( tmp.x() , tmp.y() , tmp.z() );
	
	return ret;
}

/**	\brief	The + function

	\param	vec1	a parameter of type CVect3d&
	\param	vec2	a parameter of type CVect3d&

	\return	CVect3d CVect3d::operator	
*/
/*
CVect3d operator +(CVect3d& vec1,CVect3d& vec2)
{
    	CVect3d ret(vec1.dx() + vec2.dx() , vec1.dy() + vec2.dy() , vec1.dz() + vec2.dz());
	
	return ret;
}
*/

/**
	@brief	

	@author	BHK

	@date	?

	@param	

	@return	
*/
double CVect3d::operator [](const int &at) const
{
	return ( (at<=0)?m_dx:((at>=2)?m_dz:m_dy) );
}

/**
	@brief	

	@author	BHK
*/
bool CVect3d::IsParallelTo( const CVect3d& rhs )
{
	const double value = DotProduct( rhs );
	return (value < epsilon<double>());
}

/**
	@brief	

	@author	BAEK HUM KYUNG
*/
bool CVect3d::IsPerpendicularTo( const CVect3d& rhs )
{
	const CVect3d res = (*this) * rhs;
	return ((res.m_dx < epsilon<double>()) && (res.m_dy < epsilon<double>()) && (res.m_dz < epsilon<double>()));
}

bool CVect3d::operator==( const CVect3d& rhs ) const
{
	return ( (m_dx == rhs.m_dx) && (m_dy == rhs.m_dy) && (m_dz == rhs.m_dz) );
}

void CVect3d::CrossCross(const CVect3d &V1, const CVect3d &V2)
{
	CVect3d A = (*this), B = V1, C = V2;
	CVect3d Res = B*((C.DotProduct(A))) - C*(A.DotProduct(B));
	(*this) = Res;
}

CVect3d CVect3d::CrossCrossed(const CVect3d &V1, const CVect3d &V2)
{
	CVect3d V = (*this);
	V.CrossCross(V1, V2);
	return V;
}

/**
*/
CVect3d CVect3d::UnitVector() const
{
	CVect3d result;
	double l = Length();
	if(l > 0.f)
	{
		double x = m_dx / l ;
		double y = m_dy / l;
		double z = m_dz / l;

		result.Set( x , y , z );
		return result;
	}else	return *this;
}

CVect3d operator *(const double& real , const CVect3d& vec)
{
	return CVect3d(vec.m_dx * real , vec.m_dy * real , vec.m_dz * real);
}

/**
	@brief

	@author	BHK

	@date	2009.11.10

	@param

	@return
*/
void CVect3d::Zero()
{
	m_dx = m_dy = m_dz = 0.f;
}

/**
	@brief	return angle in radian between two vectors

	@author	humkyung

	@date	2013.06.20
*/
const double CVect3d::AngleTo(const CVect3d& rhs) const
{
	return (acos(this->DotProduct(rhs) / (this->Length()*rhs.Length())));
}