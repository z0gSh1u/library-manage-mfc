#pragma once


// CReturnBookDlg 对话框

class CReturnBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CReturnBookDlg)

public:
	CReturnBookDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReturnBookDlg();

// 对话框数据
	enum { IDD = IDD_RETURNBOOKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	CString m_loginNo;
};
