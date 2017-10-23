#include "StdAfx.h"
#include "AccessDataAccess.h"

AccessDataAccess::AccessDataAccess(void)
{
}

AccessDataAccess::~AccessDataAccess(void)
{
}

bool AccessDataAccess::InitDB(_bstr_t ConnectionString, 
								_bstr_t UserID, 
								_bstr_t Password, 
								long Options )
{
	// 初始化COM,创建ADO连接等操作
	if (!AfxOleInit()) {
		printf("OLE/COM初始化失败");
		return FALSE;
	}

	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance(__uuidof(Connection));
		if(SUCCEEDED(hr))
		{
			hr = m_pConnection->Open(ConnectionString, UserID, Password,adModeUnknown);///连接
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format(L"连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		wprintf(errormessage);
		return false;
	}
	return true;
}
bool AccessDataAccess::DeleteItem(const _variant_t & Source, const long itemID)
{
	return true;
}

bool AccessDataAccess::ModifyItem(const _variant_t & Source, const _variant_t & Index, void* pOld, void *pNew)
{
	return true;
}
