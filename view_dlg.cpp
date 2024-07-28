// view_dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCCAD.h"
#include "view_dlg.h"


// view_dlg

IMPLEMENT_DYNCREATE(DlgView, CFormView)

DlgView::DlgView()
	: CFormView(IDD_DIALOG4)
{

}

DlgView::~DlgView()
{
}

void DlgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DlgView, CFormView)
END_MESSAGE_MAP()


// view_dlg 诊断

#ifdef _DEBUG
void DlgView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DlgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// view_dlg 消息处理程序
