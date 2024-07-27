#pragma once
#include "style/draw_style.h"
/// <summary>
/// ͼ�λ���
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

	//�����½ǶȺ�ĵ�
	CPoint CalculatePoint(CPoint v1, CPoint mid);

	void setbegin(CPoint& cp);

	CPoint getbegin() const;

	void setend(CPoint& cp);

	CPoint getend() const;

	double getradius() const;

	double getdiameter() const;

	CPoint getmidpoint() const;

	void SetSelect(bool off);
private://�ڲ�����
	void SetExcircle();
private://�ӿ�
	virtual void DrawGraphics(CDC* cdc_obj) {};//����
	virtual void GeneratedEffectiveRegion() {};
public://�ӿ�
	//virtual void DrawMouseSelect(CPoint& cp) = 0;//ѡ��
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
	//��
	const double pi = 3.14159265358979323846;
	//ѡ�з�Χ
	const INT range = 2;
	//��ת�Ƕ�
	double angle = 0;
	//��Ч��
	CRgn precinct;

};