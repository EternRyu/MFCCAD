#pragma once 
#include "draw_graphics.h"

/// <summary>
/// ������
/// </summary>
class DLine : public Graphics {
public:
	DLine();
	DLine(DLine* obj);
	DLine(DLine& obj);
	virtual ~DLine() {};

public:
	//����ֱ��
	void DrawLine(CDC* cdc_obj);
	//��д
	void GeneratedEffectiveRegion() override;
	//��д
	void DrawGraphics(CDC* cdc_obj) override;
	DLine* copy() override;
	INT size() override;
	PatternType type() override;
private:
	
};



