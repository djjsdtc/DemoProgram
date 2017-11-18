
// DemoProgram.h : DemoProgram 应用程序的主头文件
//
#pragma once

#define ALLOK	1000
#define NOTINITSET	1001
#define NOTINITDAT	1002
#define CANNOTGAME	IDCANCEL
#define FILENOTFOUND	1003

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CDemoProgramApp:
// 有关此类的实现，请参阅 DemoProgram.cpp
//

class CDemoProgramApp : public CWinApp
{
public:
	CDemoProgramApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDemoProgramApp theApp;
