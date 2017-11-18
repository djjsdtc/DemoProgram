// SettingDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SettingModule.h"
#include "SettingDialog.h"
#include "afxdialogex.h"

int Difficulty,Time,Number;

// CSettingDialog 对话框

IMPLEMENT_DYNAMIC(CSettingDialog, CDialogEx)

CSettingDialog::CSettingDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDialog::IDD, pParent)
{

}

CSettingDialog::~CSettingDialog()
{
}

void CSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_diff1);
	DDX_Control(pDX, IDC_RADIO2, m_diff2);
	DDX_Control(pDX, IDC_SPIN1, m_spinnum);
	DDX_Control(pDX, IDC_SPIN2, m_spintime);
	DDX_Control(pDX, IDC_EDIT1, m_num);
	DDX_Control(pDX, IDC_EDIT2, m_time);
}


BEGIN_MESSAGE_MAP(CSettingDialog, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CSettingDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CSettingDialog::OnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSettingDialog::OnClickedRadio2)
END_MESSAGE_MAP()


// CSettingDialog 消息处理程序

int CSettingDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	return 0;
}

int Setting()
{
	CSettingDialog CSetDialog;
	return CSetDialog.DoModal();
}

void CSettingDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//改变难度设置
	if(m_diff1.GetCheck()==true) Difficulty=1;
	else Difficulty=2;
	//改变时间设置
	CString mystring;
	m_time.GetWindowText(mystring);
	Time=atoi(mystring);
	//改变题量设置
	m_num.GetWindowText(mystring);
	Number=atoi(mystring);
	set(Difficulty,Time,Number);
	CDialogEx::OnOK();
}


void CSettingDialog::OnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	//这两段代码的作用：
	//使用过程中发现这两个单选框有可能会被同时选中，故加此代码
	//同时选中的原因尚不明确。
	m_diff1.SetCheck(true);
	m_diff2.SetCheck(false);
}


void CSettingDialog::OnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_diff2.SetCheck(true);
	m_diff1.SetCheck(false);
}

bool CheckAndGet(int* Diff,int* Num,int* Tim)
{
	//C语言读取文件的方式
	FILE* fp;
	if((fp=fopen("Settings.ini","r"))==NULL) return false;
	fscanf(fp,"[Settings]\nDifficulty=%d\nTime=%d\nNumber=%d",&Difficulty,&Time,&Number);
	if( (Difficulty!=1 && Difficulty!=2) || (Time<=0 || Time>32767) || (Number<5 || Number>20) ) return false;
	if(Diff!=NULL && Tim!=NULL && Num!=NULL)
	{
		*Diff=Difficulty;*Tim=Time;*Num=Number;
	}
	return true;
}

BOOL CSettingDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//读取设置
	if(CheckAndGet()==false)
	{
		MessageBox("找不到 Settings.ini 文件或文件有错，设置数据将重置。","提示",MB_ICONWARNING);
		set();
	}
	//显示当前难度
	if(Difficulty==1) OnClickedRadio1();
	else OnClickedRadio2();
	//显示时间
	CString mystring;
	mystring.Format("%d",Time);
	m_time.SetWindowText(mystring);
	//显示题量
	mystring.Format("%d",Number);
	m_num.SetWindowText(mystring);
	//题量范围5～20，时间范围1～32767，并且为上下箭头绑定对应文本框
	m_spinnum.SetBuddy(&m_num);
	m_spinnum.SetRange(5,20);
	m_spintime.SetBuddy(&m_time);
	m_spintime.SetRange(1,32767);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSettingDialog::set(int diff, int time, int num)
{
	FILE* fp;
	if((fp=fopen("Settings.ini","w"))==NULL)
	{
		MessageBox("无法创建设置文件。","警告",MB_ICONSTOP);
		EndDialog(NOTINITSET);
		return;
	}
	else
	{
		fprintf(fp,"[Settings]\nDifficulty=%d\nTime=%d\nNumber=%d",diff,time,num);
		fclose(fp);
	}
	fp=fopen("Settings.ini","r");
	fscanf(fp,"[Settings]\nDifficulty=%d\nTime=%d\nNumber=%d",&Difficulty,&Time,&Number);
}
