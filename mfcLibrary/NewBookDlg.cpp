// NewBookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "NewBookDlg.h"
#include "afxdialogex.h"


// @ cfont memory pool
std::stack<CFont*> cfontPool_newDlg;

// CNewBookDlg 对话框

IMPLEMENT_DYNAMIC(CNewBookDlg, CDialog)

CNewBookDlg::CNewBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewBookDlg::IDD, pParent)
	, m_bookname(_T(""))
	, m_authname(_T(""))
	, m_bookno(_T(""))
	, m_totalamt(_T(""))
{

}

CNewBookDlg::~CNewBookDlg()
{
}

void CNewBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, NBK_bookname, m_bookname);
	DDX_Text(pDX, NBK_authname, m_authname);
	DDX_Text(pDX, NBK_bookno, m_bookno);
	DDX_Text(pDX, NBK_totalamt, m_totalamt);
}


BEGIN_MESSAGE_MAP(CNewBookDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CNewBookDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewBookDlg 消息处理程序



BOOL CNewBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// @ font set
	auto f1 = zx::makeMFCFont(30, true, "黑体");
	cfontPool_newDlg.push(f1);
	GetDlgItem(NBK_banner)->SetFont(f1);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CNewBookDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	// @ free font
	zx::freeFont(cfontPool_newDlg);
	return CDialog::DestroyWindow();
}


void CNewBookDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	STUPD
		if (m_bookname == "" || m_authname == "" || m_bookno == "" || m_totalamt == "")
		{
			zx::wrongInfo("有项目为空！", "错误");
			EDUPD
			return;
		}
		int cnt = (int)zx::str2df(zx::cstr2str(m_totalamt));
	EDUPD
	if (cnt > 1000)
		zx::wrongInfo("一次性添加过多，请分次添加！", "错误");
	else
		CDialog::OnOK();
}
