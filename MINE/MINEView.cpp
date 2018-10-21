
// MINEView.cpp : CMINEView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CMINEView 构造/析构

CMINEView::CMINEView()
{
	// TODO: 在此处添加构造代码
	for(int ii=0;ii<12;ii++)
		m_Bitmap[ii].LoadBitmap(IDB_BITMAP0+ii);
    for(int jj=0;jj<4;jj++)
		m_anniu[jj].LoadBitmap(IDB_ANNIU1+jj);
    //计时
	second=0; 
	 //1时开始计时
	secondstart=0;
	secondstart1=0;
    //行数
	m_RowCount=25; 
	 //列数
	m_ColCount=16; 
	//雷数
    leinum=80;
	 //剩余雷数
	leftnum=leinum; 
	 //jieshu=1时停止
	jieshu=0; 

	int aa=0;
 
	//初始化为0
	for(int i=0;i<m_RowCount;i++)
	{
		for(int j=0;j<m_ColCount;j++)
		{
			MINE[i][j].shumu=0;
			MINE[i][j].weitu=0;
		}
	}
	//获取当前时间
	CTime time=GetCurrentTime();

	int s;
	//获取秒数
	s=time.GetSecond();
	//设置80个雷
	do
	{
		//以当前秒数为产生随机算法
		int k=(rand()*s)%m_RowCount;
		int l=(rand()*s)%m_ColCount;
       //为了避免一个位置同时算两个雷
       //只允许当前位置不是雷时赋值为雷
		if(MINE[k][l].shumu!=-1)
		{
			MINE[k][l].shumu=-1; 
		    aa++; 
		}
	 
	}while(aa!=leinum);   
    //给方格赋值，计算雷数
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMINEView 绘制

void CMINEView::OnDraw(CDC*pDC)
{
	CMINEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//画背景
    CBrush mybrush1;
 	mybrush1.CreateSolidBrush(RGB(192,192,192));
 	CRect myrect1(0,0,1200,800);
 	pDC->FillRect(myrect1,&mybrush1);
	//画黑框
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
	//画黑框的白线
	pDC->MoveTo(20,40);
	pDC->LineTo(70,40);
	pDC->LineTo(70,10);
	pDC->MoveTo(325,40);
	pDC->LineTo(375,40);
	pDC->LineTo(375,10);
	//画雷区边线
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
	 //显示按钮
	 Dc.SelectObject(m_anniu[0]);
	 pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);
     //判断显示什么位图
	 //weitu=1已按下的数字区
	 //weitu=2显示旗
	 //weitu=3显示问号
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
				//结束
				if(jieshu==1&&MINE[a][b].shumu==-1)
				{
                    Dc.SelectObject(m_Bitmap[11]);
					pDC->BitBlt(a*15+10,b*15+50,160,160,&Dc,0,0,SRCCOPY);
					Dc.SelectObject(m_anniu[2]);
					pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);
				}
				
			}
	//显示黑框里的数字
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


// CMINEView 打印


void CMINEView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMINEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMINEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMINEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CMINEView 诊断

#ifdef _DEBUG
void CMINEView::AssertValid() const
{
	CView::AssertValid();
}

void CMINEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMINEDoc* CMINEView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMINEDoc)));
	return (CMINEDoc*)m_pDocument;
}
#endif //_DEBUG


// CMINEView 消息处理程序


void CMINEView::OnLButtonDown(UINT nFlags, CPoint point)
{ 
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetTimer(1,50,NULL);
	secondstart=1;
	CDC *pDC=GetDC();
	CDC Dc;
 	if(Dc.CreateCompatibleDC(pDC)==FALSE)
 		 MessageBox(_T("Can't create DC"));	

	//显示按下按钮
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
		 //显示窗口按钮
		Dc.SelectObject(m_anniu[1]);
		pDC->BitBlt(180,10,160,160,&Dc,0,0,SRCCOPY);		  
		int a=(point.x-10)/15;
		int b=(point.y-50)/15;

		if(jieshu==0&&MINE[a][b].shumu==-1&&MINE[a][b].weitu==2)
			if(leftnum==0)
				MessageBox(_T("你赢了"));

		if(MINE[a][b].weitu==0||MINE[a][b].weitu==3)
        {
		    if(MINE[a][b].shumu==-1)
			{
				jieshu=1; 
				KillTimer(1);
			    Invalidate();
				MessageBox(_T("你失败了"));	
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC=GetDC();
 	CDC Dc;
 	if(Dc.CreateCompatibleDC(pDC)==FALSE)
 		MessageBox(_T("Can't create DC"));	
	//显示按钮
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//获取指针pdc
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
				MessageBox(_T("你赢了"));

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
        //重画剩下雷数
		CRect rect2;
		rect2.left=20;
		rect2.right=70;
		rect2.top=10;
		rect2.bottom=40;
		InvalidateRect(&rect2);			
		//重画打击格子
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//结束，返回
	if(jieshu==1)
		return;
	//显示个数为0的方格
	minezero();
	//计时
	if(secondstart>0&&secondstart<20)
	{
		secondstart++;
	}
	if(secondstart==20)
	{
		secondstart=1;
		second++;	
		//重画时间
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
	// TODO: 在此添加命令处理程序代码
	Setdlg dlg;
	dlg.leinum=leinum;	
	dlg.Onlong=m_RowCount;  //行数	
	dlg.Onwidth=m_ColCount;  //列数
	if(IDOK==dlg.DoModal())
	{
		leinum=dlg.leinum;
		m_RowCount=dlg.Onlong;  //行数	
		m_ColCount=dlg.Onwidth;  //列数
	}
}


void CMINEView::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1,50,NULL);
	// TODO: Add your command handler code here
	second=0;//计时
	secondstart=0;//1时开始计时
	//	num=0;
    leftnum=leinum;//剩余雷数
	jieshu=0;//jieshu=1时停止
	int aa=0;
	//初始化0
	for(int i=0;i<m_RowCount;i++)
	{
		for(int j=0;j<m_ColCount;j++)
		{
			MINE[i][j].shumu=0;
			MINE[i][j].weitu=0;
		}
	}
	//设置40个雷
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
    //给方格赋值
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
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("游戏结束"));
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
