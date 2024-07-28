// edit_style_dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCCAD.h"
#include "afxdialogex.h"
#include "edit_style_dlg.h"

EditStyleDlg* EditStyleDlg::pdlg_ptr = nullptr;

// edit_style_dlg 对话框

IMPLEMENT_DYNAMIC(EditStyleDlg, CDialogEx)

EditStyleDlg::EditStyleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

EditStyleDlg::~EditStyleDlg()
{
}

LRESULT EditStyleDlg::HookEditWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_CHAR) {
		if (wParam == 0x8) {//BackSpace
			goto DEFAULT_WNDPROC;
		}
		else if (isdigit(wParam)) {
			goto DEFAULT_WNDPROC;
		}
		return FALSE;

	}
DEFAULT_WNDPROC:
	return pdlg_ptr->old_wndfun_ptr(hWnd, message, wParam, lParam);
}

void EditStyleDlg::InitDefStyle(LOGBRUSH brush, LOGPEN pen) {

	logbrush = brush;
	logpen = pen;
	return;
}

void EditStyleDlg::InitDlg() {
	brush_style_ccb.AddString(L"实心画笔"); //BS_SOLID 0
	brush_style_ccb.AddString(L"空心画笔");	//BS_NULL 1
	brush_style_ccb.AddString(L"阴影画笔");	//BS_HATCHED
	//brush_style_ccb.SetCurSel(BS_SOLID);

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
	//brush_hatch_ccb.SetCurSel(0);

	brush_colour_cb.EnableOtherButton(_T("Other"), FALSE, TRUE);

	pdlg_ptr = this;

	old_wndfun_ptr = (WNDPROC)SetWindowLongPtr(
		pen_width_edit.GetSafeHwnd(),
		GWLP_WNDPROC,
		(LONG_PTR)HookEditWndProc
	);

	//#define PS_SOLID            0       /* ------- */
	//#define PS_DASH             1       /* - - - -  */
	//#define PS_DOT              2       /* .......  */
	//#define PS_DASHDOT          3       /* _._._._  */
	//#define PS_DASHDOTDOT       4       /* _.._.._  */
	//#define PS_NULL             5       /* 无边框    */
	pen_style_ccb.AddString(L"_______");
	pen_style_ccb.AddString(L"_ _ _ _");
	pen_style_ccb.AddString(L".......");
	pen_style_ccb.AddString(L"_._._._");
	pen_style_ccb.AddString(L"_.._.._");
	pen_style_ccb.AddString(L"       ");
	//pen_style_ccb.SetCurSel(PS_SOLID);

	pen_colour_cb.EnableOtherButton(_T("Other"), FALSE, TRUE);

	//设置默认样式
	brush_style_ccb.SetCurSel(logbrush.lbStyle);
	brush_hatch_ccb.SetCurSel(logbrush.lbHatch);
	brush_colour_cb.SetColor(logbrush.lbColor);

	pen_style_ccb.SetCurSel(logpen.lopnStyle);

	CString str;
	str.Format(L"%d", logpen.lopnWidth.x);
	pen_width_edit.SetWindowText(str);

	pen_colour_cb.SetColor(logpen.lopnColor);

	return;
}

void EditStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, brush_style_ccb);
	DDX_Control(pDX, IDC_COMBO4, brush_hatch_ccb);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, brush_colour_cb);
	DDX_Control(pDX, IDC_COMBO1, pen_style_ccb);
	DDX_Control(pDX, IDC_EDIT1, pen_width_edit);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, pen_colour_cb);
}


BEGIN_MESSAGE_MAP(EditStyleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &EditStyleDlg::ButtonOk)
	ON_BN_CLICKED(IDC_BUTTON2, &EditStyleDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// edit_style_dlg 消息处理程序


BOOL EditStyleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitDlg();
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void EditStyleDlg::ButtonOk() {

	logbrush.lbStyle = brush_style_ccb.GetCurSel();
	logbrush.lbHatch = brush_hatch_ccb.GetCurSel();

	COLORREF color = brush_colour_cb.GetColor();
	if (color == -1) {
		color = brush_colour_cb.GetAutomaticColor();
	}
	logbrush.lbColor = color;

	logpen.lopnStyle = pen_style_ccb.GetCurSel();
	CString str;
	pen_width_edit.GetWindowText(str);
	logpen.lopnWidth.x = _ttoi(str);

	color = pen_colour_cb.GetColor();
	if (color == -1) {
		color = pen_colour_cb.GetAutomaticColor();
	}
	logpen.lopnColor = color;

	OnOK();
	return;
}


void EditStyleDlg::OnBnClickedButton2() {
	OnCancel();
	return;
}
