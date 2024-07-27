#pragma once
#include "draw_factory.h"
#include <list>
#include <map>
#include <memory>
//#include <math.h>
#include <fstream>
#include <iostream>

/// <summary>
/// 图形绘图操作类
/// </summary>
class DrawDC {
private://定义
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

public://设置图形
	void DrawLine();
	void DrawRectangle();
	void DrawRound();
	void ExDrawFivePointedStar();

public://外部操作
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
	//清除操作记录
	void ClearRecord();
	//序列化
	void Serialization(const wchar_t* path);
	//反序列化
	void Deserialization(const wchar_t* path);
	
	

private://内部操作
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
	//从文件当中还原图形
	void RestoreGraphicsForFile(FileInfo info, std::fstream& file);
	

private:
	//移动记录相关
	CPoint move_begin = { 0 };
	MoveInfo move_info;
	GraphicsShPtr move_original_ectype = nullptr;
	
	//工厂类指针
	DrawFactoryShPtr dynamic_factory_ptr = nullptr;
	//临时对象
	GraphicsShPtr dynamic_graphics_ptr = nullptr;
	//保存图形的结构
	MapGraphicsPtr map_graphics;
	//临时对象保存的信息
	Select select;
	//撤回栈保存的操作记录
	UndoStack undo_stack;
	//重做栈保存的操作记录
	RundoStack rundo_stack;
};

