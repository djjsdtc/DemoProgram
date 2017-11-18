
// DemoProgramView.h : CDemoProgramView 类的接口
//

#pragma once


class CDemoProgramView : public CView
{
protected: // 仅从序列化创建
	CDemoProgramView();
	DECLARE_DYNCREATE(CDemoProgramView)

// 特性
public:
	CDemoProgramDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDemoProgramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DemoProgramView.cpp 中的调试版本
inline CDemoProgramDoc* CDemoProgramView::GetDocument() const
   { return reinterpret_cast<CDemoProgramDoc*>(m_pDocument); }
#endif

