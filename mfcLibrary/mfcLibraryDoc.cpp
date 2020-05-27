
// mfcLibraryDoc.cpp : CmfcLibraryDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mfcLibrary.h"
#endif

#include "mfcLibraryDoc.h"
#include "MainFrm.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CmfcLibraryDoc

IMPLEMENT_DYNCREATE(CmfcLibraryDoc, CDocument)

BEGIN_MESSAGE_MAP(CmfcLibraryDoc, CDocument)
	ON_COMMAND(ID_32773, &CmfcLibraryDoc::On32773)
	ON_COMMAND(ID_32774, &CmfcLibraryDoc::On32774)
END_MESSAGE_MAP()


// CmfcLibraryDoc 构造/析构

CmfcLibraryDoc::CmfcLibraryDoc()
{
	// TODO: 在此添加一次性构造代码
	leftListCtrl = NULL;
}

CmfcLibraryDoc::~CmfcLibraryDoc()
{
}

BOOL CmfcLibraryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

// CmfcLibraryDoc 序列化

void CmfcLibraryDoc::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
	bookSet.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CmfcLibraryDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CmfcLibraryDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CmfcLibraryDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CmfcLibraryDoc 诊断

#ifdef _DEBUG
void CmfcLibraryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CmfcLibraryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CmfcLibraryDoc 命令


BOOL CmfcLibraryDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDocument::OnSaveDocument(lpszPathName);
}


void CmfcLibraryDoc::On32773()
{
	// TODO: 在此添加命令处理程序代码
	// CTRL + S
	INPUT input[4];
	memset(input, 0, sizeof(input));
	input[0].type = input[1].type = input[2].type = input[3].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[2].ki.wVk = VK_CONTROL;
	input[1].ki.wVk = input[3].ki.wVk = 'S';
	input[2].ki.dwFlags = input[3].ki.dwFlags = KEYEVENTF_KEYUP;
	Sleep(50 );
	SendInput(4, input, sizeof(INPUT));
}


void CmfcLibraryDoc::On32774()
{
	// TODO: 在此添加命令处理程序代码
	// CTRL + O
	INPUT input[4];
	memset(input, 0, sizeof(input));
	input[0].type = input[1].type = input[2].type = input[3].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[2].ki.wVk = VK_CONTROL;
	input[1].ki.wVk = input[3].ki.wVk = 'O';
	input[2].ki.dwFlags = input[3].ki.dwFlags = KEYEVENTF_KEYUP;
	Sleep(50);
	SendInput(4, input, sizeof(INPUT));
}

