
// keepkeyDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Str_DES.h"


// CkeepkeyDlg 对话框
class DataAccessBase;

class CkeepkeyDlg : public CDialog
{
// 构造
public:
	CkeepkeyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KEEPKEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreateitem();
	afx_msg void OnBnClickedFinditem();
	afx_msg void OnBnClickedShowallkey();
	afx_msg void OnNMClickKeylist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDelitem();
	afx_msg void OnBnClickedChangeitem();
	afx_msg void OnBnClickedCountButton();
	afx_msg void OnBnClickedKeyButton();


	bool CheckInPutIsEmpty(CString str);
	bool InitDB();
	bool InitDataList();
	BOOL ReShowDataList(bool bShowAll);
	void ClearDataList();
	void RefreshList();
	void ChangeVisableStyle();
	bool CopyStringToClipboard(CString str);


	enum EButtonState
	{
		DEFAULT,
		CHANGED
	};

	CListCtrl		m_KeyList;
	_ConnectionPtr	m_pConnection;  
	_CommandPtr		m_pCommand;
	_RecordsetPtr	m_pRecordset;
	//_variant_t		RecordsAffected;

	long			m_curSelID;
	EButtonState	m_ShowAllButtomState;
	CString			m_cstrKey;
	CStr_DES		m_Cstr_des;
	DataAccessBase  *m_pDataBase;
//	afx_msg void OnClose();
//	afx_msg void OnDestroy();
};
