#pragma once


// Setdlg �Ի���

class Setdlg : public CDialog
{
	DECLARE_DYNAMIC(Setdlg)

public:
	Setdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Setdlg();

// �Ի�������
	enum { IDD = IDD_SETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	int leinum;
	int Onlong;
	afx_msg void OnEnChangelong();
	afx_msg void OnEnChangewidth();
	int Onwidth;
};
