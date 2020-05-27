// Reader.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "Reader.h"

IMPLEMENT_SERIAL(CReader, CObject, 1)

// CReader

CReader::CReader()
{
	readerName = _T("");
	readerNo = 0;
	nowLoanCount = 0;
}

CReader::~CReader()
{
}

// @ get null reader
CReader CReader::getNullReader()
{
	CReader a;
	a.nowLoanCount = 0; 
	a.readerName = "_CONST_NULL_READER";
	a.readerNo = -1;
	return a;
}

// @ overload copy constructor
CReader::CReader(const CReader &a)
{
	// @ self assignment check
	if (this == &a) 
		return;
	this->readerName = a.readerName;
	this->readerNo = a.readerNo;
	this->nowLoanCount = a.nowLoanCount;
	BaD_LoginNo.clear();
	for (int i = 0; i < a.BaD_LoginNo.size(); i++)
		BaD_LoginNo.push_back(a.BaD_LoginNo.at(i));
	BaD_Date.clear();
	for (int i = 0; i < a.BaD_Date.size(); i++)
		BaD_Date.push_back(a.BaD_Date.at(i));
}

// @ overload =
CReader& CReader::operator =(const CReader& a)
{
	// @ self assignment check
	if (this == &a) 
		return *this;
	this->readerName = a.readerName;
	this->readerNo = a.readerNo;
	this->nowLoanCount = a.nowLoanCount;
	BaD_LoginNo.clear();
	for (int i = 0; i < a.BaD_LoginNo.size(); i++)
		BaD_LoginNo.push_back(a.BaD_LoginNo.at(i));
	BaD_Date.clear();
	for (int i = 0; i < a.BaD_Date.size(); i++)
		BaD_Date.push_back(a.BaD_Date.at(i));
	return *this;
}


// CReader 成员函数


void CReader::Serialize(CArchive& ar)
{
	//CObject::Serialize(ar);
}
