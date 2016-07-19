// Entity.h: interface for the CBaseEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITY_H__3E24701F_24D8_4F6A_A1FB_F93888A51581__INCLUDED_)
#define AFX_ENTITY_H__3E24701F_24D8_4F6A_A1FB_F93888A51581__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <tchar.h>
#include <limits>
#include "BaseTools.h"

#ifdef ON_DLL_EXPORTS
	#define ON_EXT_CLASS	__declspec(dllexport)
	#define	ON_EXT_DECL	extern "C" __declspec(dllexport)
	#define ON_EXTERN_DECL	extern
#else
	#define ON_EXT_CLASS	__declspec(dllimport)
	#define	ON_EXT_DECL	extern "C" __declspec(dllexport)
	#define ON_EXTERN_DECL	extern __declspec(dllimport)
#endif

#define ON_DECLARE_FUNC(classname)\
public:\
	virtual bool IsKindOf(const TCHAR* typeString) const;\
	CBaseEntity* Clone();\
	void Copy( classname* p );\
	static const TCHAR* TypeString();\
	static CBaseEntity* CreateInstance();\

#define	ON_IMPLEMENT_FUNC(classname,baseclassname,typestr) \
CBaseEntity* classname::Clone()\
{\
	classname* p = new classname;\
	p->Copy(this);\
	return p;\
}\
void classname::Copy( classname* p )\
{\
	baseclassname::Copy( p );\
	(*this) = (*p);\
}\
bool classname::IsKindOf(const TCHAR* typeString) const\
{\
	if(0 == STRCMP_T(classname::TypeString() , typeString)) return true;\
	return baseclassname::IsKindOf(typeString);\
}\
const TCHAR* classname::TypeString()\
{\
	static const TCHAR* typeString=_T(typestr);\
	return _T(typestr);\
}\
CBaseEntity* classname::CreateInstance()\
{\
	return new classname;\
}\

enum Intersect
{
	kOnBothOperands = 0,
	kExtendThis	= 1,
	kExtendArg	= 2,
	kExtendBoth	= 3
};

#define IS_TOLER	0.001

namespace AppFramework
{
class ON_EXT_CLASS CBaseEntity  
{
public:
	unsigned long GetUserData() const;
	virtual int SetUserData(const unsigned long& dwReserved);
	const long Id();
	void Copy( const CBaseEntity* pEnt );
	CBaseEntity& operator=( const CBaseEntity& rhs );
	CBaseEntity( const CBaseEntity& rhs );
	CBaseEntity();
	virtual ~CBaseEntity();

	ON_DECLARE_FUNC(CBaseEntity)
protected:
	unsigned long m_dwReserved;
};
};

#endif // !defined(AFX_ENTITY_H__3E24701F_24D8_4F6A_A1FB_F93888A51581__INCLUDED_)
