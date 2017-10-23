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
	// ��ʼ��COM,����ADO���ӵȲ���
	if (!AfxOleInit()) {
		printf("OLE/COM��ʼ��ʧ��");
		return FALSE;
	}

	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance(__uuidof(Connection));
		if(SUCCEEDED(hr))
		{
			hr = m_pConnection->Open(ConnectionString, UserID, Password,adModeUnknown);///����
		}
	}
	catch(_com_error e)///��׽�쳣
	{
		CString errormessage;
		errormessage.Format(L"�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
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
