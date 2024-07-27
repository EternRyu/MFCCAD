#pragma once

#include "draw_line.h"
#include "draw_rectangle.h"
#include "draw_round.h"
#include "draw_polygon.h"



/// <summary>
/// 工厂基类
/// </summary>
class DrawFactory {
public:
	DrawFactory() = default;
	virtual ~DrawFactory() = default;
public://接口
	virtual Graphics* FactoryDrawGraphics() = 0;

};

/// <summary>
/// 工厂扩展类直线
/// </summary>
class DrawFactoryLine :public DrawFactory {
public:
	DrawFactoryLine() = default;
	virtual ~DrawFactoryLine() = default;
public:
	//重写
	virtual Graphics* FactoryDrawGraphics() override {
		return new DLine;
	}

};

/// <summary>
/// 工厂扩展类圆形
/// </summary>
class DrawFactoryRound :public DrawFactory {
public:
	DrawFactoryRound() = default;
	virtual ~DrawFactoryRound() = default;
public:
	//重写
	virtual Graphics* FactoryDrawGraphics() override {
		return new DRound;
	}

};

/// <summary>
/// 工厂扩展类矩形
/// </summary>
class DrawFactoryRectangle :public DrawFactory {
public:
	DrawFactoryRectangle() = default;
	virtual ~DrawFactoryRectangle() = default;
public:
	//重写
	virtual Graphics* FactoryDrawGraphics() override {
		return new DRectangle;
	}

};

/// <summary>
/// 工厂扩展类多边形扩展五角星
/// </summary>
class DrawFactoryPolygonFive :public DrawFactory {
public:
	DrawFactoryPolygonFive() = default;
	virtual ~DrawFactoryPolygonFive() = default;
public:
	//重写
	virtual Graphics* FactoryDrawGraphics() override {
		return new FivePointedStar;
	}

};

