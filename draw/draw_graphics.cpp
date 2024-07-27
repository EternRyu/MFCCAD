#include "../pch.h"
#include "draw_graphics.h"
#include <math.h>

Graphics::Graphics(Graphics* obj): DrawStyle(obj){
	coordinate = obj->coordinate;
	eoordinate = obj->eoordinate;
	angle = obj->angle;
	precinct.DeleteObject();
	precinct.CreateRectRgn(0, 0, 1, 1);
	precinct.CopyRgn(&(obj->precinct));
	return;
}

Graphics::Graphics(Graphics& obj) : DrawStyle(obj) {
	coordinate = obj.coordinate;
	eoordinate = obj.eoordinate;
	angle = obj.angle;
	precinct.DeleteObject();
	precinct.CreateRectRgn(0, 0, 1, 1);
	precinct.CopyRgn(&(obj.precinct));
}

CPoint Graphics::CalculatePoint(CPoint v1, CPoint mid) {
	CPoint temp;
	double radians = pi * angle / 180;
	temp.x = (((double)v1.x - (double)mid.x) * cos(radians)) - (((double)v1.y - (double)mid.y) * sin(radians)) + (double)mid.x;
	temp.y = (((double)v1.y - (double)mid.y) * cos(radians)) + (((double)v1.x - (double)mid.x) * sin(radians)) + (double)mid.y;
	return temp;
}

void Graphics::setbegin(CPoint& cp) {
	coordinate.begin = cp;
	return;
}

CPoint Graphics::getbegin() const {
	return coordinate.begin;
}

void Graphics::setend(CPoint& cp) {
	coordinate.end = cp;
	SetExcircle();
	return;
}

CPoint Graphics::getend() const {
	return coordinate.end;
}

double Graphics::getradius() const {
	return eoordinate.radius;
}

double Graphics::getdiameter() const {
	return eoordinate.diameter;
}

CPoint Graphics::getmidpoint() const {
	return eoordinate.mid;
}

void Graphics::SetSelect(bool off) {
	if (off) {
		PenSetlopnWidth(PenGetlopnWidth() + 2);
	}
	else {
		PenSetlopnWidth(PenGetlopnWidth() - 2);
	}
}

void Graphics::SetExcircle() {
	eoordinate.InitExcircle(coordinate);
	return;
}

void Graphics::DrawStyleAndGraphics(CDC* cdc_obj) {
	GeneratedEffectiveRegion();
	SetNewStyle(cdc_obj);
	DrawGraphics(cdc_obj);
	RestoreStyle(cdc_obj);
	return;
}

void Graphics::MoveGraphics(CSize offset) {
	CPoint begin = getbegin();
	CPoint end = getend();
	begin += offset;
	end += offset;
	setbegin(begin);
	setend(end);
	return;
}

Graphics* Graphics::copy() {
	return new Graphics(*this);
}

INT Graphics::size() {
	return 0;
}

Graphics::PatternType Graphics::type() {
	return PatternType::GRAPHICS;
}

bool Graphics::DrawMouseSelect(CPoint cp) {
	return precinct.PtInRegion(cp);
}



void Graphics::Excircle::InitExcircle(Coordinate coordinate) {
	diameter = sqrt(
		(coordinate.begin.x - coordinate.end.x) *
		(coordinate.begin.x - coordinate.end.x) +
		(coordinate.begin.y - coordinate.end.y) *
		(coordinate.begin.y - coordinate.end.y)
	);
	radius = diameter / 2;
	mid.x = ((double)coordinate.end.x + (double)coordinate.begin.x) / 2.0;
	mid.y = ((double)coordinate.end.y + (double)coordinate.begin.y) / 2.0;
}


