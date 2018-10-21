#pragma once


// Setdlg 对话框

class Setdlg : public CDialog
{
	DECLARE_DYNAMIC(Setdlg)

public:
	Setdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Setdlg();

// 对话框数据
	enum { IDD = IDD_SETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	int leinum;
	int Onlong;
	afx_msg void OnEnChangelong();
	afx_msg void OnEnChangewidth();
	int Onwidth;
};
