// QADialog.cpp : 实现文件
//

#include "stdafx.h"
#include "QuestionAsker.h"
#include "QADialog.h"
#include "afxdialogex.h"

typedef bool (*lpSetFun)(int* Diff,int* Num,int* Tim);
typedef bool (*lpDataFun)(int data[2][3][2]);
HINSTANCE hDataDll;lpDataFun Data;
//由于DataShow.dll中要获取两个相同的函数，故直接在此定义全局变量，不再另行定义局部变量

int data[2][3][2];
int Difficulty,Time,Number;
int result,Count,right[3]={0,0,0},oper;
CString strAlready,strLeft,strTime,strQuestion;
vector<CString> results;
//存放本次答题情况

// CQADialog 对话框

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

// CQADialog 消息处理程序

BOOL CQADialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	//以下部分用于获取题目设置
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
	//以下部分用于获取现在的统计数据
	hDataDll=LoadLibrary(_T("DataShow.dll"));
	if(hDataDll!=NULL)
	{
		Data=(lpDataFun)GetProcAddress(hDataDll,"DataGet");
		if(Data!=NULL)
		{
			if(Data(data)==false) EndDialog(NOTINITDAT);
		}
		else EndDialog(NOTINITDAT);
		//后面只用到写数据，故在此修改好指向函数对象
		Data=(lpDataFun)GetProcAddress(hDataDll,"DataSet");
	}
	else EndDialog(NOTINITDAT);

	srand((unsigned int)time(NULL));
	Count=Number+1;
	this->SetWindowPos(&CWnd::wndNoTopMost,0,0,615,207,SWP_NOMOVE|SWP_NOZORDER);
	//设置窗口大小，不移动窗口，不改变窗口是否置顶
	//仅显示答题区域的大小为615,207
	//完整窗口大小为615,407
	strTime.Format("%d",Time);
	m_time.SetWindowText(strTime);
	SetTimer(1,1000,NULL);
	//定时器1用于倒数计时
	strQuestion=GetQuestion(Difficulty,result,oper);
	//获取问题
	m_question.SetWindowText(strQuestion);
	UpdateCount(Number,Count);
	//更新剩余题量
	m_btnOK.SetWindowText("下一题(&N)（回车）");
	m_btnOK.EnableWindow(true);
	m_answer.EnableWindow(true);
	m_StartRedo.ShowWindow(SW_HIDE);
	//隐藏“开始游戏/重做”按钮

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int AskQuestion()
{
	CQADialog QADialog;
	return QADialog.DoModal();
}

void CQADialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CFont* font=new CFont;
	font->CreatePointFont(360,_T("宋体"));
	m_question.SetFont(font);
	m_answer.SetFont(font);
	m_answer.UpdateWindow();
	//设置文本框字体
	//使用动态内存分配，否则每次输入文字时文本框字体的设置都无效，因为对应的字体变量已经消失

	// 不为绘图消息调用 CDialogEx::OnPaint()
}

void CQADialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//OK按钮是“下一题/交卷”按钮
	CString myansw,correct,number;
	m_answer.GetWindowText(myansw);
	if(myansw=="")myansw="-1";
	//由于按题目设定结果不可能出负数，故定未做标志为-1
	correct.Format("%d",result);
	number.Format("第%d题：",Number-Count+1);
	int myres=atoi(myansw);
	if(CheckMyAnswer(result,myres,oper)==true)
	{
		right[oper]++;
		//对应的运算的正确数+1
		results.push_back(number+strQuestion+correct+"，您的答案是"+myansw+"，是正确的。");
		//增加结果记录
	}
	else
	{
		if(myres==-1)results.push_back(number+strQuestion+correct+"，您没有回答这道题目。");
		else results.push_back(number+strQuestion+correct+"，您的答案是"+myansw+"，是错误的。");
	}
	UpdateCount(Number,Count);
	//更新计数
	if(Count==0)m_data.SetWindowText(GiveResult(right,Number,results));
	//答题完毕，给出结果
	else
	{
		strQuestion=GetQuestion(Difficulty,result,oper);
		//获取下一题
		m_question.SetWindowText(strQuestion);
		if(Count==1)m_btnOK.SetWindowText("交卷(&N)（回车）");
		//如果只剩一题，变成交卷按钮
	}
	//如果是关闭对话框并且返回值是IDOK，则应加上下面一句
	//CDialogEx::OnOK();
	//本程序中此按钮不作以上功能，故不加入本句。
}

CString CQADialog::GetQuestion(int Difficulty,int& result,int& oper)
{
	CString mystring;
	int a=rand(),b=rand(),operate=rand()%3;
	//取随机数，在OnInitDialog中定义了随机数种子：
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
			mystring.Format("%d×%d=",a,b);
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
		//修改统计数据
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 1:
		//计时器1用于定时
		Time--;
		strTime.Format("%d",Time);
		m_time.SetWindowText(strTime);
		if(Time==0)m_data.SetWindowText(GiveResult(right,Number,results));
		//时间到时给出本次结果
		break;
	case 2:
		static int i=207;i+=5;
		this->SetWindowPos(&CWnd::wndNoTopMost,0,0,615,i,SWP_NOMOVE|SWP_NOZORDER);
		if(i==407)
		{
			i=207;
			KillTimer(2);
		}
		//计时器2用于实现动画扩展窗体的效果
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

CString CQADialog::GiveResult(const int right[3], const int& Number, vector<CString>& results)
{
	CString str="";
	KillTimer(1);
	m_btnOK.EnableWindow(false);
	//交卷按钮停止使用
	m_answer.EnableWindow(false);
	//回答文本框停止使用
	SetTimer(2,10,NULL);
	//动画方式扩展窗体
	m_StartRedo.ShowWindow(SW_SHOW);
	//显示“开始/重做”按钮
	if((right[0]+right[1]+right[2])>=0.8*Number)m_StartRedo.SetWindowText("开始游戏(&S)");
	//正确率大于80%显示开始游戏，否则显示重做
	else m_StartRedo.SetWindowText("重做(&R)");
	for(vector<CString>::iterator iter=results.begin();iter<results.end();iter++)
		str+=(*iter+"\r\n");
	//将vector中的字符串合并
	results.clear();
	//清空容器，准备如果重做则接收下一次的做题结果
	Data(data);
	//写入统计数据
	return str;
}

void CQADialog::OnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString mystr;
	m_StartRedo.GetWindowText(mystr);
	if(mystr=="重做(&R)") OnInitDialog();
	//如果是单击重做按钮，就重新开始答题
	else EndDialog(ALLOK);
	//如果是单击开始游戏按钮，返回ALLOK。
}

BOOL CQADialog::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	FreeLibrary(hDataDll);
	//释放DLL文件
	return CDialogEx::DestroyWindow();
}
