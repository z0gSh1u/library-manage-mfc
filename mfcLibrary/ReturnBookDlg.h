#pragma once


// CReturnBookDlg �Ի���

class CReturnBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CReturnBookDlg)

public:
	CReturnBookDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReturnBookDlg();

// �Ի�������
	enum { IDD = IDD_RETURNBOOKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	CString m_loginNo;
};
