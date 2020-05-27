// ReturnBookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "ReturnBookDlg.h"
#include "afxdialogex.h"

// @ cfont memory pool
std::stack<CFont*> cfontPool_rtnDlg;

// CReturnBookDlg 对话框

IMPLEMENT_DYNAMIC(CReturnBookDlg, CDialog)

CReturnBookDlg::CReturnBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReturnBookDlg::IDD, pParent)
	, m_loginNo(_T(""))
{

}

CReturnBookDlg::~CReturnBookDlg()
{
}

void CReturnBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_loginNo);
}


BEGIN_MESSAGE_MAP(CReturnBookDlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CReturnBookDlg 消息处理程序


BOOL CReturnBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// @ font set
	auto f1 = zx::makeMFCFont(30, true, "黑体");
	cfontPool_rtnDlg.push(f1);
	GetDlgItem(RTN_banner)->SetFont(f1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CReturnBookDlg::OnDestroy()
{
	CDialog::OnDestroy();
	zx::freeFont(cfontPool_rtnDlg);
}
