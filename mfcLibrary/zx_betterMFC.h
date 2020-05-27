/*	zx_betterMFC.h	*/
/*	This header covers some useful functions to make MFC easier to use.
	For example, it omits many default params when using some MFC functions.
	
	VERSION: 2018-07
	For more information, please visit my GitHub.
							github.com/z0gSh1u							*/

#pragma once
#ifndef ZX_BETTERMFC_H_
#define ZX_BETTERMFC_H_

// @ macros
#define STUPD UpdateData(TRUE);
#define EDUPD UpdateData(FALSE);

#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <Windows.h>
#include "stdafx.h"

using std::string;
using std::stringstream;
using std::stack;
using std::queue;

namespace zx
{
// @ simulate ctrl + *
inline void pressCtrlCombo(char with)
{
	INPUT input[4];
	memset(input, 0, sizeof(input));
	input[0].type = input[1].type = input[2].type = input[3].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[2].ki.wVk = VK_CONTROL;
	input[1].ki.wVk = input[3].ki.wVk = with;
	input[2].ki.dwFlags = input[3].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(4, input, sizeof(INPUT));
}

// @ create CFont easier
inline CFont* makeMFCFont
	(int size, bool bold = false, char* fontName = "Arial",
	bool italic = false, bool underline = false)
{
	CFont* res = new CFont;
	res->CreateFont
		(size,0,0,0,(bold ? FW_BOLD : 0),italic,underline,0,ANSI_CHARSET, \
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, \
		DEFAULT_PITCH | FF_SWISS, fontName);
	return res;
}

// @ convert STL string to MFC CString
inline CString str2cstr 
	(string& src)
{
	CString res = src.c_str();
	return res;
}

// @ convert MFC CString to STL string
inline string cstr2str
	(CString &src)
{
	string res = src;
	return res;
}

// @ replace all 'from' to 'to'
inline bool replaceAll
	(string &src, string from, string to)
{
	string::size_type 
		pos = 0,
		frmLen = from.size(),
		toLen = to.size();
	pos = src.find(from, pos);
	while ((pos != string::npos))
	{
		src.replace(pos, frmLen, to);
		pos = pos = src.find(from, toLen);
	}
	return true;
}

// @ wrong info msgbox
inline void wrongInfo
	(LPCSTR text, LPCSTR title)
{
	::MessageBox(NULL, text, title, MB_OK | MB_ICONERROR);
}

// @ common info msgbox
inline void commonInfo
	(LPCSTR text, LPCSTR title)
{
	::MessageBox(NULL, text, title, MB_OK);
}

// @ tick info msgbox
inline void infoInfo
	(LPCSTR text, LPCSTR title)
{
	::MessageBox(NULL, text, title, MB_OK | MB_ICONINFORMATION);
}

// @ convert an int into string
inline string int2str
	(int a)
{
	stringstream ss;
	ss << a;
	string res;
	res = ss.str();
	return res;
}

// @ convert a double/float into string
inline string df2str
	(double a)
{
	stringstream ss;
	ss << a;
	string res;
	res = ss.str();
	return res;
}

// @ convert a char into string
inline string ch2str
	(char a)
{
	string res = "";
	res += a;
	return res;
}

// @ clear a stack
template <typename T>
inline bool clearStack
	(stack<T> &a)
{
	while (!a.empty())
		a.pop();
	return true;
}

// @ reverse a stack
template <typename T>
inline void reverseStack
	(stack<T> &a)
{
    queue<T> temp;
    while(!a.empty())
	{
        temp.push(a.top());
        a.pop();
    }
    while(!temp.empty())
	{
        a.push(temp.front());
        temp.pop();
    }
}

// @ release CFont* pool
inline void freeFont
	(stack<CFont*> &a)
{
	CFont* p;
	while (!a.empty())
	{
		p = a.top();
		delete p;
		a.pop();
	}
}

// @ convert string into double
inline double str2df(string s)
{
	double res;
	stringstream ss; ss.str(s);
	ss >> res;
	return res;
}

}

#endif

// OK MARK
