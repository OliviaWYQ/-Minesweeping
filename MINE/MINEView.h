
// MINEView.h : CMINEView ��Ľӿ�
//

#pragma once

struct MINE
{
	int weitu;
	int shumu;
};

class CMINEView : public CView
{
protected: // �������л�����
	CMINEView();
	DECLARE_DYNCREATE(CMINEView)

// ����
public:
	CMINEDoc* GetDocument() const;

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
	virtual ~CMINEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
public:
	int leftnum;//ʣ������
	int leinum;//����	
	int jieshu;//����	
	short second;//��ʱ
	int secondstart;//��ʼ��ʱ
	int secondstart1;
	CBitmap m_Bitmap[12];
	CBitmap m_anniu[4];
	int m_RowCount;//��
	int m_ColCount;//��
	MINE MINE[50][50];//�������
  	void minezero();
	//UINT m_uSpendTime;//��ǰ����ʱ��
	//CRect m_rcClient;//�ͻ�������
	//UINT m_uIdTimer;//��ʱ��id �����жϵ�ǰ�Ƿ��ж�ʱ��

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

#ifndef _DEBUG  // MINEView.cpp �еĵ��԰汾
inline CMINEDoc* CMINEView::GetDocument() const
   { return reinterpret_cast<CMINEDoc*>(m_pDocument); }
#endif

