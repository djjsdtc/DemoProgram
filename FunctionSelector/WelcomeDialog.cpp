// WelcomeDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "FunctionSelector.h"
#include "WelcomeDialog.h"
#include "afxdialogex.h"

typedef int (*lpIntFun)();

// CWelcomeDialog 对话框

IMPLEMENT_DYNAMIC(CWelcomeDialog, CDialogEx)

CWelcomeDialog::CWelcomeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWelcomeDialog::IDD, pParent)
{

}

CWelcomeDialog::~CWelcomeDialog()
{
}

void CWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWelcomeDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CWelcomeDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CWelcomeDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CWelcomeDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWelcomeDialog 消息处理程序
int SelectFunction()
{
	CWelcomeDialog WelDialog;
	return WelDialog.DoModal();
}

void CWelcomeDialog::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	HINSTANCE hDataDll=LoadLibrary(_T("DataShow.dll"));
	if(hDataDll!=NULL)
	{
		lpIntFun DataShow=(lpIntFun)GetProcAddress(hDataDll,"DataShow");
		if(DataShow!=NULL) 
			if(DataShow()==NOTINITDAT) EndDialog(NOTINITDAT);
		FreeLibrary(hDataDll);
	}
	else EndDialog(NOTINITDAT);
}


void CWelcomeDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HINSTANCE hSettingDll=LoadLibrary(_T("SettingModule.dll"));
	//HINSTANCE是16位Windows句柄类型，32位句柄为HMODULE类型，但在32位编译器下二者相同
	//LoadLibrary函数动态加载dll文件，若加载成功则返回文件句柄，否则返回NULL
	//_T(string str)函数返回值保证字符串符合程序要求的ASCII或Unicode标准
	if(hSettingDll!=NULL)
	{
		lpIntFun Setting=(lpIntFun)GetProcAddress(hSettingDll,"Setting");
		//函数指针指向函数，指向的函数类型见typedef
		//GetProcAddress(dll文件句柄,字符串表示的函数名)从dll文件中加载导出函数
		//返回值：若加载成功返回过程类型FARPROC，需要强制类型转换为函数指针
		//若加载失败，返回NULL
		if(Setting!=NULL)
			if(Setting()==NOTINITSET) EndDialog(NOTINITSET);
		FreeLibrary(hSettingDll);
	}
	else EndDialog(NOTINITSET);
}


void CWelcomeDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HINSTANCE hQADll=LoadLibrary(_T("QuestionAsker.dll"));
	if(hQADll!=NULL)
	{
		lpIntFun AskQuestion=(lpIntFun)GetProcAddress(hQADll,"AskQuestion");
		if(AskQuestion!=NULL)
		{
			int value;
			if((value=AskQuestion())==CANNOTGAME);
			else EndDialog(value);
		}
		FreeLibrary(hQADll);
	}
	else EndDialog(FILENOTFOUND);
}



