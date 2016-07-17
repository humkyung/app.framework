// IsMatrix3d.cpp: implementation of the CMatrix4d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <exception>
#include "Matrix4d.h"

using namespace AppFramework;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix4d::CMatrix4d()
{
	memset(m_xform , 0 , sizeof(double) * 16);
	m_xform[0][0] = 1.f;
	m_xform[1][1] = 1.f;
	m_xform[2][2] = 1.f;
	m_xform[3][3] = 1.f;
}

CMatrix4d::CMatrix4d(const double rhs[4][4])
{
	memcpy(m_xform , rhs , sizeof(m_xform));
}

CMatrix4d::CMatrix4d(const CPoint3d& P , 
		const CVect3d& X, 
		const CVect3d& Y,
		const CVect3d& Z)
{
	m_xform[0][0] = X[0];
	m_xform[1][0] = X[1];
	m_xform[2][0] = X[2];
	m_xform[3][0] = 0.;

	m_xform[0][1] = Y[0];
	m_xform[1][1] = Y[1];
	m_xform[2][1] = Y[2];
	m_xform[3][1] = 0.;

	m_xform[0][2] = Z[0];
	m_xform[1][2] = Z[1];
	m_xform[2][2] = Z[2];
	m_xform[3][2] = 0.;

	m_xform[0][3] = P[0];
	m_xform[1][3] = P[1];
	m_xform[2][3] = P[2];
	m_xform[3][3] = 1.;
}

CMatrix4d::CMatrix4d(const CMatrix4d& rhs)
{
	(*this) = rhs;
}

CMatrix4d::~CMatrix4d()
{

}

CMatrix4d& CMatrix4d::operator=(const CMatrix4d &rhs)
{
	if(this != &rhs)
	{
		for(int i = 0;i < 4;++i)
		{
			for(int j = 0;j < 4;++j)
			{
				m_xform[i][j] = rhs.m_xform[i][j];
			}
		}
	}

	return (*this);
}

/**
	@brief	

	@author	BHK

	@date	2009.11.09

	@param
	@param
	@param
	@param

	@return
*/
void CMatrix4d::Identity()
{
	memset( m_xform, 0, sizeof(m_xform) );
	m_xform[0][0] = m_xform[1][1] = m_xform[2][2] = m_xform[3][3] = 1.0;
}

/**
	@brief	

	@author	BHK

	@date	2009.11.09

	@param
	@param
	@param
	@param

	@return
*/
void CMatrix4d::Rotation(  
			const double& sin_angle,	// sin(rotation angle)
			const double& cos_angle,	// cos(rotation angle)
			const CVect3d&  axis,		// 3d nonzero axis of rotation
			const CPoint3d& center	// 3d center of rotation
			)
{
	Identity();
	if (sin_angle != 0.0 || cos_angle != 1.0)
	{
		const double one_minus_cos_angle = 1.0 - cos_angle;
		CVect3d a = axis;
		if ( fabs(a.LengthSquared() - 1.0) >  ON_EPSILON )
			a.UnitVector();
		
		m_xform[0][0] = a.dx()*a.dx()*one_minus_cos_angle + cos_angle;
		m_xform[0][1] = a.dx()*a.dy()*one_minus_cos_angle - a.dz()*sin_angle;
		m_xform[0][2] = a.dx()*a.dz()*one_minus_cos_angle + a.dy()*sin_angle;
		
		m_xform[1][0] = a.dy()*a.dx()*one_minus_cos_angle + a.dz()*sin_angle;
		m_xform[1][1] = a.dy()*a.dy()*one_minus_cos_angle + cos_angle;
		m_xform[1][2] = a.dy()*a.dz()*one_minus_cos_angle - a.dx()*sin_angle;
		
		m_xform[2][0] = a.dz()*a.dx()*one_minus_cos_angle - a.dy()*sin_angle;
		m_xform[2][1] = a.dz()*a.dy()*one_minus_cos_angle + a.dx()*sin_angle;
		m_xform[2][2] = a.dz()*a.dz()*one_minus_cos_angle + cos_angle;
		
		if ( center.x() != 0.0 || center.y() != 0.0 || center.z() != 0.0 )
		{
			m_xform[0][3] = -((m_xform[0][0]-1.0)*center.x() + m_xform[0][1]*center.y() + m_xform[0][2]*center.z());
			m_xform[1][3] = -(m_xform[1][0]*center.x() + (m_xform[1][1]-1.0)*center.y() + m_xform[1][2]*center.z());
			m_xform[2][3] = -(m_xform[2][0]*center.x() + m_xform[2][1]*center.y() + (m_xform[2][2]-1.0)*center.z());
		}
		
		m_xform[3][0] = m_xform[3][1] = m_xform[3][2] = 0.0;
		m_xform[3][3] = 1.0;
	}
}

/**
	@brief	

	@author	BHK
  
	@date	2009.11.09
    
	@param
      
	@return
*/
void CMatrix4d::Rotation(
			const CVect3d&  X0, // initial frame X (X,Y,Z = right handed orthonormal frame)
			const CVect3d&  Y0, // initial frame Y
			const CVect3d&  Z0, // initial frame Z
			const CVect3d&  X1, // final frame X (X,Y,Z = another right handed orthonormal frame)
			const CVect3d&  Y1, // final frame Y
			const CVect3d&  Z1  // final frame Z
			)
{
	// transformation maps X0 to X1, Y0 to Y1, Z0 to Z1
	
	// F0 changes x0,y0,z0 to world X,Y,Z
	CMatrix4d F0;
	F0[0][0] = X0.dx(); F0[0][1] = X0.dy(); F0[0][2] = X0.dz();
	F0[1][0] = Y0.dx(); F0[1][1] = Y0.dy(); F0[1][2] = Y0.dz();
	F0[2][0] = Z0.dx(); F0[2][1] = Z0.dy(); F0[2][2] = Z0.dz();
	F0[3][3] = 1.0;
	
	// F1 changes world X,Y,Z to x1,y1,z1
	CMatrix4d F1;
	F1[0][0] = X1.dx(); F1[0][1] = Y1.dx(); F1[0][2] = Z1.dx();
	F1[1][0] = X1.dy(); F1[1][1] = Y1.dy(); F1[1][2] = Z1.dy();
	F1[2][0] = X1.dz(); F1[2][1] = Y1.dz(); F1[2][2] = Z1.dz();
	F1[3][3] = 1.0;
	
	*this = F1*F0;
}

///////////////////////////////////////////////////////////////
//
// ON_Xform operator* operator- operator+
//
// All non-commutative operations have "this" as left hand side and
// argument as right hand side.
CMatrix4d CMatrix4d::operator*( const CMatrix4d& rhs ) const
{
	CMatrix4d m;
	m[0][0] = m_xform[0][0]*rhs[0][0] + m_xform[0][1]*rhs[1][0] + m_xform[0][2]*rhs[2][0] + m_xform[0][3]*rhs[3][0];
	m[0][1] = m_xform[0][0]*rhs[0][1] + m_xform[0][1]*rhs[1][1] + m_xform[0][2]*rhs[2][1] + m_xform[0][3]*rhs[3][1];
	m[0][2] = m_xform[0][0]*rhs[0][2] + m_xform[0][1]*rhs[1][2] + m_xform[0][2]*rhs[2][2] + m_xform[0][3]*rhs[3][2];
	m[0][3] = m_xform[0][0]*rhs[0][3] + m_xform[0][1]*rhs[1][3] + m_xform[0][2]*rhs[2][3] + m_xform[0][3]*rhs[3][3];
	
	m[1][0] = m_xform[1][0]*rhs[0][0] + m_xform[1][1]*rhs[1][0] + m_xform[1][2]*rhs[2][0] + m_xform[1][3]*rhs[3][0];
	m[1][1] = m_xform[1][0]*rhs[0][1] + m_xform[1][1]*rhs[1][1] + m_xform[1][2]*rhs[2][1] + m_xform[1][3]*rhs[3][1];
	m[1][2] = m_xform[1][0]*rhs[0][2] + m_xform[1][1]*rhs[1][2] + m_xform[1][2]*rhs[2][2] + m_xform[1][3]*rhs[3][2];
	m[1][3] = m_xform[1][0]*rhs[0][3] + m_xform[1][1]*rhs[1][3] + m_xform[1][2]*rhs[2][3] + m_xform[1][3]*rhs[3][3];
	
	m[2][0] = m_xform[2][0]*rhs[0][0] + m_xform[2][1]*rhs[1][0] + m_xform[2][2]*rhs[2][0] + m_xform[2][3]*rhs[3][0];
	m[2][1] = m_xform[2][0]*rhs[0][1] + m_xform[2][1]*rhs[1][1] + m_xform[2][2]*rhs[2][1] + m_xform[2][3]*rhs[3][1];
	m[2][2] = m_xform[2][0]*rhs[0][2] + m_xform[2][1]*rhs[1][2] + m_xform[2][2]*rhs[2][2] + m_xform[2][3]*rhs[3][2];
	m[2][3] = m_xform[2][0]*rhs[0][3] + m_xform[2][1]*rhs[1][3] + m_xform[2][2]*rhs[2][3] + m_xform[2][3]*rhs[3][3];
	
	m[3][0] = m_xform[3][0]*rhs[0][0] + m_xform[3][1]*rhs[1][0] + m_xform[3][2]*rhs[2][0] + m_xform[3][3]*rhs[3][0];
	m[3][1] = m_xform[3][0]*rhs[0][1] + m_xform[3][1]*rhs[1][1] + m_xform[3][2]*rhs[2][1] + m_xform[3][3]*rhs[3][1];
	m[3][2] = m_xform[3][0]*rhs[0][2] + m_xform[3][1]*rhs[1][2] + m_xform[3][2]*rhs[2][2] + m_xform[3][3]*rhs[3][2];
	m[3][3] = m_xform[3][0]*rhs[0][3] + m_xform[3][1]*rhs[1][3] + m_xform[3][2]*rhs[2][3] + m_xform[3][3]*rhs[3][3];
	return m;
}