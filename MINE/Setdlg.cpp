// Setdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MINE.h"
#include "Setdlg.h"
#include "afxdialogex.h"


// Setdlg �Ի���

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


// Setdlg ��Ϣ�������


void Setdlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	Invalidate();
}


void Setdlg::OnEnChangelong()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	Invalidate();
}


void Setdlg::OnEnChangewidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	Invalidate();
}
