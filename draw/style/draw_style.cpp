#include "../../pch.h"
#include "draw_style.h"

DrawStyle::DrawStyle() {
}

DrawStyle::DrawStyle(DrawStyle* obj) : DrawStyleBrush(obj), DrawStylePen(obj) {

}

DrawStyle::DrawStyle(DrawStyle& obj) : DrawStyleBrush(obj), DrawStylePen(obj) {
}

void DrawStyle::SetNewStyle(CDC* cdc_obj) {
  SetBrushStyleToCDC(cdc_obj);
  SetPenStyleToCDC(cdc_obj);
  return;
}

void DrawStyle::RestoreStyle(CDC* cdc_obj) {
  RestoreCpen(cdc_obj);
  RestoreBrush(cdc_obj);
  return;
}
