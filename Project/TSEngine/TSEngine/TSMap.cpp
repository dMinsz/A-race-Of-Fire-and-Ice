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
		//LR_DEFAULTSIZE | LR_LOADFROMFILE	 //�⺻ũ��+�ܺ����Ϸε� DDB �� �ε��ϰ� ��
		LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION
	);

	//�޸� DC �� ��Ʈ�� ���̱�..
	tmpMap.m_MemDC = CreateCompatibleDC(hdc);
	SelectObject(tmpMap.m_MemDC, tmpMap.m_hBackGround);
	ReleaseDC(hwnd, hdc);

	//��Ʈ�� ���� �ε�..
	ZeroMemory(&tmpMap.m_hInfo, sizeof(BITMAPINFO));
	DIBSECTION ds;
	GetObject(tmpMap.m_hBackGround, sizeof(ds), &ds);
	tmpMap.m_hInfo.bmiHeader = ds.dsBmih;		//�ε���, ��Ʈ�� ���� ��ü ȹ��.	
	tmpMap.m_Width = ds.dsBmih.biWidth;			//���� ���Ǵ� ũ�⸦ ������ ����.
	tmpMap.m_Height = ds.dsBmih.biHeight;



	//�ܺε����Ϳ� ����.
	*map = tmpMap;


	//������ �ǹ̷�, true ����..
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
	{// debug ��// �簢������ �� ó��

		HDC hdc = GetDC(hwnd);
		tmpMap.m_MemDC = CreateCompatibleDC(hdc);
		HBITMAP testBitmap = CreateCompatibleBitmap(hdc, MAP_WIDTH, MAP_HEIGHT);
		SelectObject(tmpMap.m_MemDC, testBitmap);
		//ReleaseDC(hwnd, hdc);

		HBRUSH	newBrush, oldBrush;

		// brush �Ӽ��� �ٲ��ش�.
		newBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(tmpMap.m_MemDC, newBrush);

		Rectangle(tmpMap.m_MemDC, 0, 0, MAP_WIDTH, MAP_HEIGHT);

		// �� �׷����� �� �Ӽ��� �������.
		SelectObject(tmpMap.m_MemDC, oldBrush);
		DeleteObject(newBrush);

		ReleaseDC(hwnd, hdc);
	}
}
