#pragma once
#include "AniInfo.h"

class AniInfo; //���漱��

//��������Ʈ �ϳ��� ��� Ŭ����
class TSprite
{
public:
	// ��Ʈ�� �ڵ�
	HBITMAP m_hBitmap;
	// ��������Ʈ�� �ε� �� DC
	HDC m_MemDC;

	BITMAPINFO  hInfo;

	// ��������Ʈ�� �ΰ�����
	int m_Width;	// ��
	int m_Height;	// ����
	COLORREF KeyColor;	// Ű�÷�

	// ����
	int m_CenterX;
	int m_CenterY;

	AniInfo m_AniInfo;

	//���� ��������Ʈ.��
	// int sprChar[FRM_MAX_];	//���ΰ� ��������Ʈ 7�� ����
	// TSprite  g_sprMap;				//�� ��������Ʈ
	// TSprite  g_sprUI;

	// ���� ���� �浹ü 
	//
	//RECT Collision;	
	//RECT Collision2;	


};