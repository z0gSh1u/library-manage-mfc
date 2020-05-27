// BookInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "BookInfo.h"

IMPLEMENT_SERIAL(CBookInfo, CObject, 1)

// CBookInfo
CBookInfo::CBookInfo()
{
	bookName = _T("");
	bookNo = _T("");
	authorName = _T("");
	leftCount = 0;
	totalCount = 0;
}

CBookInfo::~CBookInfo()
{
}


// CBookInfo 成员函数

void CBookInfo::Serialize(CArchive& ar)
{
	//CObject::Serialize(ar);
}

// @ overload copy constructor
CBookInfo::CBookInfo(const CBookInfo &a)
{
	// @ self assignment check
	if (this == &a) 
		return;
	authorName = a.authorName;
	bookName = a.bookName;
	bookNo = a.bookNo;
	leftCount = a.leftCount;
	totalCount = a.totalCount;
	out_LoginNo.clear();
	for (int i = 0; i < a.out_LoginNo.size(); i++)
		out_LoginNo.push_back(a.out_LoginNo.at(i));
	out_Reader.clear();
	for (int j = 0; j < a.out_Reader.size(); j++)
		out_Reader.push_back(a.out_Reader.at(j));
}

// @ overload =
CBookInfo& CBookInfo::operator =(const CBookInfo& a)
{
	// @ self assignment check
	if (this == &a) 
		return *this;
	authorName = a.authorName;
	bookName = a.bookName;
	bookNo = a.bookNo;
	leftCount = a.leftCount;
	totalCount = a.totalCount;
	out_LoginNo.clear();
	for (int i = 0; i < a.out_LoginNo.size(); i++)
		out_LoginNo.push_back(a.out_LoginNo.at(i));
	out_Reader.clear();
	for (int j = 0; j < a.out_Reader.size(); j++)
		out_Reader.push_back(a.out_Reader.at(j));
	return *this;
}

