// QADialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QuestionAsker.h"
#include "QADialog.h"
#include "afxdialogex.h"

typedef bool (*lpSetFun)(int* Diff,int* Num,int* Tim);
typedef bool (*lpDataFun)(int data[2][3][2]);
HINSTANCE hDataDll;lpDataFun Data;
//����DataShow.dll��Ҫ��ȡ������ͬ�ĺ�������ֱ���ڴ˶���ȫ�ֱ������������ж���ֲ�����

int data[2][3][2];
int Difficulty,Time,Number;
int result,Count,right[3]={0,0,0},oper;
CString strAlready,strLeft,strTime,strQuestion;
vector<CString> results;
//��ű��δ������

// CQADialog �Ի���

IMPLEMENT_DYNAMIC(CQADialog, CDialogEx)

CQADialog::CQADialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQADialog::IDD, pParent)
{

}

CQADialog::~CQADialog()
{
}

void CQADialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NUM1, m_question);
	DDX_Control(pDX, IDC_EDIT1, m_answer);
	DDX_Control(pDX, IDC_LEFT, m_left);
	DDX_Control(pDX, IDC_TIME, m_time);
	DDX_Control(pDX, IDC_ALREADY, m_already);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON2, m_StartRedo);
	DDX_Control(pDX, IDC_EDIT2, m_data);
}

BEGIN_MESSAGE_MAP(CQADialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CQADialog::OnClickedButton2)
END_MESSAGE_MAP()

// CQADialog ��Ϣ�������

BOOL CQADialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//���²������ڻ�ȡ��Ŀ����
	HINSTANCE hSettingDll=LoadLibrary(_T("SettingModule.dll"));
	if(hSettingDll!=NULL)
	{
		lpSetFun CheckAndGet=(lpSetFun)GetProcAddress(hSettingDll,"CheckAndGet");
		if(CheckAndGet!=NULL)
		{
			if(CheckAndGet(&Difficulty,&Number,&Time)==false) EndDialog(NOTINITSET);
		}
		else EndDialog(NOTINITSET);
		FreeLibrary(hSettingDll);
	}
	else EndDialog(NOTINITSET);
	//���²������ڻ�ȡ���ڵ�ͳ������
	hDataDll=LoadLibrary(_T("DataShow.dll"));
	if(hDataDll!=NULL)
	{
		Data=(lpDataFun)GetProcAddress(hDataDll,"DataGet");
		if(Data!=NULL)
		{
			if(Data(data)==false) EndDialog(NOTINITDAT);
		}
		else EndDialog(NOTINITDAT);
		//����ֻ�õ�д���ݣ����ڴ��޸ĺ�ָ��������
		Data=(lpDataFun)GetProcAddress(hDataDll,"DataSet");
	}
	else EndDialog(NOTINITDAT);

	srand((unsigned int)time(NULL));
	Count=Number+1;
	this->SetWindowPos(&CWnd::wndNoTopMost,0,0,615,207,SWP_NOMOVE|SWP_NOZORDER);
	//���ô��ڴ�С�����ƶ����ڣ����ı䴰���Ƿ��ö�
	//����ʾ��������Ĵ�СΪ615,207
	//�������ڴ�СΪ615,407
	strTime.Format("%d",Time);
	m_time.SetWindowText(strTime);
	SetTimer(1,1000,NULL);
	//��ʱ��1���ڵ�����ʱ
	strQuestion=GetQuestion(Difficulty,result,oper);
	//��ȡ����
	m_question.SetWindowText(strQuestion);
	UpdateCount(Number,Count);
	//����ʣ������
	m_btnOK.SetWindowText("��һ��(&N)���س���");
	m_btnOK.EnableWindow(true);
	m_answer.EnableWindow(true);
	m_StartRedo.ShowWindow(SW_HIDE);
	//���ء���ʼ��Ϸ/��������ť

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

int AskQuestion()
{
	CQADialog QADialog;
	return QADialog.DoModal();
}

void CQADialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CFont* font=new CFont;
	font->CreatePointFont(360,_T("����"));
	m_question.SetFont(font);
	m_answer.SetFont(font);
	m_answer.UpdateWindow();
	//�����ı�������
	//ʹ�ö�̬�ڴ���䣬����ÿ����������ʱ�ı�����������ö���Ч����Ϊ��Ӧ����������Ѿ���ʧ

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}

void CQADialog::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	//OK��ť�ǡ���һ��/������ť
	CString myansw,correct,number;
	m_answer.GetWindowText(myansw);
	if(myansw=="")myansw="-1";
	//���ڰ���Ŀ�趨��������ܳ��������ʶ�δ����־Ϊ-1
	correct.Format("%d",result);
	number.Format("��%d�⣺",Number-Count+1);
	int myres=atoi(myansw);
	if(CheckMyAnswer(result,myres,oper)==true)
	{
		right[oper]++;
		//��Ӧ���������ȷ��+1
		results.push_back(number+strQuestion+correct+"�����Ĵ���"+myansw+"������ȷ�ġ�");
		//���ӽ����¼
	}
	else
	{
		if(myres==-1)results.push_back(number+strQuestion+correct+"����û�лش������Ŀ��");
		else results.push_back(number+strQuestion+correct+"�����Ĵ���"+myansw+"���Ǵ���ġ�");
	}
	UpdateCount(Number,Count);
	//���¼���
	if(Count==0)m_data.SetWindowText(GiveResult(right,Number,results));
	//������ϣ��������
	else
	{
		strQuestion=GetQuestion(Difficulty,result,oper);
		//��ȡ��һ��
		m_question.SetWindowText(strQuestion);
		if(Count==1)m_btnOK.SetWindowText("����(&N)���س���");
		//���ֻʣһ�⣬��ɽ���ť
	}
	//����ǹرնԻ����ҷ���ֵ��IDOK����Ӧ��������һ��
	//CDialogEx::OnOK();
	//�������д˰�ť�������Ϲ��ܣ��ʲ����뱾�䡣
}

CString CQADialog::GetQuestion(int Difficulty,int& result,int& oper)
{
	CString mystring;
	int a=rand(),b=rand(),operate=rand()%3;
	//ȡ���������OnInitDialog�ж�������������ӣ�
	//srand((unsigned int)time(NULL));
	int mode;
	if(Difficulty==1)mode=10;
	else mode=100;
	oper=operate;
	data[Difficulty-1][oper][0]++;
	switch(operate)
	{
		case 0:   //+
			a=a%mode;b=b%mode;
			result=a+b;
			mystring.Format("%d+%d=",a,b);
			break;
		case 1:   //-
			a=a%mode;b=b%mode;
			if(a<b){int t=a;a=b;b=t;}
			result=a-b;
			mystring.Format("%d-%d=",a,b);
			break;
		case 2:   //*
			a=a%mode;b=b%10;
			result=a*b;
			mystring.Format("%d��%d=",a,b);
	}
	m_answer.SetWindowText("");
	m_answer.SetFocus();
	return mystring;
}

bool CQADialog::CheckMyAnswer(const int & result, const int & myresult,const int & operate)
{
	if(result==myresult)
	{
		data[Difficulty-1][operate][1]++;
		//�޸�ͳ������
		return true;
	}
	else return false;
}

void CQADialog::UpdateCount(const int& Number, int& Count)
{
	Count--;
	strAlready.Format("%d",Number-Count);
	strLeft.Format("%d",Count);
	m_already.SetWindowText(strAlready);m_left.SetWindowText(strLeft);
}

void CQADialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 1:
		//��ʱ��1���ڶ�ʱ
		Time--;
		strTime.Format("%d",Time);
		m_time.SetWindowText(strTime);
		if(Time==0)m_data.SetWindowText(GiveResult(right,Number,results));
		//ʱ�䵽ʱ�������ν��
		break;
	case 2:
		static int i=207;i+=5;
		this->SetWindowPos(&CWnd::wndNoTopMost,0,0,615,i,SWP_NOMOVE|SWP_NOZORDER);
		if(i==407)
		{
			i=207;
			KillTimer(2);
		}
		//��ʱ��2����ʵ�ֶ�����չ�����Ч��
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

CString CQADialog::GiveResult(const int right[3], const int& Number, vector<CString>& results)
{
	CString str="";
	KillTimer(1);
	m_btnOK.EnableWindow(false);
	//����ťֹͣʹ��
	m_answer.EnableWindow(false);
	//�ش��ı���ֹͣʹ��
	SetTimer(2,10,NULL);
	//������ʽ��չ����
	m_StartRedo.ShowWindow(SW_SHOW);
	//��ʾ����ʼ/��������ť
	if((right[0]+right[1]+right[2])>=0.8*Number)m_StartRedo.SetWindowText("��ʼ��Ϸ(&S)");
	//��ȷ�ʴ���80%��ʾ��ʼ��Ϸ��������ʾ����
	else m_StartRedo.SetWindowText("����(&R)");
	for(vector<CString>::iterator iter=results.begin();iter<results.end();iter++)
		str+=(*iter+"\r\n");
	//��vector�е��ַ����ϲ�
	results.clear();
	//���������׼����������������һ�ε�������
	Data(data);
	//д��ͳ������
	return str;
}

void CQADialog::OnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString mystr;
	m_StartRedo.GetWindowText(mystr);
	if(mystr=="����(&R)") OnInitDialog();
	//����ǵ���������ť�������¿�ʼ����
	else EndDialog(ALLOK);
	//����ǵ�����ʼ��Ϸ��ť������ALLOK��
}

BOOL CQADialog::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	FreeLibrary(hDataDll);
	//�ͷ�DLL�ļ�
	return CDialogEx::DestroyWindow();
}
