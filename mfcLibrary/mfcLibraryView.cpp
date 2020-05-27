
// mfcLibraryView.cpp : CmfcLibraryView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mfcLibrary.h"
#endif

#include "mfcLibraryDoc.h"
#include "mfcLibraryView.h"

#include <vector>
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace zx;

// CmfcLibraryView

IMPLEMENT_DYNCREATE(CmfcLibraryView, CListView)

BEGIN_MESSAGE_MAP(CmfcLibraryView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CmfcLibraryView::OnLvnColumnclick)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CmfcLibraryView::OnNMRClick)
END_MESSAGE_MAP()

// CmfcLibraryView 构造/析构

CmfcLibraryView::CmfcLibraryView()
{
}

CmfcLibraryView::~CmfcLibraryView()
{
}

BOOL CmfcLibraryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style |= LVS_SHOWSELALWAYS | LVS_REPORT | LVS_SORTASCENDING;

	return CListView::PreCreateWindow(cs);
}

void CmfcLibraryView::OnInitialUpdate()
{
	CListView::OnInitialUpdate(); 
	CListCtrl& indexLC = GetListCtrl();
	CmfcLibraryDoc* pDoc = (CmfcLibraryDoc*)GetDocument();
	// @ make it possible to get list ctrl anywhere
	pDoc->leftListCtrl = &GetListCtrl();
	// @ set extended style
	indexLC.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// @ delete former columns when new-file
	while (indexLC.DeleteColumn(0));
	// @ delete all items
	while (indexLC.DeleteItem(0));
	// @ insert columns
	indexLC.InsertColumn(0, "登录号", LVCFMT_LEFT, 80);
	indexLC.InsertColumn(1, "书目编号", LVCFMT_LEFT, 80);
	indexLC.InsertColumn(2, "书名", LVCFMT_LEFT, 200);
	indexLC.InsertColumn(3, "作者名", LVCFMT_LEFT, 100);
	indexLC.InsertColumn(4, "借阅人证号", LVCFMT_LEFT, 90);
	indexLC.InsertColumn(5, "借阅人", LVCFMT_LEFT, 90);
	indexLC.InsertColumn(6, "借阅日期", LVCFMT_LEFT, 110);
	indexLC.InsertColumn(7, "已借册数", LVCFMT_LEFT, 80);
	indexLC.InsertColumn(8, "库存册数", LVCFMT_LEFT, 80);

	// same as OnUpdate
	// @ when receive Update message
	// @ process update message
	// @ re-scan the whole doc, re-print it all
	CBookSet& bookSet = pDoc->bookSet;
	vector<CBookInfo>& bookArr = bookSet.books;
	// @ all book info now in bookArr
	// @ delete all old data
	indexLC.DeleteAllItems();
	// @ print
	int cr = 0;
	for (int i = 0; i < bookArr.size(); i++)
	{
		// @ copy loan status
		for (int j = 0; j < bookArr.at(i).out_LoginNo.size(); j++)
		{
			indexLC.InsertItem(cr, "");
			indexLC.SetItemText(cr, 0, str2cstr(int2str(bookArr.at(i).out_LoginNo.at(j)))); // login number
			
			indexLC.SetItemText(cr, 1, bookArr.at(i).bookNo);
			indexLC.SetItemText(cr, 2, bookArr.at(i).bookName);
			indexLC.SetItemText(cr, 3, bookArr.at(i).authorName);
 			if (bookArr.at(i).out_Reader.at(j).readerNo == -1)
			{
				indexLC.SetItemText(cr, 4, ""); // loan-er no
				indexLC.SetItemText(cr, 5, ""); // loan-er name
				indexLC.SetItemText(cr, 6, ""); // borrow date
			}
			else
			{ 
				indexLC.SetItemText(cr, 4, str2cstr(zx::int2str(bookArr.at(i).out_Reader.at(j).readerNo))); // loan-er no
				indexLC.SetItemText(cr, 5, bookArr.at(i).out_Reader.at(j).readerName); // loan-er name
				// borrow date:
				for (int k = 0; k < bookArr.at(i).out_Reader.at(j).BaD_Date.size(); k++)
					if (bookArr.at(i).out_Reader.at(j).BaD_LoginNo.at(k) == bookArr.at(i).out_LoginNo.at(j))
					{
						indexLC.SetItemText(cr, 6, bookArr.at(i).out_Reader.at(j).BaD_Date.at(k));
						break;
					}
			}
			indexLC.SetItemText(cr, 7, str2cstr(int2str(bookArr.at(i).totalCount - bookArr.at(i).leftCount)));
			indexLC.SetItemText(cr, 8, str2cstr(int2str(bookArr.at(i).leftCount)));
		}
	}
}

void CmfcLibraryView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmfcLibraryView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CmfcLibraryView 诊断

#ifdef _DEBUG
void CmfcLibraryView::AssertValid() const
{
	CListView::AssertValid();
}

void CmfcLibraryView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CmfcLibraryDoc* CmfcLibraryView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfcLibraryDoc)));
	return (CmfcLibraryDoc*)m_pDocument;
}
#endif //_DEBUG


// CmfcLibraryView 消息处理程序
bool cmp(CBookInfo& a, CBookInfo& b)
{
	return (a.out_LoginNo.at(0) > b.out_LoginNo.at(0));
}

void CmfcLibraryView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// @ when receive Update message
	// @ process update message

	// @ re-sort bookSet.books vector
	CmfcLibraryDoc* pDoc = (CmfcLibraryDoc*)GetDocument();
	if (!(pDoc->bookSet.books.empty()))
		sort(pDoc->bookSet.books.begin(), pDoc->bookSet.books.end(), cmp);

	// @ re-scan the whole doc, re-print it all
	CBookSet& bookSet = pDoc->bookSet;
	vector<CBookInfo>& bookArr = bookSet.books;
	// @ all book info now in bookArr
	CListCtrl& indexLC = GetListCtrl();

	// @ delete all old data
	indexLC.DeleteAllItems();
	// @ print

	int cr = 0;
	for (int i = 0; i < bookArr.size(); i++)
	{
		// @ copy loan status
		for (int j = 0; j < bookArr.at(i).out_LoginNo.size(); j++)
		{
			indexLC.InsertItem(cr, "");
			indexLC.SetItemText(cr, 0, str2cstr(int2str(bookArr.at(i).out_LoginNo.at(j)))); // login number
			indexLC.SetItemText(cr, 1, bookArr.at(i).bookNo);
			indexLC.SetItemText(cr, 2, bookArr.at(i).bookName);
			indexLC.SetItemText(cr, 3, bookArr.at(i).authorName);
 			if (bookArr.at(i).out_Reader.at(j).readerNo == -1)
			{
				indexLC.SetItemText(cr, 4, ""); // loan-er no
				indexLC.SetItemText(cr, 5, ""); // loan-er name
				indexLC.SetItemText(cr, 6, ""); // borrow date
			}
			else
			{ 
				indexLC.SetItemText(cr, 4, str2cstr(zx::int2str(bookArr.at(i).out_Reader.at(j).readerNo))); // loan-er no
				indexLC.SetItemText(cr, 5, bookArr.at(i).out_Reader.at(j).readerName); // loan-er name
				// borrow date:
				for (int k = 0; k < bookArr.at(i).out_Reader.at(j).BaD_Date.size(); k++)
					if (bookArr.at(i).out_Reader.at(j).BaD_LoginNo.at(k) == bookArr.at(i).out_LoginNo.at(j))
					{
						indexLC.SetItemText(cr, 6, bookArr.at(i).out_Reader.at(j).BaD_Date.at(k));
						break;
					}
			}
			indexLC.SetItemText(cr, 7, str2cstr(int2str(bookArr.at(i).totalCount - bookArr.at(i).leftCount)));
			indexLC.SetItemText(cr, 8, str2cstr(int2str(bookArr.at(i).leftCount)));
		}
	}
}

// @ sort add-ons
int CmfcLibraryView::m_SortColumn = 0;
bool CmfcLibraryView::m_bAsc = false;
int CALLBACK CmfcLibraryView::listCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* pListCtrl = (CListCtrl*) lParamSort; 
    CString strItem1 = pListCtrl->GetItemText(lParam1, m_SortColumn); 
    CString strItem2 = pListCtrl->GetItemText(lParam2, m_SortColumn);     
    if (m_bAsc)   
		return (zx::str2df(zx::cstr2str(strItem2)) < zx::str2df(zx::cstr2str(strItem1)));     
    else
        return (zx::str2df(zx::cstr2str(strItem2)) > zx::str2df(zx::cstr2str(strItem1)));
}

void CmfcLibraryView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	CListCtrl& indexLC = GetListCtrl();
	m_SortColumn = pNMLV->iSubItem;
    m_bAsc = !m_bAsc;
    int count = indexLC.GetItemCount();
    for(int i = 0; i < count; i++)       
        indexLC.SetItemData(i, i);       
    indexLC.SortItems(listCompare, (LPARAM) &indexLC);
	*pResult = 0;
}

void CmfcLibraryView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
