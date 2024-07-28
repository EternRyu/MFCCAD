#pragma once
#include <afxcview.h>
//#include <afxwin.h>
#include "MFCCADDoc.h"
// tree_cwnd 视图
#include "MFCCADView.h"

typedef class CMFCCADView;

class TreeCWnd : public CTreeView
{
	DECLARE_DYNCREATE(TreeCWnd)

protected:
	TreeCWnd();           // 动态创建所使用的受保护的构造函数
	virtual ~TreeCWnd();

	//初始化样式
	void InitTreeStyle();
	//更得到绘制窗口的指针
	void GetDrawPtr();
	//设置选中
	void SetDrawSelectObject(CMFCCADView* drawview, DWORD64 key);
	void UnDrawSelectObject(CMFCCADView* drawview);
private:
	CMFCCADView* draw = nullptr;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void DrawViewDelete();
};


