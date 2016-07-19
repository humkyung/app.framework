#pragma once

#include "Point3d.h"
#include "Vect3d.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace AppFramework
{
class ON_EXT_CLASS CMatrix4d  
{
public:
	CMatrix4d& operator=(const CMatrix4d& rhs);
	CMatrix4d(const CPoint3d& P,	// as a frame. 
			const CVect3d& X,	
			const CVect3d& Y,	
			const CVect3d& Z); 
	CMatrix4d(const CMatrix4d& rhs);
	CMatrix4d(const double rhs[4][4]);	// from standard double m[4][4]
	CMatrix4d();
	virtual ~CMatrix4d();

	double* operator[](int i)
	{
		return ( i >= 0 && i < 4 ) ? &m_xform[i][0] : NULL;
	}
	
	const double* operator[](int i) const
	{
		return ( i >= 0 && i < 4 ) ? &m_xform[i][0] : NULL;
	}

	CMatrix4d operator*( const CMatrix4d& rhs ) const;
	CPoint3d operator*( const CPoint3d& p ) const;
	void Identity();
	void Rotation(
			const CVect3d&  X0, // initial frame X (X,Y,Z = right handed orthonormal frame)
			const CVect3d&  Y0, // initial frame Y
			const CVect3d&  Z0, // initial frame Z
			const CVect3d&  X1, // final frame X (X,Y,Z = another right handed orthonormal frame)
			const CVect3d&  Y1, // final frame Y
			const CVect3d&  Z1  // final frame Z
			);
	void Rotation( 
		const double& sin_angle,
		const double& cos_angle,
		const CVect3d&  axis,  // 3d nonzero axis of rotation
		const CPoint3d& center  // 3d center of rotation
        );
	void Rotation( 
		const double& angle,
		const CVect3d&  axis,  // 3d nonzero axis of rotation
		const CPoint3d& center  // 3d center of rotation
        )
	{
		Rotation( sin(angle), cos(angle), axis, center );
	}

	enum
	{
		ROWS = 4,
		COLS = 4
	};
private:
	double m_xform[4][4]; // [i][j] = row i, column j.  I.e., 
                        // [0][0] [0][1] [0][2] [0][3]
                        // [1][0] [1][1] [1][2] [1][3]
                        // [2][0] [2][1] [2][2] [2][3]
                        // [3][0] [3][1] [3][2] [3][3]
};
};