
// keepkeyDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Str_DES.h"


// CkeepkeyDlg �Ի���
class DataAccessBase;

class CkeepkeyDlg : public CDialog
{
// ����
public:
	CkeepkeyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KEEPKEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
