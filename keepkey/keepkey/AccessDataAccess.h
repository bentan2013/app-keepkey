/********************************************************************
	created:	2012/02/04
	created:	4:2:2012   11:57
	filename: 	f:\project\a±à³ÌÑ§Ï°\app_KeepKey\keepkey\keepkey\AccessDataAccess.h
	author:		tanben
	
	purpose:	
*********************************************************************/
#pragma once
#include "dataaccessbase.h"

class AccessDataAccess :
	public DataAccessBase
{
public:
	AccessDataAccess(void);
	~AccessDataAccess(void);
	bool InitDB(_bstr_t ConnectionString, 
		_bstr_t UserID, 
		_bstr_t Password, 
		long Options );
	bool DeleteItem(const _variant_t & Source, const long itemID);
	bool ModifyItem(const _variant_t & Source, const _variant_t & Index, void* pOld, void *pNew);

};
