#pragma once


// CNewBookDlg 对话框

class CNewBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewBookDlg)

public:
	CNewBookDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewBookDlg();

// 对话框数据
	enum { IDD = IDD_NEWBOOKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
