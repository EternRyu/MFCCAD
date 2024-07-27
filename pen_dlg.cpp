// pen_dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCCAD.h"
#include "afxdialogex.h"
#include "pen_dlg.h"

PenDlg* PenDlg::pdlg_ptr = nullptr;
// pen_dlg 对话框

IMPLEMENT_DYNAMIC(PenDlg, CDialogEx)

PenDlg::PenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
}

PenDlg::~PenDlg()
{
}

void PenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, pen_style_ccb);
	DDX_Control(pDX, IDC_EDIT1, px_edit);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, pen_color_cb);
}


BEGIN_MESSAGE_MAP(PenDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &PenDlg::ButtonSetPen)
	ON_BN_CLICKED(IDC_BUTTON2, &PenDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// pen_dlg 消息处理程序

/// <summary>
/// 初始化控件
/// </summary>
void PenDlg::InitDlgControl() {
	

	pdlg_ptr = this;

	old_wndfun_ptr = (WNDPROC)SetWindowLongPtr(
		px_edit.GetSafeHwnd(),
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
	pen_style_ccb.SetCurSel(PS_SOLID);

	pen_color_cb.EnableOtherButton(_T("Other"), FALSE, TRUE);
	return;
}

/// <summary>
/// 更新数据
/// </summary>
void PenDlg::UpdateWndData(LOGPEN* pen) {
	pen_style_ccb.SetCurSel(pen->lopnStyle);
	
	CString str;
	str.Format(L"%d",pen->lopnWidth.x);
	px_edit.SetWindowText(str);

	pen_color_cb.SetColor(pen->lopnColor);
}

void PenDlg::GetStyle(LOGPEN* pen) {
	if (!pen) {
		return;
	}
	pen->lopnStyle = pen_style_ccb.GetCurSel();
	CString str;
	px_edit.GetWindowText(str);
	pen->lopnWidth.x = _ttoi(str);

	COLORREF color = pen_color_cb.GetColor();
	if (color == -1) {
		color = pen_color_cb.GetAutomaticColor();
	}
	pen->lopnColor = color;
	return;
}

LRESULT PenDlg::HookEditWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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

void PenDlg::PostNcDestroy() {
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}


void PenDlg::OnCancel() {
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
	DestroyWindow();
}


BOOL PenDlg::PreTranslateMessage(MSG* pMsg) {
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == USER_SEND_LOGPEN && pMsg->wParam && pMsg->lParam) {
		LOGPEN* pen_ptr = (LOGPEN*)pMsg->wParam;
		p_hwnd = (HWND)pMsg->lParam;
		UpdateWndData(pen_ptr);
		delete pen_ptr;
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL PenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDlgControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void PenDlg::ButtonSetPen() {
	LOGPEN* temp = new LOGPEN;
	GetStyle(temp);
	::PostMessage(p_hwnd, USER_SET_LOGPEN, (WPARAM)temp, NULL);
	return;
}


void PenDlg::OnBnClickedButton2() {
	OnCancel();
	return;
}
