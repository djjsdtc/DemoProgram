
// DemoProgramView.h : CDemoProgramView ��Ľӿ�
//

#pragma once


class CDemoProgramView : public CView
{
protected: // �������л�����
	CDemoProgramView();
	DECLARE_DYNCREATE(CDemoProgramView)

// ����
public:
	CDemoProgramDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDemoProgramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DemoProgramView.cpp �еĵ��԰汾
inline CDemoProgramDoc* CDemoProgramView::GetDocument() const
   { return reinterpret_cast<CDemoProgramDoc*>(m_pDocument); }
#endif
