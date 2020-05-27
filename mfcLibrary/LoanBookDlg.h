#pragma once
#include "afxdtctl.h"
#include "atltime.h"


// CLoanBookDlg 对话框

class CLoanBookDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoanBookDlg)

public:
	CLoanBookDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoanBookDlg();

// 对话框数据
	enum { IDD = IDD_LOANBOOKDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedcheckbtn();
	CString m_toLoanLoginNo;
	CString m_bookName;
	CString m_authorName;
	afx_msg void OnBnClickedOk();
	CString m_readerNo;
	CString m_readerName;
	CDateTimeCtrl m_dateTimeCtrl;
	afx_msg void OnNMKillfocusDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	CTime m_ct_dtpicker;
};
