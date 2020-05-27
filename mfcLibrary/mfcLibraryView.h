
// mfcLibraryView.h : CmfcLibraryView ��Ľӿ�
//

#pragma once

static bool _INITUPD_FINISHED = false;

class CmfcLibraryView : public CListView
{
protected: // �������л�����
	CmfcLibraryView();
	DECLARE_DYNCREATE(CmfcLibraryView)

// ����
public:
	CmfcLibraryDoc* GetDocument() const;
	


public:
	// @ used for list sorting
	static int m_SortColumn;  // which column 
	static bool m_bAsc; // sort method
	static int CALLBACK listCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CmfcLibraryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // mfcLibraryView.cpp �еĵ��԰汾
inline CmfcLibraryDoc* CmfcLibraryView::GetDocument() const
   { return reinterpret_cast<CmfcLibraryDoc*>(m_pDocument); }
#endif

