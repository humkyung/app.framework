#include "StdAfx.h"
#include <windows.h>
#include <math.h>
#include <assert.h>
#include <tchar.h>

#include <IsString.h>

#include <AcisLib.h>
#include <AcisEntityFactory.h>
#include <AcisPlaneSurf.h>
#include <AcisConeSurf.h>
#include <AcisSphereSurf.h>
#include <AcisTorusSurf.h>
#include <AcisSplineSurf.h>
#include <AcisStraightCurv.h>
#include <AcisEllipseCurv.h>
#include <AcisIntCurve.h>
#include <AcisPCurve.h>
#include <AcisTransform.h>
#include <AcisDisplayAttribute.h>
#include <AcisColorAdeskAttrib.h>
#include <AcisRefVTEyeAttrib.h>
#include <AcisUnknownEntity.h>
/// subtype entity
#include <AcisRotSurf.h>
#include <AcisExactSurf.h>
#include <AcisExactCurv.h>
#include <AcisExppcCurv.h>
#include <AcisSurfIntCurv.h>
#include <AcisRefEntity.h>

#include <fstream>
using namespace std;

//////////////////////////////////////////////////////////////////////////
/**	
	@brief
*/
AcisEntityFactory::AcisEntityFactory()
{
}

/**	
	@brief
*/
AcisEntityFactory::~AcisEntityFactory()
{
}

/**	
	@brief	create a acis entity corresponding to given type
	@author	humkyung
	@date	2014.10.24
	@param	pType	
	@return	AcisEntity*
*/
AcisEntity* AcisEntityFactory::CreateEntity(const TCHAR* pType , const unsigned long& lIndex)
{
	assert(pType && "pType is NULL");
	AcisEntity* res = NULL;

	if(NULL != pType)
	{
		if(AcisBody::TypeOf(pType))
		{
			res = new AcisBody(pType , lIndex);
		}
		else if(AcisLump::TypeOf(pType))
		{
			res = new AcisLump(pType , lIndex);
		}
		else if(AcisShell::TypeOf(pType))
		{
			res = new AcisShell(pType , lIndex);
		}
		else if(AcisFace::TypeOf(pType))
		{
			res = new AcisFace(pType , lIndex);
		}
		else if(AcisLoop::TypeOf(pType))
		{
			res = new AcisLoop(pType , lIndex);
		}
		else if(AcisCoEdge::TypeOf(pType))
		{
			res = new AcisCoEdge(pType , lIndex);
		}
		else if(AcisEdge::TypeOf(pType))
		{
			res = new AcisEdge(pType , lIndex);
		}
		else if(AcisStraightCurv::TypeOf(pType))
		{
			res = new AcisStraightCurv(pType , lIndex);
		}
		else if(AcisEllipseCurv::TypeOf(pType))
		{ /// "ellipse-curve"
			res = new AcisEllipseCurv(pType , lIndex);
		}
		else if(AcisIntCurve::TypeOf(pType))
		{ /// "intcurve-curve"
			res = new AcisIntCurve(pType , lIndex);
		}
		else if(AcisPCurve::TypeOf(pType))
		{ /// "pcurve"
			res = new AcisPCurve(pType , lIndex);	
		}
		else if(AcisPlaneSurf::TypeOf(pType))
		{ /// "plane-surface"
			res = new AcisPlaneSurf(pType , lIndex);
		}
		else if(AcisConeSurf::TypeOf(pType))
		{ /// "cone-surface"
			res = new AcisConeSurf(pType , lIndex);
		}
		else if(AcisSphereSurf::TypeOf(pType))
		{ /// "sphere-surface"
			res = new AcisSphereSurf(pType , lIndex);
		}
		else if(AcisTorusSurf::TypeOf(pType))
		{ /// "torus-surface"
			res = new AcisTorusSurf(pType , lIndex);
		}
		else if(AcisSplineSurf::TypeOf(pType))
		{ /// "spline-surface"
			res = new AcisSplineSurf(pType , lIndex);
		}
		else if(AcisVertex::TypeOf(pType))
		{ /// "vertex"
			res = new AcisVertex(pType , lIndex);
		}
		else if(AcisPoint::TypeOf(pType))
		{ /// "point"
			res = new AcisPoint(pType , lIndex);
		}
		else if(AcisTransform::TypeOf(pType))
		{
			res = new AcisTransform(pType , lIndex);
		}
		else if(AcisDisplayAttribute::TypeOf(pType))
		{
			res = new AcisDisplayAttribute(pType , lIndex);
		}
		else if(AcisColorAdeskAttrib::TypeOf(pType))
		{
			res = new AcisColorAdeskAttrib(pType , lIndex);
		}
		else if(AcisRefVTEyeAttrib::TypeOf(pType))
		{
			res = new AcisRefVTEyeAttrib(pType , lIndex);
		}
		else if(AcisRotSurf::TypeOf(pType))
		{
			res = new AcisRotSurf(pType , lIndex);
		}
		else if(AcisExactCurv::TypeOf(pType))
		{
			res = new AcisExactCurv(pType , lIndex);
		}
		else if(AcisExactSurf::TypeOf(pType))
		{
			res = new AcisExactSurf(pType , lIndex);
		}
		else if(AcisExppcCurv::TypeOf(pType))
		{
			res = new AcisExppcCurv(pType , lIndex);
		}
		else if(AcisSurfIntCurv::TypeOf(pType))
		{
			res = new AcisSurfIntCurv(pType , lIndex);
		}
		else if(AcisRefEntity::TypeOf(pType))
		{
			res = new AcisRefEntity(pType , lIndex);
		}
		else
		{
			res = new AcisUnknownEntity(pType , lIndex);
		}
	}

	return res;
}