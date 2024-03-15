#pragma once
//made by SungMing and SeongYOON!
//기본예제 참고 많이함

#include "Framework.h"
#include <stdlib.h>
#include "AniInfo.h"
#include "TSprite.h"

// 1/1000 초로 동기화 합니다.
//이후에 엔진타임이 중요해지면 다른 함수로 교체해야함
#define  FPS(v)   (1.0f/(float)v)   //( 1000/(float)(v) * 0.001f)


struct SCREEN
{
	int Width;
	int Height;

};


class TSEngine
{
public:
	~TSEngine();

	static TSEngine* GetEngine();
private:
	TSEngine();

	static TSEngine* m_Instance;


	// 화면 정보용
	SCREEN Screen;

	/// GDI에 필요한 변수들
	HWND m_hWnd;
	HDC m_hMainDC;		// Client Area

	HDC m_BackBuffer;
	HBITMAP m_BackBufferBitmap;

	// 임시 위치값
	int m_PosX;
	int m_PosY;

	// 엔진 시간
	float m_DTime;

	// 브러시, 펜 등 오브젝트 최소화 위해서사용
	HBRUSH m_NewBrush;
	HBRUSH m_OldBrush;
	HPEN m_NewPen;
	HPEN m_OldPen;

	// 폰트 지정 관련
	HFONT m_Font, m_Oldfont;

public:
	// 임시
	HDC GetMainDC();
	HDC GetBackBufferDC();


public:
	// 큰단위

	void Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight);

	void UpdateAll();
	void RenderAll();

	void BeginRender();
	void EndRender();


public:
	// 엔진 타이머 
	float GetEngineTime();

	//FPS 보여주기
	void ShowFPS(int x, int y);


public:
	/// Sprite 관련
	
	// Test / prototype 용 

	//빈 비트맵과 사각형 생성
	int MakeLectangleSprite(TSprite* sprite, int LSizeWidth, int LSizeHeight);
	//메모리dc에 사각형 그려놓기
	void DrawRectangle(HDC hdc, int x, int y, int x1, int y1, COLORREF crBrush);

	/// test / prototype 용

	//충돌체 관련 디버깅용
	void DrawRectangleDebug(int left, int top, int right, int bottom, COLORREF color);


	// 스프라이트 로드 no animation
	int LoadSprite(TSprite* sprite, const char* filePath);

	//스프라이트 시트 로드 / 애니메이션용
	int LoadSpriteSheet(TSprite* sprite, const char* filePath, AniInfo aniInfo);

	//sprite handle,memdc 제거
	void SpriteRelease(TSprite* sprite);

	// 스프라이트를 원본 그대로 출력
	/// <summary>
	/// 스프라이트를 원본 그대로 출력
	/// </summary>
	/// <param name="hdc">출력할 목표dc 핸들</param>
	/// <param name="x">출력 좌표 x</param>
	/// <param name="y">출력 좌표 y</param>
	/// <param name="sprite">출력할 스프라이트 포인터</param>
	/// <param name="scaleX">출력시 원본기준 스케일값 ( 100% = 1.0f )</param>
	/// <param name="scaleY">출력시 원본기준 스케일값 ( 100% = 1.0f )</param>
	void DrawSpriteOrigin(HDC hdc, int x, int y, TSprite* sprite, float scaleX = 1.0f, float scaleY = 1.0f);

	// 스프라이트를 컬러키로 배경색 지우고 출력
	/// <summary>
	/// 스프라이트를 배경색을 뺀후 출력
	/// </summary>
	/// <param name="hdc">출력할 목표dc 핸들</param>
	/// <param name="x">출력 좌표 x</param>
	/// <param name="y">출력 좌표 y</param>
	/// <param name="sprite">출력할 스프라이트 포인터</param>
	/// <param name="scaleX">출력시 원본기준 스케일값 ( 100% = 1.0f )</param>
	/// <param name="scaleY">출력시 원본기준 스케일값 ( 100% = 1.0f )</param>
	void DrawSprite(HDC hdc, int x, int y, TSprite* sprite, float scaleX = 1.0f, float scaleY = 1.0f);

	//스프라이트 회전 출력하기
	/// <summary>
	/// 스프라이트 회전 출력하기 (배경색빼기 포함)
	/// </summary>
	/// <param name="hdc">출력할 목표 핸들</param>
	/// <param name="x">출력할 x</param>
	/// <param name="y">출력할 y</param>
	/// <param name="sprite">출력할 스프라이트 포인터</param>
	/// <param name="angle">회전량 (각도)</param>
	/// <param name="scaleX">출력시 원본기준 스케일값 ( 100% = 1.0f )</param>
	/// <param name="scaleY">출력시 원본기준 스케일값</param>
	void RotateDrawSprite(HDC hdc, int x, int y, TSprite* sprite, float angle, float scaleX = 1.0f, float scaleY = 1.0f);


	//추가로 원본 스프라이트의 일정영역만 그리게하는 메소드가 필요할까?


	//Animation 관련
	void SpriteAnimation(TSprite* sprite , float dtime);

	void DrawAnimation(HDC hdc, int x, int y, TSprite* sprite, float dtime);


public:
	/// 그리기 함수들

	// 문자열 출력 함수
	void DrawTextT(HDC hdc, int x, int y, COLORREF col, char* msg, ...);


	// 기본 도형을 그리는 함수들 // 김주환교수님의 예제들 사용
	void SetStockObject(int value);
	void RemoveBrush();
	void SetTextColor(COLORREF color);
	void SetBKMode(int mode);
	void SetROP2(int rop2);

	// 도형을 그리는 브러시 관련
	void SetBrushColor(unsigned long dwRGBColor);

	// 지정된 좌표에 사각형을 출력한다.

	void DrawRectangle(int x, int y, int x1, int y1, COLORREF crBrush);
	void DrawRectangle(int x, int y, int x1, int y1);
	void DrawLine(int x1, int y1, int x2, int y2);

	//10 , 10 짜리 동그라미 그리기
	void DrawEllipse(int x, int y);

	void DrawEllipse(int left, int top, int right, int bottom);

	//브러쉬랑 펜 기본세팅되어있음
	void DrawSelectRectangle(int x1, int y1, int x2, int y2);
	void DrawSelectedCircle(int x, int y, int size);

};