/********************************************************************
	created:	2012/02/04
	created:	4:2:2012   11:43
	filename: 	f:\project\a编程学习\app_KeepKey\keepkey\keepkey\DataAccessBase.h
	author:		tanben
	
	purpose:	数据库操作基类
*********************************************************************/
#pragma once

//加入ADO支持库
#ifndef INPORT_ADO_SUPPORT
#define INPORT_ADO_SUPPORT
#import "c:\program files\common files\system\ado\msado15.dll" \
	no_namespace rename ("EOF", "adoEOF")  
#endif


class DataAccessBase
{
public:
	DataAccessBase(void);
	virtual ~DataAccessBase(void);
	virtual bool InitDB(_bstr_t ConnectionString, 
						_bstr_t UserID, 
						_bstr_t Password, 
						long Options ) = 0;
	virtual bool DeleteItem(const _variant_t & Source, const long itemID) = 0;
	virtual bool ModifyItem(const _variant_t & Source, const _variant_t & Index, void* pOld, void *pNew) = 0;

protected:
	CListCtrl		m_KeyList;
	_ConnectionPtr	m_pConnection;  
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;

};
