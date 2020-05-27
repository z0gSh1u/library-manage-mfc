
// mfcLibraryDoc.h : CmfcLibraryDoc ��Ľӿ�
//
#include "stdafx.h"
#include "BookSet.h"

#include <vector>

#pragma once


class CmfcLibraryDoc : public CDocument
{
protected: // �������л�����
	CmfcLibraryDoc();
	DECLARE_DYNCREATE(CmfcLibraryDoc)


// ���� <- bad translation
// @ attributes
public:
	// only need to serialize bookSet
	CBookSet bookSet;

	CListCtrl* leftListCtrl;

// ����
public:


// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CmfcLibraryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32771();
};
