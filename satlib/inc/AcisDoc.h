#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <list>
#include <vector>

#ifdef ON_DLL_EXPORTS
	#define ON_EXT_CLASS	__declspec(dllexport)
	#define	ON_EXT_DECL	extern "C" __declspec(dllexport)
	#define ON_EXTERN_DECL	extern
#else
	#define ON_EXT_CLASS	__declspec(dllimport)
	#define	ON_EXT_DECL	extern "C" __declspec(dllexport)
	#define ON_EXTERN_DECL	extern __declspec(dllimport)
#endif

#define ACIS_START_OF_SUBTYPE	_T("{")
#define ACIS_END_OF_SUBTYPE		_T("}")

#include "AcisEntity.h"
#include "AcisBody.h"

class ON_EXT_CLASS AcisDoc
{
public:
	AcisDoc();
	virtual ~AcisDoc();
public:
	/**
	@brief	read .sat file
	*/
	int Read(const TCHAR*);
	AcisEntity* operator[](const unsigned long&) const;
	AcisEntity* subtype(const unsigned long&) const;
	unsigned long RegisterSubType(AcisEntity*);

	void SetVer(const int& nSATVer);
	const int GetVer() const;
public:
	typedef map<long , AcisEntity*>::const_iterator iterator;
	iterator begin()
	{
		return m_pAcisEntMap->begin();	
	}
	iterator end()
	{
		return m_pAcisEntMap->end();	
	}
private:
	int m_nSATVer,m_nNumOfRecords,m_nNumOfEntities;
	map<long , AcisEntity*>* m_pAcisEntMap;
	vector<AcisEntity*>* m_pSubTypeHolder;
};