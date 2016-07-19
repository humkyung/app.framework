#pragma once

#include "AcisEnum.h"
#include "AcisDoc.h"
#include "AcisDef.h"
#include "AcisFile.h"

#include <list>
using namespace std;

#define ACIS_END_MARK		'#'
#define ACIS_LINE_BUF_SIZ	2048
#define ACIS_TYPE_BUF_SIZ	80

class ON_EXT_CLASS AcisLib
{
private:
	AcisLib();
	AcisLib(const AcisLib&);
	AcisLib& operator=(const AcisLib&);
public:
	~AcisLib();
public:
	AcisDoc* GetDoc();
	void Initialize();
	bool Load(const char* pFilePath);
	
	static AcisLib* GetInstance();
	
	////////////////////////////////////////////////////////////////////////////
	//static boost::pool<>* m_pPrimitivePool;
	//static boost::pool<>* m_pConeSurfPool;
	//static boost::pool<>* m_pPlaneSurfPool;
	//static boost::pool<>* m_pSphereSurfPool;
	//static boost::pool<>* m_pTorusSurfPool;
	//static boost::pool<>* m_pSurfPool;
	//static boost::pool<>* m_pSurfElmPool;
	////static list<POINT_T*>* m_pPointPool;
private:
public:
	static void DeleteInstance();
	
	const static TCHAR* szDelimiter;
	const static TCHAR* szSolid[3];
	const static TCHAR* szDir[2];

	static TCHAR m_szLine[ACIS_LINE_BUF_SIZ];
private:
	static AcisLib* m_pInst;

	AcisDoc* m_pDoc;
	AcisFile* m_pclsImporter;
	//CSATExport* m_pclsExporter;
};

extern STRING_T GetStringOfSubType(STRING_T& aLine , int& iLineIndex , vector<STRING_T>& oLines);