// LoanBookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "LoanBookDlg.h"
#include "afxdialogex.h"

using namespace zx;

// @ cfont memory pool
std::stack<CFont*> cfontPool_loanDlg;

// CLoanBookDlg 对话框

IMPLEMENT_DYNAMIC(CLoanBookDlg, CDialog)

CLoanBookDlg::CLoanBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoanBookDlg::IDD, pParent)
	, m_toLoanLoginNo(_T(""))
	, m_bookName(_T(""))
	, m_authorName(_T(""))
	, m_readerNo(_T(""))
	, m_readerName(_T(""))
	, m_ct_dtpicker(0)
{

}

CLoanBookDlg::~CLoanBookDlg()
{
}

void CLoanBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_toLoanLoginNo);
	DDX_Text(pDX, IDC_EDIT2, m_bookName);
	DDX_Text(pDX, IDC_EDIT3, m_authorName);
	DDX_Text(pDX, IDC_EDIT4, m_readerNo);
	DDX_Text(pDX, IDC_EDIT5, m_readerName);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dateTimeCtrl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_ct_dtpicker);
}


BEGIN_MESSAGE_MAP(CLoanBookDlg, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(LBK_checkBtn, &CLoanBookDlg::OnBnClickedcheckbtn)
	ON_BN_CLICKED(IDOK, &CLoanBookDlg::OnBnClickedOk)
	ON_NOTIFY(NM_KILLFOCUS, IDC_DATETIMEPICKER1, &CLoanBookDlg::OnNMKillfocusDatetimepicker1)
END_MESSAGE_MAP()


// CLoanBookDlg 消息处理程序


BOOL CLoanBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// @ font set
	auto f1 = zx::makeMFCFont(30, true, "黑体");
	cfontPool_loanDlg.push(f1);
	GetDlgItem(LBK_banner)->SetFont(f1);

	// @ current time set
	CTime initTime = CTime::GetCurrentTime();
	STUPD
		m_ct_dtpicker = initTime;
	EDUPD

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLoanBookDlg::OnDestroy()
{
	CDialog::OnDestroy();
	zx::freeFont(cfontPool_loanDlg);
}


void CLoanBookDlg::OnBnClickedcheckbtn()
{
	CListCtrl& indexLC = _GETLISTCTRLANYWHERE;
	
	int type_col = 0;
	STUPD
		CString toFind = m_toLoanLoginNo;
	EDUPD
	if (toFind == "")
	{
		wrongInfo("未输入任何信息！", "错误");
		return;
	}

	bool canFind = false;
	for (int i = 0; i < indexLC.GetItemCount(); i++)
	{
		CString itemText = indexLC.GetItemText(i, type_col);
		if (itemText == toFind)
		{
			STUPD
				m_bookName = indexLC.GetItemText(i, 2);
				m_authorName = indexLC.GetItemText(i, 3);
			EDUPD
			canFind = true;
		}
	}
	if (!canFind)
	{
		wrongInfo("查无此书，请检查登录号输入！", "错误");
		STUPD
			m_bookName = "";
			m_authorName = "";
		EDUPD
	}
}


void CLoanBookDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	STUPD
	if (m_readerNo == "" || m_readerName == "")
	{
		wrongInfo("读者相关信息不全！", "错误");
		EDUPD
		return;
	}
	EDUPD
	CDialog::OnOK();
}


void CLoanBookDlg::OnNMKillfocusDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
