#pragma once 
#include "draw_graphics.h"

/// <summary>
/// 多边形类
/// </summary>
class DPolygon : public Graphics {
public:
	DPolygon();
	DPolygon(DPolygon* obj);
	DPolygon(DPolygon& obj);
	virtual ~DPolygon() {};

public:

	//绘制多边形
	virtual void DrawPolygon(CDC* cdc_obj) = 0;

	//重写
	void GeneratedEffectiveRegion() override;

	//重写
	void DrawGraphics(CDC* cdc_obj) override;

};


/// <summary>
/// 五角星类
/// </summary>
class FivePointedStar :public DPolygon {

private:
#define POINT_COUNT  5
public:
	FivePointedStar() {};
	FivePointedStar(FivePointedStar* obj) :DPolygon(obj) {};
	FivePointedStar(FivePointedStar& obj) :DPolygon(obj) {};
	virtual ~FivePointedStar() {};

	//绘制多边形
	void DrawPolygon(CDC* cdc_obj) override {
		CPoint begin = getbegin();
		CPoint end = getend();
		if (angle != 0) {
			CPoint mid = getmidpoint();
			begin = CalculatePoint(begin, mid);
			end = CalculatePoint(end, mid);
		}
		//double radius = sqrt((begin.x - end.x) * (begin.x - end.x) + (begin.y - end.y) * (begin.y - end.y)) / 2.0;
		//double midx = ((double)end.x + (double)begin.x) / 2.0;
		//double midy = ((double)end.y + (double)begin.y) / 2.0;
		CPoint mid = getmidpoint();
		CPoint cpo_group[POINT_COUNT] = { 0 };
		CalculatedPoint(cpo_group,getradius(), mid.x, mid.y);
		//设置填充模式
		cdc_obj->SetPolyFillMode(WINDING);
		//cdc_obj->SelectStockObject(NULL_BRUSH);
		//绘制多边形
		cdc_obj->Polygon(cpo_group, POINT_COUNT);
		//设置填充模式
		cdc_obj->SetPolyFillMode(ALTERNATE);
		return;
	};

	/// <summary>
	/// 计算点位
	/// </summary>
	/// <param name="radius">半径</param>
	/// <param name="midx">中点x</param>
	/// <param name="midy">中点y</param>
	void CalculatedPoint(CPoint* parr,double radius, double midx, double midy) {
		double pi = 3.141592653589793;
		double alpha = pi / 5.0;
		double slope = 1.499;

		parr[0].x = (long)(midx + radius * cos(alpha * (2 * 0 + slope)));
		parr[0].y = (long)(midy + radius * sin(alpha * (2 * 0 + slope)));
																																 
		parr[1].x = (long)(midx + radius * cos(alpha * (2 * 2 + slope)));
		parr[1].y = (long)(midy + radius * sin(alpha * (2 * 2 + slope)));
																																 
		parr[2].x = (long)(midx + radius * cos(alpha * (2 * 4 + slope)));
		parr[2].y = (long)(midy + radius * sin(alpha * (2 * 4 + slope)));
																																 
		parr[3].x = (long)(midx + radius * cos(alpha * (2 * 1 + slope)));
		parr[3].y = (long)(midy + radius * sin(alpha * (2 * 1 + slope)));
																																 
		parr[4].x = (long)(midx + radius * cos(alpha * (2 * 3 + slope)));
		parr[4].y = (long)(midy + radius * sin(alpha * (2 * 3 + slope)));
		return;
	};


	FivePointedStar* copy() override {
		return new FivePointedStar(this);
	};

	INT size() override {
		return sizeof(FivePointedStar);
	};

	PatternType type() override {
		return PatternType::FIVEPOINTEDSTAR;
	};
};

