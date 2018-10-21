
// MINEView.cpp : CMINEView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MINE.h"
#endif

#include "MINEDoc.h"
#include "MINEView.h"
#include "Setdlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
//#define ID_TIMER WM_USER+1

#endif


// CMINEView

IMPLEMENT_DYNCREATE(CMINEView, CView)

BEGIN_MESSAGE_MAP(CMINEView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMINEView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
//	ON_COMMAND(ID_32771, &CMINEView::OnStart)
//	ON_MESSAGE(leizero, &CMINEView::OnLeizero)
//ON_EN_CHANGE(IDC_EDIT1, &CMINEView::OnEnChangeEdit1)
ON_COMMAND(ID_32773, &CMINEView::OnSetleinum)
ON_COMMAND(ID_32774, &CMINEView::OnStart)
ON_COMMAND(ID_32772, &CMINEView::Onlogout)
END_MESSAGE_MAP()

// CMINEView ����/����

CMINEView::CMINEView()
{
	// TODO: �ڴ˴���ӹ������
	for(int ii=0;ii<12;ii++)
		m_Bitmap[ii].LoadBitmap(IDB_BITMAP0+ii);
    for(int jj=0;jj<4;jj++)
		m_anniu[jj].LoadBitmap(IDB_ANNIU1+jj);
    //��ʱ
	second=0; 
	 //1ʱ��ʼ��ʱ
	secondstart=0;
	secondstart1=0;
    //����
	m_RowCount=25; 
	 //����
	m_ColCount=16; 
	//����
    leinum=80;
	 //ʣ������
	leftnum=leinum; 
	 //jieshu=1ʱֹͣ
	jieshu=0; 

	int aa=0;
 
	//��ʼ��Ϊ0
	for(int i=0;i<m_RowCount;i++)
	{
		for(int j=0;j<m_ColCount;j++)
		{
			MINE[i][j].shumu=0;
			MINE[i][j].weitu=0;
		}
	}
	//��ȡ��ǰʱ��
	CTime time=GetCurrentTime();

	int s;
	//��ȡ����
	s=time.GetSecond();
	//����80����
	do
	{
		//�Ե�ǰ����Ϊ��������㷨
		int k=(rand()*s)%m_RowCount;
		int l=(rand()*s)%m_ColCount;
       //Ϊ�˱���һ��λ��ͬʱ��������
       //ֻ����ǰλ�ò�����ʱ��ֵΪ��
		if(MINE[k][l].shumu!=-1)
		{
			MINE[k][l].shumu=-1; 
		    aa++; 
		}
	 
	}while(aa!=leinum);   
    //������ֵ����������
	for(int a=0;a<m_RowCount;a++)
		for(int b=0;b<m_ColCount;b++)
			if(MINE[a][b].shumu==0)
			{
				for(int c=a-1;c<a+2;c++)
					for(int d=b-1;d<b+2;d++)
						if(c>=0&&c<m_RowCount&&d>=0&&d<m_ColCount)
							if(MINE[c][d].shumu==-1)
								MINE[a][b].shumu++;		
			}

}

CMINEView::~CMINEView()
{
}

BOOL CMINEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMINEView ����

void CMINEView::OnDraw(CDC*pDC)
{
	CMINEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//������
    CBrush mybrush1;
 	mybrush1.CreateSolidBrush(RGB(192,192,192));
 	CRect myrect1(0,0,1200,800);
 	pDC->FillRect(myrect1,&mybrush1);
	//���ڿ�
	CBrush mybrush;
 	mybrush.CreateSolidBrush(RGB(0,0,0));
 	CRect myrect(20,10,70,40);
 	pDC->FillRect(myrect,&mybrush);

	CRect myrect2(325,10,375,40);
 	pDC->FillRect(myrect2,&mybrush);

	CPen mypen;
	CPen*myoldPen;
	mypen.CreatePen(PS_SOLID,2,RGB(255,255,255));
    myoldPen=pDC->SelectObject(&mypen);
	//���ڿ�İ���
	pDC->MoveTo(20,40);
	pDC->LineTo(70,40);
	pDC->LineTo(70,10);
	pDC->MoveTo(325,40);
	pDC->LineTo(375,40);
	pDC->LineTo(375,10);
	//����������
    for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
		{
			pDC->MoveTo(10+i*15,50+j*15+14);
			pDC->LineTo(10+i*15,50+j*15);	
			pDC->LineTo(10+i*15+14,50+j*15);
		}
	pDC->SelectObject(myoldPen);

	CPen mypen2;
	CPen*myoldPen2;
	mypen2.CreatePen(PS_SOLID,1,RGB(0,0,0));
    myoldPen2=pDC->SelectObject(&mypen2);
    for(int ii=0;ii<m_RowCount;ii++)
		for(int jj=0;jj<m_ColCount;jj++)
		{
			pDC->MoveTo(10+ii*15,50+jj*15+14);
			pDC->LineTo(10+ii*15+14,50+jj*15+14);	
			pDC->LineTo(10+ii*15+14,50+jj*15);
		}
	pDC->SelectObject(myoldPen2);

 		 CDC Dc;
  	 if(Dc.CreateCompatibleDC(pDC)==FALSE)
  		  AfxMessageBox(_T("Can't create DC"));	
	 //��ʾ��ť
	 Dc.SelectObject(m_anniu[0]);
	 pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);
     //�ж���ʾʲôλͼ
	 //weitu=1�Ѱ��µ�������
	 //weitu=2��ʾ��
	 //weitu=3��ʾ�ʺ�
	 for(int a=0;a<m_RowCount;a++)
		 for(int b=0;b<m_ColCount;b++)
			{
				if(MINE[a][b].weitu==1)
				{
                    Dc.SelectObject(m_Bitmap[MINE[a][b].shumu]);
					pDC->BitBlt(a*15+10,b*15+50,160,160,&Dc,0,0,SRCCOPY);
				}
				if(MINE[a][b].weitu==2)
				{
					Dc.SelectObject(m_Bitmap[9]);
					pDC->BitBlt(a*15+10,b*15+50,160,160,&Dc,0,0,SRCCOPY);
				}
				if(MINE[a][b].weitu==3)
				{
					Dc.SelectObject(m_Bitmap[10]);
					pDC->BitBlt(a*15+10,b*15+50,160,160,&Dc,0,0,SRCCOPY);
				}
				//����
				if(jieshu==1&&MINE[a][b].shumu==-1)
				{
                    Dc.SelectObject(m_Bitmap[11]);
					pDC->BitBlt(a*15+10,b*15+50,160,160,&Dc,0,0,SRCCOPY);
					Dc.SelectObject(m_anniu[2]);
					pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);
				}
				
			}
	//��ʾ�ڿ��������
	int nOldDC=pDC->SaveDC();
	pDC->SetTextColor(RGB(255,0,0));
	pDC->SetBkColor(RGB(0,0,0));
	CFont font; 					             
	if(0==font.CreatePointFont(160,_T("Comic Sans MS")))
	{
		AfxMessageBox(_T("Can't Create Font"));
	}
	pDC->SelectObject(&font);
	CString str;  
	if(leftnum<10) 
		str.Format(_T("00%d"),leftnum);
	else
		str.Format(_T("0%d"),leftnum);					
	pDC->TextOut(25,10,str);
	if(second<10)
		str.Format(_T("00%d"),second);
	else if(second<100)
			str.Format(_T("0%d") ,second);
		else
			str.Format(_T("%d") ,second);
	pDC->TextOut(330,10,str);
	pDC->RestoreDC(nOldDC);
	
}


// CMINEView ��ӡ


void CMINEView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMINEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMINEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMINEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMINEView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMINEView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMINEView ���

#ifdef _DEBUG
void CMINEView::AssertValid() const
{
	CView::AssertValid();
}

void CMINEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMINEDoc* CMINEView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMINEDoc)));
	return (CMINEDoc*)m_pDocument;
}
#endif //_DEBUG


// CMINEView ��Ϣ�������


void CMINEView::OnLButtonDown(UINT nFlags, CPoint point)
{ 
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetTimer(1,50,NULL);
	secondstart=1;
	CDC *pDC=GetDC();
	CDC Dc;
 	if(Dc.CreateCompatibleDC(pDC)==FALSE)
 		 MessageBox(_T("Can't create DC"));	

	//��ʾ���°�ť
	if(point.x>180&&point.x<210&&point.y>10&&point.y<40)
	{
    	Dc.SelectObject(m_anniu[3]);
    	pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);
	}
    if((point.x>=10)&&(point.x<=385)&&(point.y>=50)&&(point.y<=290))
	{	
		if(jieshu==1)
			return;
		secondstart=1;
		 //��ʾ���ڰ�ť
		Dc.SelectObject(m_anniu[1]);
		pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);		  
		int a=(point.x-10)/15;
		int b=(point.y-50)/15;

		if(jieshu==0&&MINE[a][b].shumu==-1&&MINE[a][b].weitu==2)
			if(leftnum==0)
				MessageBox(_T("��Ӯ��"));

		if(MINE[a][b].weitu==0||MINE[a][b].weitu==3)
        {
		    if(MINE[a][b].shumu==-1)
			{
				jieshu=1; 
				KillTimer(1);
			    Invalidate();
				MessageBox(_T("��ʧ����"));	
			}
            else 
			{		
				MINE[a][b].weitu=1;
				CRect rect;
				rect.left=a*15+10;
				rect.right=a*15+25;
				rect.top=b*15+50;
				rect.bottom=b*15+65;
				InvalidateRect(&rect);				
			}
		}
		
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMINEView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC=GetDC();
 	CDC Dc;
 	if(Dc.CreateCompatibleDC(pDC)==FALSE)
 		MessageBox(_T("Can't create DC"));	
	//��ʾ��ť
	Dc.SelectObject(m_anniu[0]);
	pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);
	secondstart=1;	
	if(jieshu==1)
	{
		Dc.SelectObject(m_anniu[2]);
		pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);
	}	
	if(point.x>180&&point.x<210&&point.y>10&&point.y<40)
	    OnStart();	
	CView::OnLButtonUp(nFlags, point);
}


void CMINEView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡָ��pdc
	SetTimer(1,50,NULL);
	secondstart=1;
    if(jieshu==1)
		return;
	
	if((point.x>=10)&&(point.x<=385)&&(point.y>=50)&&(point.y<=290))
	{	
		int a=(point.x-10)/15;
		int b=(point.y-50)/15;

		if(jieshu==0&&MINE[a][b].shumu==-1&&MINE[a][b].weitu==2)
			if(leftnum==0)	
				MessageBox(_T("��Ӯ��"));

		if(MINE[a][b].weitu==0||MINE[a][b].weitu==3)	
		{
			MINE[a][b].weitu=2;			
			leftnum--;			
		}
	    else
			if(MINE[a][b].weitu==2)
			{
				MINE[a][b].weitu=3;
				leftnum++;
			}
        //�ػ�ʣ������
		CRect rect2;
		rect2.left=20;
		rect2.right=70;
		rect2.top=10;
		rect2.bottom=40;
		InvalidateRect(&rect2);			
		//�ػ��������
		CRect rect;
    	rect.left=a*15+10;
		rect.right=a*15+25;
		rect.top=b*15+50;
		rect.bottom=b*15+65;
		InvalidateRect(&rect);		
	}
	CView::OnRButtonDown(nFlags, point);
}


void CMINEView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//����������
	if(jieshu==1)
		return;
	//��ʾ����Ϊ0�ķ���
	minezero();
	//��ʱ
	if(secondstart>0&&secondstart<20)
	{
		secondstart++;
	}
	if(secondstart==20)
	{
		secondstart=1;
		second++;	
		//�ػ�ʱ��
    	CRect rect3;
		rect3.left=325;
		rect3.right=375;
		rect3.top=10;
		rect3.bottom=40;
		InvalidateRect(&rect3);	
	}
	
	CView::OnTimer(nIDEvent);
}


void CMINEView::minezero()
{
    for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			if(MINE[i][j].shumu==0&&MINE[i][j].weitu==1)
			{
				for(int n=i-1;n<i+2;n++)
					for(int m=j-1;m<j+2;m++)
						if(n>=0&&n<25&&m>=0&&m<m_ColCount)
							if(MINE[n][m].shumu!=-1&&MINE[n][m].weitu==0)
							{
							    MINE[n][m].weitu=1;
								CRect rect;
								rect.left=n*15+10;
								rect.right=n*15+25;
								rect.top=m*15+50;
								rect.bottom=m*15+65;
								InvalidateRect(&rect);		
							}
			}

}

void CMINEView::OnSetleinum()
{
	// TODO: �ڴ���������������
	Setdlg dlg;
	dlg.leinum=leinum;	
	dlg.Onlong=m_RowCount;  //����	
	dlg.Onwidth=m_ColCount;  //����
	if(IDOK==dlg.DoModal())
	{
		leinum=dlg.leinum;
		m_RowCount=dlg.Onlong;  //����	
		m_ColCount=dlg.Onwidth;  //����
	}
}


void CMINEView::OnStart()
{
	// TODO: �ڴ���������������
	SetTimer(1,50,NULL);
	// TODO: Add your command handler code here
	second=0;//��ʱ
	secondstart=0;//1ʱ��ʼ��ʱ
	//	num=0;
    leftnum=leinum;//ʣ������
	jieshu=0;//jieshu=1ʱֹͣ
	int aa=0;
	//��ʼ��0
	for(int i=0;i<m_RowCount;i++)
	{
		for(int j=0;j<m_ColCount;j++)
		{
			MINE[i][j].shumu=0;
			MINE[i][j].weitu=0;
		}
	}
	//����40����
	do
	{
		int k=rand()%m_RowCount;
		int l=rand()%m_ColCount;
		if(MINE[k][l].shumu!=-1)
		{
			MINE[k][l].shumu=-1; 
		    aa++; 
		}
	 
	}while(aa!=leinum);   
    //������ֵ
	for(int a=0;a<m_RowCount;a++)
		for(int b=0;b<m_ColCount;b++)
			if(MINE[a][b].shumu==0)
			{
				for(int c=a-1;c<a+2;c++)
					for(int d=b-1;d<b+2;d++)
						if(c>=0&&c<m_RowCount&&d>=0&&d<m_ColCount)
							if(MINE[c][d].shumu==-1)
								MINE[a][b].shumu++;		
			}
	
	Invalidate(); 
}


void CMINEView::Onlogout()
{
	// TODO: �ڴ���������������
	MessageBox(_T("��Ϸ����"));
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
