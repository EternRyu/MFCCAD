#pragma once
#include "afxdialogex.h"


// edit_style_dlg 对话框

class EditStyleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditStyleDlg)

public:
	EditStyleDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~EditStyleDlg();

public:
	static LRESULT HookEditWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitDefStyle(LOGBRUSH brush, LOGPEN pen);
	void InitDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 画刷样式
	CComboBox brush_style_ccb;
	// 画刷阴影
	CComboBox brush_hatch_ccb;
	// 画刷颜色
	CMFCColorButton brush_colour_cb;
	// 画笔样式
	CComboBox pen_style_ccb;
	// 画笔宽度
	CEdit pen_width_edit;
	// 画笔颜色
	CMFCColorButton pen_colour_cb;

	LOGBRUSH logbrush;
	LOGPEN logpen;

	static EditStyleDlg* pdlg_ptr;
	WNDPROC old_wndfun_ptr = nullptr;;
	HWND p_hwnd = nullptr;

public:
	virtual BOOL OnInitDialog();
	afx_msg void ButtonOk();
	afx_msg void OnBnClickedButton2();
};
