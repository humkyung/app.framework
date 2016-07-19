#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <BaseTools.h>
#include <fstream>

#include "AcisEnum.h"
using namespace std;

#ifdef	linux
	#define ON_EXT_CLASS
	#define	ON_EXT_DECL
	#define ON_EXTERN_DECL
#else
#ifdef ON_DLL_EXPORTS
	#define ON_EXT_CLASS	__declspec(dllexport)
	#define	ON_EXT_DECL	extern "C" __declspec(dllexport)
	#define ON_EXTERN_DECL	extern
#else
	#define ON_EXT_CLASS	__declspec(dllimport)
	#define	ON_EXT_DECL	extern "C" __declspec(dllexport)
	#define ON_EXTERN_DECL	extern __declspec(dllimport)
#endif
#endif // linux

#ifndef ON_DLL_EXPORTS
#ifdef _WIN64
	#ifdef _UNICODE
		#ifdef _DEBUG
			#if _MSC_VER == 1700
				#pragma comment(lib, "acislib_vc110_x64_unicode_debug")
				#pragma message("Automatically linking with acislib_vc110_x64_unicode_debug.dll (Debug Unicode)")
			#elif _MSC_VER == 1600
				#pragma comment(lib, "acislib_vc100_x64_unicode_debug")
				#pragma message("Automatically linking with acislib_vc100_x64_unicode_debug.dll (Debug Unicode)")
			#else
				#pragma comment(lib, "acislib_vc90_x64_unicode_debug")
				#pragma message("Automatically linking with acislib_vc90_x64_unicode_debug.dll (Debug Unicode)")
			#endif
		#else
			#if _MSC_VER == 1700
				#pragma comment(lib, "acislib_vc110_x64_unicode")
				#pragma message("Automatically linking with acislib_vc110_x64_unicode.dll (Release Unicode)")
			#elif _MSC_VER == 1600
				#pragma comment(lib, "acislib_vc100_x64_unicode")
				#pragma message("Automatically linking with acis_vc100_x64_unicode.dll (Release Unicode)")
			#else
				#pragma comment(lib, "acislib_vc90_x64_unicode")
				#pragma message("Automatically linking with acislib_vc90_x64_unicode.dll (Release Unicode)")
			#endif
		#endif
	#else
		#ifdef _DEBUG
			#if _MSC_VER == 1700
				#pragma comment(lib, "acislib_vc110_x64_debug")
				#pragma message("Automatically linking with acislib_vc110_x64_debug.dll (Debug)")
			#elif _MSC_VER == 1600
				#pragma comment(lib, "acislib_vc100_x64_debug")
				#pragma message("Automatically linking with acislib_vc100_x64_debug.dll (Debug)")
			#else
				#pragma comment(lib, "acislib_vc90_x64_debug")
				#pragma message("Automatically linking with acislib_vc90_x64_debug.dll (Debug)")
			#endif
		#else
			#if _MSC_VER == 1700
				#pragma comment(lib, "acislib_vc110_x64")
				#pragma message("Automatically linking with acislib_vc110_x64.dll (Release)")
			#elif _MSC_VER == 1600
				#pragma comment(lib, "acislib_vc100_x64")
				#pragma message("Automatically linking with acislib_vc100_x64.dll (Release)")
			#else
				#pragma comment(lib, "acislib_vc90_x64")
				#pragma message("Automatically linking with acislib_vc90_x64.dll (Release)")
			#endif
		#endif
	#endif // _UNICODE
#else
	#ifdef _UNICODE
		#ifdef _DEBUG
			#if _MSC_VER == 1700
				#pragma comment(lib, "acislib_vc110_unicode_debug")
				#pragma message("Automatically linking with acislib_vc110_unicode_debug.dll (Debug Unicode)")
			#elif _MSC_VER == 1600
				#pragma comment(lib, "acislib_vc100_unicode_debug")
				#pragma message("Automatically linking with acislib_vc100_unicode_debug.dll (Debug Unicode)")
			#else
				#pragma comment(lib, "acislib_vc90_unicode_debug")
				#pragma message("Automatically linking with acislib_vc90_unicode_debug.dll (Debug Unicode)")
			#endif
		#else
			#if _MSC_VER == 1700
				#pragma comment(lib, "acislib_vc110_unicode")
				#pragma message("Automatically linking with acislib_vc110_unicode.dll (Release Unicode)")
			#elif _MSC_VER == 1600
				#pragma comment(lib, "acislib_vc100_unicode")
				#pragma message("Automatically linking with acis_vc100_unicode.dll (Release Unicode)")
			#else
				#pragma comment(lib, "acislib_vc90_unicode")
				#pragma message("Automatically linking with acislib_vc90_unicode.dll (Release Unicode)")
			#endif
		#endif
	#else
		#ifdef _DEBUG
			#if _MSC_VER == 1700
				#pragma comment(lib, "acislib_vc110_debug")
				#pragma message("Automatically linking with acislib_vc110_debug.dll (Debug)")
			#elif _MSC_VER == 1600
				#pragma comment(lib, "acislib_vc100_debug")
				#pragma message("Automatically linking with acislib_vc100_debug.dll (Debug)")
			#else
				#pragma comment(lib, "acislib_vc90_debug")
				#pragma message("Automatically linking with acislib_vc90_debug.dll (Debug)")
			#endif
		#else
			#if _MSC_VER == 1700
				#pragma comment(lib, "acislib_vc110")
				#pragma message("Automatically linking with acislib_vc110.dll (Release)")
			#elif _MSC_VER == 1600
				#pragma comment(lib, "acislib_vc100")
				#pragma message("Automatically linking with acislib_vc100.dll (Release)")
			#else
				#pragma comment(lib, "acislib_vc90")
				#pragma message("Automatically linking with acislib_vc90.dll (Release)")
			#endif
		#endif
	#endif // _UNICODE
#endif
#endif // USER_EXPORTS

#define	TYPELIST(...) __VA_ARGS__

#define ACISLIB_DECLARE_FUNC(classname)\
public:\
	virtual bool IsKindOf(const TCHAR* typeString) const;\
	static bool TypeOf(const TCHAR* typeString);\
	static const TCHAR** TypeString();\

#define	ACISLIB_IMPLEMENT_FUNC(classname,baseclassname,typestr) \
bool classname::IsKindOf(const TCHAR* typeString) const\
{\
	const TCHAR** tmp=classname::TypeString();\
	for(int i = 0;NULL != tmp[i];++i)\
	{\
		if(0 == STRICMP_T(tmp[i] , typeString)) return true;\
	}\
	return baseclassname::IsKindOf(typeString);\
}\
bool classname::TypeOf(const TCHAR* typeString)\
{\
	const TCHAR** tmp=classname::TypeString();\
	for(int i = 0;NULL != tmp[i];++i)\
	{\
		if(0 == STRICMP_T(tmp[i] , typeString)) return true;\
	}\
	return false;\
}\
const TCHAR** classname::TypeString()\
{\
	static const TCHAR* tmp[]=typestr;\
	return tmp;\
}\

class AcisDoc;
class ON_EXT_CLASS AcisEntity
{
public:
	enum
	{
		ENM_SAT_BODY = 1,
		ENM_SAT_LUMP = 2
	};

	AcisEntity(const TCHAR*,const long& lIndex);
	virtual ~AcisEntity();
public:
	const TCHAR* GetTypeString() const;
	virtual bool Parse(AcisDoc*,const TCHAR*)=0;
	long GetIndex() const;
	long SubTypeRefIndex() const;
	long& SubTypeRefIndex();
	static bool IsIndexString(const STRING_T&);

	ACISLIB_DECLARE_FUNC(AcisEntity)
protected:
	long m_lIndex;
	long m_lSubTypeRef;
	STRING_T* m_pType;
};
