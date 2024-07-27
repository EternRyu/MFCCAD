#pragma once
#include "style/draw_style.h"
/// <summary>
/// 图形基类
/// </summary>
class Graphics : public DrawStyle {

public:
	enum class PatternType {
		GRAPHICS = 0,
		LINE,
		RECTANGLE,
		ROUND,
		FIVEPOINTEDSTAR
	};

public:
	Graphics() = default;
	Graphics(Graphics* obj);
	Graphics(Graphics& obj);
	virtual ~Graphics() = default;

public:

	//计算新角度后的点
	CPoint CalculatePoint(CPoint v1, CPoint mid);

	void setbegin(CPoint& cp);

	CPoint getbegin() const;

	void setend(CPoint& cp);

	CPoint getend() const;

	double getradius() const;

	double getdiameter() const;

	CPoint getmidpoint() const;

	void SetSelect(bool off);
private://内部操作
	void SetExcircle();
private://接口
	virtual void DrawGraphics(CDC* cdc_obj) {};//绘制
	virtual void GeneratedEffectiveRegion() {};
public://接口
	//virtual void DrawMouseSelect(CPoint& cp) = 0;//选中
	virtual void DrawStyleAndGraphics(CDC* cdc_obj);
	virtual void MoveGraphics(CSize offset);
	virtual Graphics* copy();
	virtual INT size();
	virtual PatternType type();
public:
	bool DrawMouseSelect(CPoint cp);
	
private:
	struct Coordinate {
	public:
		CPoint begin;
		CPoint end;
	}coordinate;

	struct Excircle {
	public:
		//Excircle() = default;
		//Excircle(Coordinate coordinate);
		void InitExcircle(Coordinate coordinate);
		CPoint mid;
		double diameter;
		double radius;
	}eoordinate;

public:
	//Π
	const double pi = 3.14159265358979323846;
	//选中范围
	const INT range = 2;
	//旋转角度
	double angle = 0;
	//有效区
	CRgn precinct;

};