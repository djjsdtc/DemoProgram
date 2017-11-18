// WelcomeDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FunctionSelector.h"
#include "WelcomeDialog.h"
#include "afxdialogex.h"

typedef int (*lpIntFun)();

// CWelcomeDialog �Ի���

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


// CWelcomeDialog ��Ϣ�������
int SelectFunction()
{
	CWelcomeDialog WelDialog;
	return WelDialog.DoModal();
}

void CWelcomeDialog::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HINSTANCE hSettingDll=LoadLibrary(_T("SettingModule.dll"));
	//HINSTANCE��16λWindows������ͣ�32λ���ΪHMODULE���ͣ�����32λ�������¶�����ͬ
	//LoadLibrary������̬����dll�ļ��������سɹ��򷵻��ļ���������򷵻�NULL
	//_T(string str)��������ֵ��֤�ַ������ϳ���Ҫ���ASCII��Unicode��׼
	if(hSettingDll!=NULL)
	{
		lpIntFun Setting=(lpIntFun)GetProcAddress(hSettingDll,"Setting");
		//����ָ��ָ������ָ��ĺ������ͼ�typedef
		//GetProcAddress(dll�ļ����,�ַ�����ʾ�ĺ�����)��dll�ļ��м��ص�������
		//����ֵ�������سɹ����ع�������FARPROC����Ҫǿ������ת��Ϊ����ָ��
		//������ʧ�ܣ�����NULL
		if(Setting!=NULL)
			if(Setting()==NOTINITSET) EndDialog(NOTINITSET);
		FreeLibrary(hSettingDll);
	}
	else EndDialog(NOTINITSET);
}


void CWelcomeDialog::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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



