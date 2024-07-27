#pragma once 
#include <Windows.h>
#include <afxwin.h>
#include <wingdi.h>
#include <iostream>
/// <summary>
/// 画刷样式
/// </summary>
class DrawStyleBrush {
public:
	DrawStyleBrush();
	DrawStyleBrush(DrawStyleBrush& obj);
	DrawStyleBrush(DrawStyleBrush* obj);
	virtual ~DrawStyleBrush();

public:
	//画刷样式
	void BrushSetlobStyle(UINT pnstyle);

	//画刷阴影样式
	void BrushSetlobHatch(ULONG_PTR hatch);

	//画刷颜色
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