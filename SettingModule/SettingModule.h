// SettingModule.h : SettingModule DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSettingModuleApp
// �йش���ʵ�ֵ���Ϣ������� SettingModule.cpp
//

class CSettingModuleApp : public CWinApp
{
public:
	CSettingModuleApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
