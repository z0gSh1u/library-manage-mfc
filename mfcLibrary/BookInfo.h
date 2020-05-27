#pragma once

#include "Reader.h"
#include <vector>
using namespace std;

// CBookInfo ����Ŀ��

class CBookInfo : public CObject
{
public:
	DECLARE_SERIAL(CBookInfo)

	// ����
	CBookInfo();
	virtual ~CBookInfo();
	virtual void Serialize(CArchive& ar);

	// ����
	// ע��һ��������ж౾������ÿ�������ɵ�¼��Ψһ��ʶ
	int leftCount; // ʣ������
	int totalCount; // ������
	CString bookName; // ����
	CString bookNo; // ��Ŀ���
	CString authorName; // ������
	vector<int> out_LoginNo; // ��������ĵ�¼��
	vector<CReader> out_Reader; // ��������Ķ���


	// @ overload default copy constructor
	CBookInfo(const CBookInfo &a);
	// @ overload default operator =
	CBookInfo& operator = (const CBookInfo& a);

};


