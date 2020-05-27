// NewBookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "NewBookDlg.h"
#include "afxdialogex.h"


// @ cfont memory pool
std::stack<CFont*> cfontPool_newDlg;

// CNewBookDlg �Ի���

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


// CNewBookDlg ��Ϣ�������



BOOL CNewBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// @ font set
	auto f1 = zx::makeMFCFont(30, true, "����");
	cfontPool_newDlg.push(f1);
	GetDlgItem(NBK_banner)->SetFont(f1);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CNewBookDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	// @ free font
	zx::freeFont(cfontPool_newDlg);
	return CDialog::DestroyWindow();
}


void CNewBookDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	STUPD
		if (m_bookname == "" || m_authname == "" || m_bookno == "" || m_totalamt == "")
		{
			zx::wrongInfo("����ĿΪ�գ�", "����");
			EDUPD
			return;
		}
		int cnt = (int)zx::str2df(zx::cstr2str(m_totalamt));
	EDUPD
	if (cnt > 1000)
		zx::wrongInfo("һ������ӹ��࣬��ִ���ӣ�", "����");
	else
		CDialog::OnOK();
}
