#pragma once

//Debug용 임시 맵 크기
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

	// 스프라이트가 로드 될 DC
	HDC m_MemDC;
	// 비트맵 핸들
	HBITMAP m_hBackGround;

	BITMAPINFO  m_hInfo;
	
	//BackBuffer 기준 위치
	POSITION Pos;

	int m_Width;	// 폭
	int m_Height;	// 높이

private:
	//내부적으로 사용중
	int LoadBackGround(HWND hwnd, TSMap* map, const char* filePath);

public:
	TSMap();

	//color는 디버그용 // 사각형으로 맵처리
	void Init(HWND hwnd, HDC memDC, HBITMAP hBitmap, POSITION pos, const char* filePath = NULL, COLORREF color=NULL);
};