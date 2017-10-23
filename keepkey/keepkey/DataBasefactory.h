/********************************************************************
	created:	2012/02/04
	created:	4:2:2012   18:06
	filename: 	f:\project\a±à³ÌÑ§Ï°\app_KeepKey\keepkey\keepkey\DataBasefactory.h
	author:		tanben
	
	purpose:	
*********************************************************************/
#pragma once

class DataAccessBase;

enum E_DataBaseType
{
	ACCESS,
	MYSQL
};

class DataBasefactory
{
public:
	DataBasefactory(void);
	~DataBasefactory(void);
	DataAccessBase* CreateDataBase(E_DataBaseType eDBType);

};
