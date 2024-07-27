#include "../pch.h"
#include "draw_rectangle.h"


DRectangle::DRectangle() {
}

DRectangle::DRectangle(DRectangle* obj):Graphics(obj){
	return;
}

DRectangle::DRectangle(DRectangle& obj):Graphics(obj) {
	return;
}

/// <summary>
/// 绘制矩形
/// </summary>
/// <param name="cdc_obj">CDC</param>
void DRectangle::DrawRectangle(CDC* cdc_obj) {
	CPoint begin = getbegin();
	CPoint end = getend();
	if (angle != 0) {
		CPoint mid = getmidpoint();
		begin = CalculatePoint(begin, mid);
		end = CalculatePoint(end, mid);
	}
	CPoint cpoint_arr[4];

	cpoint_arr[0].x = begin.x;
	cpoint_arr[0].y = begin.y;

	cpoint_arr[1].x = end.x;
	cpoint_arr[1].y = begin.y;

	cpoint_arr[2].x = end.x;
	cpoint_arr[2].y = end.y;

	cpoint_arr[3].x = begin.x;
	cpoint_arr[3].y = end.y;

	//绘制矩形
	cdc_obj->Polygon(cpoint_arr,4);
	return;
}

/// <summary>
/// 选中区
/// </summary>
void DRectangle::GeneratedEffectiveRegion() {
	CPoint begin = getbegin();
	CPoint end = getend();
	if (angle != 0) {
		CPoint mid = getmidpoint();
		begin = CalculatePoint(begin, mid);
		end = CalculatePoint(end, mid);
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

void DRectangle::DrawGraphics(CDC* cdc_obj) {
	DrawRectangle(cdc_obj);
	return;
}

DRectangle* DRectangle::copy(){
	
	return new DRectangle(this);
}

INT DRectangle::size() {
	return sizeof(DRectangle);
}

Graphics::PatternType DRectangle::type() {
	return PatternType::RECTANGLE;
}
