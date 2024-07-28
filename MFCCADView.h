
// MFCCADView.h: CMFCCADView 类的接口
//

#pragma once
#include "draw/draw.h"
#include "pen_dlg.h"
#include "brush_dlg.h"
#include "edit_style_dlg.h"
#include "MFCCADDoc.h"
#include "tree_cwnd.h"
#include "dlg_view.h"

typedef class DlgView;

class CMFCCADView : public CView {

	enum class Menu {
		OPERATION_NULL,
		OPERATION_MOVE
	}rb_menu;
protected: // 仅从序列化创建
	CMFCCADView() noexcept;
	DECLARE_DYNCREATE(CMFCCADView)

// 特性
public:
	CMFCCADDoc* GetDocument() const;

// 操作
public:

private:
	//更新Tree控件
	void UpdateTreeView();
	//添加数据到Tree控件
	void AddDataTreeView(CTreeCtrl& tree_ctrl);
	//更新ViewDlg控件
	void UpdateDlgView();
	//添加数据到dlg控件
	void SetDataForDlgView(DlgView* dlg);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCCADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CPoint cp_begin;
	DrawDC drawdc;
	LOGPEN current_pen;
	LOGBRUSH current_brush;
protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//重写
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);//重写
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);//重写
	afx_msg void DrawLineMenuButton();
	afx_msg void DrawRectangleMenuButton();
	afx_msg void DrawRoundMenuButton();
	afx_msg void DrawFivePointedStarMenuButton();
	afx_msg void OpenPenDlg();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OpenBeushDlg();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void MenuMove();
	afx_msg void MenuDelete();
	afx_msg void MenuRotate();
	afx_msg void MenuEditStyle();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRundo();
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // MFCCADView.cpp 中的调试版本
inline CMFCCADDoc* CMFCCADView::GetDocument() const
   { return reinterpret_cast<CMFCCADDoc*>(m_pDocument); }
#endif

