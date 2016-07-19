#pragma once

#include <BaseTools.h>
#include <AcisEntity.h>

#include <vector>
#include <map>
using namespace std;

class ON_EXT_CLASS AcisEntityFactory
{
	AcisEntityFactory(const AcisEntityFactory&){}
	AcisEntityFactory& operator =(const AcisEntityFactory&){return (*this);} 
public:
	AcisEntityFactory();
	virtual ~AcisEntityFactory();
public:
	static AcisEntity* CreateEntity(const TCHAR*,const unsigned long&);
};