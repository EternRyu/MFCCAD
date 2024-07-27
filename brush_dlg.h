#pragma once
#include "afxdialogex.h"

#define USER_SEND_BRUSH WM_USER + 3
#define USER_SET_BRUSH WM_USER + 4
// brush_dlg 对话框

class BrushDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BrushDlg)

public:
	BrushDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BrushDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void SetBrushStyle();
	afx_msg void OnBnClickedButton2();

public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	void InitDlgControl();
	void UpdateWndData(LOGBRUSH* brush);
	void GetStyle(LOGBRUSH* brush);
private:
	HWND p_hwnd = nullptr;
	// 画刷样式
	CComboBox brush_style_ccb;
	// 阴影样式
	CComboBox brush_hatch_ccb;
	// 颜色
	CMFCColorButton brush_color_cb;


};
