#pragma once

#define ACIS_MAX_BUF		81920
#define	ACIS_END_OF_FILE	_T("End-of-ACIS-data")

#define	NUM_OF_CURVES	4
#define NUM_OF_SURFS	5

#include <BaseTools.h>
#include "AcisDef.h"
#include "AcisBody.h"
#include "AcisLump.h"
#include "AcisShell.h"
#include "AcisFace.h"
#include "AcisSurf.h"
#include "AcisLoop.h"
#include "AcisCurve.h"
#include "AcisCoEdge.h"
#include "AcisEdge.h"
#include "AcisVertex.h"
#include "AcisPoint.h"

#include <vector>
#include <map>
using namespace std;

class ON_EXT_CLASS AcisFile
{
	AcisFile(const AcisFile&){}
	AcisFile& operator =(const AcisFile&){return (*this);} 
public:
	AcisFile(AcisDoc*);
	virtual ~AcisFile();
public:
	int ReadHeaderSection(IFSTREAM_T& file);
	TCHAR* ReadElement(IFSTREAM_T& file);
	AcisEntity* ParseElement(TCHAR* data);
	//PSQPRIMITIVE OnImportFile(const char* pFilePath);
private:
	bool ReadFile(const char* pImportFilePath);
	void FreeSATLine();

	/*PSQPRIMITIVE ReadBody();
	PSQPRIMITIVE ReadLump(long& nIndex);
	PSQPRIMITIVE ReadShell(long& nIndex);
	PSQPRIMITIVE ReadFace(long& nIndex);
	PSQPRIMITIVE ReadLoop(long& nIndex);
	PSQPRIMITIVE ReadCoEdge(long& nIndex,const long& nLoopIndex);
	PSQPRIMITIVE ReadEdge(long nIndex,bool bForward);
	PSQPRIMITIVE ReadCurve(POINT_T& ptStart,POINT_T& ptEnd,bool bCoEdgeForward,CSATCurve* pCurve);
	POINT_T ReadVertex(long nIndex);
	POINT_T ReadPoint(long nIndex);*/
public:
	const static char* szIdentifier[9];
	const static char* szCurve[NUM_OF_CURVES];
	const static char* szSurface[NUM_OF_SURFS];
private:
	/*vector<AcisBody*> m_vtBody;
	map<long,AcisLump*> m_lumpMap;
	map<long,AcisShell*> m_shellMap;
	map<long,AcisFace*> m_faceMap;
	map<long,AcisSurf*> m_surfaceMap;
	map<long,AcisLoop*> m_loopMap;
	map<long,AcisCoEdge*> m_coedgeMap;
	map<long,AcisEdge*> m_edgeMap;
	map<long,AcisCurve*> m_curveMap;
	map<long,AcisVertex*> m_vertexMap;
	map<long,AcisPoint*> m_pointMap;*/
	AcisDoc* m_pDoc;
	int m_iEntIndex;
	static TCHAR m_szElement[ACIS_MAX_BUF];
};