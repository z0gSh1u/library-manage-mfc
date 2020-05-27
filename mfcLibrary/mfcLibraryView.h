
// mfcLibraryView.h : CmfcLibraryView 类的接口
//

#pragma once

static bool _INITUPD_FINISHED = false;

class CmfcLibraryView : public CListView
{
protected: // 仅从序列化创建
	CmfcLibraryView();
	DECLARE_DYNCREATE(CmfcLibraryView)

// 特性
public:
	CmfcLibraryDoc* GetDocument() const;
	


public:
	// @ used for list sorting
	static int m_SortColumn;  // which column 
	static bool m_bAsc; // sort method
	static int CALLBACK listCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CmfcLibraryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFileSave();
	afx_msg void On32773();
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // mfcLibraryView.cpp 中的调试版本
inline CmfcLibraryDoc* CmfcLibraryView::GetDocument() const
   { return reinterpret_cast<CmfcLibraryDoc*>(m_pDocument); }
#endif

