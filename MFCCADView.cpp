
// MFCCADView.cpp: CMFCCADView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCCAD.h"
#endif

#include "MFCCADDoc.h"
#include "MFCCADView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCCADView

IMPLEMENT_DYNCREATE(CMFCCADView, CView)

BEGIN_MESSAGE_MAP(CMFCCADView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(DRAW_LINE, &CMFCCADView::DrawLineMenuButton)
	ON_COMMAND(DRAW_RECTANGLE, &CMFCCADView::DrawRectangleMenuButton)
	ON_COMMAND(DRAW_ROUND, &CMFCCADView::DrawRoundMenuButton)
	ON_COMMAND(DRAW_FIVESTAR, &CMFCCADView::DrawFivePointedStarMenuButton)
	ON_COMMAND(DRAW_PEN, &CMFCCADView::OpenPenDlg)
	ON_COMMAND(DRAW_BRUSH, &CMFCCADView::OpenBeushDlg)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(MENU_MOVE, &CMFCCADView::MenuMove)
	ON_COMMAND(MENU_DELETE, &CMFCCADView::MenuDelete)
	ON_COMMAND(MENU_ROTATE, &CMFCCADView::MenuRotate)
	ON_COMMAND(MENU_EDIT_STYLE, &CMFCCADView::MenuEditStyle)
	ON_COMMAND(ID_EDIT_UNDO, &CMFCCADView::OnEditUndo)
	ON_COMMAND(ID_EDIT_RUNDO, &CMFCCADView::OnEditRundo)
	ON_COMMAND(ID_FILE_SAVE, &CMFCCADView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CMFCCADView::OnFileOpen)
END_MESSAGE_MAP()

// CMFCCADView 构造/析构

CMFCCADView::CMFCCADView() noexcept
{
	// TODO: 在此处添加构造代码
	current_pen.lopnStyle = PS_SOLID;
	current_pen.lopnWidth.x = 1;
	current_pen.lopnColor = RGB(0, 0, 0);

	current_brush.lbStyle = BS_NULL;
	current_brush.lbHatch = HS_VERTICAL;
	current_brush.lbColor = RGB(255, 255, 255);

	//typedef std::shared_ptr<DLine> DLinePtr;
	//DLinePtr aa = std::make_shared<DLine>(new DLine);
	//DLinePtr bb = std::make_shared<DLine>(*aa);
	//aa->BrushSetlobStyle(10);
	return;
}

CMFCCADView::~CMFCCADView()
{
}

BOOL CMFCCADView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCCADView 绘图

/// <summary>
/// 更新树窗口
/// </summary>
void CMFCCADView::UpdateTreeView() {

	CMFCCADDoc* doc_ptr = (CMFCCADDoc*)GetDocument();

	POSITION pos = doc_ptr->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = doc_ptr->GetNextView(pos);
		if (pView->GetRuntimeClass()->IsDerivedFrom(RUNTIME_CLASS(TreeCWnd))) {
			TreeCWnd* tree = (TreeCWnd*)pView;
			CTreeCtrl& tree_ctrl = tree->GetTreeCtrl();
			AddDataTreeView(tree_ctrl);
			return;
		}
	}
	return;
}

/// <summary>
/// 添加数据到Tree控件
/// </summary>
/// <param name="tree_ctrl">CTreeCtrl</param>
void CMFCCADView::AddDataTreeView(CTreeCtrl& tree_ctrl) {
	//清空数据
	tree_ctrl.DeleteAllItems();
	//得到所有图形信息
	GraphInfoStack stack;
	drawdc.GetGraphInfo(stack);
	//导入到控件
	while (!stack.empty()) {
		GraphInfo temp = stack.top();

		CString tempstr;
		tempstr.Format(_T("%s:ID(%d)"), temp.type.GetBuffer(), temp.key);
		HTREEITEM root = tree_ctrl.InsertItem(tempstr);

		tempstr.Format(_T("%d"), temp.key);
		tree_ctrl.InsertItem(tempstr, root);

		tempstr.Format(_T("起点:(X=%d)-(Y=%d)"), temp.coord1.x, temp.coord1.y);
		tree_ctrl.InsertItem(tempstr, root);

		tempstr.Format(_T("终点:(X=%d)-(Y=%d)"), temp.coord2.x, temp.coord2.y);
		tree_ctrl.InsertItem(tempstr, root);

		stack.pop();
	}
	return;
}

void CMFCCADView::OnDraw(CDC* pDC)
{
	CMFCCADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) {
		return;
	}
	// TODO: 在此处为本机数据添加绘制代码
	CRect crect_wnd;
	GetClientRect(&crect_wnd);
	drawdc.DrawPaintDC(pDC, crect_wnd);
	//更新树控件
	UpdateTreeView();
	return;
}


// CMFCCADView 打印

BOOL CMFCCADView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCCADView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCCADView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCCADView 诊断

#ifdef _DEBUG
void CMFCCADView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCCADView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCCADDoc* CMFCCADView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCCADDoc)));
	return (CMFCCADDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCCADView 消息处理程序


void CMFCCADView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//移动操作
	if (drawdc.SelectEmpty()) {
		rb_menu = Menu::OPERATION_NULL;
	}
	if (rb_menu == Menu::OPERATION_MOVE) {
		drawdc.MoveStart(point);
	}
	//鼠标选中判断
	drawdc.IsSelect(point);
	//保存图形的起点
	drawdc.DrawSetBeginPoint(point);
	CView::OnLButtonDown(nFlags, point);
}


void CMFCCADView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//左键按下才绘制
	if ((nFlags & MK_LBUTTON)) {

		//移动操作
		if (rb_menu == Menu::OPERATION_MOVE) {
			drawdc.Moving(point);
		}

		//保存图形的终点

		drawdc.DrawSetEndPoint(point);
		drawdc.DrawSetPen(current_pen);
		drawdc.DrawSetBrush(current_brush);
		//更新界面
		InvalidateRect(nullptr, FALSE);
		UpdateWindow();
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCCADView::OnLButtonUp(UINT nFlags, CPoint point) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//移动操作
	if (rb_menu == Menu::OPERATION_MOVE) {
		drawdc.MoveEnd(point);
	}
	//保存图形的终点
	drawdc.DrawSetEndPoint(point);
	//保存图形对象
	drawdc.DrawObjectPush();
	//设置全局默认样式
	drawdc.DrawSetPen(current_pen);
	drawdc.DrawSetBrush(current_brush);
	//释放临时对象
	drawdc.DrawObjectReset();
	//更新界面
	InvalidateRect(nullptr, FALSE);
	UpdateWindow();
	CView::OnLButtonUp(nFlags, point);
}


/// <summary>
/// 菜单按钮直线
/// </summary>
void CMFCCADView::DrawLineMenuButton() {
	drawdc.DrawLine();
	return;
}

/// <summary>
/// 菜单按钮矩形
/// </summary>
void CMFCCADView::DrawRectangleMenuButton() {
	drawdc.DrawRectangle();
	return;
}

/// <summary>
/// 菜单按钮圆形
/// </summary>
void CMFCCADView::DrawRoundMenuButton() {
	drawdc.DrawRound();
	return;
}

/// <summary>
/// 菜单按钮多边形五角星
/// </summary>
void CMFCCADView::DrawFivePointedStarMenuButton() {
	drawdc.ExDrawFivePointedStar();
	return;
}

/// <summary>
/// 打开画笔设置窗口
/// </summary>
void CMFCCADView::OpenPenDlg() {
	PenDlg* sdlg = new PenDlg();
	sdlg->Create(IDD_DIALOG1, this);
	sdlg->ShowWindow(SW_SHOW);
	LOGPEN* temp = new LOGPEN;
	*temp = current_pen;
	::PostMessage(sdlg->GetSafeHwnd(), USER_SEND_LOGPEN, (WPARAM)temp, (LPARAM)m_hWnd);
	return;
}


BOOL CMFCCADView::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == USER_SET_LOGPEN && pMsg->wParam) {
		LOGPEN* pen_ptr = (LOGPEN*)pMsg->wParam;
		current_pen = *pen_ptr;
		delete pen_ptr;
		return TRUE;
	}
	else if (pMsg->message == USER_SET_BRUSH && pMsg->wParam) {
		LOGBRUSH* brush_ptr = (LOGBRUSH*)pMsg->wParam;
		current_brush = *brush_ptr;
		delete brush_ptr;
		return TRUE;
	}
	return CView::PreTranslateMessage(pMsg);
}

/// <summary>
/// 打开画刷设置窗口
/// </summary>
void CMFCCADView::OpenBeushDlg() {
	BrushDlg* sdlg = new BrushDlg();
	sdlg->Create(IDD_DIALOG2, this);
	sdlg->ShowWindow(SW_SHOW);
	LOGBRUSH* temp = new LOGBRUSH;
	*temp = current_brush;
	::PostMessage(sdlg->GetSafeHwnd(), USER_SEND_BRUSH, (WPARAM)temp, (LPARAM)m_hWnd);
	return;
}


void CMFCCADView::OnRButtonDown(UINT nFlags, CPoint point) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	rb_menu = Menu::OPERATION_NULL;
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	if (drawdc.SelectEmpty()) {
		menu.EnableMenuItem(MENU_MOVE, TRUE);
		menu.EnableMenuItem(MENU_ROTATE, TRUE);
		menu.EnableMenuItem(MENU_DELETE, TRUE);
		menu.EnableMenuItem(MENU_EDIT_STYLE, TRUE);
	}
	else {
		menu.EnableMenuItem(MENU_MOVE, FALSE);
		menu.EnableMenuItem(MENU_ROTATE, FALSE);
		menu.EnableMenuItem(MENU_DELETE, FALSE);
		menu.EnableMenuItem(MENU_EDIT_STYLE, FALSE);
	}
	CMenu* pPopup = menu.GetSubMenu(0);
	CPoint pointPos;
	GetCursorPos(&pointPos);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pointPos.x, pointPos.y, this);
	CView::OnRButtonDown(nFlags, point);
}

/// <summary>
/// 移动操作
/// </summary>
void CMFCCADView::MenuMove() {
	rb_menu = Menu::OPERATION_MOVE;
	return;
}

/// <summary>
/// 删除操作
/// </summary>
void CMFCCADView::MenuDelete() {
	drawdc.DeletePattern();
	//更新界面
	InvalidateRect(nullptr, TRUE);
	UpdateWindow();
	return;
}

/// <summary>
/// 旋转操作
/// </summary>
void CMFCCADView::MenuRotate() {
	
	drawdc.RotatePattern(90);
	//更新界面
	InvalidateRect(nullptr, FALSE);
	UpdateWindow();
	return;
}

/// <summary>
/// 选中对象设置样式
/// </summary>
void CMFCCADView::MenuEditStyle() {
	EditStyleDlg editdlg;
	editdlg.InitDefStyle(drawdc.DrawSelectGetBrush(), drawdc.DrawSelectGetPen());
	INT_PTR nResponse = editdlg.DoModal();
	if (nResponse == IDOK) {
		drawdc.DrawSelectSetBrush(editdlg.logbrush);
		drawdc.DrawSelectSetPen(editdlg.logpen);

		InvalidateRect(nullptr, FALSE);
		UpdateWindow();
	}
	return;
}

/// <summary>
/// 撤销操作
/// </summary>
void CMFCCADView::OnEditUndo() {
	drawdc.DrawUndo();
	InvalidateRect(nullptr, FALSE);
	UpdateWindow();
	return;
}

/// <summary>
/// 重做操作
/// </summary>
void CMFCCADView::OnEditRundo() {
	drawdc.DrawRUndo();
	InvalidateRect(nullptr, FALSE);
	UpdateWindow();
	return;
}

/// <summary>
/// 菜单点击保存
/// </summary>
void CMFCCADView::OnFileSave() {
	//保存文件
	CFileDialog file_dlg(FALSE, L"ini", L"data.ini", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"ini files(.ini)||", NULL);//打开文件
	if (file_dlg.DoModal() != IDOK) {//判断是否成功
		return;
	}
	CString path = file_dlg.GetPathName();
	//序列化
	drawdc.Serialization(path.GetBuffer());
	return;
}

/// <summary>
/// 菜单点击打开
/// </summary>
void CMFCCADView::OnFileOpen() {

	//保存文件
	CFileDialog file_dlg(TRUE, L"ini", L"*.ini", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"ini files(*.ini)||", NULL);//打开文件
	if (file_dlg.DoModal() != IDOK) {//判断是否成功
		return;
	}
	CString path = file_dlg.GetPathName();
	drawdc.Deserialization(path.GetBuffer());
	InvalidateRect(nullptr, FALSE);
	UpdateWindow();
	return;
}
