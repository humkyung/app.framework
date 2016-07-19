// SATLump.h: interface for the AcisLump class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SATLUMP_H__BFD82C97_CB93_4F25_8BE0_037215381478__INCLUDED_)
#define AFX_SATLUMP_H__BFD82C97_CB93_4F25_8BE0_037215381478__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcisEntity.h"

class ON_EXT_CLASS AcisLump : public AcisEntity  
{
public:
	AcisLump(const TCHAR*,const long& nIndex);
	virtual ~AcisLump();
public:
	bool Parse(AcisDoc*,const TCHAR*);
	long GetAttributeIndex() const;
	long GetNextIndex() const;
	long GetShellIndex() const;
	long GetBodyIndex() const;

	ACISLIB_DECLARE_FUNC(AcisLump)
private:
	long m_lAttributeIndex;
	long m_lNextIndex;
	long m_lShellIndex;
	long m_lBodyIndex;
};

#endif // !defined(AFX_SATLUMP_H__BFD82C97_CB93_4F25_8BE0_037215381478__INCLUDED_)
