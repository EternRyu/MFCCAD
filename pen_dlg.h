#pragma once
#include "afxdialogex.h"

#define USER_SEND_LOGPEN WM_USER + 1
#define USER_SET_LOGPEN WM_USER + 2
// pen_dlg 对话框

class PenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PenDlg)

public:
	PenDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PenDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:

	void InitDlgControl();
	void UpdateWndData(LOGPEN* pen);
	void GetStyle(LOGPEN* pen);
	static LRESULT HookEditWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//static LRESULT HookMainDlgWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	virtual void PostNcDestroy();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

public:
	afx_msg void ButtonSetPen();
	afx_msg void OnBnClickedButton2();

public:
	static PenDlg* pdlg_ptr;
	WNDPROC old_wndfun_ptr = nullptr;;
	HWND p_hwnd = nullptr;

	//LOGPEN pen_style;
	// 笔样式
	CComboBox pen_style_ccb;
	// 笔像素
	CEdit px_edit;
	// 笔颜色
	CMFCColorButton pen_color_cb;
	
};
