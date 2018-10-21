// Setdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MINE.h"
#include "Setdlg.h"
#include "afxdialogex.h"


// Setdlg 对话框

IMPLEMENT_DYNAMIC(Setdlg, CDialog)

Setdlg::Setdlg(CWnd* pParent /*=NULL*/)
	: CDialog(Setdlg::IDD, pParent)
	, leinum(0)
	, Onlong(0)
	, Onwidth(0)
{

}

Setdlg::~Setdlg()
{
}

void Setdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, leinum);
	DDX_Text(pDX, IDC_EDIT2, Onlong);
	DDV_MinMaxInt(pDX, Onlong, 1, 25);
	DDX_Text(pDX, IDC_EDIT3, Onwidth);
	DDV_MinMaxInt(pDX, Onwidth, 1, 16);
	DDV_MinMaxInt(pDX, leinum, 1, 99);
}


BEGIN_MESSAGE_MAP(Setdlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &Setdlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &Setdlg::OnEnChangelong)
	ON_EN_CHANGE(IDC_EDIT3, &Setdlg::OnEnChangewidth)
END_MESSAGE_MAP()


// Setdlg 消息处理程序


void Setdlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	Invalidate();
}


void Setdlg::OnEnChangelong()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	Invalidate();
}


void Setdlg::OnEnChangewidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	Invalidate();
}
