
// DemoProgram.h : DemoProgram Ӧ�ó������ͷ�ļ�
//
#pragma once

#define ALLOK	1000
#define NOTINITSET	1001
#define NOTINITDAT	1002
#define CANNOTGAME	IDCANCEL
#define FILENOTFOUND	1003

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDemoProgramApp:
// �йش����ʵ�֣������ DemoProgram.cpp
//

class CDemoProgramApp : public CWinApp
{
public:
	CDemoProgramApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDemoProgramApp theApp;
