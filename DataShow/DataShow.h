// DataShow.h : DataShow DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDataShowApp
// �йش���ʵ�ֵ���Ϣ������� DataShow.cpp
//

class CDataShowApp : public CWinApp
{
public:
	CDataShowApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
