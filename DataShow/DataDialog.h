#pragma once
#include "afxwin.h"
int zero[2][3][2]={{{0,0},{0,0},{0,0}},{{0,0},{0,0},{0,0}}};
extern "C" int _declspec(dllexport) DataShow();
extern "C" bool _declspec(dllexport) DataGet(int data[2][3][2]);
extern "C" bool _declspec(dllexport) DataSet(int data[2][3][2]=zero);
#define NOTINITDAT 1002


// CDataDialog 对话框

class CDataDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDataDialog)

public:
	CDataDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	void cleandata(void);
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CEdit m_text;
};
