#include "../pch.h"
#include "draw_line.h"
#include <gdiplus.h>

DLine::DLine() {
	return;
}

DLine::DLine(DLine* obj) :Graphics(obj) {
	return;
}

DLine::DLine(DLine& obj) :Graphics(obj) {
	return;
}

/// <summary>
/// 绘图直线
/// </summary>
/// <param name="cdc_obj">CDC</param>
void DLine::DrawLine(CDC* cdc_obj) {
	
	CPoint begin = getbegin();
	CPoint end = getend();
	if (angle != 0) {
		CPoint mid = getmidpoint();
		begin = CalculatePoint(begin, mid);
		end = CalculatePoint(end, mid);
	}
	cdc_obj->MoveTo(begin); //起点
	cdc_obj->LineTo(end);//终点
	return;
}


void DLine::DrawGraphics(CDC* cdc_obj) {
	DrawLine(cdc_obj);
	return;
}

DLine* DLine::copy() {
	return new DLine(*this);
}

INT DLine::size() {
	return sizeof(DLine);
}

Graphics::PatternType DLine::type() {
	return PatternType::LINE;
}

/// <summary>
/// 选中区
/// </summary>
void DLine::GeneratedEffectiveRegion() {
	CPoint begin = getbegin();
	CPoint end = getend();
	if (angle != 0) {
		CPoint mid = getmidpoint();
		begin = CalculatePoint(begin, mid);
		end = CalculatePoint(end, mid);
	}
	CPoint pointarr[4];
	pointarr[0].x = begin.x - range;
	pointarr[0].y = begin.y + range;

	pointarr[1].x = begin.x + range;
	pointarr[1].y = begin.y - range;

	pointarr[2].x = end.x + range;
	pointarr[2].y = end.y - range;

	pointarr[3].x = end.x - range;
	pointarr[3].y = end.y + range;
	precinct.DeleteObject();
	
	precinct.CreatePolygonRgn(pointarr, 4, ALTERNATE);
	return;
}