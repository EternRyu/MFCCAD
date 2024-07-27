#include "../../pch.h"
#include "draw_brush.h"

DrawStyleBrush::DrawStyleBrush() {
  brush_style.lbStyle = BS_HOLLOW;
  brush_style.lbColor = RGB(0, 0, 0);
  brush_style.lbHatch = HS_HORIZONTAL;
  return;
}


DrawStyleBrush::DrawStyleBrush(DrawStyleBrush& obj) {
  brush_style = obj.brush_style;
  return;
}

DrawStyleBrush::DrawStyleBrush(DrawStyleBrush* obj) {
  brush_style = obj->brush_style;
  return;
}

DrawStyleBrush::~DrawStyleBrush() {
  DeleteBrushObject();
  return;
}


void DrawStyleBrush::BrushSetlobStyle(UINT pnstyle) {
  brush_style.lbStyle = pnstyle;
  return;
}

void DrawStyleBrush::BrushSetlobHatch(ULONG_PTR hatch) {
  brush_style.lbHatch = hatch;
  return;
}

void DrawStyleBrush::BrushSetlobColor(COLORREF pncolor) {
  brush_style.lbColor = pncolor;
  return;
}

UINT DrawStyleBrush::BrushGetlobStyle() const {
  return brush_style.lbStyle;
}

ULONG_PTR DrawStyleBrush::BrushGetlobHatch() const {
  return brush_style.lbHatch;
}

COLORREF DrawStyleBrush::BrushGetlobColor() const {
  return brush_style.lbColor;
}

void DrawStyleBrush::BrushSetLogBrush(LOGBRUSH bstyle) {
  brush_style = bstyle;
  return;
}

LOGBRUSH DrawStyleBrush::BrushGetLogBrush() const {
  return brush_style;
}

void DrawStyleBrush::SetBrushStyleToCDC(CDC* cdc_obj) {
  DeleteBrushObject();
  brush.CreateBrushIndirect(&brush_style);
  old_brush_ptr = cdc_obj->SelectObject(&brush);
  return;
}

void DrawStyleBrush::RestoreBrush(CDC* cdc_obj) {
  if (!old_brush_ptr) {
    return;
  }
  cdc_obj->SelectObject(old_brush_ptr);
  return;
}

void DrawStyleBrush::DeleteBrushObject() {
  brush.DeleteObject();
  return;
}
