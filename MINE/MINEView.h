
// MINEView.h : CMINEView 类的接口
//

#pragma once

struct MINE
{
	int weitu;
	int shumu;
};

class CMINEView : public CView
{
protected: // 仅从序列化创建
	CMINEView();
	DECLARE_DYNCREATE(CMINEView)

// 特性
public:
	CMINEDoc* GetDocument() const;

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
	virtual ~CMINEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
public:
	int leftnum;//剩下雷数
	int leinum;//雷数	
	int jieshu;//结束	
	short second;//计时
	int secondstart;//开始计时
	int secondstart1;
	CBitmap m_Bitmap[12];
	CBitmap m_anniu[4];
	int m_RowCount;//行
	int m_ColCount;//列
	MINE MINE[50][50];//最大雷区
  	void minezero();
	//UINT m_uSpendTime;//当前所花时间
	//CRect m_rcClient;//客户区区域
	//UINT m_uIdTimer;//定时器id 用于判断当前是否有定时器

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnStart();
protected:
public:
	afx_msg void OnSetleinum();
	afx_msg void OnStart();
	afx_msg void Onlogout();
};

#ifndef _DEBUG  // MINEView.cpp 中的调试版本
inline CMINEDoc* CMINEView::GetDocument() const
   { return reinterpret_cast<CMINEDoc*>(m_pDocument); }
#endif

