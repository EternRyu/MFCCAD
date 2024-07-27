#pragma once 

#include "draw_graphics.h"

/// <summary>
/// 圆形类
/// </summary>
class DRound : public Graphics {
public:
	DRound();
	DRound(DRound* obj);
	DRound(DRound& obj);
	virtual ~DRound() {};

public:

	//绘制圆形
	void DrawRound(CDC* cdc_obj);
	//重写
	void GeneratedEffectiveRegion() override;

	//重写
	void DrawGraphics(CDC* cdc_obj) override;

	DRound* copy() override;

	INT size() override;

	PatternType type() override;
private:
};