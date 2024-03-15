#pragma once
#include "AniInfo.h"

class AniInfo; //전방선언

//스프라이트 하나를 담는 클래스
class TSprite
{
public:
	// 비트맵 핸들
	HBITMAP m_hBitmap;
	// 스프라이트가 로드 될 DC
	HDC m_MemDC;

	BITMAPINFO  hInfo;

	// 스프라이트의 부가정보
	int m_Width;	// 폭
	int m_Height;	// 높이
	COLORREF KeyColor;	// 키컬러

	// 중점
	int m_CenterX;
	int m_CenterY;

	AniInfo m_AniInfo;

	//장면용 스프라이트.★
	// int sprChar[FRM_MAX_];	//주인공 스프라이트 7장 설정
	// TSprite  g_sprMap;				//멥 스프라이트
	// TSprite  g_sprUI;

	// 게임 관련 충돌체 
	//
	//RECT Collision;	
	//RECT Collision2;	


};