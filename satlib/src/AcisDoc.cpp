// AcisDoc.cpp: implementation of the AcisDoc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <BaseTools.h>
#include <AcisDoc.h>
#include <AcisFile.h>
#include <AcisRefEntity.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
	@brief
*/
AcisDoc::AcisDoc()
{
	m_nSATVer = 0;
	m_nNumOfRecords = m_nNumOfEntities = 0;
	m_pAcisEntMap = new map<long,AcisEntity*>;
	m_pSubTypeHolder = new vector<AcisEntity*>;
}

AcisDoc::~AcisDoc()
{
	try
	{
		for(map<long,AcisEntity*>::iterator itr = m_pAcisEntMap->begin();itr != m_pAcisEntMap->end();++itr)
		{
			SAFE_DELETE(itr->second);
		}
		SAFE_DELETE(m_pAcisEntMap);

		for(vector<AcisEntity*>::iterator itr = m_pSubTypeHolder->begin();itr != m_pSubTypeHolder->end();++itr)
		{
			SAFE_DELETE(*itr);
		}
		SAFE_DELETE(m_pSubTypeHolder);
	}
	catch(...)
	{
	}
}

/**	
	@brief	read .sat file
	@author	humkyung
	@date	2014.10.21
	@param	pszFilePath	.sat file path
	@return	int
*/
int AcisDoc::Read(const TCHAR* pszFilePath)
{
	assert(pszFilePath && "pszFilePath is NULL");
	if(NULL != pszFilePath)
	{
		AcisFile acis(this);
		IFSTREAM_T file(pszFilePath);
		if(file.good())
		{
			acis.ReadHeaderSection(file);
			do
			{
				TCHAR* psz = acis.ReadElement(file);
				if(NULL == psz) break;
				AcisEntity* pAcisEnt = acis.ParseElement(psz);
				if(NULL != pAcisEnt) m_pAcisEntMap->insert(make_pair(pAcisEnt->GetIndex() , pAcisEnt));
			}while(1);
		}
		return ERROR_SUCCESS;
	}

	return ERROR_INVALID_PARAMETER;
}

/**
	@brief	register subtype entity
	@author	humkyung
	@date	2014.10.23
	@return	subtype index
*/
unsigned long AcisDoc::RegisterSubType(AcisEntity* pAcisEnt)
{
	assert(pAcisEnt && "pAcisEnt is NULL");
	if((NULL != pAcisEnt) && (!AcisRefEntity::TypeOf(pAcisEnt->GetTypeString())))
	{
		m_pSubTypeHolder->push_back(pAcisEnt);
		return m_pSubTypeHolder->size() - 1;
	}

	return -1;
}

/**
	@brief	return acis entity which is located at given index
	@author	humkyung
	@date	2014.10.21
	@return	acis entity
*/
AcisEntity* AcisDoc::operator[](const unsigned long& at) const
{
	map<long,AcisEntity*>::const_iterator where = m_pAcisEntMap->find(at);
	if(where != m_pAcisEntMap->end()) return where->second;

	throw exception("out of index");
}

/**
	@brief	return acis entity which is located at given index of subtype holder
	@author	humkyung
	@date	2014.10.23
	@return	acis entity
*/
AcisEntity* AcisDoc::subtype(const unsigned long& at) const
{
	if(at < m_pSubTypeHolder->size()) return (*m_pSubTypeHolder)[at];

	throw std::out_of_range("out of subtype holder range");
}

/**	
	@brief	The AcisDoc::SetVer function
	@author	humkyung
	@param	nSATVer	a parameter of type const int&
	@return	void	
*/
void AcisDoc::SetVer(const int& nSATVer){m_nSATVer = nSATVer;}

/**	
	@brief	The AcisDoc::GetVer function
	@author	humkyung
	@return	const char*	
*/
const int AcisDoc::GetVer() const {return m_nSATVer;}
