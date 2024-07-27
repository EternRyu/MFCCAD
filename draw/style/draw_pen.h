
#pragma once 

#include <Windows.h>
#include <afxwin.h>
#include <wingdi.h>
#include <iostream>

/// <summary>
/// 画笔样式
/// </summary>
class DrawStylePen {
public:
	DrawStylePen();
	DrawStylePen(DrawStylePen& obj);
	DrawStylePen(DrawStylePen* obj);
	virtual ~DrawStylePen();

public:

	//笔样式
	void PenSetlopnStyle(UINT pnstyle);

	//笔宽度
	void PenSetlopnWidth(INT width);

	//笔颜色
	void PenSetlopnColor(COLORREF pncolor);

	UINT PenGetlopnStyle() const;

	INT PenGetlopnWidth() const;

	COLORREF PenGetlopnColor() const;

	void PenSetLogpen(LOGPEN logpen);

	LOGPEN PenGetLogpen() const;

	void SetPenStyleToCDC(CDC* cdc_obj);

	void RestoreCpen(CDC* cdc_obj);

	void DeleteHpenObject();


private:
	CPen cpen;
	CPen* old_pen_ptr = nullptr;
	LOGPEN pen_style;
};

