// SATLib.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <Tokenizer.h>
#include <IsString.h>
#include <AcisLib.h>
#include <AcisFile.h>
#include <SATExport.h>

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch(ul_reason_for_call){ 
		case DLL_PROCESS_DETACH: 
		/* Indicates that the DLL is being unloaded from 
		the virtual address space of the calling process 
		as a result of either a process exit or a call to 
		FreeLibrary. The DLL can use this opportunity to 
		call the TlsFree function to free any TLS indices 
		allocated by using TlsAlloc and to free any thread 
			local data.*/
			AcisLib::DeleteInstance();
			break;
			
		default:
			break;
	}

	return TRUE;
}

const TCHAR* AcisLib::szDelimiter=_T(" \t");
const TCHAR* AcisLib::szSolid[3]={_T("cone"),_T("sphere"),_T("torus")};
const TCHAR* AcisLib::szDir[2] = {_T("forward"),_T("reversed")};

TCHAR AcisLib::m_szLine[ACIS_LINE_BUF_SIZ]={0,};
//boost::pool<>* AcisLib::m_pPrimitivePool = NULL;
//boost::pool<>* AcisLib::m_pConeSurfPool  = NULL;
//boost::pool<>* AcisLib::m_pPlaneSurfPool = NULL;
//boost::pool<>* AcisLib::m_pSphereSurfPool= NULL;
//boost::pool<>* AcisLib::m_pSurfPool = NULL;
//boost::pool<>* AcisLib::m_pTorusSurfPool = NULL;
//boost::pool<>* AcisLib::m_pSurfElmPool = NULL;
////list<POINT_T*>* AcisLib::m_pPointPool = NULL;

/**	
	@brief
*/
AcisLib::AcisLib() : m_pclsImporter(NULL)
{
	m_pDoc = new AcisDoc();
	//m_pclsExporter = NULL;
}

AcisLib::AcisLib(const AcisLib&){}
AcisLib& AcisLib::operator=(const AcisLib&){return (*this);}

/**	
	@brief
*/
AcisLib::~AcisLib()
{
	try
	{
		if(m_pDoc) SAFE_DELETE(m_pDoc);
		if(m_pclsImporter) delete m_pclsImporter;

		Initialize();
	}
	catch(...)
	{
	}
}

/**	\brief	The AcisLib::Initialize function


	\return	void	
*/
void AcisLib::Initialize()
{
	try
	{
		/*if(NULL != AcisLib::m_pPointPool)
		{
			for(list<POINT_T*>::iterator itr = AcisLib::m_pPointPool->begin();
			itr != AcisLib::m_pPointPool->end();++itr)
			{
				::free((void*)(*itr));
			}
			delete (AcisLib::m_pPointPool);
			AcisLib::m_pPointPool = NULL;
		}*/

		/*if(NULL != AcisLib::m_pConeSurfPool)
		{
			delete AcisLib::m_pConeSurfPool;
			AcisLib::m_pConeSurfPool = NULL;
		}

		if(NULL != AcisLib::m_pPlaneSurfPool)
		{
			delete AcisLib::m_pPlaneSurfPool;
			AcisLib::m_pPlaneSurfPool = NULL;
		}

		if(NULL != AcisLib::m_pSphereSurfPool)
		{
			delete AcisLib::m_pSphereSurfPool;
			AcisLib::m_pSphereSurfPool = NULL;
		}
		
		if(NULL != AcisLib::m_pTorusSurfPool)
		{
			delete AcisLib::m_pTorusSurfPool;
			AcisLib::m_pTorusSurfPool = NULL;
		}
		
		if(NULL != AcisLib::m_pSurfPool)
		{
			delete AcisLib::m_pSurfPool;
			AcisLib::m_pSurfPool = NULL;
		}

		if(NULL != AcisLib::m_pSurfElmPool)
		{
			delete AcisLib::m_pSurfElmPool;
			AcisLib::m_pSurfElmPool = NULL;
		}

		if(NULL != m_pPrimitivePool)
		{
			delete m_pPrimitivePool;
			m_pPrimitivePool = NULL;
		}*/
	}
	catch(...)
	{
		OutputDebugString(_T("Error in Initialize"));
	}
}

/**	
	@brief	The AcisLib::Load function

	@author	BHK

	@date	?

	@param	pFilePath	a parameter of type const char*

	@return	bool	
*/
bool AcisLib::Load(const char* pFilePath)
{
	assert(pFilePath && "pFilePath is NULL");
	bool bRet=false;

	if(pFilePath)
	{
		if(NULL == m_pDoc) m_pDoc = new AcisDoc;
		if(NULL == m_pclsImporter) m_pclsImporter = new AcisFile(m_pDoc);

		if(m_pclsImporter && m_pDoc)
		{
			Initialize();
			
			//m_pPrimitive=m_pclsImporter->OnImportFile(pFilePath);
			bRet = true;
		}
	}

	return bRet;
}

/**	
	@brief	The AcisLib::GetDoc function
	@author	humkyung
	@return	CSATDoc*	
*/
AcisDoc* AcisLib::GetDoc()
{
	return m_pDoc;
}

AcisLib* AcisLib::m_pInst = NULL;

/**	\brief	The AcisLib::GetInstance function


	\return	AcisLib*	
*/
AcisLib* AcisLib::GetInstance()
{
	if(NULL == AcisLib::m_pInst) AcisLib::m_pInst = new AcisLib;
	return AcisLib::m_pInst;
}

/**	\brief	The AcisLib::AllocPrimitive function


	\return	PSQPRIMITIVE	
*/
//PSQPRIMITIVE AcisLib::AllocPrimitive()
//{	
//	PSQPRIMITIVE pRet=NULL;
//	
//	if(NULL == m_pPrimitivePool) m_pPrimitivePool= new boost::pool<>(sizeof(SQPRIMITIVE));
//	if(NULL != m_pPrimitivePool)
//	{
//		pRet=(PSQPRIMITIVE)(m_pPrimitivePool->malloc());
//		memset(pRet,'\0',sizeof(SQPRIMITIVE));
//
//		pRet->hdr.attr.f = 1;
//		pRet->hdr.attr.d = 3;
//	}
//
//	return pRet;
//}

//------------------------------------------------------------------
/**	\brief	The ImportSATFile function

	\param	pFilePath	a parameter of type const char*

	\return	PSQPRIMITIVE	
*/
extern "C" __declspec(dllexport)
//PSQPRIMITIVE ImportSATFile(const char* pFilePath)
//{
//	assert(pFilePath && "pFilePath is invalid");
//	PSQPRIMITIVE pRet=NULL;
//
//	if(pFilePath)
//	{
//		AcisLib* pSATLib=AcisLib::GetInstance();
//		if(pSATLib)
//		{
//			pSATLib->Load(pFilePath);
//			pRet = pSATLib->m_pPrimitive;
//		}
//	}
//
//	return pRet;
//}

//extern "C" __declspec(dllexport)
//void ExportSATFile(const char* pFilePath,PSQPRIMITIVE pPrimitive)
//{
	//assert(pFilePath && "pFilePath is invalid");
	//assert(pPrimitive&& "pPrimitive is invalid");

	//if(pFilePath && pPrimitive){
	//	theNSQFile.m_NSQExport.OnExportFile(pFilePath,pPrimitive);
	//}
//}

/**	\brief	The AcisLib::DeleteInstance function


	\return	void	
*/
void AcisLib::DeleteInstance()
{
	if(NULL != AcisLib::m_pInst) delete AcisLib::m_pInst;
	AcisLib::m_pInst = NULL;
}

/**	\brief	The AcisLib::RegisterToPointPool function

	\param	ppt	a parameter of type POINT_T*

	\return	void	
*/
//void AcisLib::RegisterToPointPool(POINT_T* ppt)
//{
//	assert(ppt && "ppt is NULL");
//
//	if(ppt)
//	{		
//		if(NULL == AcisLib::m_pPointPool) AcisLib::m_pPointPool = new list<POINT_T*>;
//		if(NULL != AcisLib::m_pPointPool) AcisLib::m_pPointPool->push_back(ppt);
//	}
//}

/**	\brief	The AcisLib::AllocConeSurf function


	\return	CONESURF_T*	
*/
//CONESURF_T* AcisLib::AllocConeSurf()
//{
//	CONESURF_T* pRet=NULL;
//	if(NULL == AcisLib::m_pConeSurfPool) AcisLib::m_pConeSurfPool = new boost::pool<>(sizeof(CONESURF_T));
//	if(NULL != AcisLib::m_pConeSurfPool)
//	{
//		pRet = (CONESURF_T*)AcisLib::m_pConeSurfPool->malloc();
//		memset(pRet,'\0',sizeof(CONESURF_T));
//	}
//
//	return pRet;
//}

/**	\brief	The AcisLib::AllocPlaneSurf function


	\return	PLANESURF_T*	
*/
//PLANESURF_T* AcisLib::AllocPlaneSurf()
//{
//	PLANESURF_T* pRet=NULL;
//	if(NULL == AcisLib::m_pPlaneSurfPool) AcisLib::m_pPlaneSurfPool = new boost::pool<>(sizeof(PLANESURF_T));
//	if(NULL != AcisLib::m_pPlaneSurfPool)
//	{
//		pRet = (PLANESURF_T*)AcisLib::m_pPlaneSurfPool->malloc();
//		memset(pRet,'\0',sizeof(PLANESURF_T));
//	}
//
//	return pRet;
//}

/**	\brief	The AcisLib::AllocSphereSurf function


	\return	SQSPHERESURFACE*	
*/
//SQSPHERESURFACE* AcisLib::AllocSphereSurf()
//{
//	SQSPHERESURFACE* pRet=NULL;
//	if(NULL == AcisLib::m_pSphereSurfPool) AcisLib::m_pSphereSurfPool = new boost::pool<>(sizeof(SQSPHERESURFACE));
//	if(NULL != AcisLib::m_pSphereSurfPool)
//	{
//		pRet = (SQSPHERESURFACE*)AcisLib::m_pSphereSurfPool->malloc();
//		memset(pRet,'\0',sizeof(SQSPHERESURFACE));
//	}
//	
//	return pRet;
//}

/**	\brief	The AcisLib::AllocSurf function


	\return	SURF_T*	
*/
//SURF_T* AcisLib::AllocSurf()
//{
//	SURF_T* pRet=NULL;
//	if(NULL == AcisLib::m_pSurfPool) AcisLib::m_pSurfPool = new boost::pool<>(sizeof(SURF_T));
//	if(NULL != AcisLib::m_pSurfPool)
//	{
//		pRet = (SURF_T*)AcisLib::m_pSurfPool->malloc();
//		memset(pRet,'\0',sizeof(SURF_T));
//	}
//	
//	return pRet;
//}

/**	@brief	Torus Surf 구조체를 메모리 할당한 후 pool에 추가한다.
	@author	백흠경

	@return	Torus Surf 구조체 포인터
*/
//SQTORUSSURFACE* AcisLib::AllocTorusSurf()
//{
//	SQTORUSSURFACE* pRet=NULL;
//	if(NULL == AcisLib::m_pTorusSurfPool) AcisLib::m_pTorusSurfPool = new boost::pool<>(sizeof(SQTORUSSURFACE));
//	if(NULL != AcisLib::m_pTorusSurfPool)
//	{
//		pRet = (SQTORUSSURFACE*)AcisLib::m_pTorusSurfPool->malloc();
//		memset(pRet,'\0',sizeof(SQTORUSSURFACE));
//	}
//	
//	return pRet;
//}

/**	\brief	The AcisLib::AllocSurfElm function


	\return	SQSURFACE::SURFELM_T*	
*/
//SQSURFACE::SURFELM_T* AcisLib::AllocSurfElm()
//{
//	SQSURFACE::SURFELM_T* pRet=NULL;
//	if(NULL == AcisLib::m_pSurfElmPool) AcisLib::m_pSurfElmPool = new boost::pool<>(sizeof(SQSURFACE::SURFELM_T));
//	if(NULL != AcisLib::m_pSurfElmPool)
//	{
//		pRet = (SQSURFACE::SURFELM_T*)AcisLib::m_pSurfElmPool->malloc();
//		memset(pRet,'\0',sizeof(SQSURFACE::SURFELM_T));
//	}
//	
//	return pRet;
//}

/**
	@brief	return string for subtype
	@author	humkyung
	@date	2014.10.23
	@return	string for subtype
*/
STRING_T GetStringOfSubType(STRING_T& aLine , int& iLineIndex , vector<STRING_T>& oLines)
{
	STRINGSTREAM_T oss;

	int iStartOfSubTypeCount = 0;

	vector<STRING_T> oResult;
	IsString::TrimWhiteSpace(aLine);
	CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
	for(vector<STRING_T>::iterator itr = oResult.begin();itr != oResult.end();++itr)
	{
		oss.str().empty() ? (oss << (*itr)) : (oss << _T(" ") << (*itr));
		if((*itr) == ACIS_START_OF_SUBTYPE)
		{
			++iStartOfSubTypeCount;
		}
		else if((*itr) == ACIS_END_OF_SUBTYPE)
		{
			--iStartOfSubTypeCount;
			if(0 == iStartOfSubTypeCount)
			{
				OSTRINGSTREAM_T stream;
#ifdef	_UNICODE
				std::copy(itr+1 , oResult.end(), std::ostream_iterator<STRING_T,wchar_t>(stream , _T(" ")));
#else
				std::copy(itr+1 , oResult.end(), std::ostream_iterator<STRING_T>(stream , _T(" ")));
#endif
				aLine = stream.str();

				return oss.str();
			}
		}
	}
	oss << std::endl;

	for(++iLineIndex;iLineIndex < int(oLines.size());++iLineIndex)
	{
		aLine = oLines[iLineIndex];
		IsString::TrimWhiteSpace(aLine);
		if(aLine.empty()) continue;
		CTokenizer<CIsFromString>::Tokenize(oResult , aLine , CIsFromString(_T(" \t")));
		for(vector<STRING_T>::iterator itr = oResult.begin();itr != oResult.end();++itr)
		{
			oss.str().empty() ? (oss << (*itr)) : (oss << _T(" ") << (*itr));
			if((*itr) == ACIS_START_OF_SUBTYPE)
			{
				++iStartOfSubTypeCount;
			}
			else if((*itr) == ACIS_END_OF_SUBTYPE)
			{
				--iStartOfSubTypeCount;
				if(0 == iStartOfSubTypeCount)
				{
					OSTRINGSTREAM_T stream;
#ifdef	_UNICODE
					std::copy(itr + 1 , oResult.end(), std::ostream_iterator<STRING_T,wchar_t>(stream , _T(" ")));
#else
					std::copy(itr + 1 , oResult.end(), std::ostream_iterator<STRING_T>(stream , _T(" ")));
#endif
					aLine = stream.str();
					return oss.str();
				}
			}
		}
		oss << std::endl;
	}

	return STRING_T();
}