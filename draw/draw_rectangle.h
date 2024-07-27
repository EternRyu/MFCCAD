#pragma once 

#include "draw_graphics.h"
/// <summary>
/// 矩形类
/// </summary>
class DRectangle : public Graphics {
public:
	DRectangle();
	DRectangle(DRectangle* obj);
	DRectangle(DRectangle& obj);
	virtual ~DRectangle() {};

public:


	//绘制矩形
	void DrawRectangle(CDC* cdc_obj);

	//重写
	void GeneratedEffectiveRegion() override;

	//重写
	void DrawGraphics(CDC* cdc_obj) override;

	DRectangle* copy() override;

	INT size() override;

	PatternType type() override;
private:
	//DWORD64* ref = nullptr;
};