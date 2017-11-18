#pragma once
extern "C" int _declspec(dllexport) Setting();
extern "C" bool _declspec(dllexport) CheckAndGet(int* Diff=NULL,int* Num=NULL,int* Tim=NULL);
#define NOTINITSET 1001

// CSettingDialog 对话框

class CSettingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDialog)

public:
	CSettingDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CButton m_diff1;
	CButton m_diff2;
	CSpinButtonCtrl m_spinnum;
	CSpinButtonCtrl m_spintime;
	CEdit m_num;
	CEdit m_time;
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedRadio1();
	afx_msg void OnClickedRadio2();
	virtual BOOL OnInitDialog();
	void set(int diff=1, int time=30, int num=5);
};
