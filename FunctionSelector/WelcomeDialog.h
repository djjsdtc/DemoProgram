#pragma once
extern "C" int _declspec(dllexport) SelectFunction();

#define ALLOK	1000
#define NOTINITSET	1001
#define NOTINITDAT	1002
#define CANNOTGAME	IDCANCEL
#define FILENOTFOUND	1003

// CWelcomeDialog 对话框

class CWelcomeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CWelcomeDialog)

public:
	CWelcomeDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWelcomeDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};