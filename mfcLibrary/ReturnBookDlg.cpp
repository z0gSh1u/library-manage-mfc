// ReturnBookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "ReturnBookDlg.h"
#include "afxdialogex.h"

// @ cfont memory pool
std::stack<CFont*> cfontPool_rtnDlg;

// CReturnBookDlg �Ի���

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


// CReturnBookDlg ��Ϣ�������


BOOL CReturnBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// @ font set
	auto f1 = zx::makeMFCFont(30, true, "����");
	cfontPool_rtnDlg.push(f1);
	GetDlgItem(RTN_banner)->SetFont(f1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CReturnBookDlg::OnDestroy()
{
	CDialog::OnDestroy();
	zx::freeFont(cfontPool_rtnDlg);
}
