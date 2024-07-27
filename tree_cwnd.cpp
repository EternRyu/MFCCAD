// tree_cwnd.cpp: 实现文件
//

#include "pch.h"
#include "MFCCAD.h"
#include "tree_cwnd.h"


// tree_cwnd

IMPLEMENT_DYNCREATE(TreeCWnd, CTreeView)

TreeCWnd::TreeCWnd() {
}

TreeCWnd::~TreeCWnd()
{
}

/// <summary>
/// 初始化样式
/// </summary>
void TreeCWnd::InitTreeStyle() {
	CTreeCtrl& tree = GetTreeCtrl();
	//添加风格
	this->ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
	return;
}

void TreeCWnd::GetDrawPtr() {
	CMFCCADDoc* doc_ptr = (CMFCCADDoc*)GetDocument();

	POSITION pos = doc_ptr->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = doc_ptr->GetNextView(pos);
		if (pView->GetRuntimeClass()->IsDerivedFrom(RUNTIME_CLASS(CMFCCADView))) {
			draw = (CMFCCADView*)pView;
			return;
		}
	}
	return;
}



void TreeCWnd::SetDrawSelectObject(CMFCCADView* drawview,DWORD64 key) {
	if (!drawview) {
		return;
	}
	drawview->drawdc.IsSelect(key);
	drawview->InvalidateRect(nullptr, FALSE);
	drawview->UpdateWindow();
	return;
}

/// <summary>
/// 取消选中
/// </summary>
/// <param name="drawview">窗口对象</param>
void TreeCWnd::UnDrawSelectObject(CMFCCADView* drawview) {
	if (!drawview) {
		return;
	}
	CPoint point;
	// 获取屏幕鼠标坐标
	GetCursorPos(&point);
	ScreenToClient(&point);
	CTreeCtrl& tree = GetTreeCtrl();
	UINT uFlag = 0;
	HTREEITEM item = tree.HitTest(point, &uFlag);
	//如果选中了节点直接返回
	if (!item && !(TVHT_ONITEMSTATEICON & uFlag)) {
		drawview->drawdc.UnSelect();
		drawview->InvalidateRect(nullptr, FALSE);
		drawview->UpdateWindow();
		return;
	}

	HTREEITEM temp = tree.GetParentItem(item);


	//是父亲节点
	if (temp == nullptr) {
		//获取第一个子结点
		item = tree.GetChildItem(item);
	}
	else {//子节点检索的父亲节点
		//获取第一个子结点 
		//hitem = tree.GetChildItem(temp);
		return;
	}
	//图形的key
	CString str = tree.GetItemText(item);
	SetDrawSelectObject(draw, _ttoi(str));
	return;
}

BEGIN_MESSAGE_MAP(TreeCWnd, CTreeView)
	//ON_NOTIFY_REFLECT(TVN_SELCHANGED, &TreeCWnd::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(NM_CLICK, &TreeCWnd::OnNMClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, &TreeCWnd::OnNMRClick)
	ON_COMMAND(MENU2_DELETE, &TreeCWnd::DrawViewDelete)
END_MESSAGE_MAP()


// tree_cwnd 诊断

#ifdef _DEBUG
void TreeCWnd::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void TreeCWnd::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// tree_cwnd 消息处理程序

void TreeCWnd::OnInitialUpdate() {
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	InitTreeStyle();
	GetDrawPtr();
}

void TreeCWnd::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult) {
	UnDrawSelectObject(draw);
	*pResult = 0;
}





void TreeCWnd::OnNMRClick(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: 在此添加控件通知处理程序代码
	CPoint point;
	// 获取屏幕鼠标坐标
	GetCursorPos(&point);
	ScreenToClient(&point);
	CTreeCtrl& tree = GetTreeCtrl();
	UINT uFlag = 0;
	HTREEITEM item = tree.HitTest(point, &uFlag);
	if (!item) {
		return;
	}

	CMenu menu;
	menu.LoadMenu(IDR_MENU2);
	//if (!item) {
	//	menu.EnableMenuItem(MENU2_ROTATE, TRUE);
	//	menu.EnableMenuItem(MENU2_DELETE, TRUE);
	//}
	//else {
	//	menu.EnableMenuItem(MENU2_ROTATE, FALSE);
	//	menu.EnableMenuItem(MENU2_DELETE, FALSE);
	//}
	CMenu* pPopup = menu.GetSubMenu(0);
	CPoint pointPos;
	GetCursorPos(&pointPos);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pointPos.x, pointPos.y, this);
	*pResult = 0;
}

/// <summary>
/// 菜单右键删除事件
/// </summary>
void TreeCWnd::DrawViewDelete() {
	if (!draw) {
		return;
	}
	draw->drawdc.DeletePattern();
	draw->InvalidateRect(nullptr, FALSE);
	draw->UpdateWindow();
	return;
}
