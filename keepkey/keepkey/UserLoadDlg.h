#pragma once


// UserLoadDlg dialog

class UserLoadDlg : public CDialog
{
	DECLARE_DYNAMIC(UserLoadDlg)

public:
	UserLoadDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~UserLoadDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedModify();
};
