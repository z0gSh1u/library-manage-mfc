#pragma once

#include "stdafx.h"
#include "BookInfo.h"

#include <vector>
using namespace std;
// CBookSet ÃüÁîÄ¿±ê

class CBookSet : public CObject
{
public:
	DECLARE_SERIAL(CBookSet)
	CBookSet();
	virtual ~CBookSet();
	virtual void Serialize(CArchive& ar);

	// @ add-ons
	vector<CBookInfo> books;
	int currentTailLoginNo;

	bool insertNewBook(CBookInfo book);

	// @ overload default copy constructor
	CBookSet(const CBookSet &a);
	// @ overload default operator =
	CBookSet& operator = (const CBookSet& a);
};


