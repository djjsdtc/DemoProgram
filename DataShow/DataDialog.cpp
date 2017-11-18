// DataDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataShow.h"
#include "DataDialog.h"
#include "afxdialogex.h"
int data[2][3][2];

// CDataDialog �Ի���

IMPLEMENT_DYNAMIC(CDataDialog, CDialogEx)

CDataDialog::CDataDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataDialog::IDD, pParent)
{
}

CDataDialog::~CDataDialog()
{
}

void CDataDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_text);
}


BEGIN_MESSAGE_MAP(CDataDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CDataDialog::OnBnClickedButton2)
END_MESSAGE_MAP()

// CDataDialog ��Ϣ�������

void CDataDialog::cleandata(void)
{
	if(DataSet()==false)
	//DataSet������Ĭ�ϲ���ֵ��ͷ�ļ���PPT����������
	{
		MessageBox("�޷����������ļ���","����",MB_ICONSTOP);
		EndDialog(NOTINITDAT);
		return;
	}
	else OnInitDialog();
	//�������ݺ����¼��ضԻ���
}

int DataShow()
{
	CDataDialog CDDialog;
	return CDDialog.DoModal();
}

void CDataDialog::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox("ȷ��Ҫ����ɼ���","ȷ��",MB_ICONQUESTION|MB_YESNO)==IDYES) cleandata();
}


BOOL CDataDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(DataGet(data)==false)
	{
		MessageBox("�Ҳ��������ļ������ڽ��ؽ������ļ�������������ʷ�ɼ����������","����",MB_ICONWARNING);
		cleandata();
	}
	CString text;	
	text.Format("�Ѷ�1��10���ڵļӼ�����һλ����һλ���˷�����\r\n�ӷ�����%d�⣬������ȷ%d��Ŀ��\r\n��������%d�⣬������ȷ%d��Ŀ��\r\n�˷�����%d�⣬������ȷ%d��Ŀ��\r\n�Ѷ�2��100���ڵļӼ�������λ����һλ���˷�����\r\n�ӷ�����%d�⣬������ȷ%d��Ŀ��\r\n��������%d�⣬������ȷ%d��Ŀ��\r\n�˷�����%d�⣬������ȷ%d��Ŀ��",data[0][0][0],data[0][0][1],data[0][1][0],data[0][1][1],data[0][2][0],data[0][2][1],data[1][0][0],data[1][0][1],data[1][1][0],data[1][1][1],data[1][2][0],data[1][2][1]);
	m_text.SetWindowText(text);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

bool DataGet(int data[2][3][2])
{
	//����C���Ե��ļ���д��ʽ
	FILE* fp;
	if((fp=fopen("Data.dat","r"))==NULL)return false;
	else
	{
		fscanf(fp,"A\n+ %d %d\n- %d %d\n* %d %d\nB\n+ %d %d\n- %d %d\n* %d %d",&data[0][0][0],&data[0][0][1],&data[0][1][0],&data[0][1][1],&data[0][2][0],&data[0][2][1],&data[1][0][0],&data[1][0][1],&data[1][1][0],&data[1][1][1],&data[1][2][0],&data[1][2][1]);
		fclose(fp);
		return true;
	}
}

bool DataSet(int data[2][3][2])
{
	FILE* fp;
	if((fp=fopen("Data.dat","w"))==NULL)return false;
	else
	{
		if(data==NULL) fprintf(fp,"A\n+ 0 0\n- 0 0\n* 0 0\nB\n+ 0 0\n- 0 0\n* 0 0");
		else fprintf(fp,"A\n+ %d %d\n- %d %d\n* %d %d\nB\n+ %d %d\n- %d %d\n* %d %d",data[0][0][0],data[0][0][1],data[0][1][0],data[0][1][1],data[0][2][0],data[0][2][1],data[1][0][0],data[1][0][1],data[1][1][0],data[1][1][1],data[1][2][0],data[1][2][1]);
		fclose(fp);
		return true;
	}
}