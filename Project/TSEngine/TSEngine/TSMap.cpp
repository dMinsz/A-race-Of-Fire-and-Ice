#include "Framework.h"
#include "TSEngine.h"
#include "AniInfo.h"
#include "TSprite.h"
#include "TSMap.h"
#include "GameMap.h"

TSMap::TSMap()
{
	Pos.x = NULL;
	Pos.y = NULL;
	m_hBackGround = NULL;
	m_MemDC = NULL;
	m_hInfo = {};
	m_Width = 0;
	m_Height = 0;
}

int TSMap::LoadBackGround(HWND hwnd, TSMap* map, const char* filePath)
{

	TSMap tmpMap;
	HDC hdc = GetDC(hwnd);

	tmpMap.m_hBackGround = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0,
		//LR_DEFAULTSIZE | LR_LOADFROMFILE	 //기본크기+외부파일로딩 DDB 로 로딩하게 됨
		LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION
	);

	//메모리 DC 에 비트멥 붙이기..
	tmpMap.m_MemDC = CreateCompatibleDC(hdc);
	SelectObject(tmpMap.m_MemDC, tmpMap.m_hBackGround);
	ReleaseDC(hwnd, hdc);

	//비트멥 정보 로딩..
	ZeroMemory(&tmpMap.m_hInfo, sizeof(BITMAPINFO));
	DIBSECTION ds;
	GetObject(tmpMap.m_hBackGround, sizeof(ds), &ds);
	tmpMap.m_hInfo.bmiHeader = ds.dsBmih;		//로딩된, 비트멥 정보 전체 획득.	
	tmpMap.m_Width = ds.dsBmih.biWidth;			//자주 사용되는 크기를 별도로 저장.
	tmpMap.m_Height = ds.dsBmih.biHeight;



	//외부데이터에 복사.
	*map = tmpMap;


	//성공이 의미로, true 리턴..
	return TRUE;
}

void TSMap::Init(HWND hwnd, HDC memDC, HBITMAP hBitmap, POSITION pos, const char* filePath, COLORREF color)
{
	TSMap tmpMap;

	if (filePath != NULL)
	{
		this->LoadBackGround(hwnd, &tmpMap, filePath);
	}
	else
	{// debug 용// 사각형으로 맵 처리

		HDC hdc = GetDC(hwnd);
		tmpMap.m_MemDC = CreateCompatibleDC(hdc);
		HBITMAP testBitmap = CreateCompatibleBitmap(hdc, MAP_WIDTH, MAP_HEIGHT);
		SelectObject(tmpMap.m_MemDC, testBitmap);
		//ReleaseDC(hwnd, hdc);

		HBRUSH	newBrush, oldBrush;

		// brush 속성도 바꿔준다.
		newBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(tmpMap.m_MemDC, newBrush);

		Rectangle(tmpMap.m_MemDC, 0, 0, MAP_WIDTH, MAP_HEIGHT);

		// 다 그렸으면 각 속성을 원래대로.
		SelectObject(tmpMap.m_MemDC, oldBrush);
		DeleteObject(newBrush);

		ReleaseDC(hwnd, hdc);
	}
}
