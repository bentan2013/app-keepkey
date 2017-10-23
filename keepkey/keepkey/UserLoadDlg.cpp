// UserLoadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "keepkey.h"
#include "UserLoadDlg.h"


// UserLoadDlg dialog

IMPLEMENT_DYNAMIC(UserLoadDlg, CDialog)

UserLoadDlg::UserLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(UserLoadDlg::IDD, pParent)
{

}

UserLoadDlg::~UserLoadDlg()
{
}

void UserLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(UserLoadDlg, CDialog)
	ON_BN_CLICKED(IDC_LOGIN, &UserLoadDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_MODIFY, &UserLoadDlg::OnBnClickedModify)
END_MESSAGE_MAP()


// UserLoadDlg message handlers

void UserLoadDlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	CString strPassword;
	GetDlgItemText(IDC_USERLOAD_PASSOWRD, strPassword);
	if (strPassword == L"china617")
	{
		OnOK();
	}
	else
	{
		AfxMessageBox(L"´íÎóµÄÃÜÂë£¡");
	}
}

void UserLoadDlg::OnBnClickedModify()
{
	// TODO: Add your control notification handler code here
}
