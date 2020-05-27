#pragma once


// CDeleteBookDlg 对话框

class CDeleteBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeleteBookDlg)

public:
	CDeleteBookDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeleteBookDlg();

// 对话框数据
	enum { IDD = IDD_DELETEBOOKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
