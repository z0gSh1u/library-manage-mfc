#pragma once

#include "Reader.h"
#include <vector>
using namespace std;

// CBookInfo 命令目标

class CBookInfo : public CObject
{
public:
	DECLARE_SERIAL(CBookInfo)

	// 函数
	CBookInfo();
	virtual ~CBookInfo();
	virtual void Serialize(CArchive& ar);

	// 变量
	// 注：一版书可以有多本副本，每个副本由登录号唯一标识
	int leftCount; // 剩余数量
	int totalCount; // 总数量
	CString bookName; // 书名
	CString bookNo; // 书目编号
	CString authorName; // 作者名
	vector<int> out_LoginNo; // 借出副本的登录号
	vector<CReader> out_Reader; // 借出副本的读者


	// @ overload default copy constructor
	CBookInfo(const CBookInfo &a);
	// @ overload default operator =
	CBookInfo& operator = (const CBookInfo& a);

};


