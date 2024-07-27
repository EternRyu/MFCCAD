#include "..\pch.h"

#include "draw.h"


/// <summary>
/// 绘制直线
/// </summary>
void DrawDC::DrawLine() {
  dynamic_factory_ptr = DrawFactoryShPtr(new DrawFactoryLine);
  DrawCreatObject();
  return;
}

/// <summary>
/// 绘制矩形
/// </summary>
void DrawDC::DrawRectangle() {
  dynamic_factory_ptr = DrawFactoryShPtr(new DrawFactoryRectangle);
  DrawCreatObject();
  return;
}

/// <summary>
/// 绘制圆形
/// </summary>
void DrawDC::DrawRound() {
  dynamic_factory_ptr = DrawFactoryShPtr(new DrawFactoryRound);
  DrawCreatObject();
  return;
}

/// <summary>
/// 绘制扩展多边形五角星
/// </summary>
void DrawDC::ExDrawFivePointedStar() {
  dynamic_factory_ptr = DrawFactoryShPtr(new DrawFactoryPolygonFive);
  DrawCreatObject();
  return;
}

/// <summary>
/// 创建图形对象
/// </summary>
void DrawDC::DrawCreatObject() {
	if (!dynamic_factory_ptr) {
		return;
	}
  dynamic_graphics_ptr = GraphicsShPtr(dynamic_factory_ptr->FactoryDrawGraphics());
	dynamic_factory_ptr.reset();
  return;
}

/// <summary>
/// 设置起始坐标
/// </summary>
/// <param name="point">坐标点</param>
void DrawDC::DrawSetBeginPoint(CPoint point) {
	if (!dynamic_graphics_ptr) {
		return;
	}
  dynamic_graphics_ptr->setbegin(point);
  return;
}

/// <summary>
/// 设置结束坐标
/// </summary>
/// <param name="point">坐标点</param>
void DrawDC::DrawSetEndPoint(CPoint point) {
	if (!dynamic_graphics_ptr) {
		return;
	}
  dynamic_graphics_ptr->setend(point);
  return;
}

/// <summary>
/// 对象清空
/// </summary>
void DrawDC::DrawObjectReset() {
	if (dynamic_graphics_ptr) {
		dynamic_graphics_ptr.reset();
	}
	dynamic_graphics_ptr = nullptr;
  return;
}

/// <summary>
/// 保存当前对象
/// </summary>
void DrawDC::DrawObjectPush() {
	DWORD64 key = 0;
	if (!dynamic_graphics_ptr) {
		return;
	}

	DrawRundoRecordClear();

	if (map_graphics.empty()) {
		map_graphics.insert(MapNode(key, dynamic_graphics_ptr));
	}
	else {
		MapGraphicsPtr::iterator max = map_graphics.end(); 
		max--;
		key = max->first + 1;
		map_graphics.insert(MapNode(key, dynamic_graphics_ptr));
	}
	DrawUndoCreateRecordOperation(key);
	//list_graphics.push_back(dynamic_graphics_ptr);
	return;
}

/// <summary>
/// 释放所有对象
/// </summary>
void DrawDC::DrawAllObjectRelease() {
  while (!map_graphics.empty()) {
		MapGraphicsPtr::iterator max = map_graphics.begin();
		max->second.reset();
		map_graphics.erase(max);
  }
  return;
}

/// <summary>
/// 绘制到cdc当中
/// </summary>
/// <param name="cdc_obj">目标cdc</param>
/// <param name="crect_wnd">窗口参数</param>
void DrawDC::DrawPaintDC(CDC* cdc_obj, CRect& crect_wnd) {
	//创建内存DC
	CDC memory_cdc;
	memory_cdc.CreateCompatibleDC(cdc_obj);
	//获取窗口参数
	//CRect crect_wnd;
	//GetClientRect(&crect_wnd);
	//创建兼容位图
	CBitmap cbitmap;
	cbitmap.CreateCompatibleBitmap(cdc_obj, crect_wnd.Width(), crect_wnd.Height());
	//将位图选入内存DC
	memory_cdc.SelectObject(&cbitmap);
	//设置背景为白色
	memory_cdc.FillSolidRect(&crect_wnd, RGB(255, 255, 255));

	//绘制当前图案
	if (dynamic_graphics_ptr) {
		dynamic_graphics_ptr->DrawStyleAndGraphics(&memory_cdc);
	}
	

	if (map_graphics.empty()) {
		goto EXIT;
	}
	//设置选中中图案加粗
	if (select.obj) {
		select.obj->PenSetlopnWidth(select.obj->PenGetlopnWidth() + 2);
	}
	//绘制所有图形

	for (MapGraphicsPtr::iterator it = map_graphics.begin(); it != map_graphics.end(); it++) {
		//在内存DC上完成绘制
		it->second->DrawStyleAndGraphics(&memory_cdc);
	}

	if (select.obj) {
		select.obj->PenSetlopnWidth(select.obj->PenGetlopnWidth() - 2);
	}
EXIT:
	//将内存DC中的图片拷贝到客户区
	cdc_obj->BitBlt(NULL,
		NULL,
		crect_wnd.Width(),
		crect_wnd.Height(),
		&memory_cdc,
		NULL,
		NULL,
		SRCCOPY
	);
	return;
}

/// <summary>
/// 设置画笔
/// </summary>
/// <param name="brush">画笔结构体</param>
void DrawDC::DrawSetPen(LOGPEN pen) {
	if (dynamic_graphics_ptr) {
		dynamic_graphics_ptr->PenSetLogpen(pen);
	}
	return;
}

/// <summary>
/// 设置画刷
/// </summary>
/// <param name="brush">画刷结构体</param>
void DrawDC::DrawSetBrush(LOGBRUSH brush) {
	if (dynamic_graphics_ptr) {
		dynamic_graphics_ptr->BrushSetLogBrush(brush);
	}
}

/// <summary>
/// 设置选中对象画笔
/// </summary>
/// <param name="pen">画笔结构体</param>
void DrawDC::DrawSelectSetPen(LOGPEN pen) {
	if (select.obj) {
		select.obj->PenSetLogpen(pen);
	}
	return;
}

/// <summary>
/// 设置选中对象画刷
/// </summary>
/// <param name="brush">画刷结构体</param>
void DrawDC::DrawSelectSetBrush(LOGBRUSH brush) {
	if (select.obj) {
		select.obj->BrushSetLogBrush(brush);
	}
	return;
}

/// <summary>
/// 获取选中对象画笔信息
/// </summary>
/// <returns>画笔结构体</returns>
LOGPEN DrawDC::DrawSelectGetPen() {
	if (select.obj) {
		return select.obj->PenGetLogpen();
	}
	return LOGPEN();
}

/// <summary>
/// 获取选中对象画刷信息
/// </summary>
/// <returns>画刷结构体</returns>
LOGBRUSH DrawDC::DrawSelectGetBrush() {
	if (select.obj) {
		return select.obj->BrushGetLogBrush();
	}
	return LOGBRUSH();
}

/// <summary>
/// 如果选中
/// </summary>
/// <param name="point">坐标</param>
void DrawDC::IsSelect(CPoint point) {
	if (dynamic_graphics_ptr) {
		return;
	}

	//反向迭代器遍历
	for (MapGraphicsPtr::reverse_iterator it = map_graphics.rbegin(); it != map_graphics.rend(); it++) {
		if (it->second->DrawMouseSelect(point)) {
			if (select.obj) {
				return;
			}
			//(*itr)->SetSelect(TRUE);
			select.key = it->first;
			select.obj = it->second;
			return;
		}
	}

	if (select.obj) {
		//select_obj->SetSelect(FALSE);
		select.obj = nullptr;
	}
	return;
}

/// <summary>
/// 设置选中
/// </summary>
/// <param name="key">图形的key</param>
void DrawDC::IsSelect(DWORD64 key) {
	//空返回
	if (map_graphics.empty()) {
		return;
	}
	MapGraphicsPtr::iterator it = map_graphics.find(key);
	//没找到直接返回
	if (it == map_graphics.end()) {
		return;
	}
	if (select.obj) {
		select.obj = nullptr;
	}
	//找到设置为选中
	select.key = key;
	select.obj = it->second;
	return;
}

/// <summary>
/// 取消选中
/// </summary>
void DrawDC::UnSelect() {
	select.key = -1;
	select.obj = nullptr;
	return;
}

/// <summary>
/// 空判断
/// </summary>
/// <returns></returns>
bool DrawDC::SelectEmpty() {
	if (select.obj) {
		return false;
	}
	return true;
}

/// <summary>
/// 移动开始
/// </summary>
/// <param name="begin">起始坐标</param>
void DrawDC::MoveStart(CPoint begin) {
	MoveStatRecordOperation();
	move_begin = begin;
	return;
}

/// <summary>
/// 移动中
/// </summary>
/// <param name="cpoint">移动坐标</param>
void DrawDC::Moving(CPoint cpoint) {
	MoveingRecordOperation();
	CSize csize = cpoint - move_begin;
	MovePattern(csize);
	move_begin = cpoint;
	return;
}

/// <summary>
/// 移动结束
/// </summary>
/// <param name="end">结束坐标</param>
void DrawDC::MoveEnd(CPoint end) {
	MoveEndRecordOperation();
	CSize csize = end - move_begin;
	MovePattern(csize);
	return;
}

/// <summary>
/// 移动图形操作
/// </summary>
/// <param name="offset">相对位移</param>
void DrawDC::MovePattern(CSize offset) {
	if (!(select.obj)) {
		 return;
	}
	
	select.obj->MoveGraphics(offset);
	return;
}

/// <summary>
/// 记录移动开始信息
/// </summary>
void DrawDC::MoveStatRecordOperation() {
	if (move_info.moveing == true) {
		move_info.moveing == false;
	}
	if (move_original_ectype) {
		move_original_ectype.reset();
		move_original_ectype = nullptr;
	}
	if (!(select.obj)) {
		return;
	}
	move_original_ectype = GraphicsShPtr(select.obj->copy());
	move_info.move_start = true;
	return;
}

/// <summary>
/// 记录中开始信息
/// </summary>
void DrawDC::MoveingRecordOperation() {
	move_info.moveing = true;
	return;
}

/// <summary>
/// 记录结束开始信息
/// </summary>
void DrawDC::MoveEndRecordOperation() {
	if (move_info.moveing == true && move_info.move_start == true) {
		Select temp = { 0 };
		temp.key = select.key;
		temp.obj = move_original_ectype;
		DrawUndoRecordOperation(temp);
	}
	move_info.moveing = false;
	move_info.move_start = false;
	return;
}

/// <summary>
/// 保存重做记录
/// </summary>
void DrawDC::DrawRundoRecordOperation(DWORD64 key) {
	//找到当前图形创建副本并保存
	MapGraphicsPtr::iterator it = map_graphics.find(key);
	//没有找到 重做时候要删除
	RecordsStruct current = RecordsStruct(new Records);
	current->key = key;
	if (it == map_graphics.end()) {
		current->history = nullptr;
	}
	else {
		//找的则记录图形副本
		current->history = GraphicsShPtr(it->second->copy());
	}
	rundo_stack.push_front(current);
	return;
}


/// <summary>
/// 旋转图形操作
/// </summary>
/// <param name="angle">旋转角度</param>
void DrawDC::RotatePattern(double angle) {
	if (!(select.obj) && map_graphics.empty()) {
		return;
	}
	DrawUndoRecordOperation(select);
	double temp = select.obj->angle;
	//temp = temp % 360.0;
	temp = fmod(temp, 360.0);
	select.obj->angle = temp + angle;
	return;
}

/// <summary>
/// 删除图形操作
/// </summary>
void DrawDC::DeletePattern() {
	if (!(select.obj) && map_graphics.empty()) {
		return;
	}
	DrawUndoRecordOperation(select);
	select.obj.reset();
	//MapGraphicsPtr::iterator it = map_graphics.find(select.key);
	//it->second.reset();
	map_graphics.erase(select.key);
	select.obj = nullptr;
	return;
}

/// <summary>
/// 记录创建操作
/// </summary>
/// <param name="key">图形的Key</param>
void DrawDC::DrawUndoCreateRecordOperation(DWORD64 key) {
	RecordsStruct temp = RecordsStruct(new Records);
	temp->key = key;
	temp->history = nullptr;
	undo_stack.push_front(temp);
	return;
}

/// <summary>
/// 记录删除或其他操作
/// </summary>
/// <param name="source">图形信息结构体</param>
void DrawDC::DrawUndoRecordOperation(Select source) {
	RecordsStruct temp = RecordsStruct(new Records);
	MapGraphicsPtr::iterator it = map_graphics.find(source.key);
	temp->key = source.key;
	temp->history = GraphicsShPtr(source.obj->copy());
	undo_stack.push_front(temp);
	return;
}

/// <summary>
/// 记录操作
/// </summary>
/// <param name="source">图形key</param>
void DrawDC::DrawUndoRecordOperation(DWORD64 key) {
	//找到当前图形创建副本并保存
	MapGraphicsPtr::iterator it = map_graphics.find(key);
	
	RecordsStruct current = RecordsStruct(new Records);
	current->key = key;
	if (it == map_graphics.end()) {//没有找到 撤销时候要删除
		current->history = nullptr;
	}
	else {
		//找的则记录图形副本
		current->history = GraphicsShPtr(it->second->copy());
	}
	undo_stack.push_front(current);
	return;
}


/// <summary>
/// 撤销操作
/// </summary>
void DrawDC::DrawUndo() {
	if (undo_stack.empty()) {
		return;
	}
	
	RecordsStruct temp = undo_stack.front();
	//保存当前图形
	DrawRundoRecordOperation(temp->key);
	//创建操作记录恢复
	if (!temp->history) {
		map_graphics.erase(temp->key);
	}
	else {
		//删除操作记录恢复 
		MapGraphicsPtr::iterator it = map_graphics.find(temp->key);
		if (it == map_graphics.end()) {
			map_graphics.insert(MapNode(temp->key, temp->history));
		}
		//其他操作记录恢复
		else {
			it->second.swap(temp->history);
			temp->history.reset();
		}
	}
	undo_stack.remove(temp);
	temp.reset();
	return;
}

/// <summary>
/// 重做操作
/// </summary>
void DrawDC::DrawRUndo() {
	if (rundo_stack.empty()) {
		return;
	}

	RecordsStruct temp = rundo_stack.front();
	DrawUndoRecordOperation(temp->key);
	//删除操作记录恢复
	if (!temp->history) {
		map_graphics.erase(temp->key);
	}
	else {
		//创建记录恢复 
		MapGraphicsPtr::iterator it = map_graphics.find(temp->key);
		if (it == map_graphics.end()) {
			map_graphics.insert(MapNode(temp->key, temp->history));
		}
		//其他操作记录恢复
		else {
			it->second.swap(temp->history);
			temp->history.reset();
		}
	}
	rundo_stack.remove(temp);
	//保存撤销操作记录
	//undo_stack.push_front(temp);
	temp.reset();
	return;
}

/// <summary>
/// 清除操作记录
/// </summary>
void DrawDC::ClearRecord() {
	undo_stack.clear();
	rundo_stack.clear();
	return;
}

/// <summary>
/// 反序列化
/// </summary>
void DrawDC::Serialization(const wchar_t* path) {
	std::fstream file;
	file.open(path, std::ios_base::out | std::ios_base::binary);
	if (file.fail()) {
		return;
	}
	for (MapGraphicsPtr::iterator it = map_graphics.begin(); it != map_graphics.end(); it++) {
		//导出图形数据
		Graphics* temp = nullptr;
		temp = it->second.get();
		FileInfo info;
		info.type = temp->type();
		info.size = temp->size();
		file.write((char*)&info, sizeof(FileInfo));
		file.write((char*)temp, info.size);
	}
	
	file.close();
	return;
}

/// <summary>
/// 反序列化
/// </summary>
void DrawDC::Deserialization(const wchar_t* path) {

	//清空图形存储结构
	DrawAllObjectRelease();
	//清空现有操作记录
	ClearRecord();

	std::fstream file;
	file.open(path, std::ios_base::in | std::ios_base::binary);
	if (file.fail()) {
		return;
	}
	//Graphics* a=nullptr;
	//file.read((char*)&a, sizeof(DLine));
	//Graphics* b = a->copy();
	FileInfo info;
	while (file.read((char*) & info,sizeof(FileInfo))) {
		RestoreGraphicsForFile(info, file);
		//file.seekg(sizeof(FileInfo), std::ios_base::cur);
		//Graphics* a=nullptr;
		//DLine a;
		//file.read((char*)&a, info.size);
		//Graphics* b = a.copy();
		//int e = 1;
	}
	file.close();
	

	return;
}

/// <summary>
/// 得到所以图形信息
/// </summary>
/// <param name="stack">保存数据的栈</param>
void DrawDC::GetGraphInfo(GraphInfoStack& stack) {
	//反向迭代器遍历
	for (MapGraphicsPtr::reverse_iterator it = map_graphics.rbegin(); it != map_graphics.rend(); it++) {
		GraphInfo temp;
		//得到图形KEY
		temp.key = it->first;
		//得到图形类型名称
		temp.type = GetTypeStr(it->second->type());
		//得到图形坐标
		temp.coord1 = it->second->getbegin();
		temp.coord2 = it->second->getend();
		//得到图形画笔
		temp.pen = it->second->PenGetLogpen();
		//得到图形画刷
		temp.brush = it->second->BrushGetLogBrush();
		//保存到栈
		stack.push(temp);
	}
	return;
}

/// <summary>
/// 得到图形标志位对应的图形信息字符串
/// </summary>
/// <param name="type">标志位</param>
/// <returns></returns>
CString DrawDC::GetTypeStr(Graphics::PatternType type) {
	CString str;
	switch (type) {
		case Graphics::PatternType::GRAPHICS: {
			str = "图形";
			break;
		}
		case Graphics::PatternType::LINE: {
			str = "直线";
			break;
		}	
		case Graphics::PatternType::RECTANGLE: {
			str = "矩形";
			break;
		}
		case Graphics::PatternType::ROUND: {
			str = "圆形";
			break;
		}
		case Graphics::PatternType::FIVEPOINTEDSTAR: {
			str = "五角星";
			break;
		}
		default: {
			break;
		}
	}
	return str;
}

/// <summary>
/// 判断文件内容并还原到图形保存结构当中
/// </summary>
/// <param name="info">文件当中的图形信息</param>
/// <param name="file">文件指针</param>
void DrawDC::RestoreGraphicsForFile(FileInfo info, std::fstream& file) {
	
	DrawFactoryShPtr factory = nullptr;
	//判断图形类型
	switch (info.type) {
		case Graphics::PatternType::LINE: {
			factory= DrawFactoryShPtr(new DrawFactoryLine);
			break;
		}
		case Graphics::PatternType::RECTANGLE: {
			factory = DrawFactoryShPtr(new DrawFactoryRectangle);
			break;
		}
		case Graphics::PatternType::ROUND: {
			factory = DrawFactoryShPtr(new DrawFactoryRound);
			break;
		}
		case Graphics::PatternType::FIVEPOINTEDSTAR: {
			factory = DrawFactoryShPtr(new DrawFactoryPolygonFive);
			break;
		}
	}

	//创建对应类
	GraphicsShPtr gs_ptr = nullptr;
	GraphicsShPtr temp= GraphicsShPtr(factory->FactoryDrawGraphics());
	file.read((char*)temp.get(), info.size);
	gs_ptr = GraphicsShPtr(temp->copy());

	DWORD64 key = 0;
	//入栈图形
	if (map_graphics.empty()) {
		map_graphics.insert(MapNode(key, gs_ptr));
	}
	else {
		MapGraphicsPtr::iterator max = map_graphics.end();
		max--;
		key = max->first + 1;
		map_graphics.insert(MapNode(key, gs_ptr));
	}
	gs_ptr.reset();
	return;
}

/// <summary>
/// 删除所有重做记录
/// </summary>
void DrawDC::DrawRundoRecordClear() {
	rundo_stack.clear();
	return;
}
