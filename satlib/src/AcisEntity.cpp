// AcisEntity.cpp: implementation of the AcisEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include <AcisEntity.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	
@brief
*/
AcisEntity::AcisEntity(const TCHAR* pType,const long& lIndex) : m_lIndex(lIndex) , m_lSubTypeRef(-1)
{
	m_pType = new STRING_T;
	m_pType->assign(pType);
}

AcisEntity::~AcisEntity()
{
	try
	{
		SAFE_DELETE(m_pType);
	}
	catch(...)
	{
	}
}

/**	
	@brief	The AcisEntity::GetIndex function
	@author	humkyung
	@return	long	
*/
long AcisEntity::GetIndex() const
{
	return m_lIndex;
}

/**	
	@brief	return subtype reference index
	@author	humkyung
	@return	long	
*/
long AcisEntity::SubTypeRefIndex() const
{
	return m_lSubTypeRef;
}

/**	
	@brief	return subtype reference index
	@author	humkyung
	@return	long	
*/
long& AcisEntity::SubTypeRefIndex()
{
	return m_lSubTypeRef;
}

bool AcisEntity::IsKindOf(const TCHAR* typeString) const
{
	return false;
}
bool AcisEntity::TypeOf(const TCHAR* typeString)
{
	return false;
}
const TCHAR** AcisEntity::TypeString()
{
	return NULL;
}

/**
	@brief	return type string
	@author	humkyung
	@date	2014.10.21
	@return	type string
*/
const TCHAR* AcisEntity::GetTypeString() const
{
	return (m_pType->c_str());
}

/**
	@brief	return true if given string starts with $
	@author	humkyung
	@date	2016.07.06
	@return	bool
*/
bool AcisEntity::IsIndexString(const STRING_T& str)
{
	return ((str.length() > 0) && ('$' == str[0]));
}