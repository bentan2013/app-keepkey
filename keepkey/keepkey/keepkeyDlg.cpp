
// keepkeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "keepkey.h"
#include "keepkeyDlg.h"
#include "CommonMacro.h"
#include "AccessDataAccess.h"
#include "UserLoadDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()




CkeepkeyDlg::CkeepkeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CkeepkeyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CkeepkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KEYLIST, m_KeyList);
}

BEGIN_MESSAGE_MAP(CkeepkeyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CREATEITEM, &CkeepkeyDlg::OnBnClickedCreateitem)
	ON_BN_CLICKED(IDC_FINDITEM, &CkeepkeyDlg::OnBnClickedFinditem)
	ON_BN_CLICKED(IDC_SHOWALLKEY, &CkeepkeyDlg::OnBnClickedShowallkey)
	ON_NOTIFY(NM_CLICK, IDC_KEYLIST, &CkeepkeyDlg::OnNMClickKeylist)
	ON_BN_CLICKED(IDC_DELITEM, &CkeepkeyDlg::OnBnClickedDelitem)
	ON_BN_CLICKED(IDC_CHANGEITEM, &CkeepkeyDlg::OnBnClickedChangeitem)
//	ON_WM_CLOSE()
//	ON_WM_DESTROY()
ON_BN_CLICKED(IDC_COUNT_BUTTON, &CkeepkeyDlg::OnBnClickedCountButton)
ON_BN_CLICKED(IDC_KEY_BUTTON, &CkeepkeyDlg::OnBnClickedKeyButton)
END_MESSAGE_MAP()


bool CkeepkeyDlg::InitDB()
{
	// ��ʼ��COM,����ADO���ӵȲ���
	if (!AfxOleInit()) {
		AfxMessageBox(L"OLE/COM��ʼ��ʧ��");
		return FALSE;
	}

	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance(__uuidof(Connection));
		if(SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=keyDB.mdb","","",adModeUnknown);///����
		}
	}
	catch(_com_error e)///��׽�쳣
	{
		CString errormessage;
		errormessage.Format(L"�������ݿ�ʧ��!\r������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///��ʾ������Ϣ
	}
}

void CkeepkeyDlg::ClearDataList()
{
	m_KeyList.DeleteAllItems();
}

//������ʾ
BOOL CkeepkeyDlg::ReShowDataList(bool bShowAll)
{
	ClearDataList();

	int nRowum = 0;
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->Open("SELECT * FROM [key]",                // ��ѯDemoTable���������ֶ�
		_variant_t((IDispatch *)m_pConnection,true),	 // ��ȡ��ӿ��IDispatchָ��
		adOpenDynamic,
		adLockOptimistic,
		adCmdText);
	_variant_t vDescript,vCount,vPassword;          
	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(L"��������Ϊ��");
			return false;
		}
		CString strtemp;
		while (!m_pRecordset->adoEOF)
		{
			strtemp = "";
			vDescript = m_pRecordset->GetCollect("����");
			vCount = m_pRecordset->GetCollect("�˺�");
			vPassword = m_pRecordset->GetCollect("����");
			
			//����
			vDescript = m_Cstr_des.Decode(vDescript);
			vCount = m_Cstr_des.Decode(vCount);
			vPassword = m_Cstr_des.Decode(vPassword);

			long curInsertItem;

			if(vDescript.vt != VT_NULL)
			{
				curInsertItem = m_pRecordset->GetCollect("ID");
				strtemp = (LPCTSTR)(_bstr_t)vDescript;
				m_KeyList.InsertItem(nRowum, strtemp);
				m_KeyList.SetItemData(nRowum, curInsertItem);

				if (bShowAll)
				{
					strtemp = (LPCTSTR)(_bstr_t)vCount;
					m_KeyList.SetItemText(nRowum, 1, strtemp);
					strtemp = (LPCTSTR)(_bstr_t)vPassword;
					m_KeyList.SetItemText(nRowum, 2, strtemp);
				}
				else
				{
					strtemp = L"******";
					m_KeyList.SetItemText(nRowum, 1, strtemp);
					m_KeyList.SetItemText(nRowum, 2, strtemp);
				}
			}

			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset=NULL;
	return TRUE;
}

//��ʼ���б�
bool CkeepkeyDlg::InitDataList()
{
	ChangeVisableStyle();

	m_KeyList.InsertColumn(0, L"����", LVCFMT_LEFT,  200, 0);
	m_KeyList.InsertColumn(1, L"�˺�", LVCFMT_LEFT,  160, 1);
	m_KeyList.InsertColumn(2, L"����", LVCFMT_LEFT,  80, 2);

	ReShowDataList(false);

	return true;
}

BOOL CkeepkeyDlg::OnInitDialog()
{
	UserLoadDlg login_dlg;
	INT_PTR hr;
	if (IDCANCEL == login_dlg.DoModal())
	{
		exit(1);
	}

	CDialog::OnInitDialog();


	WCHAR wChar[8] = L"china";
	char key[8];
	memset(key, 0, 8);
	memcpy(key, wChar, 8);
	m_Cstr_des.SetKey(key, 8);


	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_ShowAllButtomState = DEFAULT;

	InitDB();
	InitDataList();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CkeepkeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CkeepkeyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CkeepkeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�������
bool CkeepkeyDlg::CheckInPutIsEmpty(CString str)
{
	if (str == "")
	{
		return false;
	}
}

//������Ŀ
void CkeepkeyDlg::OnBnClickedCreateitem()
{
	// TODO: Add your control notification handler code here
	CString strDescript;
	CString strCount;
	CString strPassword;
	GetDlgItemText(IDC_DESCRIPT, strDescript);
	GetDlgItemText(IDC_COUNT, strCount);
	GetDlgItemText(IDC_PASSWORD, strPassword);

 	if (   !CheckInPutIsEmpty(strCount) 
 		|| !CheckInPutIsEmpty(strCount)
 		|| !CheckInPutIsEmpty(strPassword))
 	{
 		AfxMessageBox(L"Input empty");
 	}

	m_pRecordset.CreateInstance(__uuidof(Recordset));
 	try
	{
 		m_pRecordset->Open("SELECT * FROM [key]",                // ��ѯDemoTable���������ֶ�
 			_variant_t((IDispatch *)m_pConnection,true),	 // ��ȡ��ӿ��IDispatchָ��
 			adOpenDynamic,
 			adLockOptimistic,
 			adCmdText);
 		m_pRecordset->AddNew();                         //�����ַ���������ݾͱ�����open ���ִ��SQL���

		//����
		CString strDescript_jiami = m_Cstr_des.Encode(strDescript);
		CString strCount_jiami = m_Cstr_des.Encode(strCount);
		CString strPassword_jiami = m_Cstr_des.Encode(strPassword);

	
		m_pRecordset->PutCollect("����", _variant_t(strDescript_jiami));
		m_pRecordset->PutCollect("�˺�", _variant_t(strCount_jiami));
		m_pRecordset->PutCollect("����", _variant_t(strPassword_jiami));


 		m_pRecordset->Update();
 		m_pRecordset->Close();
		AfxMessageBox(L"����ɹ�!");
	}
 	catch(_com_error *e)
 	{
 		AfxMessageBox(e->ErrorMessage());
 	}
 	m_pRecordset=NULL;

	RefreshList();
}

//ˢ���б�
void CkeepkeyDlg::RefreshList()
{
	ReShowDataList(m_ShowAllButtomState);
}

void CkeepkeyDlg::ChangeVisableStyle()
{
	ListView_SetExtendedListViewStyleEx(m_KeyList.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
}

//����
void CkeepkeyDlg::OnBnClickedFinditem()
{
	// TODO: Add your control notification handler code here
	//�������˺Ŷ���ȷ������ʾ����
	CString strDescript;
	CString strCount;
	CString strPassword;
	GetDlgItemText(IDC_DESCRIPT, strDescript);
	GetDlgItemText(IDC_COUNT, strCount);

	if (   !CheckInPutIsEmpty(strCount) 
		|| !CheckInPutIsEmpty(strCount)
		)
	{
		AfxMessageBox(L"Input empty");
	}

	m_pRecordset.CreateInstance(__uuidof(Recordset));

	m_pRecordset->Open("SELECT * FROM [key]",                // ��ѯDemoTable���������ֶ�
		_variant_t((IDispatch *)m_pConnection,true),	 // ��ȡ��ӿ��IDispatchָ��
		adOpenDynamic,
		adLockOptimistic,
		adCmdText);

	_variant_t vDescript,vCount,vPassword;          

	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(L"��������Ϊ��");
			return;
		}
		CString strtemp;
		while (!m_pRecordset->adoEOF)
		{
			strtemp = "";
			vDescript = m_pRecordset->GetCollect("����");
			//ȡ�õ�1�е�ֵ����0��ʼ��������Ҳ����ֱ���г��е����ƣ�����һ��
			vCount = m_pRecordset->GetCollect("�˺�");
			vPassword = m_pRecordset->GetCollect("����");

			//����
			vDescript = m_Cstr_des.Decode(vDescript);
			vCount = m_Cstr_des.Decode(vCount);
			vPassword = m_Cstr_des.Decode(vPassword);

			if(vDescript.vt != VT_NULL)
			{
				strtemp = (LPCTSTR)(_bstr_t)vDescript;
			}

			if (strtemp != strDescript)
			{
				m_pRecordset->MoveNext();

				continue;
			}

			if(vPassword.vt!= VT_NULL)
			{
				strPassword = (LPCTSTR)(_bstr_t)vPassword;
				strCount	= (LPCTSTR)(_bstr_t)vCount;
			}

			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset=NULL;
	SetDlgItemText(IDC_PASSWORD, strPassword);
	SetDlgItemText(IDC_COUNT, strCount);

}

void CkeepkeyDlg::OnBnClickedShowallkey()
{
	// TODO: Add your control notification handler code here
	if (m_ShowAllButtomState == DEFAULT)
	{
		ReShowDataList(true);
		SetDlgItemText(IDC_SHOWALLKEY, L"��������");
		m_ShowAllButtomState = CHANGED;
	}
	else
	{
		ReShowDataList(false);
		SetDlgItemText(IDC_SHOWALLKEY, L"��ʾ����");
		m_ShowAllButtomState = DEFAULT;

	}
}

//ѡ��
void CkeepkeyDlg::OnNMClickKeylist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	int rowNum = 0;
	int colNum = 0;

	rowNum = pNMItemActivate->iItem;
	colNum = pNMItemActivate->iSubItem;

	if (   rowNum == -1
		|| colNum == -1)
	{
		*pResult = 0;
		return;
	}

	CString strtemp;
	strtemp = m_KeyList.GetItemText(rowNum, 0);
	SetDlgItemText(IDC_DESCRIPT, strtemp);
	strtemp = m_KeyList.GetItemText(rowNum, 1);
	SetDlgItemText(IDC_COUNT, strtemp);
	strtemp = m_KeyList.GetItemText(rowNum, 2);
	SetDlgItemText(IDC_PASSWORD, strtemp);

	m_curSelID = m_KeyList.GetItemData(rowNum);

	*pResult = 0;
}

void CkeepkeyDlg::OnBnClickedDelitem()
{
	// TODO: Add your control notification handler code here
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	m_pRecordset->Open("SELECT * FROM [key]",                // ��ѯDemoTable���������ֶ�
		_variant_t((IDispatch *)m_pConnection,true),	 // ��ȡ��ӿ��IDispatchָ��
		adOpenDynamic,
		adLockOptimistic,
		adCmdText);

	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(L"��������Ϊ��");
			return;
		}
		long thisID;
		while (!m_pRecordset->adoEOF)
		{
			thisID = m_pRecordset->GetCollect("ID");
			if (thisID == m_curSelID)
			{
				m_pRecordset->Delete(adAffectCurrent);             //����adAffectCurrentΪɾ����ǰ��¼
				m_pRecordset->Update();
				m_pRecordset->Close();
				m_pRecordset=NULL;
				RefreshList();
				return;
			}
	
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	m_pRecordset->Close();
	m_pRecordset=NULL;


}

void CkeepkeyDlg::OnBnClickedChangeitem()
{
	// TODO: Add your control notification handler code here
	CString strDescript;
	CString strCount;
	CString strPassword;
	GetDlgItemText(IDC_DESCRIPT, strDescript);
	GetDlgItemText(IDC_COUNT, strCount);
	GetDlgItemText(IDC_PASSWORD, strPassword);
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->Open("SELECT * FROM [key]",                // ��ѯDemoTable���������ֶ�
						_variant_t((IDispatch *)m_pConnection,true),	 // ��ȡ��ӿ��IDispatchָ��
						adOpenDynamic,
						adLockOptimistic,
						adCmdText);

	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox(L"��������Ϊ��");
			return;
		}
		long thisID;
		while (!m_pRecordset->adoEOF)
		{
			thisID = m_pRecordset->GetCollect("ID");
			if (thisID == m_curSelID)
			{
				//����
				strDescript = m_Cstr_des.Encode(strDescript);
				strCount = m_Cstr_des.Encode(strCount);
				strPassword = m_Cstr_des.Encode(strPassword);

				m_pRecordset->PutCollect("����", _variant_t(strDescript));
 				m_pRecordset->PutCollect("�˺�", _variant_t(strCount));
 				m_pRecordset->PutCollect("����", _variant_t(strPassword));
				m_pRecordset->Update();
				m_pRecordset->Close();
				m_pRecordset=NULL;
				RefreshList();
				return;
			}
	
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}

	m_pRecordset->Close();
	m_pRecordset=NULL;
}





//void CkeepkeyDlg::OnClose()
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CDialog::OnClose();
//}

//void CkeepkeyDlg::OnDestroy()
//{
//	CDialog::OnDestroy();
//
//	// TODO: Add your message handler code here
//}

//�����˺�
void CkeepkeyDlg::OnBnClickedCountButton()
{
	// TODO: Add your control notification handler code here
	CString strCount;
//	SetDlgItemText(IDC_PASSWORD, strPassword);
	GetDlgItemText(IDC_COUNT, strCount);
	if (strCount != L'')
	{
		if (!CopyStringToClipboard(strCount))
		{
			AfxMessageBox(L"Clipboard erro!");
			return;
		}
	}

}

//��������
void CkeepkeyDlg::OnBnClickedKeyButton()
{
	CString strPassword;
	GetDlgItemText(IDC_PASSWORD, strPassword);
	if (strPassword != L'')
	{
		if (!CopyStringToClipboard(strPassword))
		{
			AfxMessageBox(L"Clipboard erro!");
			return;
		}
	}
}

//�����ַ�����������
bool CkeepkeyDlg::CopyStringToClipboard(CString str)
{
	std::string asciiStr = StrConvTools::U2M(str.GetBuffer());
	int nLen = asciiStr.length() + 1;
	HGLOBAL    hglbCopy;
	if (!(hglbCopy = GlobalAlloc(GHND, nLen)))
	{
		CloseClipboard();
		return false;
	}
	char *pCopyChar = (char *)GlobalLock(hglbCopy);
	memset(pCopyChar, 0, nLen);
	memcpy(pCopyChar, asciiStr.c_str(), nLen - 1);
	GlobalUnlock(pCopyChar);
	OpenClipboard();
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hglbCopy);
	CloseClipboard();
	return true;
}






