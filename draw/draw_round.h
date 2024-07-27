#pragma once 

#include "draw_graphics.h"

/// <summary>
/// Բ����
/// </summary>
class DRound : public Graphics {
public:
	DRound();
	DRound(DRound* obj);
	DRound(DRound& obj);
	virtual ~DRound() {};

public:

	//����Բ��
	void DrawRound(CDC* cdc_obj);
	//��д
	void GeneratedEffectiveRegion() override;

	//��д
	void DrawGraphics(CDC* cdc_obj) override;

	DRound* copy() override;

	INT size() override;

	PatternType type() override;
private:
};