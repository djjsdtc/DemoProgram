// QuestionAsker.h : QuestionAsker DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQuestionAskerApp
// �йش���ʵ�ֵ���Ϣ������� QuestionAsker.cpp
//

class CQuestionAskerApp : public CWinApp
{
public:
	CQuestionAskerApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
