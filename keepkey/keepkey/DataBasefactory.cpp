#include "StdAfx.h"
#include "DataBasefactory.h"
#include "DataAccessBase.h"
#include "AccessDataAccess.h"

DataBasefactory::DataBasefactory(void)
{
}

DataBasefactory::~DataBasefactory(void)
{
}

DataAccessBase* DataBasefactory::CreateDataBase(E_DataBaseType eDBType)
{
	DataAccessBase *pDB = NULL;
	switch (eDBType)
	{
	case ACCESS:
		pDB = new AccessDataAccess;
		break;
	default:
		break;
	}
	return pDB;
}