#pragma once
#include "MFCCADDoc.h"
#include "MFCCADView.h"

// dlg_view 窗体视图
typedef class CMFCCADView;

class DlgView : public CFormView
{
	DECLARE_DYNCREATE(DlgView)

protected:
	DlgView();           // 动态创建所使用的受保护的构造函数
	virtual ~DlgView();

public:
	//获得绘画窗口指针 
	void GetDrawPtr();
	//初始化界面
	void InitDlgView();
	//设置画笔画刷
	void SetDefStyle(LOGBRUSH brush, LOGPEN pen);
	//获取样式
	void GetDlgvViewStyle();
	//更新对话框
	void UpdateDlgView();
	//更新绘画窗口
	void UpdateDrawWnd();
	//编辑框回调
	static LRESULT HookEditWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//绘制窗口的指针
	CMFCCADView * draw = nullptr;

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

	static DlgView* pdlg_ptr;
	WNDPROC old_wndfun_ptr = nullptr;;
	HWND p_hwnd = nullptr;

public:
	virtual void OnInitialUpdate();
	afx_msg void SetStyleToSelect();
};


