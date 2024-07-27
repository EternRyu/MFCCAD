#pragma once 

#include "draw_graphics.h"
/// <summary>
/// ������
/// </summary>
class DRectangle : public Graphics {
public:
	DRectangle();
	DRectangle(DRectangle* obj);
	DRectangle(DRectangle& obj);
	virtual ~DRectangle() {};

public:


	//���ƾ���
	void DrawRectangle(CDC* cdc_obj);

	//��д
	void GeneratedEffectiveRegion() override;

	//��д
	void DrawGraphics(CDC* cdc_obj) override;

	DRectangle* copy() override;

	INT size() override;

	PatternType type() override;
private:
	//DWORD64* ref = nullptr;
};