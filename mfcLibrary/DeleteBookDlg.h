#pragma once


// CDeleteBookDlg �Ի���

class CDeleteBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeleteBookDlg)

public:
	CDeleteBookDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeleteBookDlg();

// �Ի�������
	enum { IDD = IDD_DELETEBOOKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedcheckbtn();
	CString m_outLoginNo;
	CString m_bookName;
	CString m_authorName;
	afx_msg void OnBnClickedOk();
};
