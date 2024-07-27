#pragma once 
#include "draw_graphics.h"

/// <summary>
/// 线条类
/// </summary>
class DLine : public Graphics {
public:
	DLine();
	DLine(DLine* obj);
	DLine(DLine& obj);
	virtual ~DLine() {};

public:
	//绘制直线
	void DrawLine(CDC* cdc_obj);
	//重写
	void GeneratedEffectiveRegion() override;
	//重写
	void DrawGraphics(CDC* cdc_obj) override;
	DLine* copy() override;
	INT size() override;
	PatternType type() override;
private:
	
};



