
// DemoProgramView.cpp : CDemoProgramView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDemoProgramView ����/����

CDemoProgramView::CDemoProgramView()
{
	// TODO: �ڴ˴���ӹ������

}

CDemoProgramView::~CDemoProgramView()
{
}

BOOL CDemoProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDemoProgramView ����

void CDemoProgramView::OnDraw(CDC* /*pDC*/)
{
	CDemoProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDemoProgramView ��ӡ

BOOL CDemoProgramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDemoProgramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDemoProgramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CDemoProgramView ���

#ifdef _DEBUG
void CDemoProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoProgramDoc* CDemoProgramView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoProgramDoc)));
	return (CDemoProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// CDemoProgramView ��Ϣ�������
