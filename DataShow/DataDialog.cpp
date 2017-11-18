// DataDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "DataShow.h"
#include "DataDialog.h"
#include "afxdialogex.h"
int data[2][3][2];

// CDataDialog 对话框

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

// CDataDialog 消息处理程序

void CDataDialog::cleandata(void)
{
	if(DataSet()==false)
	//DataSet函数的默认参数值见头文件或PPT，用于清零
	{
		MessageBox("无法创建数据文件。","警告",MB_ICONSTOP);
		EndDialog(NOTINITDAT);
		return;
	}
	else OnInitDialog();
	//重置数据后重新加载对话框
}

int DataShow()
{
	CDataDialog CDDialog;
	return CDDialog.DoModal();
}

void CDataDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox("确定要清除成绩吗？","确认",MB_ICONQUESTION|MB_YESNO)==IDYES) cleandata();
}


BOOL CDataDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(DataGet(data)==false)
	{
		MessageBox("找不到数据文件，现在将重建数据文件，您的所有历史成绩将被清除。","警告",MB_ICONWARNING);
		cleandata();
	}
	CString text;	
	text.Format("难度1（10以内的加减法和一位数乘一位数乘法）：\r\n加法已做%d题，其中正确%d题目；\r\n减法已做%d题，其中正确%d题目；\r\n乘法已做%d题，其中正确%d题目。\r\n难度2（100以内的加减法和两位数乘一位数乘法）：\r\n加法已做%d题，其中正确%d题目；\r\n减法已做%d题，其中正确%d题目；\r\n乘法已做%d题，其中正确%d题目。",data[0][0][0],data[0][0][1],data[0][1][0],data[0][1][1],data[0][2][0],data[0][2][1],data[1][0][0],data[1][0][1],data[1][1][0],data[1][1][1],data[1][2][0],data[1][2][1]);
	m_text.SetWindowText(text);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

bool DataGet(int data[2][3][2])
{
	//采用C语言的文件读写方式
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