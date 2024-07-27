#include "../../pch.h"
#include "draw_pen.h"

//DrawStylePen::DrawStylePen(UINT lopnStyle, INT lopnWidth, COLORREF lopnColor) {
//	pen_style.lopnStyle = lopnStyle;
//	pen_style.lopnWidth.x = lopnWidth;
//	pen_style.lopnColor = lopnColor;
//	return;
//}

DrawStylePen::DrawStylePen() {
	pen_style.lopnStyle = PS_SOLID;
	pen_style.lopnWidth.x = 1;
	pen_style.lopnColor = RGB(0, 0, 0);
}

DrawStylePen::DrawStylePen(DrawStylePen& obj) {
	 pen_style = obj.pen_style;
	 return;
}

DrawStylePen::DrawStylePen(DrawStylePen* obj) {
	pen_style = obj->pen_style;
	return;
}

DrawStylePen::~DrawStylePen() {
	DeleteHpenObject();
	return;
}

void DrawStylePen::PenSetlopnStyle(UINT pnstyle) {
	pen_style.lopnStyle = pnstyle;
	return;
}

void DrawStylePen::PenSetlopnWidth(INT width) {
	pen_style.lopnWidth.x = width;
	return;
}

void DrawStylePen::PenSetlopnColor(COLORREF pncolor) {
	pen_style.lopnColor = pncolor;
	return;
}

UINT DrawStylePen::PenGetlopnStyle() const {
	return pen_style.lopnStyle;
}

INT DrawStylePen::PenGetlopnWidth() const {
	return pen_style.lopnWidth.x;
}

COLORREF DrawStylePen::PenGetlopnColor() const {
	return pen_style.lopnColor;
}

void DrawStylePen::PenSetLogpen(LOGPEN logpen) {
	pen_style = logpen;
	return;
}

LOGPEN DrawStylePen::PenGetLogpen() const{
	return pen_style;
}

void DrawStylePen::SetPenStyleToCDC(CDC* cdc_obj) {
	DeleteHpenObject();
	cpen.CreatePenIndirect(&pen_style);
	
	old_pen_ptr = cdc_obj->SelectObject(&cpen);
	return;
}

void DrawStylePen::RestoreCpen(CDC* cdc_obj) {
	if (!old_pen_ptr) {
		return;
	}
	cdc_obj->SelectObject(old_pen_ptr);
	old_pen_ptr = nullptr;
	return;
}

void DrawStylePen::DeleteHpenObject() {
	cpen.DeleteObject();
	return;
}
