#pragma once

//Debug�� �ӽ� �� ũ��
#define MAP_WIDTH 720
#define MAP_HEIGHT 1280

struct POSITION
{
	int x;
	int y;
};


class TSMap
{
public:

	// ��������Ʈ�� �ε� �� DC
	HDC m_MemDC;
	// ��Ʈ�� �ڵ�
	HBITMAP m_hBackGround;

	BITMAPINFO  m_hInfo;
	
	//BackBuffer ���� ��ġ
	POSITION Pos;

	int m_Width;	// ��
	int m_Height;	// ����

private:
	//���������� �����
	int LoadBackGround(HWND hwnd, TSMap* map, const char* filePath);

public:
	TSMap();

	//color�� ����׿� // �簢������ ��ó��
	void Init(HWND hwnd, HDC memDC, HBITMAP hBitmap, POSITION pos, const char* filePath = NULL, COLORREF color=NULL);
};