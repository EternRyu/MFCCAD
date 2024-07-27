#include "../pch.h"
#include "draw_polygon.h"


DPolygon::DPolygon() {
}

DPolygon::DPolygon(DPolygon* obj) :Graphics(obj) {
}

DPolygon::DPolygon(DPolygon& obj) :Graphics(obj) {
}

/// <summary>
/// Ñ¡ÖÐÇø
/// </summary>
void DPolygon::GeneratedEffectiveRegion() {
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

void DPolygon::DrawGraphics(CDC* cdc_obj) {
  DrawPolygon(cdc_obj);
  return;
}
