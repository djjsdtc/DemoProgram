// FunctionSelector.h : FunctionSelector DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFunctionSelectorApp
// �йش���ʵ�ֵ���Ϣ������� FunctionSelector.cpp
//

class CFunctionSelectorApp : public CWinApp
{
public:
	CFunctionSelectorApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
