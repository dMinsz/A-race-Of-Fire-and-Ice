#include "TSEngine.h"


TSEngine* TSEngine::m_Instance = nullptr;

TSEngine::TSEngine()
{
}

TSEngine::~TSEngine()
{
}

TSEngine* TSEngine::GetEngine()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new TSEngine();
	}

	return m_Instance;
}

HDC TSEngine::GetMainDC()
{
	return m_hMainDC;
}

HDC TSEngine::GetBackBufferDC()
{
	return m_BackBuffer;
}

void TSEngine::Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight)
{

	//스크린 크기 초기화 백버퍼 및 윈도우크기도
	Screen.Width = screenWidth;
	Screen.Height = screenHeight;


	m_hWnd = hWnd;

	// 화면에 대한 DC
	m_hMainDC = GetDC(hWnd);


	// 백버퍼
	m_BackBuffer = CreateCompatibleDC(m_hMainDC);
	HBITMAP m_BackBufferBitmap = CreateCompatibleBitmap(m_hMainDC, Screen.Width, Screen.Height);
	SelectObject(m_BackBuffer, m_BackBufferBitmap);
}

void TSEngine::UpdateAll()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_PosX -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_PosX += 1;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_PosY -= 1;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_PosY += 1;
	}
}

void TSEngine::RenderAll()
{
	// 화면을 지운다.
	Rectangle(m_BackBuffer, 0, 0, Screen.Width, Screen.Height);

	// 캐릭터를 그린다.
	//int _x = rand() % 100;
	//int _y = rand() % 100;

	/*Ellipse(m_BackBuffer, m_PosX, m_PosY, m_PosX + 100, m_PosY + 100);
	Ellipse(m_BackBuffer, m_PosX, m_PosY, m_PosX + 200, m_PosY + 200);
	Ellipse(m_BackBuffer, m_PosX, m_PosY, m_PosX + 300, m_PosY + 300);*/


	/// 백버퍼를 화면에 그린다. (더블 버퍼링)
	BitBlt(m_hMainDC, 0, 0, Screen.Width, Screen.Height, m_BackBuffer, 0, 0, SRCCOPY);

}

//?
void TSEngine::BeginRender()
{

	// 화면을 지운다.
	Rectangle(m_BackBuffer, 0, 0, Screen.Width, Screen.Height);

}

void TSEngine::EndRender()
{
	/// 백버퍼를 화면에 그린다. (더블 버퍼링)
	BitBlt(m_hMainDC, 0, 0, Screen.Width, Screen.Height, m_BackBuffer, 0, 0, SRCCOPY);
}

int TSEngine::MakeLectangleSprite(TSprite* sprite, int LSizeWidth, int LSizeHeight)
{
	TSprite tmpSprite;
	HDC tempMemDC;
	HDC hdc = GetDC(m_hWnd);

	//tempMemDC = CreateCompatibleDC(m_hMainDC);
	tmpSprite.m_MemDC = CreateCompatibleDC(hdc);
	tmpSprite.m_hBitmap = CreateCompatibleBitmap(hdc, LSizeWidth, LSizeHeight);
	
	SelectObject(tmpSprite.m_MemDC, tmpSprite.m_hBitmap);

	//릴리즈
	ReleaseDC(m_hWnd, hdc);


	//비트멥 정보 로딩..
	ZeroMemory(&tmpSprite.hInfo, sizeof(BITMAPINFO));
	DIBSECTION ds;
	GetObject(tmpSprite.m_hBitmap, sizeof(ds), &ds);
	tmpSprite.hInfo.bmiHeader = ds.dsBmih;		//로딩된, 비트멥 정보 전체 획득.	
	tmpSprite.m_Width = ds.dsBmih.biWidth;			//자주 사용되는 크기를 별도로 저장.
	tmpSprite.m_Height = ds.dsBmih.biHeight;

	// 스프라이트 중점
	tmpSprite.m_CenterX = tmpSprite.m_Width / 2;
	tmpSprite.m_CenterY = tmpSprite.m_Height / 2;

	//충돌체


	//test / prototype 용
	this->DrawRectangle(tmpSprite.m_MemDC,0,0, LSizeWidth, LSizeHeight,RGB(255,0,255));

	*sprite = tmpSprite;

	
	return TRUE;
}

int TSEngine::LoadSprite(TSprite* sprite, const char* filePath)
{
	if (sprite == NULL) return FALSE;

	TSprite tmpSprite;
	HDC hdc = GetDC(m_hWnd);

	tmpSprite.m_hBitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0,
		//LR_DEFAULTSIZE | LR_LOADFROMFILE	 //기본크기+외부파일로딩 DDB 로 로딩하게 됨
		LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION
	);

	//메모리 DC 에 비트멥 붙이기..
	tmpSprite.m_MemDC = CreateCompatibleDC(hdc);
	SelectObject(tmpSprite.m_MemDC, tmpSprite.m_hBitmap);
	ReleaseDC(m_hWnd, hdc);

	//비트멥 정보 로딩..
	ZeroMemory(&tmpSprite.hInfo, sizeof(BITMAPINFO));
	DIBSECTION ds;
	GetObject(tmpSprite.m_hBitmap, sizeof(ds), &ds);
	tmpSprite.hInfo.bmiHeader = ds.dsBmih;		//로딩된, 비트멥 정보 전체 획득.	
	tmpSprite.m_Width = ds.dsBmih.biWidth;			//자주 사용되는 크기를 별도로 저장.
	tmpSprite.m_Height = ds.dsBmih.biHeight;

	// 스프라이트 중점
	tmpSprite.m_CenterX = tmpSprite.m_Width / 2;
	tmpSprite.m_CenterY = tmpSprite.m_Height / 2;

	//컬러키 마젠타값
	tmpSprite.KeyColor = RGB(255, 0, 255);


	//애니메이션관련 세팅해야함


	//충돌체 관련데이터 만들기.




	//외부데이터에 복사.
	* sprite = tmpSprite;



	//성공이 의미로, true 리턴..
	return TRUE;
}

int TSEngine::LoadSpriteSheet(TSprite* sprite, const char* filePath, AniInfo aniInfo)
{
	if (sprite == NULL) return FALSE;

	TSprite tmpSprite;
	HDC hdc = GetDC(m_hWnd);

	tmpSprite.m_hBitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0,
		//LR_DEFAULTSIZE | LR_LOADFROMFILE	 //기본크기+외부파일로딩 DDB 로 로딩하게 됨
		LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION
	);

	//메모리 DC 에 비트멥 붙이기..
	tmpSprite.m_MemDC = CreateCompatibleDC(hdc);
	SelectObject(tmpSprite.m_MemDC, tmpSprite.m_hBitmap);
	ReleaseDC(m_hWnd, hdc);

	//비트멥 정보 로딩..
	ZeroMemory(&tmpSprite.hInfo, sizeof(BITMAPINFO));
	DIBSECTION ds;
	GetObject(tmpSprite.m_hBitmap, sizeof(ds), &ds);
	tmpSprite.hInfo.bmiHeader = ds.dsBmih;		//로딩된, 비트멥 정보 전체 획득.	
	tmpSprite.m_Width = ds.dsBmih.biWidth;			//자주 사용되는 크기를 별도로 저장.
	tmpSprite.m_Height = ds.dsBmih.biHeight;

	// 스프라이트 중점
	//tmpSprite.m_CenterX = tmpSprite.m_Width / 2;
	//tmpSprite.m_CenterY = tmpSprite.m_Height / 2;

	//컬러키 마젠타값
	tmpSprite.KeyColor = RGB(255, 0, 255);


	//애니메이션관련 세팅해야함



	tmpSprite.m_AniInfo = aniInfo;




	//충돌체 관련데이터 만들기.




	//외부데이터에 복사.
	* sprite = tmpSprite;



	//성공이 의미로, true 리턴..
	return TRUE;
}


void TSEngine::SpriteRelease(TSprite* sprite)
{
	DeleteObject(sprite->m_hBitmap);  sprite->m_hBitmap = NULL;
	DeleteDC(sprite->m_MemDC);	sprite->m_MemDC = NULL;

}

void TSEngine::DrawSpriteOrigin(HDC hdc, int x, int y, TSprite* sprite, float scaleX, float scaleY)
{
	//스케일 처리..
	int width = (int)(sprite->m_Width * scaleX);
	int height = (int)(sprite->m_Height * scaleY);

	//투명색 없이 그리기.
	::BitBlt(hdc, x, y, width, height, sprite->m_MemDC, 0, 0, SRCCOPY);
}

void TSEngine::DrawSprite(HDC hdc, int x, int y, TSprite* sprite, float scaleX, float scaleY)
{
	//스케일 처리..
	int width = (int)(sprite->m_Width * scaleX);
	int height = (int)(sprite->m_Height * scaleY);

	//투명색 처리.

	if (sprite->KeyColor != NULL)
	{
		::TransparentBlt(hdc, x, y, width, height,
			sprite->m_MemDC, 0, 0, sprite->m_Width, sprite->m_Height, sprite->KeyColor);
	}
	else
	{
		//투명색 없이 그리기.
		::BitBlt(hdc, x, y, width, height, sprite->m_MemDC, 0, 0, SRCCOPY);
	}


}

void TSEngine::RotateDrawSprite(HDC hdc, int x, int y, TSprite* sprite, float angle, float scaleX, float scaleY)
{

	//스케일 처리..
	int width = (int)(sprite->m_Width * scaleX);
	int height = (int)(sprite->m_Height * scaleY);

	// 파이값 = 3.141592f 
	// 1 라디안 값 =  0.017453f // 1라디안 구하는 공식 => PI /180.0f
	// 1라디안 * angle => rad값 

	float rad = 0.017453f * angle;
	float cs = cos(rad);
	float si = sin(rad);

	int& ow = width;
	int& oh = height;
	int w = (int)((float)width * 1.4f);
	int h = (int)((float)height * 1.4f);

	//회전된 비트멥 결과용 리소스 생성.	
	HDC destDC = CreateCompatibleDC(hdc);                             // 회전할 비트맵을 출력받을 DC           
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, w, h);			// 회전할 비트맵을 출력받을 메모리비트맵 핸들      
	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);   // 회전할 비트맵을 출력받을 DC에, 회전할 비트맵을 출력받을 메모리비트맵 선택     

	//결과용 비트멥, 클리어
	//HBRUSH hbrBack = CreateSolidBrush(RGB(255, 255, 255));         // 회전으로 인한, 공백영역을 칠할 브러시핸들 생성    (디버그용)
	////HBRUSH hbrBack      = CreateSolidBrush( transColor );           // 회전으로 인한, 공백영역을 칠할 브러시핸들 생성    
	//HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);      // 브러시핸들 선택    
	//PatBlt(destDC, 0, 0, w, h, PATCOPY);								// 선택된 브러시로, 회전할 비트맵을 출력받을 DC에, 미리 색상을 채워 지움    
	//DeleteObject(SelectObject(destDC, hbrOld));                     // 브러시 해제     


	// 비트멥 회전 처리.
	::SetGraphicsMode(destDC, GM_ADVANCED);
	//::SetMapMode(hdc, MM_LOENGLISH); 

	XFORM xform;
	xform.eM11 = cs * scaleX;
	xform.eM12 = si * scaleX;
	xform.eM21 = -si * scaleY;
	xform.eM22 = cs * scaleY;
	xform.eDx = (float)w / 2.0f;
	xform.eDy = (float)h / 2.0f;

	//xform.eDx = (float)width * 1.4f / 2.0f;
	//xform.eDy = (float)height * 1.4f / 2.0f;
	//xform.eDx = x - cos(rad) * x + sin(rad) * y;     
	//xform.eDy = y - cos(rad) * y - sin(rad) * x;     

	//xform.eDx = 0; 
	//xform.eDy = 0;  

	::SetWorldTransform(destDC, &xform);

	// Now do the actual rotating - a pixel at a time    
	//BitBlt(destDC, 0, 0, w, h, pSpr->hSurface, 0, 0, SRCCOPY );     
	//BitBlt(destDC, -(ow/2), -(oh/2), w, h, pSpr->hSurface, 0, 0, SRCCOPY );     
	int dx = (int)((float)ow / (2 * scaleX));
	int dy = (int)((float)oh / (2 * scaleY));
	BitBlt(destDC, -dx, -dy, w, h, sprite->m_MemDC, 0, 0, SRCCOPY);
	//StretchBlt(destDC, -(ow/2), -(oh/2), w, h, pSpr->hSurface, 0, 0, w, h, SRCCOPY );     
	SelectObject(destDC, hbmOldDest);



	// * 회전된 비트멥 얻기 완료....* ★
	HDC hTempMemDC = CreateCompatibleDC(hdc);
	SelectObject(hTempMemDC, hbmResult);

	//(백버퍼) 화면에 출력.★

	//투명색 처리.
	::TransparentBlt(
		hdc,
		x, y,
		w, h,					//회전된 비트멥의 가로/세로 크기.(스케일 처리 포함)
		//width, height,		//원본 비트멥의 가로/세로 크기 (스케일 처리 포함)
		destDC, 0, 0, w, h,  //회전된 비트멥..★
		//pSpr->hSurface, 0, 0,  pSpr->Width, pSpr->Height,  //<-- 필요하다면, 일정 부분 잘라서 그리기도 가능하겠지요.
		sprite->KeyColor);
	BitBlt(hdc, x, y, w, h, destDC, 0, 0, SRCCOPY);
	//BitBlt( hdc, x-w/2, y-h/2, w, h, hTempMemDC, 0, 0, SRCCOPY);
//BitBlt(hdc, x, y, w, h, hTempMemDC, 0, 0, SRCCOPY);
	::TransparentBlt(
		hdc, x, y, w, h,		//회전된 비트멥의 가로/세로 크기.(스케일 처리 포함)
		hTempMemDC, 0, 0, w, h,		//회전된 비트멥..★
		sprite->KeyColor);


	// 그래픽 모드 복구.    
	//SetGraphicsMode(destDC, GM_COMPATIBLE);    

	//리소스 해제.
	DeleteDC(destDC);
	DeleteDC(hTempMemDC);
	DeleteObject(hbmResult);
}

void TSEngine::SpriteAnimation(TSprite* sprite, float dtime)
{
	sprite->m_AniInfo.m_AniTime += dtime;

	if (sprite->m_AniInfo.m_AniTime > FPS(sprite->m_AniInfo.m_AniFPS))		//1초당 7프레임의 속도 경과후..
	{
		sprite->m_AniInfo.m_AniTime = 0.0f;

		sprite->m_AniInfo.m_AniFrm += 1;

		if (sprite->m_AniInfo.m_AniFrm >= sprite->m_AniInfo.m_FrmMax) sprite->m_AniInfo.m_AniFrm = 0;	//프레임 리셋.
	}
}

void TSEngine::DrawAnimation(HDC hdc, int x, int y, TSprite* sprite, float dtime)
{
	SpriteAnimation(sprite, dtime); //프레임,시간 설정

	int sprX = sprite->m_AniInfo.m_CutSizeWidth * sprite->m_AniInfo.m_AniFrm;
	int sprY = 0;
	int sprWidth = sprite->m_AniInfo.m_CutSizeWidth;
	int sprHeight = sprite->m_AniInfo.m_CutSizeHeight;

	//BitBlt(hdc, x, y, sprWidth, sprHeight, sprite->m_MemDC, sprX, sprY, SRCCOPY);

	TransparentBlt(hdc, x, y, sprWidth, sprHeight, sprite->m_MemDC, sprX, sprY, sprWidth, sprHeight, sprite->KeyColor);

	//BitBlt(hdc,sprite->m_AniInfo.m_CutSizeWidth * spri , g_HeroPos.y, 55, 70, g_sprHero[g_AniFrm].hDC, 0, 0, SRCCOPY);


}






//hdc에 따라서 Text 를 그린다. // 1024크기
void TSEngine::DrawTextT(HDC hdc, int x, int y, COLORREF col, char* msg, ...)
{
	char buff[1024] = "";
	va_list vl;
	va_start(vl, msg);
	vsprintf_s(buff, msg, vl);
	va_end(vl);

	COLORREF bkcol = ::SetTextColor(hdc, col);
	int bkmode = SetBkMode(hdc, TRANSPARENT);

	RECT rc = { x, y, Screen.Width, Screen.Height };
	::DrawText(hdc, buff, (int)strlen(buff), &rc, DT_WORDBREAK);
	::SetTextColor(hdc, bkcol);
	SetBkMode(hdc, bkmode);
}

float TSEngine::GetEngineTime()
{
	static ULONGLONG oldtime = GetTickCount64();
	ULONGLONG nowtime = GetTickCount64();
	float dTime = ((nowtime - oldtime) % 1000) * 0.001f;
	oldtime = nowtime;

	//클래스에 타이머 저장.
	m_DTime = dTime;

	
	//DrawText(m_BackBuffer,50,100,RGB(255,0,255),"Dtime:%d",dTime);

	return dTime;
}

//Draw to x,y 
void TSEngine::ShowFPS(int x, int y)
{
	static int frm = 0;
	static ULONGLONG oldtime = GetTickCount64();
	static int frmcnt = 0;
	static float  fps = 0.0f;
	//static float evfps = 0;		//평균 프레임.

	++frmcnt;

	//char msg[80];  
	ULONGLONG dtime = GetTickCount64() - oldtime;
	if (dtime >= 999) // 0~999 밀리세컨드.. 1~1000이 아님
	{
		oldtime = GetTickCount64();

		//1초간 증가된 프레임 수를 구합니다..
		frm = frmcnt;	frmcnt = 0;

		//초당 프래임 수를 계산합니다.
		fps = (float)(frm * 1000) / (float)dtime;
	}

	//sprintf(msg, "fps=%.1f/%d    ", fps, (int)time); 
	//TextOut(hdc, x, y, msg, strlen(msg));
	DrawTextT(m_BackBuffer, x, y, RGB(0, 255, 0), "fps=%.1f/%03d", fps, (int)dtime);

}

/// 그리기 관련
/// 기본 도형을 그리는 함수들
/// 
void TSEngine::SetStockObject(int value)
{
	m_NewBrush = (HBRUSH)GetStockObject(value);
	m_OldBrush = (HBRUSH)SelectObject(m_BackBuffer, m_NewBrush);
}

void TSEngine::RemoveBrush()
{
	SelectObject(m_BackBuffer, m_OldBrush);
	DeleteObject(m_NewBrush);
}

void TSEngine::SetTextColor(COLORREF color)
{
	::SetTextColor(m_BackBuffer, color);
}

void TSEngine::SetBKMode(int mode)
{
	SetBkMode(m_BackBuffer, mode);
}

void TSEngine::SetROP2(int rop2)
{
	::SetROP2(m_BackBuffer, rop2);
}

void TSEngine::SetBrushColor(unsigned long dwRGBColor)
{
	m_NewBrush = CreateSolidBrush(dwRGBColor);
	m_OldBrush = (HBRUSH)SelectObject(m_BackBuffer, m_NewBrush);
}

void TSEngine::DrawRectangle(HDC hdc, int x, int y, int x1, int y1, COLORREF crBrush)
{
	HBRUSH	newBrush, oldBrush;

	// brush 속성도 바꿔준다.
	newBrush = CreateSolidBrush(crBrush);
	oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

	Rectangle(hdc, x, y, x1, y1);

	// 다 그렸으면 각 속성을 원래대로.
	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);
}

void TSEngine::DrawRectangleDebug(int left, int top, int right, int bottom, COLORREF color)
{
	// 색
	//COLORREF _brushColor = RGB(0, 255, 0);

	// 브러시
	HBRUSH _newBrush, _oldBrush;
	///_newBrush = CreateSolidBrush(_brushColor);
	_newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	_oldBrush = (HBRUSH)SelectObject(m_BackBuffer, _newBrush);

	// 펜
	HPEN _newPen, _oldPen;

	// 스타일과 두께
	int _penStyle = PS_SOLID;
	int _penWidth = 1;

	_newPen = CreatePen(_penStyle, _penWidth, color);
	_oldPen = (HPEN)SelectObject(m_BackBuffer, _newPen);

	Rectangle(m_BackBuffer, left, top, right, bottom);

	// 브러시를 원래대로 돌리고, 해제
	SelectObject(m_BackBuffer, _oldBrush);
	DeleteObject(_newBrush);

	// 펜을 원래대로 돌리고, 해제
	SelectObject(m_BackBuffer, _oldPen);
	DeleteObject(_newPen);


}

void TSEngine::DrawRectangle(int x, int y, int x1, int y1, COLORREF crBrush)
{
	HBRUSH	newBrush, oldBrush;

	// brush 속성도 바꿔준다.
	newBrush = CreateSolidBrush(crBrush);
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, newBrush);

	Rectangle(m_BackBuffer, x, y, x1, y1);

	// 다 그렸으면 각 속성을 원래대로.
	SelectObject(m_BackBuffer, oldBrush);
	DeleteObject(newBrush);
}

void TSEngine::DrawRectangle(int x, int y, int x1, int y1)
{
	Rectangle(m_BackBuffer, x, y, x1, y1);
}

void TSEngine::DrawLine(int x1, int y1, int x2, int y2)
{
	HPEN newPen, oldPen;
	newPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);

	MoveToEx(m_BackBuffer, x1, y1, NULL);
	LineTo(m_BackBuffer, x2, y2);

	SelectObject(m_BackBuffer, oldPen);
	DeleteObject(newPen);
}

void TSEngine::DrawEllipse(int x, int y)
{
	HBRUSH	oldBrush;
	HPEN	newPen, oldPen;

	int pen_style;
	int pen_width;
	pen_width = 1;
	pen_style = PS_SOLID;
	// pen 속성을 바꿔준다.
	newPen = CreatePen(pen_style, pen_width, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);
	// brush 속성도 바꿔준다.
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, GetStockObject(WHITE_BRUSH));

	Ellipse(m_BackBuffer, x - 10, y - 10, x + 10, y + 10);

	// 다 그렸으면 각 속성을 원래대로.
	DeleteObject(newPen);
	SelectObject(m_BackBuffer, oldBrush);
	SelectObject(m_BackBuffer, oldPen);
}

void TSEngine::DrawEllipse(int left, int top, int right, int bottom)
{
	HBRUSH	oldBrush;
	HPEN	newPen, oldPen;

	int pen_style;
	int pen_width;
	pen_width = 1;
	pen_style = PS_SOLID;
	// pen 속성을 바꿔준다.
	newPen = CreatePen(pen_style, pen_width, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);
	// brush 속성도 바꿔준다.
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, GetStockObject(WHITE_BRUSH));

	Ellipse(m_BackBuffer, left, top, right, bottom);

	// 다 그렸으면 각 속성을 원래대로.
	DeleteObject(newPen);
	SelectObject(m_BackBuffer, oldBrush);
	SelectObject(m_BackBuffer, oldPen);
}

void TSEngine::DrawSelectRectangle(int x1, int y1, int x2, int y2)
{
	HBRUSH	oldBrush;
	HPEN	newPen, oldPen;

	int pen_style;
	int pen_width;
	pen_width = 1;
	pen_style = PS_SOLID;
	// pen 속성을 바꿔준다.
	newPen = CreatePen(pen_style, pen_width, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);
	// brush 속성도 바꿔준다.
//	newBrush = CreateSolidBrush(crBrush);
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, GetStockObject(NULL_BRUSH));
	Rectangle(m_BackBuffer, x1, y1, x2, y2);

	// 다 그렸으면 각 속성을 원래대로.
	DeleteObject(newPen);
	SelectObject(m_BackBuffer, oldBrush);
	SelectObject(m_BackBuffer, oldPen);
}

void TSEngine::DrawSelectedCircle(int x, int y, int size)
{
	HBRUSH	oldBrush;
	HPEN	newPen, oldPen;

	int pen_style;
	int pen_width;
	pen_width = 1;
	pen_style = PS_SOLID;

	// pen 속성을 바꿔준다.
	newPen = CreatePen(pen_style, pen_width, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);

	// brush 속성도 바꿔준다.
//	newBrush = CreateSolidBrush(crBrush);
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, GetStockObject(NULL_BRUSH));
	Ellipse(m_BackBuffer, x - size, y - size, x + size, y + size);

	// 다 그렸으면 각 속성을 원래대로.
	DeleteObject(newPen);
	SelectObject(m_BackBuffer, oldBrush);
	SelectObject(m_BackBuffer, oldPen);
}
