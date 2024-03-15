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

	//��ũ�� ũ�� �ʱ�ȭ ����� �� ������ũ�⵵
	Screen.Width = screenWidth;
	Screen.Height = screenHeight;


	m_hWnd = hWnd;

	// ȭ�鿡 ���� DC
	m_hMainDC = GetDC(hWnd);


	// �����
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
	// ȭ���� �����.
	Rectangle(m_BackBuffer, 0, 0, Screen.Width, Screen.Height);

	// ĳ���͸� �׸���.
	//int _x = rand() % 100;
	//int _y = rand() % 100;

	/*Ellipse(m_BackBuffer, m_PosX, m_PosY, m_PosX + 100, m_PosY + 100);
	Ellipse(m_BackBuffer, m_PosX, m_PosY, m_PosX + 200, m_PosY + 200);
	Ellipse(m_BackBuffer, m_PosX, m_PosY, m_PosX + 300, m_PosY + 300);*/


	/// ����۸� ȭ�鿡 �׸���. (���� ���۸�)
	BitBlt(m_hMainDC, 0, 0, Screen.Width, Screen.Height, m_BackBuffer, 0, 0, SRCCOPY);

}

//?
void TSEngine::BeginRender()
{

	// ȭ���� �����.
	Rectangle(m_BackBuffer, 0, 0, Screen.Width, Screen.Height);

}

void TSEngine::EndRender()
{
	/// ����۸� ȭ�鿡 �׸���. (���� ���۸�)
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

	//������
	ReleaseDC(m_hWnd, hdc);


	//��Ʈ�� ���� �ε�..
	ZeroMemory(&tmpSprite.hInfo, sizeof(BITMAPINFO));
	DIBSECTION ds;
	GetObject(tmpSprite.m_hBitmap, sizeof(ds), &ds);
	tmpSprite.hInfo.bmiHeader = ds.dsBmih;		//�ε���, ��Ʈ�� ���� ��ü ȹ��.	
	tmpSprite.m_Width = ds.dsBmih.biWidth;			//���� ���Ǵ� ũ�⸦ ������ ����.
	tmpSprite.m_Height = ds.dsBmih.biHeight;

	// ��������Ʈ ����
	tmpSprite.m_CenterX = tmpSprite.m_Width / 2;
	tmpSprite.m_CenterY = tmpSprite.m_Height / 2;

	//�浹ü


	//test / prototype ��
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
		//LR_DEFAULTSIZE | LR_LOADFROMFILE	 //�⺻ũ��+�ܺ����Ϸε� DDB �� �ε��ϰ� ��
		LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION
	);

	//�޸� DC �� ��Ʈ�� ���̱�..
	tmpSprite.m_MemDC = CreateCompatibleDC(hdc);
	SelectObject(tmpSprite.m_MemDC, tmpSprite.m_hBitmap);
	ReleaseDC(m_hWnd, hdc);

	//��Ʈ�� ���� �ε�..
	ZeroMemory(&tmpSprite.hInfo, sizeof(BITMAPINFO));
	DIBSECTION ds;
	GetObject(tmpSprite.m_hBitmap, sizeof(ds), &ds);
	tmpSprite.hInfo.bmiHeader = ds.dsBmih;		//�ε���, ��Ʈ�� ���� ��ü ȹ��.	
	tmpSprite.m_Width = ds.dsBmih.biWidth;			//���� ���Ǵ� ũ�⸦ ������ ����.
	tmpSprite.m_Height = ds.dsBmih.biHeight;

	// ��������Ʈ ����
	tmpSprite.m_CenterX = tmpSprite.m_Width / 2;
	tmpSprite.m_CenterY = tmpSprite.m_Height / 2;

	//�÷�Ű ����Ÿ��
	tmpSprite.KeyColor = RGB(255, 0, 255);


	//�ִϸ��̼ǰ��� �����ؾ���


	//�浹ü ���õ����� �����.




	//�ܺε����Ϳ� ����.
	* sprite = tmpSprite;



	//������ �ǹ̷�, true ����..
	return TRUE;
}

int TSEngine::LoadSpriteSheet(TSprite* sprite, const char* filePath, AniInfo aniInfo)
{
	if (sprite == NULL) return FALSE;

	TSprite tmpSprite;
	HDC hdc = GetDC(m_hWnd);

	tmpSprite.m_hBitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0,
		//LR_DEFAULTSIZE | LR_LOADFROMFILE	 //�⺻ũ��+�ܺ����Ϸε� DDB �� �ε��ϰ� ��
		LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION
	);

	//�޸� DC �� ��Ʈ�� ���̱�..
	tmpSprite.m_MemDC = CreateCompatibleDC(hdc);
	SelectObject(tmpSprite.m_MemDC, tmpSprite.m_hBitmap);
	ReleaseDC(m_hWnd, hdc);

	//��Ʈ�� ���� �ε�..
	ZeroMemory(&tmpSprite.hInfo, sizeof(BITMAPINFO));
	DIBSECTION ds;
	GetObject(tmpSprite.m_hBitmap, sizeof(ds), &ds);
	tmpSprite.hInfo.bmiHeader = ds.dsBmih;		//�ε���, ��Ʈ�� ���� ��ü ȹ��.	
	tmpSprite.m_Width = ds.dsBmih.biWidth;			//���� ���Ǵ� ũ�⸦ ������ ����.
	tmpSprite.m_Height = ds.dsBmih.biHeight;

	// ��������Ʈ ����
	//tmpSprite.m_CenterX = tmpSprite.m_Width / 2;
	//tmpSprite.m_CenterY = tmpSprite.m_Height / 2;

	//�÷�Ű ����Ÿ��
	tmpSprite.KeyColor = RGB(255, 0, 255);


	//�ִϸ��̼ǰ��� �����ؾ���



	tmpSprite.m_AniInfo = aniInfo;




	//�浹ü ���õ����� �����.




	//�ܺε����Ϳ� ����.
	* sprite = tmpSprite;



	//������ �ǹ̷�, true ����..
	return TRUE;
}


void TSEngine::SpriteRelease(TSprite* sprite)
{
	DeleteObject(sprite->m_hBitmap);  sprite->m_hBitmap = NULL;
	DeleteDC(sprite->m_MemDC);	sprite->m_MemDC = NULL;

}

void TSEngine::DrawSpriteOrigin(HDC hdc, int x, int y, TSprite* sprite, float scaleX, float scaleY)
{
	//������ ó��..
	int width = (int)(sprite->m_Width * scaleX);
	int height = (int)(sprite->m_Height * scaleY);

	//����� ���� �׸���.
	::BitBlt(hdc, x, y, width, height, sprite->m_MemDC, 0, 0, SRCCOPY);
}

void TSEngine::DrawSprite(HDC hdc, int x, int y, TSprite* sprite, float scaleX, float scaleY)
{
	//������ ó��..
	int width = (int)(sprite->m_Width * scaleX);
	int height = (int)(sprite->m_Height * scaleY);

	//����� ó��.

	if (sprite->KeyColor != NULL)
	{
		::TransparentBlt(hdc, x, y, width, height,
			sprite->m_MemDC, 0, 0, sprite->m_Width, sprite->m_Height, sprite->KeyColor);
	}
	else
	{
		//����� ���� �׸���.
		::BitBlt(hdc, x, y, width, height, sprite->m_MemDC, 0, 0, SRCCOPY);
	}


}

void TSEngine::RotateDrawSprite(HDC hdc, int x, int y, TSprite* sprite, float angle, float scaleX, float scaleY)
{

	//������ ó��..
	int width = (int)(sprite->m_Width * scaleX);
	int height = (int)(sprite->m_Height * scaleY);

	// ���̰� = 3.141592f 
	// 1 ���� �� =  0.017453f // 1���� ���ϴ� ���� => PI /180.0f
	// 1���� * angle => rad�� 

	float rad = 0.017453f * angle;
	float cs = cos(rad);
	float si = sin(rad);

	int& ow = width;
	int& oh = height;
	int w = (int)((float)width * 1.4f);
	int h = (int)((float)height * 1.4f);

	//ȸ���� ��Ʈ�� ����� ���ҽ� ����.	
	HDC destDC = CreateCompatibleDC(hdc);                             // ȸ���� ��Ʈ���� ��¹��� DC           
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, w, h);			// ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� �ڵ�      
	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);   // ȸ���� ��Ʈ���� ��¹��� DC��, ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� ����     

	//����� ��Ʈ��, Ŭ����
	//HBRUSH hbrBack = CreateSolidBrush(RGB(255, 255, 255));         // ȸ������ ����, ���鿵���� ĥ�� �귯���ڵ� ����    (����׿�)
	////HBRUSH hbrBack      = CreateSolidBrush( transColor );           // ȸ������ ����, ���鿵���� ĥ�� �귯���ڵ� ����    
	//HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);      // �귯���ڵ� ����    
	//PatBlt(destDC, 0, 0, w, h, PATCOPY);								// ���õ� �귯�÷�, ȸ���� ��Ʈ���� ��¹��� DC��, �̸� ������ ä�� ����    
	//DeleteObject(SelectObject(destDC, hbrOld));                     // �귯�� ����     


	// ��Ʈ�� ȸ�� ó��.
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



	// * ȸ���� ��Ʈ�� ��� �Ϸ�....* ��
	HDC hTempMemDC = CreateCompatibleDC(hdc);
	SelectObject(hTempMemDC, hbmResult);

	//(�����) ȭ�鿡 ���.��

	//����� ó��.
	::TransparentBlt(
		hdc,
		x, y,
		w, h,					//ȸ���� ��Ʈ���� ����/���� ũ��.(������ ó�� ����)
		//width, height,		//���� ��Ʈ���� ����/���� ũ�� (������ ó�� ����)
		destDC, 0, 0, w, h,  //ȸ���� ��Ʈ��..��
		//pSpr->hSurface, 0, 0,  pSpr->Width, pSpr->Height,  //<-- �ʿ��ϴٸ�, ���� �κ� �߶� �׸��⵵ �����ϰ�����.
		sprite->KeyColor);
	BitBlt(hdc, x, y, w, h, destDC, 0, 0, SRCCOPY);
	//BitBlt( hdc, x-w/2, y-h/2, w, h, hTempMemDC, 0, 0, SRCCOPY);
//BitBlt(hdc, x, y, w, h, hTempMemDC, 0, 0, SRCCOPY);
	::TransparentBlt(
		hdc, x, y, w, h,		//ȸ���� ��Ʈ���� ����/���� ũ��.(������ ó�� ����)
		hTempMemDC, 0, 0, w, h,		//ȸ���� ��Ʈ��..��
		sprite->KeyColor);


	// �׷��� ��� ����.    
	//SetGraphicsMode(destDC, GM_COMPATIBLE);    

	//���ҽ� ����.
	DeleteDC(destDC);
	DeleteDC(hTempMemDC);
	DeleteObject(hbmResult);
}

void TSEngine::SpriteAnimation(TSprite* sprite, float dtime)
{
	sprite->m_AniInfo.m_AniTime += dtime;

	if (sprite->m_AniInfo.m_AniTime > FPS(sprite->m_AniInfo.m_AniFPS))		//1�ʴ� 7�������� �ӵ� �����..
	{
		sprite->m_AniInfo.m_AniTime = 0.0f;

		sprite->m_AniInfo.m_AniFrm += 1;

		if (sprite->m_AniInfo.m_AniFrm >= sprite->m_AniInfo.m_FrmMax) sprite->m_AniInfo.m_AniFrm = 0;	//������ ����.
	}
}

void TSEngine::DrawAnimation(HDC hdc, int x, int y, TSprite* sprite, float dtime)
{
	SpriteAnimation(sprite, dtime); //������,�ð� ����

	int sprX = sprite->m_AniInfo.m_CutSizeWidth * sprite->m_AniInfo.m_AniFrm;
	int sprY = 0;
	int sprWidth = sprite->m_AniInfo.m_CutSizeWidth;
	int sprHeight = sprite->m_AniInfo.m_CutSizeHeight;

	//BitBlt(hdc, x, y, sprWidth, sprHeight, sprite->m_MemDC, sprX, sprY, SRCCOPY);

	TransparentBlt(hdc, x, y, sprWidth, sprHeight, sprite->m_MemDC, sprX, sprY, sprWidth, sprHeight, sprite->KeyColor);

	//BitBlt(hdc,sprite->m_AniInfo.m_CutSizeWidth * spri , g_HeroPos.y, 55, 70, g_sprHero[g_AniFrm].hDC, 0, 0, SRCCOPY);


}






//hdc�� ���� Text �� �׸���. // 1024ũ��
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

	//Ŭ������ Ÿ�̸� ����.
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
	//static float evfps = 0;		//��� ������.

	++frmcnt;

	//char msg[80];  
	ULONGLONG dtime = GetTickCount64() - oldtime;
	if (dtime >= 999) // 0~999 �и�������.. 1~1000�� �ƴ�
	{
		oldtime = GetTickCount64();

		//1�ʰ� ������ ������ ���� ���մϴ�..
		frm = frmcnt;	frmcnt = 0;

		//�ʴ� ������ ���� ����մϴ�.
		fps = (float)(frm * 1000) / (float)dtime;
	}

	//sprintf(msg, "fps=%.1f/%d    ", fps, (int)time); 
	//TextOut(hdc, x, y, msg, strlen(msg));
	DrawTextT(m_BackBuffer, x, y, RGB(0, 255, 0), "fps=%.1f/%03d", fps, (int)dtime);

}

/// �׸��� ����
/// �⺻ ������ �׸��� �Լ���
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

	// brush �Ӽ��� �ٲ��ش�.
	newBrush = CreateSolidBrush(crBrush);
	oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

	Rectangle(hdc, x, y, x1, y1);

	// �� �׷����� �� �Ӽ��� �������.
	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);
}

void TSEngine::DrawRectangleDebug(int left, int top, int right, int bottom, COLORREF color)
{
	// ��
	//COLORREF _brushColor = RGB(0, 255, 0);

	// �귯��
	HBRUSH _newBrush, _oldBrush;
	///_newBrush = CreateSolidBrush(_brushColor);
	_newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	_oldBrush = (HBRUSH)SelectObject(m_BackBuffer, _newBrush);

	// ��
	HPEN _newPen, _oldPen;

	// ��Ÿ�ϰ� �β�
	int _penStyle = PS_SOLID;
	int _penWidth = 1;

	_newPen = CreatePen(_penStyle, _penWidth, color);
	_oldPen = (HPEN)SelectObject(m_BackBuffer, _newPen);

	Rectangle(m_BackBuffer, left, top, right, bottom);

	// �귯�ø� ������� ������, ����
	SelectObject(m_BackBuffer, _oldBrush);
	DeleteObject(_newBrush);

	// ���� ������� ������, ����
	SelectObject(m_BackBuffer, _oldPen);
	DeleteObject(_newPen);


}

void TSEngine::DrawRectangle(int x, int y, int x1, int y1, COLORREF crBrush)
{
	HBRUSH	newBrush, oldBrush;

	// brush �Ӽ��� �ٲ��ش�.
	newBrush = CreateSolidBrush(crBrush);
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, newBrush);

	Rectangle(m_BackBuffer, x, y, x1, y1);

	// �� �׷����� �� �Ӽ��� �������.
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
	// pen �Ӽ��� �ٲ��ش�.
	newPen = CreatePen(pen_style, pen_width, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);
	// brush �Ӽ��� �ٲ��ش�.
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, GetStockObject(WHITE_BRUSH));

	Ellipse(m_BackBuffer, x - 10, y - 10, x + 10, y + 10);

	// �� �׷����� �� �Ӽ��� �������.
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
	// pen �Ӽ��� �ٲ��ش�.
	newPen = CreatePen(pen_style, pen_width, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);
	// brush �Ӽ��� �ٲ��ش�.
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, GetStockObject(WHITE_BRUSH));

	Ellipse(m_BackBuffer, left, top, right, bottom);

	// �� �׷����� �� �Ӽ��� �������.
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
	// pen �Ӽ��� �ٲ��ش�.
	newPen = CreatePen(pen_style, pen_width, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);
	// brush �Ӽ��� �ٲ��ش�.
//	newBrush = CreateSolidBrush(crBrush);
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, GetStockObject(NULL_BRUSH));
	Rectangle(m_BackBuffer, x1, y1, x2, y2);

	// �� �׷����� �� �Ӽ��� �������.
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

	// pen �Ӽ��� �ٲ��ش�.
	newPen = CreatePen(pen_style, pen_width, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(m_BackBuffer, newPen);

	// brush �Ӽ��� �ٲ��ش�.
//	newBrush = CreateSolidBrush(crBrush);
	oldBrush = (HBRUSH)SelectObject(m_BackBuffer, GetStockObject(NULL_BRUSH));
	Ellipse(m_BackBuffer, x - size, y - size, x + size, y + size);

	// �� �׷����� �� �Ӽ��� �������.
	DeleteObject(newPen);
	SelectObject(m_BackBuffer, oldBrush);
	SelectObject(m_BackBuffer, oldPen);
}
