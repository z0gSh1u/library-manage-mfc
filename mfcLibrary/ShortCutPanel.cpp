// ShortCutPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "ShortCutPanel.h"

// @ add-ons
#include "zx_betterMFC.h"
#include "Reader.h"
#include <stack>
#include <algorithm>
#include <iterator>
#include "mfcLibraryDoc.h"

using namespace zx;

// @ cfont memory pool
std::stack<CFont*> RIGHT_cfontPool;

// CShortCutPanel

IMPLEMENT_DYNCREATE(CShortCutPanel, CFormView)

CShortCutPanel::CShortCutPanel()
	: CFormView(CShortCutPanel::IDD)
	, m_search_bookname(_T(""))
	, m_search_bookno(_T(""))
	, m_search_loginno(_T(""))
	, m_readerno(_T(""))
{

}

CShortCutPanel::~CShortCutPanel()
{
	// @ like onDestory(), free fonts here
	zx::freeFont(RIGHT_cfontPool);
}

void CShortCutPanel::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, SEARCHBOOK_byName, m_search_bookname);
	DDX_Text(pDX, SEARCHBOOK_byNo, m_search_bookno);
	DDX_Text(pDX, SERACHBOOK_byLogin, m_search_loginno);
	DDX_Text(pDX, SEARCHREADER_readerno, m_readerno);
}

BEGIN_MESSAGE_MAP(CShortCutPanel, CFormView)
	ON_BN_CLICKED(RIGHT_btn_newBook, &CShortCutPanel::OnBnClickedbtnnewbook)
	ON_BN_CLICKED(RIGHT_btn_backupDB, &CShortCutPanel::OnBnClickedbtnbackupdb)
	ON_BN_CLICKED(RIGHT_btn_loadDB, &CShortCutPanel::OnBnClickedbtnloaddb)
	ON_BN_CLICKED(RIGHT_btn_deleteBook, &CShortCutPanel::OnBnClickedbtndeletebook)
	ON_BN_CLICKED(RIGHT_btn_loanBook, &CShortCutPanel::OnBnClickedbtnloanbook)
	ON_BN_CLICKED(RIGHT_btn_returnBook, &CShortCutPanel::OnBnClickedbtnreturnbook)
	ON_BN_CLICKED(RIGHT_btn_searchBook, &CShortCutPanel::OnBnClickedbtnsearchbook)
	ON_BN_CLICKED(RIGHT_btn_searchReader, &CShortCutPanel::OnBnClickedbtnsearchreader)
END_MESSAGE_MAP()


// CShortCutPanel 诊断

#ifdef _DEBUG
void CShortCutPanel::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShortCutPanel::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShortCutPanel 消息处理程序


void CShortCutPanel::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	auto f1 = zx::makeMFCFont(30, true, "黑体"); RIGHT_cfontPool.push(f1);
	GetDlgItem(RIGHT_banner)->SetFont(f1);
}

void CShortCutPanel::OnBnClickedbtnnewbook()
{
	CNewBookDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		// @ fill new book's info
		CBookInfo tmp;
		tmp.authorName = dlg.m_authname;
		tmp.bookName = dlg.m_bookname;
		tmp.bookNo = dlg.m_bookno;
		tmp.totalCount = 
			tmp.leftCount = 
			(int)zx::str2df(zx::cstr2str(dlg.m_totalamt));

		CReader _CONST_NULL_READER = CReader::getNullReader();
		int _CUR_LOGIN_NO = (((CmfcLibraryDoc*)GetDocument())->bookSet.currentTailLoginNo) + 1;
		std::stack<int> loginNumbers; std::stack<int> hintNumbers;
		for (int i = 1; i <= tmp.totalCount; i++)
		{
			loginNumbers.push(_CUR_LOGIN_NO);
			hintNumbers.push(_CUR_LOGIN_NO);
			_CUR_LOGIN_NO++;
		}
		// @ update latest login number
		(((CmfcLibraryDoc*)GetDocument())->bookSet.currentTailLoginNo) = _CUR_LOGIN_NO - 1;
		// @ organize hint messgae
		CString hintMsg = "您本次添加的书籍登录号分别为：\r\n";
		int order = 1;
		reverseStack(hintNumbers);
		while (!loginNumbers.empty())
		{
			hintMsg += "[";
			hintMsg += str2cstr(int2str(order));
			hintMsg += "] ";
			hintMsg += str2cstr(int2str(hintNumbers.top()));
			hintMsg += "\r\n";
			tmp.out_LoginNo.push_back(loginNumbers.top());
			tmp.out_Reader.push_back(_CONST_NULL_READER);
			loginNumbers.pop();
			hintNumbers.pop();
			order++;
		}
		// @ tmp is formed now
		// @ write into document
		CmfcLibraryDoc* pDoc = (CmfcLibraryDoc*)GetDocument();
		pDoc->bookSet.insertNewBook(tmp);
		// @ display hint message
		zx::infoInfo(hintMsg, "成功");
		// @ update list
		pDoc->UpdateAllViews(NULL);
	}
}

void CShortCutPanel::OnBnClickedbtnbackupdb()
{
	// CTRL + S
	zx::pressCtrlCombo('S');
}

void CShortCutPanel::OnBnClickedbtnloaddb()
{
	// CTRL + O
	zx::pressCtrlCombo('O');
}

void CShortCutPanel::OnBnClickedbtndeletebook()
{
	CDeleteBookDlg dlg;
	CmfcLibraryDoc* pDoc = _GETDOCPTR;
	CListCtrl& indexLC = _GETLISTCTRL;
	if (dlg.DoModal() == IDOK)
	{
		CString toDel = dlg.m_outLoginNo;
		int toDelLoginNo = (int)str2df(cstr2str(toDel));
		bool canFind = false;
		for (int i = 0; i < pDoc->bookSet.books.size(); i++)
		{
			for (int j = 0; j < pDoc->bookSet.books.at(i).out_LoginNo.size(); j++)
				if (pDoc->bookSet.books.at(i).out_LoginNo.at(j) == toDelLoginNo)
				{
					canFind = true;
					pDoc->bookSet.books.at(i).out_LoginNo.erase(pDoc->bookSet.books.at(i).out_LoginNo.begin() + j);
					pDoc->bookSet.books.at(i).out_Reader.erase(pDoc->bookSet.books.at(i).out_Reader.begin() + j);
					break;
				}
			// @ no book left
			if (canFind)
			{
				if (pDoc->bookSet.books.at(i).out_LoginNo.empty())
					pDoc->bookSet.books.erase(pDoc->bookSet.books.begin() + i);
				break;
			}
		}
		if (!canFind)
		{
			wrongInfo("找不到该登录号的书籍！", "错误");
			return;
		}
		else
		{
			infoInfo("书籍出库成功！", "信息");
			pDoc->UpdateAllViews(NULL);
			return;
		}
	}
}

void CShortCutPanel::OnBnClickedbtnloanbook()
{
	CLoanBookDlg dlg;
	CmfcLibraryDoc* pDoc = _GETDOCPTR;
	CListCtrl& indexLC = _GETLISTCTRL;
	if (dlg.DoModal() == IDOK)
	{
		// @ collect info
		CString toLoan = dlg.m_toLoanLoginNo;
		CTime m_date = dlg.m_ct_dtpicker;
		CString loanDate = m_date.Format("%Y-%m-%d");

		CReader loaner;
		loaner.readerName = dlg.m_readerName;
		loaner.readerNo = (int)str2df(cstr2str(dlg.m_readerNo));

		// @ check reader loan amount
		int type_col = 4;
		CString toFind = dlg.m_readerNo;
		int cnt = 0;
		for (int i = 0; i < indexLC.GetItemCount(); i++)
		{
			CString itemText = indexLC.GetItemText(i, type_col);
			if (itemText == toFind)
			{
				cnt++;
				loaner.BaD_Date.push_back(indexLC.GetItemText(i, 6));
				loaner.BaD_LoginNo.push_back((int)str2df(cstr2str(indexLC.GetItemText(i, 0))));
			}
		}
		if (cnt >= MAX_LOAN_COUNT)
		{
			wrongInfo("该用户借书量已达到最大值！", "错误");
			return;
		}
		loaner.nowLoanCount = cnt;
		// @ check book left amount
		for (int i = 0; i < pDoc->bookSet.books.size(); i++)
		{
			for (int j = 0; j < pDoc->bookSet.books.at(i).out_LoginNo.size(); j++)
				// this login number book found
				if (pDoc->bookSet.books.at(i).out_LoginNo.at(j) == ((int)(str2df(cstr2str(toLoan)))))
				{
					if (pDoc->bookSet.books.at(i).out_Reader.at(j).readerNo != -1)
					{
						wrongInfo("该书已被借走！", "错误");
						return;
					}
					else
					{
						// @ finish request
						pDoc->bookSet.books.at(i).leftCount--;
						loaner.BaD_LoginNo.push_back(((int)(str2df(cstr2str(toLoan)))));
						loaner.BaD_Date.push_back(loanDate);
						pDoc->bookSet.books.at(i).out_Reader.at(j) = loaner;
						CString toHint = "借书成功！\r\n读者号：" + dlg.m_readerNo + "\r\n登录号：" + toLoan;
						zx::infoInfo(toHint, "提示");
						pDoc->UpdateAllViews(NULL);
						return;
					}
				}
		}
		zx::wrongInfo("查无此书！", "错误");
	}
}

void CShortCutPanel::OnBnClickedbtnreturnbook()
{
	CReturnBookDlg dlg;
	CmfcLibraryDoc* pDoc = _GETDOCPTR;
	CListCtrl& indexLC = _GETLISTCTRL;
	if (dlg.DoModal() == IDOK)
	{
		int status = 0;

		CString toReturn = dlg.m_loginNo;
		int toReLoginNo = (int)str2df(cstr2str(toReturn));

		for (int i = 0; i < pDoc->bookSet.books.size(); i++)
		{
			for (int j = 0; j < pDoc->bookSet.books.at(i).out_LoginNo.size(); j++)
				if (pDoc->bookSet.books.at(i).out_LoginNo.at(j) == toReLoginNo)
					if (pDoc->bookSet.books.at(i).out_Reader.at(j).readerNo != -1)
					{
						status = 1;
						pDoc->bookSet.books.at(i).out_Reader.at(j) = CReader::getNullReader();
						break;
					}
					else
					{
						status = 2;
						break;
					}
			// @ update count variable
			if (status == 1)
			{
				pDoc->bookSet.books.at(i).leftCount++;
				break;
			}
		}
		if (status == 0)
		{
			wrongInfo("找不到登录号为 " + toReturn + " 的书籍！", "错误");
			return;
		}
		else if (status == 1)
		{
			infoInfo("登录号为 " + toReturn + " 的书籍归还成功！", "信息");
			pDoc->UpdateAllViews(NULL);
			return;
		}
		else if (status == 2)
		{
			wrongInfo("登录号为 " + toReturn + " 的书籍没有借出，不可归还！", "错误");
			return;
		}
	}
}

void CShortCutPanel::OnBnClickedbtnsearchbook()
{
	CListCtrl& indexLC = _GETLISTCTRL;
	int type_col;
	CString toFind;
	STUPD
		if (m_search_bookname != "")
		{
			toFind = m_search_bookname;
			type_col = 2;
		}
		else if (m_search_bookno != "")
		{
			toFind = m_search_bookno;
			type_col = 1;
		}
		else if (m_search_loginno != "")
		{
			toFind = m_search_loginno;
			type_col = 0;
		}
		else
		{
			zx::wrongInfo("未输入任何信息！", "错误");
			EDUPD
			return;
		}
	EDUPD

		bool canFind = false;
		for (int i = 0; i < indexLC.GetItemCount(); i++)
		{
			CString itemText = indexLC.GetItemText(i, type_col);
			if (itemText == toFind)
			{
				indexLC.SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
				indexLC.EnsureVisible(i, 0);
				canFind = true;
			}
		}
		if (canFind)
			infoInfo("查找成功！", "信息");
		else
			infoInfo("未能找到相关信息！", "信息");
		indexLC.SetFocus();
}

void CShortCutPanel::OnBnClickedbtnsearchreader()
{
	CListCtrl& indexLC = _GETLISTCTRL;
	int type_col = 4;
	STUPD
		CString toFind = m_readerno;
	EDUPD
	if (toFind == "")
	{
		wrongInfo("未输入任何信息！", "错误");
		return;
	}
	CString toHint = "读者号：" + toFind + " 的查询结果\r\n";

	bool canFind = false;
	for (int i = 0; i < indexLC.GetItemCount(); i++)
	{
		CString itemText = indexLC.GetItemText(i, type_col);
		if (itemText == toFind)
		{
			indexLC.SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
			toHint += "\r\n书名：";
			toHint += indexLC.GetItemText(i, 2);
			toHint += "\r\n登录号：";
			toHint += indexLC.GetItemText(i, 0);
			canFind = true;
		}
	}
	if (!canFind) toHint += "查无此人！";
	infoInfo(toHint, "提示");
	indexLC.SetFocus();
}

