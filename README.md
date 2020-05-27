# 基于MFC的图书室管理系统

*大一课程设计写的项目，太嫩了*

![](https://ftp.bmp.ovh/imgs/2020/05/e54b723d427115f2.png)

## 项目说明

| 项目     | 说明                                                         |
| -------- | ------------------------------------------------------------ |
| 设计任务 | 使用MFC框架的单文档架构，设计一个基于文档-视图结构的图书室管理系统。<br>该系统应能实现书籍添加、删除、借书、还书等操作，并能保存与加载文档。 |
| 任务分析 | 视图方面，应有用于列出所有书籍当前状态的列表，并且应该有用于执行各种相关操作的按钮、菜单等。<br>文档方面，应根据具体需要，设计读者类、书本信息类、书本集合类，建立它们之间的耦合关系，并完成更新、序列化的相关代码。 |
| 设计思路 | 1、界面设计：提供列表、按钮、菜单<br/>2、类设计：读者类、书本信息类、书本集合类<br/>3、核心功能设计：搜索、借书、还书、新书入库、旧书出库<br/>4、程序测试 |
| 功能介绍 | 支持图书的新增、删除功能，支持图书的借出、归还功能，<br/>支持读者最大借阅数的限制，支持文档的保存与载入，<br/>支持图书的按属性排序功能，支持基本的搜索功能，<br/>有基本的异常处理功能，支持程序外观的切换。 |

## 文件描述

| **文件名**                           | **文件描述**                      |
| ------------------------------------ | --------------------------------- |
| mfcLibrary.sln                       | Visual Studio 2010 解决方案文件   |
| LibraryDB.libdata                    | 测试用文档文件                    |
| ./mfcLibrary/MainFrm.h & .cpp        | SDI应用主框架文件                 |
| ./mfcLibrary/mfcLibrary.h & .cpp     | SDI应用文件                       |
| ./mfcLibrary/mfcLibraryDoc.h & .cpp  | SDI应用文档类                     |
| ./mfcLibrary/mfcLibraryView.h & .cpp | CListView类，用于实现左侧列表框   |
| ./mfcLibrary/ShortCutPanel.h & .cpp  | CFormView类，用于实现右侧控制面板 |
| ./mfcLibrary/***Dlg.h & .cpp         | 各类对话框相关文件                |
| ./mfcLibrary/BookInfo.h & .cpp       | 书本信息类                        |
| ./mfcLibrary/Reader.h & .cpp         | 读者类                            |
| ./mfcLibrary/BookSet.h & .cpp        | 书本集合类                        |
| ./mfcLibrary/stdafx.h                | 预编译头文件                      |
| ./mfcLibrary/zx_betterMFC.h          | 提高MFC开发效率的头文件           |

**头文件描述：**

*BookInfo.h*

| **属性名/函数名**                                            | **描述**             |
| ------------------------------------------------------------ | -------------------- |
| `int leftCount  `                                            | 书本剩余副本数量     |
| `int totalCount  `                                           | 书本总副本数量       |
| `CString bookName  `                                         | 书名                 |
| `CString bookNo  `                                           | 书目编号             |
| `CString authorName  `                                       | 作者名               |
| `vector<int> out_LoginNo  `                                  | 借出副本的登录号集合 |
| `vector<CReader> out_Reader  `                               | 借出副本的读者       |
| `CBookInfo(const CBookInfo &a)  `                            | 重载拷贝构造函数     |
| `CBookInfo& operator = (const  CBookInfo& a)  `              | 重载等号             |
| *注：out_LoginNo与out_Reader构成平行数组，两条记录合起来唯一标识一次借阅* |                      |

*BookSet.h*

| **属性名/函数名**                                            | **描述**                                |
| ------------------------------------------------------------ | --------------------------------------- |
| ` vector<CBookInfo> books  `                                 | 保存了所有BookInfo的数组                |
| `  int currentTailLoginNo  `                                 | 用于记录本BookSet的登录号已经记录到多少 |
| `  bool insertNewBook(CBookInfo book)  `                     | 向books数组中加入一本新书               |
| `  virtual void Serialize(CArchive& ar)  `                   | 序列化函数                              |
| `  CBookSet(const CBookSet &a)  `                            | 重载拷贝构造函数                        |
| `  CBookSet& operator = (const CBookSet&  a)  `              | 重载等号                                |
| *注：本SDI应用的全部序列化操作均在BookSet的Serialize函数中完成* |                                         |

*MainFrm.h*

| **属性名/函数名**                                            | **描述**                             |
| ------------------------------------------------------------ | ------------------------------------ |
| `  CSplitterWnd m_wndSplitter  `                             | 用于分割用户区窗口的CSplitterWnd变量 |
| `  virtual  BOOL OnCreateClient  (LPCREATESTRUCT  lpcs,   CCreateContext*  pContext)  ` | 在用户区创建时进行窗口分割           |
| `  afx_msg void OnSize(UINT nType, int cx,  int cy)  `       | 在用户区大小改变时重新分割窗口       |

*mfcLibraryDoc.h*

| **属性名/函数名**                       | **描述**                             |
| ---------------------------------------- | ------------------------------------ |
| `CBookSet bookSet  `                     | 书本集合类的对象                     |
| `CListCtrl*  leftListCtrl  `             | 指向窗口左部分的CListView的CListCtrl |
| `virtual void Serialize(CArchive& ar)  ` | 序列化函数                           |

*mfcLibraryView.h*

| **属性名/函数名**                                            | **描述**                                 |
| ------------------------------------------------------------ | ---------------------------------------- |
| `  static int m_SortColumn  `                                | 用于实现点击列表表头排序的相关变量和函数 |
| `  static  bool m_bAsc  `                                    | 用于实现点击列表表头排序的相关变量和函数 |
| `  static  int CALLBACK listCompare  (LPARAM  lParam1, LPARAM lParam2,   LPARAM  lParamSort)  ` | 用于实现点击列表表头排序的相关变量和函数 |
| ` virtual  void OnInitialUpdate()  `                         | 进行视图初始化的函数                     |
| `  virtual  void OnUpdate  (CView*  /*pSender*/, LPARAM /*lHint*/,   CObject*  /*pHint*/)  ` | 用于处理文档告知视图更新的函数           |

*Reader.h*

| **属性名/函数名/宏**                                       | **描述**               |
| ------------------------------------------------------------ | ---------------------- |
| `  CString  readerName  `                                    | 读者姓名               |
| `  int  readerNo  `                                          | 读者证号               |
| `  int  nowLoanCount  `                                      | 读者已借量             |
| ` vector<int>  BaD_LoginNo  `                                | 读者借的书的登录号集合 |
| ` vector<CString>  BaD_Date  `                               | 读者借的书的日期集合   |
| `  #define  MAX_LOAN_COUNT 2  `                              | 定义最大借书量为2      |
| *注：BaD_LoginNo与BaD_Date构成平行数组，两条记录合起来唯一标识一次借阅* |                        |

*ShortCutPanel.h*

| **属性名/函数名/宏**        | **描述**                   |
| --------------------------- | -------------------------- |
| `  CString  m_search_...  ` | 用于进行搜索的书本信息     |
| `  CString  m_readerno  `   | 用于进行搜索的读者信息     |
| `  afx_msg  void On…  `     | 用于处理各种点击事件的函数 |

*stdafx.h*

| **属性名/函数名/宏**                                         | **描述**                                              |
| ------------------------------------------------------------ | ----------------------------------------------------- |
| `  #define  _GETLISTCTRL *(((CmfcLibraryDoc*)GetDocument())->leftListCtrl);  ` | 方便地在各种View内获得  左部分的CListCtrl             |
| `  #define  _GETLISTCTRLANYWHERE  *(((CmfcLibraryDoc*)((CMainFrame*)AfxGetApp()->m_pMainWnd)  ->GetActiveDocument())->leftListCtrl);  ` | 方便地在任何位置（包括Dialog）内获得左部分的CListCtrl |
| `  #define  _GETDOCPTR (CmfcLibraryDoc*)GetDocument();  `    | 方便地在各种View内获得pDoc                            |

*zx_betterMFC.h*

| **属性名/函数名/宏**                                         | **描述**                                            |
| ------------------------------------------------------------ | --------------------------------------------------- |
| `  void  pressCtrlCombo(char with)  `                        | 模拟Ctrl+with组合键按压                             |
| `  CFont*  makeMFCFont  (int  size, bool bold = false, char* fontName = "Arial",      bool italic = false, bool underline =  false)  ` | 用于方便地创建字体CFont*，可直接作SetFont函数的参数 |
| `  CString  str2cstr(string& src)  `                         | 将STL的string转为CString                            |
| `  string  cstr2str(CString &src)  `                         | 将CString转为STL的string                            |
| `void  …Info(LPCSTR text, LPCSTR title)  `                   | 方便地弹出各类MessageBox                            |
| `string  int2str(int a)S  `                                   | 将int转为STL的string                                |
| ` template  <typename T>  void  reverseStack (stack<T> &a)  ` | 反转一个栈                                          |
| `void  freeFont(stack<CFont*> &a)  `                         | 释放CFont*内存池                                    |
| `double  str2df(string s)  `                                 | 将STL的string转为浮点数                             |
| `string  df2str(double a)  `                                 | 将浮点数转为STL的string                             |

## 补充说明

| 序号 | 说明                                                         |
| ---- | ------------------------------------------------------------ |
| 1    | 在许多对话框和CFormView中，都维护了用于`CFont*`的内存池`std::stack<CFont*>  cfontPool_...  ` |
| 2    | 本程序没有使用MFC自带的各类容器，而是使用了STL的vector，故在CBookSet中手动进行了所有的序列化操作 |
| 3    | 在每次视图OnUpdate时，都会按照登录号对文档进行内容排序       |
| 4    | 程序默认的保存/打开扩展名为.libdata                          |
| 5    | 搜索功能扫描的是整个CListView而非文档                        |
| 6    | 一种书可以有多个副本，它们的书目编号相同，而登录号不同       |
