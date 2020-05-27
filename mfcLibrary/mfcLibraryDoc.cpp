
// mfcLibraryDoc.cpp : CmfcLibraryDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CmfcLibraryDoc ����/����

CmfcLibraryDoc::CmfcLibraryDoc()
{
	// TODO: �ڴ����һ���Թ������
	leftListCtrl = NULL;
}

CmfcLibraryDoc::~CmfcLibraryDoc()
{
}

BOOL CmfcLibraryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

// CmfcLibraryDoc ���л�

void CmfcLibraryDoc::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
	bookSet.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CmfcLibraryDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CmfcLibraryDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CmfcLibraryDoc ���

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


// CmfcLibraryDoc ����


BOOL CmfcLibraryDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDocument::OnSaveDocument(lpszPathName);
}


void CmfcLibraryDoc::On32773()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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

