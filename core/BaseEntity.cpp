// Entity.cpp: implementation of the CBaseEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <assert.h>
#include "BaseEntity.h"

#include <string>
using namespace std;
using namespace AppFramework;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseEntity::CBaseEntity() : m_dwReserved(0)
{

}

CBaseEntity::CBaseEntity( const CBaseEntity& rhs )
{
	(*this) = rhs;
}

CBaseEntity& CBaseEntity::operator =( const CBaseEntity& rhs )
{
	if(this != &rhs)
	{
		m_dwReserved = rhs.m_dwReserved;
	}

	return (*this);
}

CBaseEntity::~CBaseEntity()
{
	try
	{
	}
	catch(...)
	{
	}
}

/**
 * IsKindOf:
 *
 * @param id 
 * @return bool 
 */
bool CBaseEntity::IsKindOf(const TCHAR* typeString) const
{
	assert(typeString && "pTypeString is NULL");

	return false;
}

/**
	@brief	ENTITY의 TYPE STRING을 리턴한다.
*/
const TCHAR* CBaseEntity::TypeString()
{
	static const STRING_T _typeString(_T("ISENTITY"));

	return _typeString.c_str();
}

/**
 * Copy:
 *
 * @param pEnt 
 * @return void 
 */
void CBaseEntity::Copy( const CBaseEntity *pEnt )
{
	assert(pEnt && "pEnt is NULL");

	if(pEnt && pEnt->IsKindOf(CBaseEntity::TypeString()))
	{
		m_dwReserved = pEnt->m_dwReserved;
		return;
	}
}

/**
 * Clone:
 *
 * @return CBaseEntity* 
 */
CBaseEntity* CBaseEntity::Clone()
{
	CBaseEntity* p = new CBaseEntity;
	p->Copy(this);
	return p;
}

/**
 * SetUserData:
 *
 * @param pUserData 
 * @return bool 
 */
int CBaseEntity::SetUserData(const unsigned long& dwReserved)
{
	m_dwReserved = dwReserved;

	return ERROR_SUCCESS;
}

/**
	@brief	User Data를 반환한다.
*/
DWORD CBaseEntity::GetUserData() const
{
	return m_dwReserved;
}

/**
	@brief	p의 내용을 복사한다.
*/
void CBaseEntity::Copy( CBaseEntity* p )
{
	assert( p && "p is NULL");

	if(p) m_dwReserved = p->m_dwReserved;
}