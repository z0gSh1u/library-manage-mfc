#pragma once

// CShortCutPanel ������ͼ

class CShortCutPanel : public CFormView
{
	DECLARE_DYNCREATE(CShortCutPanel)

protected:
	CShortCutPanel();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CShortCutPanel();

public:
	enum { IDD = IDD_SHORTCUTPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedbtnnewbook();
	afx_msg void OnBnClickedbtnloaddb();
	afx_msg void OnBnClickedbtnbackupdb();
	afx_msg void OnBnClickedbtndeletebook();
	afx_msg void OnBnClickedbtnloanbook();
	afx_msg void OnBnClickedbtnreturnbook();
	afx_msg void OnBnClickedbtnsearchbook();
	CString m_search_bookname;
	CString m_search_bookno;
	CString m_search_loginno;
	CString m_readerno;
	afx_msg void OnBnClickedbtnsearchreader();
	afx_msg void On32773();
	afx_msg void On32774();
};


