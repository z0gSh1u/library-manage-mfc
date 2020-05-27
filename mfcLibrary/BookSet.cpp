// BookSet.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcLibrary.h"
#include "BookSet.h"


// CBookSet

CBookSet::CBookSet()
{
	currentTailLoginNo = 0;
}

CBookSet::~CBookSet()
{
}

bool CBookSet::insertNewBook(CBookInfo book)
{
	books.push_back(book);
	return true;
}

// CBookSet 成员函数

IMPLEMENT_SERIAL(CBookSet, CObject, 1)
void CBookSet::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << currentTailLoginNo;
		ar << books.size();
		for (int i = 0; i < books.size(); i++)
		{
			ar << books.at(i).authorName;
			ar << books.at(i).bookName;
			ar << books.at(i).bookNo;
			ar << books.at(i).leftCount;
			ar << books.at(i).totalCount;
			ar << books.at(i).out_LoginNo.size();
			for (int j = 0; j < books.at(i).out_LoginNo.size(); j++)
				ar << books.at(i).out_LoginNo.at(j);
			ar << books.at(i).out_Reader.size();
			for (int j = 0; j < books.at(i).out_Reader.size(); j++)
			{
				ar << books.at(i).out_Reader.at(j).readerName;
				ar << books.at(i).out_Reader.at(j).readerNo;
				ar << books.at(i).out_Reader.at(j).nowLoanCount;
				ar << books.at(i).out_Reader.at(j).BaD_LoginNo.size();
				for (int k = 0; k < books.at(i).out_Reader.at(j).BaD_LoginNo.size(); k++)
					ar << books.at(i).out_Reader.at(j).BaD_LoginNo.at(k);
				ar << books.at(i).out_Reader.at(j).BaD_Date.size();
				for (int k = 0; k < books.at(i).out_Reader.at(j).BaD_Date.size(); k++)
					ar << books.at(i).out_Reader.at(j).BaD_Date.at(k);
			}
		}
	}
	else
	{
		ar >> currentTailLoginNo;
		int books_size;
		ar >> books_size;
		books.resize(books_size);
		for (int i = 0; i < books_size; i++)
		{
			ar >> books.at(i).authorName;
			ar >> books.at(i).bookName;
			ar >> books.at(i).bookNo;
			ar >> books.at(i).leftCount;
			ar >> books.at(i).totalCount;
			int out_LoginNo_size;
			ar >> out_LoginNo_size;
			books.at(i).out_LoginNo.resize(out_LoginNo_size);
			for (int j = 0; j < out_LoginNo_size; j++)
				ar >> books.at(i).out_LoginNo.at(j);
			int out_Reader_size;
			ar >> out_Reader_size;
			books.at(i).out_Reader.resize(out_Reader_size);
			for (int j = 0; j < out_Reader_size; j++)
			{
				ar >> books.at(i).out_Reader.at(j).readerName;
				ar >> books.at(i).out_Reader.at(j).readerNo;
				ar >> books.at(i).out_Reader.at(j).nowLoanCount;
				int Bad_LoginNo_size;
				ar >> Bad_LoginNo_size;
				books.at(i).out_Reader.at(j).BaD_LoginNo.resize(Bad_LoginNo_size);
				for (int k = 0; k < Bad_LoginNo_size; k++)
					ar >> books.at(i).out_Reader.at(j).BaD_LoginNo.at(k);
				int Bad_Reader_size;
				ar >> Bad_Reader_size;
				books.at(i).out_Reader.at(j).BaD_Date.resize(Bad_Reader_size);
				for (int k = 0; k < Bad_Reader_size; k++)
					ar >> books.at(i).out_Reader.at(j).BaD_Date.at(k);
			}
		}
	}
}

// @ overload copy constructor
CBookSet::CBookSet(const CBookSet &a)
{
	// @ self assignment check
	if (this == &a) 
		return;
	this->currentTailLoginNo = a.currentTailLoginNo;
	this->books.clear();
	for (int i = 0; i < a.books.size(); i++)
		this->books.push_back(a.books.at(i));
}

// @ overload =
CBookSet& CBookSet::operator = (const CBookSet& a)
{
	// @ self assignment check
	if (this == &a) 
		return *this;
	this->currentTailLoginNo = a.currentTailLoginNo;
	this->books.clear();
	for (int i = 0; i < a.books.size(); i++)
		this->books.push_back(a.books.at(i));
	return *this;
}
