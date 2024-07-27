#include "../pch.h"
#include "draw_round.h"

DRound::DRound() {
}

DRound::DRound(DRound* obj) :Graphics(obj) {
}

DRound::DRound(DRound& obj) :Graphics(obj) {
}

void DRound::DrawRound(CDC* cdc_obj) {
	CPoint begin = getbegin();
	CPoint end = getend();
	//设置透明背景画刷
	//cdc_obj->SelectStockObject(NULL_BRUSH);
	//绘制圆形
	cdc_obj->Ellipse(begin.x, begin.y, end.x, end.y);
	return;
}


/// <summary>
/// 选中区
/// </summary>
void DRound::GeneratedEffectiveRegion() {
	CPoint begin = getbegin();
	CPoint end = getend();
	if (angle != 0) {
		CPoint mid = getmidpoint();
		begin = CalculatePoint(begin, mid);
		end = CalculatePoint(end, mid);
		//setbegin(begin);
		//setend(end);
	}
	CPoint pointarr[4];
	pointarr[0].x = begin.x;
	pointarr[0].y = begin.y;

	pointarr[1].x = end.x;
	pointarr[1].y = begin.y;

	pointarr[2].x = end.x;
	pointarr[2].y = end.y;

	pointarr[3].x = begin.x;
	pointarr[3].y = end.y;
	precinct.DeleteObject();
	precinct.CreatePolygonRgn(pointarr, 4, ALTERNATE);
	return;
}

void DRound::DrawGraphics(CDC* cdc_obj) {
	DrawRound(cdc_obj);
	return;
}

DRound* DRound::copy() {
	return new DRound(this);
}

INT DRound::size() {
	return sizeof(DRound);
}

Graphics::PatternType DRound::type() {
	return PatternType::ROUND;
}
