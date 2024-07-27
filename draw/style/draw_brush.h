#pragma once 
#include <Windows.h>
#include <afxwin.h>
#include <wingdi.h>
#include <iostream>
/// <summary>
/// ��ˢ��ʽ
/// </summary>
class DrawStyleBrush {
public:
	DrawStyleBrush();
	DrawStyleBrush(DrawStyleBrush& obj);
	DrawStyleBrush(DrawStyleBrush* obj);
	virtual ~DrawStyleBrush();

public:
	//��ˢ��ʽ
	void BrushSetlobStyle(UINT pnstyle);

	//��ˢ��Ӱ��ʽ
	void BrushSetlobHatch(ULONG_PTR hatch);

	//��ˢ��ɫ
	void BrushSetlobColor(COLORREF pncolor);

	UINT BrushGetlobStyle() const;

	ULONG_PTR BrushGetlobHatch() const;

	COLORREF BrushGetlobColor() const;

	void BrushSetLogBrush(LOGBRUSH brush_style);

	LOGBRUSH BrushGetLogBrush() const;

	void SetBrushStyleToCDC(CDC* cdc_obj);

	void RestoreBrush(CDC* cdc_obj);

	void DeleteBrushObject();
private:
	CBrush brush;
	CBrush* old_brush_ptr = nullptr;
	LOGBRUSH brush_style;
	
};