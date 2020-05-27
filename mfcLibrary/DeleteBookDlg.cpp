// DeleteBookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "DeleteBookDlg.h"
#include "afxdialogex.h"

using namespace zx;


// @ cfont memory pool
std::stack<CFont*> cfontPool_delDlg;

// CDeleteBookDlg 对话框

IMPLEMENT_DYNAMIC(CDeleteBookDlg, CDialog)

CDeleteBookDlg::CDeleteBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteBookDlg::IDD, pParent)
	, m_outLoginNo(_T(""))
	, m_bookName(_T(""))
	, m_authorName(_T(""))
{

}

CDeleteBookDlg::~CDeleteBookDlg()
{
}

void CDeleteBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, DLB_loginNo, m_outLoginNo);
	DDX_Text(pDX, IDC_EDIT2, m_bookName);
	DDX_Text(pDX, IDC_EDIT3, m_authorName);
}


BEGIN_MESSAGE_MAP(CDeleteBookDlg, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(LBK_checkBtn, &CDeleteBookDlg::OnBnClickedcheckbtn)
	ON_BN_CLICKED(IDOK, &CDeleteBookDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDeleteBookDlg 消息处理程序


BOOL CDeleteBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// @ font set
	auto f1 = zx::makeMFCFont(30, true, "黑体");
	cfontPool_delDlg.push(f1);
	GetDlgItem(DBK_banner)->SetFont(f1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDeleteBookDlg::OnDestroy()
{
	CDialog::OnDestroy();
	zx::freeFont(cfontPool_delDlg);
}


void CDeleteBookDlg::OnBnClickedcheckbtn()
{
	CListCtrl& indexLC = _GETLISTCTRLANYWHERE;
	
	int type_col = 0;
	STUPD
		CString toFind = m_outLoginNo;
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


void CDeleteBookDlg::OnBnClickedOk()
{
	CDialog::OnOK();
}
