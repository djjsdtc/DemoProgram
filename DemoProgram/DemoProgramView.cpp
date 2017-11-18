
// DemoProgramView.cpp : CDemoProgramView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DemoProgram.h"
#endif

#include "DemoProgramDoc.h"
#include "DemoProgramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDemoProgramView

IMPLEMENT_DYNCREATE(CDemoProgramView, CView)

BEGIN_MESSAGE_MAP(CDemoProgramView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDemoProgramView 构造/析构

CDemoProgramView::CDemoProgramView()
{
	// TODO: 在此处添加构造代码

}

CDemoProgramView::~CDemoProgramView()
{
}

BOOL CDemoProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDemoProgramView 绘制

void CDemoProgramView::OnDraw(CDC* /*pDC*/)
{
	CDemoProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDemoProgramView 打印

BOOL CDemoProgramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDemoProgramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDemoProgramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDemoProgramView 诊断

#ifdef _DEBUG
void CDemoProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoProgramDoc* CDemoProgramView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoProgramDoc)));
	return (CDemoProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// CDemoProgramView 消息处理程序
