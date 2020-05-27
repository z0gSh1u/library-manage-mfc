
// mfcLibraryDoc.h : CmfcLibraryDoc 类的接口
//
#include "stdafx.h"
#include "BookSet.h"

#include <vector>

#pragma once


class CmfcLibraryDoc : public CDocument
{
protected: // 仅从序列化创建
	CmfcLibraryDoc();
	DECLARE_DYNCREATE(CmfcLibraryDoc)


// 特性 <- bad translation
// @ attributes
public:
	// only need to serialize bookSet
	CBookSet bookSet;

	CListCtrl* leftListCtrl;

// 操作
public:


// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CmfcLibraryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32771();
};
