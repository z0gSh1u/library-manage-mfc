#pragma once

// CReader ÃüÁîÄ¿±ê

#include <vector>
using namespace std;

#define MAX_LOAN_COUNT 2

class CReader : public CObject
{
public:
	DECLARE_SERIAL(CReader)

	// @ get null reader
	static CReader getNullReader();
	CReader();
	virtual ~CReader();
	virtual void Serialize(CArchive& ar);
	// @ overload default copy constructor
	CReader(const CReader &a);
	// @ overload default operator =
	CReader& operator = (const CReader& a);

	CString readerName;
	int readerNo;
	int nowLoanCount;
	
	vector<int> BaD_LoginNo;
	vector<CString> BaD_Date;

};


