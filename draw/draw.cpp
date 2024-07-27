#include "..\pch.h"

#include "draw.h"


/// <summary>
/// ����ֱ��
/// </summary>
void DrawDC::DrawLine() {
  dynamic_factory_ptr = DrawFactoryShPtr(new DrawFactoryLine);
  DrawCreatObject();
  return;
}

/// <summary>
/// ���ƾ���
/// </summary>
void DrawDC::DrawRectangle() {
  dynamic_factory_ptr = DrawFactoryShPtr(new DrawFactoryRectangle);
  DrawCreatObject();
  return;
}

/// <summary>
/// ����Բ��
/// </summary>
void DrawDC::DrawRound() {
  dynamic_factory_ptr = DrawFactoryShPtr(new DrawFactoryRound);
  DrawCreatObject();
  return;
}

/// <summary>
/// ������չ����������
/// </summary>
void DrawDC::ExDrawFivePointedStar() {
  dynamic_factory_ptr = DrawFactoryShPtr(new DrawFactoryPolygonFive);
  DrawCreatObject();
  return;
}

/// <summary>
/// ����ͼ�ζ���
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
/// ������ʼ����
/// </summary>
/// <param name="point">�����</param>
void DrawDC::DrawSetBeginPoint(CPoint point) {
	if (!dynamic_graphics_ptr) {
		return;
	}
  dynamic_graphics_ptr->setbegin(point);
  return;
}

/// <summary>
/// ���ý�������
/// </summary>
/// <param name="point">�����</param>
void DrawDC::DrawSetEndPoint(CPoint point) {
	if (!dynamic_graphics_ptr) {
		return;
	}
  dynamic_graphics_ptr->setend(point);
  return;
}

/// <summary>
/// �������
/// </summary>
void DrawDC::DrawObjectReset() {
	if (dynamic_graphics_ptr) {
		dynamic_graphics_ptr.reset();
	}
	dynamic_graphics_ptr = nullptr;
  return;
}

/// <summary>
/// ���浱ǰ����
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
/// �ͷ����ж���
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
/// ���Ƶ�cdc����
/// </summary>
/// <param name="cdc_obj">Ŀ��cdc</param>
/// <param name="crect_wnd">���ڲ���</param>
void DrawDC::DrawPaintDC(CDC* cdc_obj, CRect& crect_wnd) {
	//�����ڴ�DC
	CDC memory_cdc;
	memory_cdc.CreateCompatibleDC(cdc_obj);
	//��ȡ���ڲ���
	//CRect crect_wnd;
	//GetClientRect(&crect_wnd);
	//��������λͼ
	CBitmap cbitmap;
	cbitmap.CreateCompatibleBitmap(cdc_obj, crect_wnd.Width(), crect_wnd.Height());
	//��λͼѡ���ڴ�DC
	memory_cdc.SelectObject(&cbitmap);
	//���ñ���Ϊ��ɫ
	memory_cdc.FillSolidRect(&crect_wnd, RGB(255, 255, 255));

	//���Ƶ�ǰͼ��
	if (dynamic_graphics_ptr) {
		dynamic_graphics_ptr->DrawStyleAndGraphics(&memory_cdc);
	}
	

	if (map_graphics.empty()) {
		goto EXIT;
	}
	//����ѡ����ͼ���Ӵ�
	if (select.obj) {
		select.obj->PenSetlopnWidth(select.obj->PenGetlopnWidth() + 2);
	}
	//��������ͼ��

	for (MapGraphicsPtr::iterator it = map_graphics.begin(); it != map_graphics.end(); it++) {
		//���ڴ�DC����ɻ���
		it->second->DrawStyleAndGraphics(&memory_cdc);
	}

	if (select.obj) {
		select.obj->PenSetlopnWidth(select.obj->PenGetlopnWidth() - 2);
	}
EXIT:
	//���ڴ�DC�е�ͼƬ�������ͻ���
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
/// ���û���
/// </summary>
/// <param name="brush">���ʽṹ��</param>
void DrawDC::DrawSetPen(LOGPEN pen) {
	if (dynamic_graphics_ptr) {
		dynamic_graphics_ptr->PenSetLogpen(pen);
	}
	return;
}

/// <summary>
/// ���û�ˢ
/// </summary>
/// <param name="brush">��ˢ�ṹ��</param>
void DrawDC::DrawSetBrush(LOGBRUSH brush) {
	if (dynamic_graphics_ptr) {
		dynamic_graphics_ptr->BrushSetLogBrush(brush);
	}
}

/// <summary>
/// ����ѡ�ж��󻭱�
/// </summary>
/// <param name="pen">���ʽṹ��</param>
void DrawDC::DrawSelectSetPen(LOGPEN pen) {
	if (select.obj) {
		select.obj->PenSetLogpen(pen);
	}
	return;
}

/// <summary>
/// ����ѡ�ж���ˢ
/// </summary>
/// <param name="brush">��ˢ�ṹ��</param>
void DrawDC::DrawSelectSetBrush(LOGBRUSH brush) {
	if (select.obj) {
		select.obj->BrushSetLogBrush(brush);
	}
	return;
}

/// <summary>
/// ��ȡѡ�ж��󻭱���Ϣ
/// </summary>
/// <returns>���ʽṹ��</returns>
LOGPEN DrawDC::DrawSelectGetPen() {
	if (select.obj) {
		return select.obj->PenGetLogpen();
	}
	return LOGPEN();
}

/// <summary>
/// ��ȡѡ�ж���ˢ��Ϣ
/// </summary>
/// <returns>��ˢ�ṹ��</returns>
LOGBRUSH DrawDC::DrawSelectGetBrush() {
	if (select.obj) {
		return select.obj->BrushGetLogBrush();
	}
	return LOGBRUSH();
}

/// <summary>
/// ���ѡ��
/// </summary>
/// <param name="point">����</param>
void DrawDC::IsSelect(CPoint point) {
	if (dynamic_graphics_ptr) {
		return;
	}

	//�������������
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
/// ����ѡ��
/// </summary>
/// <param name="key">ͼ�ε�key</param>
void DrawDC::IsSelect(DWORD64 key) {
	//�շ���
	if (map_graphics.empty()) {
		return;
	}
	MapGraphicsPtr::iterator it = map_graphics.find(key);
	//û�ҵ�ֱ�ӷ���
	if (it == map_graphics.end()) {
		return;
	}
	if (select.obj) {
		select.obj = nullptr;
	}
	//�ҵ�����Ϊѡ��
	select.key = key;
	select.obj = it->second;
	return;
}

/// <summary>
/// ȡ��ѡ��
/// </summary>
void DrawDC::UnSelect() {
	select.key = -1;
	select.obj = nullptr;
	return;
}

/// <summary>
/// ���ж�
/// </summary>
/// <returns></returns>
bool DrawDC::SelectEmpty() {
	if (select.obj) {
		return false;
	}
	return true;
}

/// <summary>
/// �ƶ���ʼ
/// </summary>
/// <param name="begin">��ʼ����</param>
void DrawDC::MoveStart(CPoint begin) {
	MoveStatRecordOperation();
	move_begin = begin;
	return;
}

/// <summary>
/// �ƶ���
/// </summary>
/// <param name="cpoint">�ƶ�����</param>
void DrawDC::Moving(CPoint cpoint) {
	MoveingRecordOperation();
	CSize csize = cpoint - move_begin;
	MovePattern(csize);
	move_begin = cpoint;
	return;
}

/// <summary>
/// �ƶ�����
/// </summary>
/// <param name="end">��������</param>
void DrawDC::MoveEnd(CPoint end) {
	MoveEndRecordOperation();
	CSize csize = end - move_begin;
	MovePattern(csize);
	return;
}

/// <summary>
/// �ƶ�ͼ�β���
/// </summary>
/// <param name="offset">���λ��</param>
void DrawDC::MovePattern(CSize offset) {
	if (!(select.obj)) {
		 return;
	}
	
	select.obj->MoveGraphics(offset);
	return;
}

/// <summary>
/// ��¼�ƶ���ʼ��Ϣ
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
/// ��¼�п�ʼ��Ϣ
/// </summary>
void DrawDC::MoveingRecordOperation() {
	move_info.moveing = true;
	return;
}

/// <summary>
/// ��¼������ʼ��Ϣ
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
/// ����������¼
/// </summary>
void DrawDC::DrawRundoRecordOperation(DWORD64 key) {
	//�ҵ���ǰͼ�δ�������������
	MapGraphicsPtr::iterator it = map_graphics.find(key);
	//û���ҵ� ����ʱ��Ҫɾ��
	RecordsStruct current = RecordsStruct(new Records);
	current->key = key;
	if (it == map_graphics.end()) {
		current->history = nullptr;
	}
	else {
		//�ҵ����¼ͼ�θ���
		current->history = GraphicsShPtr(it->second->copy());
	}
	rundo_stack.push_front(current);
	return;
}


/// <summary>
/// ��תͼ�β���
/// </summary>
/// <param name="angle">��ת�Ƕ�</param>
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
/// ɾ��ͼ�β���
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
/// ��¼��������
/// </summary>
/// <param name="key">ͼ�ε�Key</param>
void DrawDC::DrawUndoCreateRecordOperation(DWORD64 key) {
	RecordsStruct temp = RecordsStruct(new Records);
	temp->key = key;
	temp->history = nullptr;
	undo_stack.push_front(temp);
	return;
}

/// <summary>
/// ��¼ɾ������������
/// </summary>
/// <param name="source">ͼ����Ϣ�ṹ��</param>
void DrawDC::DrawUndoRecordOperation(Select source) {
	RecordsStruct temp = RecordsStruct(new Records);
	MapGraphicsPtr::iterator it = map_graphics.find(source.key);
	temp->key = source.key;
	temp->history = GraphicsShPtr(source.obj->copy());
	undo_stack.push_front(temp);
	return;
}

/// <summary>
/// ��¼����
/// </summary>
/// <param name="source">ͼ��key</param>
void DrawDC::DrawUndoRecordOperation(DWORD64 key) {
	//�ҵ���ǰͼ�δ�������������
	MapGraphicsPtr::iterator it = map_graphics.find(key);
	
	RecordsStruct current = RecordsStruct(new Records);
	current->key = key;
	if (it == map_graphics.end()) {//û���ҵ� ����ʱ��Ҫɾ��
		current->history = nullptr;
	}
	else {
		//�ҵ����¼ͼ�θ���
		current->history = GraphicsShPtr(it->second->copy());
	}
	undo_stack.push_front(current);
	return;
}


/// <summary>
/// ��������
/// </summary>
void DrawDC::DrawUndo() {
	if (undo_stack.empty()) {
		return;
	}
	
	RecordsStruct temp = undo_stack.front();
	//���浱ǰͼ��
	DrawRundoRecordOperation(temp->key);
	//����������¼�ָ�
	if (!temp->history) {
		map_graphics.erase(temp->key);
	}
	else {
		//ɾ��������¼�ָ� 
		MapGraphicsPtr::iterator it = map_graphics.find(temp->key);
		if (it == map_graphics.end()) {
			map_graphics.insert(MapNode(temp->key, temp->history));
		}
		//����������¼�ָ�
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
/// ��������
/// </summary>
void DrawDC::DrawRUndo() {
	if (rundo_stack.empty()) {
		return;
	}

	RecordsStruct temp = rundo_stack.front();
	DrawUndoRecordOperation(temp->key);
	//ɾ��������¼�ָ�
	if (!temp->history) {
		map_graphics.erase(temp->key);
	}
	else {
		//������¼�ָ� 
		MapGraphicsPtr::iterator it = map_graphics.find(temp->key);
		if (it == map_graphics.end()) {
			map_graphics.insert(MapNode(temp->key, temp->history));
		}
		//����������¼�ָ�
		else {
			it->second.swap(temp->history);
			temp->history.reset();
		}
	}
	rundo_stack.remove(temp);
	//���泷��������¼
	//undo_stack.push_front(temp);
	temp.reset();
	return;
}

/// <summary>
/// ���������¼
/// </summary>
void DrawDC::ClearRecord() {
	undo_stack.clear();
	rundo_stack.clear();
	return;
}

/// <summary>
/// �����л�
/// </summary>
void DrawDC::Serialization(const wchar_t* path) {
	std::fstream file;
	file.open(path, std::ios_base::out | std::ios_base::binary);
	if (file.fail()) {
		return;
	}
	for (MapGraphicsPtr::iterator it = map_graphics.begin(); it != map_graphics.end(); it++) {
		//����ͼ������
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
/// �����л�
/// </summary>
void DrawDC::Deserialization(const wchar_t* path) {

	//���ͼ�δ洢�ṹ
	DrawAllObjectRelease();
	//������в�����¼
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
/// �õ�����ͼ����Ϣ
/// </summary>
/// <param name="stack">�������ݵ�ջ</param>
void DrawDC::GetGraphInfo(GraphInfoStack& stack) {
	//�������������
	for (MapGraphicsPtr::reverse_iterator it = map_graphics.rbegin(); it != map_graphics.rend(); it++) {
		GraphInfo temp;
		//�õ�ͼ��KEY
		temp.key = it->first;
		//�õ�ͼ����������
		temp.type = GetTypeStr(it->second->type());
		//�õ�ͼ������
		temp.coord1 = it->second->getbegin();
		temp.coord2 = it->second->getend();
		//�õ�ͼ�λ���
		temp.pen = it->second->PenGetLogpen();
		//�õ�ͼ�λ�ˢ
		temp.brush = it->second->BrushGetLogBrush();
		//���浽ջ
		stack.push(temp);
	}
	return;
}

/// <summary>
/// �õ�ͼ�α�־λ��Ӧ��ͼ����Ϣ�ַ���
/// </summary>
/// <param name="type">��־λ</param>
/// <returns></returns>
CString DrawDC::GetTypeStr(Graphics::PatternType type) {
	CString str;
	switch (type) {
		case Graphics::PatternType::GRAPHICS: {
			str = "ͼ��";
			break;
		}
		case Graphics::PatternType::LINE: {
			str = "ֱ��";
			break;
		}	
		case Graphics::PatternType::RECTANGLE: {
			str = "����";
			break;
		}
		case Graphics::PatternType::ROUND: {
			str = "Բ��";
			break;
		}
		case Graphics::PatternType::FIVEPOINTEDSTAR: {
			str = "�����";
			break;
		}
		default: {
			break;
		}
	}
	return str;
}

/// <summary>
/// �ж��ļ����ݲ���ԭ��ͼ�α���ṹ����
/// </summary>
/// <param name="info">�ļ����е�ͼ����Ϣ</param>
/// <param name="file">�ļ�ָ��</param>
void DrawDC::RestoreGraphicsForFile(FileInfo info, std::fstream& file) {
	
	DrawFactoryShPtr factory = nullptr;
	//�ж�ͼ������
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

	//������Ӧ��
	GraphicsShPtr gs_ptr = nullptr;
	GraphicsShPtr temp= GraphicsShPtr(factory->FactoryDrawGraphics());
	file.read((char*)temp.get(), info.size);
	gs_ptr = GraphicsShPtr(temp->copy());

	DWORD64 key = 0;
	//��ջͼ��
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
/// ɾ������������¼
/// </summary>
void DrawDC::DrawRundoRecordClear() {
	rundo_stack.clear();
	return;
}
