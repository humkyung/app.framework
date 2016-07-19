#include "StdAfx.h"
#include <windows.h>
#include <math.h>
#include <assert.h>
#include <tchar.h>

#include <IsString.h>

#include <AcisLib.h>
#include <AcisFile.h>
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

#include <AcisEntityFactory.h>

#include <fstream>
using namespace std;

//////////////////////////////////////////////////////////////////////////
// buf for reading sat text file.
TCHAR AcisFile::m_szElement[ACIS_MAX_BUF]={0,};

const char* AcisFile::szIdentifier[9]={"body","lump","shell","face","loop","coedge","edge","vertex","point"};
const char* AcisFile::szCurve[4] = {"straight-curve","ellipse-curve","intcurve-curve","pcurve"};
const char* AcisFile::szSurface[5] = {"plane-surface","cone-surface","sphere-surface","torus-surface","spline-surface"};
/**	\brief
*/
AcisFile::AcisFile(AcisDoc* pDoc) : m_pDoc(pDoc) , m_iEntIndex(-1)
{
	m_szElement[0] = '\0';
}

/**	\brief
*/
AcisFile::~AcisFile()
{
}

/**	
	@brief	read an identifier from sat file.
	@author	humkyung
	@param	file	a parameter of type KTextFile&
	@return	bool	
*/
TCHAR* AcisFile::ReadElement(IFSTREAM_T& file)
{
	bool bRet=false;

	if(file.good() && !file.eof())
	{
		memset(m_szElement , 0 , sizeof(TCHAR)*ACIS_MAX_BUF);

		bool bGotEntIndex = false;
		STRING_T aLine;
		do
		{
			getline(file , aLine);
			if(aLine.empty() || (ACIS_END_OF_FILE == aLine)) return NULL;
			if(('\0' == m_szElement[0]) && ('-' == aLine[0]))
			{
				int i = 1;
				for(i = 1;i < int(aLine.length());++i)
				{
					if(!::isdigit(aLine[i])) break;
				}
				m_iEntIndex = ATOI_T(aLine.substr(1,i - 1).c_str());
				bGotEntIndex = true;
				aLine = aLine.substr(i);
				IsString::TrimWhiteSpace(aLine);
			}
			STRINGSTREAM_T oss;
			oss << aLine << std::endl;
			STRCAT_T(m_szElement , oss.str().c_str());
			if(STRING_T::npos != aLine.find(ACIS_END_MARK)) break;
		}while(!file.eof());
		STRING_T::size_type pos = STRING_T(m_szElement).find(ACIS_END_MARK);
		m_szElement[pos + 1] = '\0';

		if(false == bGotEntIndex) ++m_iEntIndex;

		return m_szElement;
	}

	return NULL;
}

/**	
	@brief	parse given data from sat file.
	@author	humkyung
	@param	data	
	@return	AcisEntity*
*/
AcisEntity* AcisFile::ParseElement(TCHAR* data)
{
	assert(data && "data is NULL");
	AcisEntity* res = NULL;

	if(NULL != data)
	{
		TCHAR szId[ACIS_TYPE_BUF_SIZ]={0,};

		SSCANF_T(data , _T("%s") , szId);
		res = AcisEntityFactory::CreateEntity(szId , m_iEntIndex);

		if(NULL != res) res->Parse(m_pDoc , data);
	}

	return res;
}

/**	
	@brief	The AcisFile::ParseHeader function
	@author	humkyung
	@param	pszHeader	a parameter of type const char*
	@return	void	
*/
int AcisFile::ReadHeaderSection(IFSTREAM_T& file)
{
	if(file.good() && !file.eof())
	{
		/// parse and skip header section.
		file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ);
		int nAcisVer=0,nNumOfRecords=0,nNumOfEntities=0,xxx=0;
		SSCANF_T(AcisLib::m_szLine , _T("%d %d %d %d") ,&nAcisVer,&nNumOfRecords,&nNumOfEntities,&xxx);
		m_pDoc->SetVer(nAcisVer);

		file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ);
		file.getline(AcisLib::m_szLine,ACIS_LINE_BUF_SIZ);
		/// up to here	
		m_iEntIndex = -1;

		return ERROR_SUCCESS;
	}

	return ERROR_INVALID_PARAMETER;
}

/**	
	@brief	read identifier from sat file.
	@author	humkyung	
	@date	?
	@param	pImportFilePath	a parameter of type const char*
	@return	bool	
*/
bool AcisFile::ReadFile(const char* pImportFilePath)
{
	bool bRet = false;
	return bRet;
}

/**	\brief	The AcisFile::FreeSATLine function
	\return	void	
*/
void AcisFile::FreeSATLine()
{
}