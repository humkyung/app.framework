// SATDoc.cpp: implementation of the CSATDoc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <SATDoc.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**	\brief
*/
CSATDoc::CSATDoc()
{
	m_nSATVer = 0;
	m_nNumOfRecords = m_nNumOfEntities = 0;
}

CASTDoc::CASTDoc(const CSATDoc& rhs)
{
	(*this) = rhs;
}

CSATDoc& CASTDoc::operator=(const CSATDoc& rhs)
{
	return (*this);
}
	
CSATDoc::~CSATDoc()
{

}

/**	\brief	The CSATDoc::Append function

	\param	pObj	a parameter of type CObjInterface*

	\return	bool	
*/
bool CSATDoc::Append(CObjInterface* pObj){
	assert(pObj && "pObj is NULL");

	if(pObj){
		if(NULL == m_plstObj) m_plstObj = new list<CObjInterface*>;
		if(m_plstObj) m_plstObj->push_back(pObj);
	}

	return true;
};

/**	\brief	The CSATDoc::GetObjList function


	\return	list<CObjInterface*>*	
*/
list<CObjInterface*>* CSATDoc::GetObjList(){return m_plstObj;}

/**	\brief	The CSATDoc::SetSATVer function

	\param	nSATVer	a parameter of type const int&

	\return	void	
*/
void CSATDoc::SetSATVer(const int& nSATVer){m_nSATVer = nSATVer;}

/**	\brief	The CSATDoc::GetSATVer function


	\return	const char*	
*/
const int CSATDoc::GetSATVer(){return m_nSATVer;}
