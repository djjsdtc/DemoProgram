// SettingDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SettingModule.h"
#include "SettingDialog.h"
#include "afxdialogex.h"

int Difficulty,Time,Number;

// CSettingDialog �Ի���

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


// CSettingDialog ��Ϣ�������

int CSettingDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}

int Setting()
{
	CSettingDialog CSetDialog;
	return CSetDialog.DoModal();
}

void CSettingDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ı��Ѷ�����
	if(m_diff1.GetCheck()==true) Difficulty=1;
	else Difficulty=2;
	//�ı�ʱ������
	CString mystring;
	m_time.GetWindowText(mystring);
	Time=atoi(mystring);
	//�ı���������
	m_num.GetWindowText(mystring);
	Number=atoi(mystring);
	set(Difficulty,Time,Number);
	CDialogEx::OnOK();
}


void CSettingDialog::OnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����δ�������ã�
	//ʹ�ù����з�����������ѡ���п��ܻᱻͬʱѡ�У��ʼӴ˴���
	//ͬʱѡ�е�ԭ���в���ȷ��
	m_diff1.SetCheck(true);
	m_diff2.SetCheck(false);
}


void CSettingDialog::OnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_diff2.SetCheck(true);
	m_diff1.SetCheck(false);
}

bool CheckAndGet(int* Diff,int* Num,int* Tim)
{
	//C���Զ�ȡ�ļ��ķ�ʽ
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ȡ����
	if(CheckAndGet()==false)
	{
		MessageBox("�Ҳ��� Settings.ini �ļ����ļ��д��������ݽ����á�","��ʾ",MB_ICONWARNING);
		set();
	}
	//��ʾ��ǰ�Ѷ�
	if(Difficulty==1) OnClickedRadio1();
	else OnClickedRadio2();
	//��ʾʱ��
	CString mystring;
	mystring.Format("%d",Time);
	m_time.SetWindowText(mystring);
	//��ʾ����
	mystring.Format("%d",Number);
	m_num.SetWindowText(mystring);
	//������Χ5��20��ʱ�䷶Χ1��32767������Ϊ���¼�ͷ�󶨶�Ӧ�ı���
	m_spinnum.SetBuddy(&m_num);
	m_spinnum.SetRange(5,20);
	m_spintime.SetBuddy(&m_time);
	m_spintime.SetRange(1,32767);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSettingDialog::set(int diff, int time, int num)
{
	FILE* fp;
	if((fp=fopen("Settings.ini","w"))==NULL)
	{
		MessageBox("�޷����������ļ���","����",MB_ICONSTOP);
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
