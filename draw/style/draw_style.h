#pragma once 
#include <Windows.h>
#include <atltypes.h>
#include<afxwin.h>
#include <iostream>
#include"draw_pen.h"
#include"draw_brush.h"
/// <summary>
/// »æÖÆÑùÊ½
/// </summary>
class DrawStyle:public DrawStyleBrush, public DrawStylePen {
public:
	DrawStyle();
	DrawStyle(DrawStyle* obj);
	DrawStyle(DrawStyle& obj);
	virtual ~DrawStyle() {};

public:
	void SetNewStyle(CDC* cdc_obj);
	void RestoreStyle(CDC* cdc_obj);
private:
};


