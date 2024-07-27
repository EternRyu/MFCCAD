#pragma once

#include "draw_line.h"
#include "draw_rectangle.h"
#include "draw_round.h"
#include "draw_polygon.h"



/// <summary>
/// ��������
/// </summary>
class DrawFactory {
public:
	DrawFactory() = default;
	virtual ~DrawFactory() = default;
public://�ӿ�
	virtual Graphics* FactoryDrawGraphics() = 0;

};

/// <summary>
/// ������չ��ֱ��
/// </summary>
class DrawFactoryLine :public DrawFactory {
public:
	DrawFactoryLine() = default;
	virtual ~DrawFactoryLine() = default;
public:
	//��д
	virtual Graphics* FactoryDrawGraphics() override {
		return new DLine;
	}

};

/// <summary>
/// ������չ��Բ��
/// </summary>
class DrawFactoryRound :public DrawFactory {
public:
	DrawFactoryRound() = default;
	virtual ~DrawFactoryRound() = default;
public:
	//��д
	virtual Graphics* FactoryDrawGraphics() override {
		return new DRound;
	}

};

/// <summary>
/// ������չ�����
/// </summary>
class DrawFactoryRectangle :public DrawFactory {
public:
	DrawFactoryRectangle() = default;
	virtual ~DrawFactoryRectangle() = default;
public:
	//��д
	virtual Graphics* FactoryDrawGraphics() override {
		return new DRectangle;
	}

};

/// <summary>
/// ������չ��������չ�����
/// </summary>
class DrawFactoryPolygonFive :public DrawFactory {
public:
	DrawFactoryPolygonFive() = default;
	virtual ~DrawFactoryPolygonFive() = default;
public:
	//��д
	virtual Graphics* FactoryDrawGraphics() override {
		return new FivePointedStar;
	}

};

