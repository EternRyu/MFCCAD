// brush_dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCCAD.h"
#include "afxdialogex.h"
#include "brush_dlg.h"


// brush_dlg 对话框

IMPLEMENT_DYNAMIC(BrushDlg, CDialogEx)

BrushDlg::BrushDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

BrushDlg::~BrushDlg()
{
}

void BrushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, brush_style_ccb);
	DDX_Control(pDX, IDC_COMBO2, brush_hatch_ccb);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, brush_color_cb);
}


BEGIN_MESSAGE_MAP(BrushDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &BrushDlg::SetBrushStyle)
	ON_BN_CLICKED(IDC_BUTTON2, &BrushDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// brush_dlg 消息处理程序


BOOL BrushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDlgControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void BrushDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BrushDlg::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}

/// <summary>
/// 初始化控件
/// </summary>
void BrushDlg::InitDlgControl() {
	
	brush_style_ccb.AddString(L"实心画笔"); //BS_SOLID 0
	brush_style_ccb.AddString(L"空心画笔");	//BS_NULL 1
	brush_style_ccb.AddString(L"阴影画笔");	//BS_HATCHED
	brush_style_ccb.SetCurSel(BS_SOLID);

//#define HS_HORIZONTAL       0       /* ----- */
//#define HS_VERTICAL         1       /* ||||| */
//#define HS_FDIAGONAL        2       /* \\\\\ */
//#define HS_BDIAGONAL        3       /* ///// */
//#define HS_CROSS            4       /* +++++ */
//#define HS_DIAGCROSS        5       /* xxxxx */
	brush_hatch_ccb.AddString(L"水平阴影"); //HS_HORIZONTAL
	brush_hatch_ccb.AddString(L"垂直阴影");	//HS_VERTICAL
	brush_hatch_ccb.AddString(L"向下45度");	//HS_FDIAGONAL
	brush_hatch_ccb.AddString(L"向上45度");	//HS_BDIAGONAL
	brush_hatch_ccb.AddString(L"水平垂直");	//HS_CROSS
	brush_hatch_ccb.AddString(L"45度交叉");	//HS_DIAGCROS
	brush_hatch_ccb.SetCurSel(0);

	brush_color_cb.EnableOtherButton(_T("Other"), FALSE, TRUE);
	return;
}

/// <summary>
/// 更新数据
/// </summary>
void BrushDlg::UpdateWndData(LOGBRUSH* brush) {
	brush_style_ccb.SetCurSel(brush->lbStyle);
	brush_hatch_ccb.SetCurSel(brush->lbHatch);
	brush_color_cb.SetColor(brush->lbColor);
	return;
}

void BrushDlg::GetStyle(LOGBRUSH* brush) {
	if (!brush) {
		return;
	}
	brush->lbStyle = brush_style_ccb.GetCurSel();
	brush->lbHatch = brush_hatch_ccb.GetCurSel();

	COLORREF color = brush_color_cb.GetColor();
	if (color == -1) {
		color = brush_color_cb.GetAutomaticColor();
	}
	brush->lbColor = color;
	return;
}


void BrushDlg::OnBnClickedButton2() {
	OnCancel();
	return;
}

/// <summary>
/// 设置样式
/// </summary>
void BrushDlg::SetBrushStyle() {
	LOGBRUSH* temp = new LOGBRUSH;
	GetStyle(temp);
	::PostMessage(p_hwnd, USER_SET_BRUSH, (WPARAM)temp, NULL);
}

BOOL BrushDlg::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == USER_SEND_BRUSH && pMsg->wParam && pMsg->lParam) {
		LOGBRUSH* brush_ptr = (LOGBRUSH* )pMsg->wParam;
		p_hwnd = (HWND)pMsg->lParam;
		UpdateWndData(brush_ptr);
		delete brush_ptr;
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

