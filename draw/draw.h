#pragma once
#include "draw_factory.h"
#include <list>
#include <map>
#include <memory>
//#include <math.h>
#include <fstream>
#include <iostream>

/// <summary>
/// ͼ�λ�ͼ������
/// </summary>
class DrawDC {
private://����
	typedef std::shared_ptr<Graphics> GraphicsShPtr;
	typedef std::shared_ptr<DrawFactory> DrawFactoryShPtr;
	typedef std::map<DWORD64,GraphicsShPtr> MapGraphicsPtr;
	typedef std::pair<DWORD64, GraphicsShPtr> MapNode;

	struct Records {
		int key = -1;
		GraphicsShPtr history = nullptr;
	};

	typedef std::shared_ptr<Records> RecordsStruct;
	typedef std::list<RecordsStruct> UndoStack;
	typedef UndoStack RundoStack;

	struct Select {
		DWORD64 key = -1;
		GraphicsShPtr obj = nullptr;
	};

	struct MoveInfo {
		bool move_start = false;
		bool moveing = false;
	};

	friend Graphics::PatternType;

	struct FileInfo {
		Graphics::PatternType type;
		DWORD size;
	};

public:
	DrawDC() = default;
	~DrawDC() = default;

public://����ͼ��
	void DrawLine();
	void DrawRectangle();
	void DrawRound();
	void ExDrawFivePointedStar();

public://�ⲿ����
	void DrawSetBeginPoint(CPoint point);
	void DrawSetEndPoint(CPoint point);
	void DrawObjectReset();
	void DrawObjectPush();
	void DrawAllObjectRelease();
	void DrawPaintDC(CDC* cdc_obj, CRect& crect_wnd);
	void DrawSetPen(LOGPEN pen);
	void DrawSetBrush(LOGBRUSH brush);
	void DrawSelectSetPen(LOGPEN pen);
	void DrawSelectSetBrush(LOGBRUSH brush);
	LOGPEN DrawSelectGetPen();
	LOGBRUSH DrawSelectGetBrush();
	void IsSelect(CPoint point);
	bool SelectEmpty();
	void MoveStart(CPoint begin);
	void Moving(CPoint cpoint);
	void MoveEnd(CPoint end);
	void RotatePattern(double angle);
	void DeletePattern();
	void DrawUndo();
	void DrawRUndo();
	//���������¼
	void ClearRecord();
	//���л�
	void Serialization(const wchar_t* path);
	//�����л�
	void Deserialization(const wchar_t* path);
	
	

private://�ڲ�����
	void DrawCreatObject();
	void DrawUndoCreateRecordOperation(DWORD64 key);
	void DrawUndoRecordOperation(Select source);
	void DrawUndoRecordOperation(DWORD64 key);
	void MovePattern(CSize offset);
	void MoveStatRecordOperation();
	void MoveingRecordOperation();
	void MoveEndRecordOperation();
	void DrawRundoRecordOperation(DWORD64 key);
	void DrawRundoRecordClear();
	//���ļ����л�ԭͼ��
	void RestoreGraphicsForFile(FileInfo info, std::fstream& file);
	

private:
	//�ƶ���¼���
	CPoint move_begin = { 0 };
	MoveInfo move_info;
	GraphicsShPtr move_original_ectype = nullptr;
	
	//������ָ��
	DrawFactoryShPtr dynamic_factory_ptr = nullptr;
	//��ʱ����
	GraphicsShPtr dynamic_graphics_ptr = nullptr;
	//����ͼ�εĽṹ
	MapGraphicsPtr map_graphics;
	//��ʱ���󱣴����Ϣ
	Select select;
	//����ջ����Ĳ�����¼
	UndoStack undo_stack;
	//����ջ����Ĳ�����¼
	RundoStack rundo_stack;
};

