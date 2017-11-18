#pragma once
#include <vector>
using namespace std;
extern "C" int _declspec(dllexport) AskQuestion();

#define ALLOK	1000
#define NOTINITSET	1001
#define NOTINITDAT	1002
// CQADialog 对话框

class CQADialog : public CDialogEx
{
	DECLARE_DYNAMIC(CQADialog)

public:
	CQADialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQADialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	CString GetQuestion(int Difficulty,int& result,int& oper);
	CStatic m_question;
	CEdit m_answer;
	bool CheckMyAnswer(const int & result, const int & myresul,const int & operate);
	CStatic m_left;
	CStatic m_time;
	CStatic m_already;
	void UpdateCount(const int& Number, int& Count);
	CButton m_btnOK;
	CButton m_StartRedo;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString GiveResult(const int right[3], const int& Number, vector<CString>& results);
	CEdit m_data;
	afx_msg void OnClickedButton2();
	virtual BOOL DestroyWindow();
};
