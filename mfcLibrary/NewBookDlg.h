#pragma once


// CNewBookDlg �Ի���

class CNewBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewBookDlg)

public:
	CNewBookDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewBookDlg();

// �Ի�������
	enum { IDD = IDD_NEWBOOKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	CString m_bookname;
	CString m_authname;
	CString m_bookno;
	CString m_totalamt;
	afx_msg void OnBnClickedOk();
};
