#pragma once
#include "afxwin.h"
int zero[2][3][2]={{{0,0},{0,0},{0,0}},{{0,0},{0,0},{0,0}}};
extern "C" int _declspec(dllexport) DataShow();
extern "C" bool _declspec(dllexport) DataGet(int data[2][3][2]);
extern "C" bool _declspec(dllexport) DataSet(int data[2][3][2]=zero);
#define NOTINITDAT 1002


// CDataDialog �Ի���

class CDataDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDataDialog)

public:
	CDataDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	void cleandata(void);
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CEdit m_text;
};
