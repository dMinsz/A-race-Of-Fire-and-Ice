#pragma once
//made by SungMing and SeongYOON!
//�⺻���� ���� ������

#include "Framework.h"
#include <stdlib.h>
#include "AniInfo.h"
#include "TSprite.h"

// 1/1000 �ʷ� ����ȭ �մϴ�.
//���Ŀ� ����Ÿ���� �߿������� �ٸ� �Լ��� ��ü�ؾ���
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


	// ȭ�� ������
	SCREEN Screen;

	/// GDI�� �ʿ��� ������
	HWND m_hWnd;
	HDC m_hMainDC;		// Client Area

	HDC m_BackBuffer;
	HBITMAP m_BackBufferBitmap;

	// �ӽ� ��ġ��
	int m_PosX;
	int m_PosY;

	// ���� �ð�
	float m_DTime;

	// �귯��, �� �� ������Ʈ �ּ�ȭ ���ؼ����
	HBRUSH m_NewBrush;
	HBRUSH m_OldBrush;
	HPEN m_NewPen;
	HPEN m_OldPen;

	// ��Ʈ ���� ����
	HFONT m_Font, m_Oldfont;

public:
	// �ӽ�
	HDC GetMainDC();
	HDC GetBackBufferDC();


public:
	// ū����

	void Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight);

	void UpdateAll();
	void RenderAll();

	void BeginRender();
	void EndRender();


public:
	// ���� Ÿ�̸� 
	float GetEngineTime();

	//FPS �����ֱ�
	void ShowFPS(int x, int y);


public:
	/// Sprite ����
	
	// Test / prototype �� 

	//�� ��Ʈ�ʰ� �簢�� ����
	int MakeLectangleSprite(TSprite* sprite, int LSizeWidth, int LSizeHeight);
	//�޸�dc�� �簢�� �׷�����
	void DrawRectangle(HDC hdc, int x, int y, int x1, int y1, COLORREF crBrush);

	/// test / prototype ��

	//�浹ü ���� ������
	void DrawRectangleDebug(int left, int top, int right, int bottom, COLORREF color);


	// ��������Ʈ �ε� no animation
	int LoadSprite(TSprite* sprite, const char* filePath);

	//��������Ʈ ��Ʈ �ε� / �ִϸ��̼ǿ�
	int LoadSpriteSheet(TSprite* sprite, const char* filePath, AniInfo aniInfo);

	//sprite handle,memdc ����
	void SpriteRelease(TSprite* sprite);

	// ��������Ʈ�� ���� �״�� ���
	/// <summary>
	/// ��������Ʈ�� ���� �״�� ���
	/// </summary>
	/// <param name="hdc">����� ��ǥdc �ڵ�</param>
	/// <param name="x">��� ��ǥ x</param>
	/// <param name="y">��� ��ǥ y</param>
	/// <param name="sprite">����� ��������Ʈ ������</param>
	/// <param name="scaleX">��½� �������� �����ϰ� ( 100% = 1.0f )</param>
	/// <param name="scaleY">��½� �������� �����ϰ� ( 100% = 1.0f )</param>
	void DrawSpriteOrigin(HDC hdc, int x, int y, TSprite* sprite, float scaleX = 1.0f, float scaleY = 1.0f);

	// ��������Ʈ�� �÷�Ű�� ���� ����� ���
	/// <summary>
	/// ��������Ʈ�� ������ ���� ���
	/// </summary>
	/// <param name="hdc">����� ��ǥdc �ڵ�</param>
	/// <param name="x">��� ��ǥ x</param>
	/// <param name="y">��� ��ǥ y</param>
	/// <param name="sprite">����� ��������Ʈ ������</param>
	/// <param name="scaleX">��½� �������� �����ϰ� ( 100% = 1.0f )</param>
	/// <param name="scaleY">��½� �������� �����ϰ� ( 100% = 1.0f )</param>
	void DrawSprite(HDC hdc, int x, int y, TSprite* sprite, float scaleX = 1.0f, float scaleY = 1.0f);

	//��������Ʈ ȸ�� ����ϱ�
	/// <summary>
	/// ��������Ʈ ȸ�� ����ϱ� (�������� ����)
	/// </summary>
	/// <param name="hdc">����� ��ǥ �ڵ�</param>
	/// <param name="x">����� x</param>
	/// <param name="y">����� y</param>
	/// <param name="sprite">����� ��������Ʈ ������</param>
	/// <param name="angle">ȸ���� (����)</param>
	/// <param name="scaleX">��½� �������� �����ϰ� ( 100% = 1.0f )</param>
	/// <param name="scaleY">��½� �������� �����ϰ�</param>
	void RotateDrawSprite(HDC hdc, int x, int y, TSprite* sprite, float angle, float scaleX = 1.0f, float scaleY = 1.0f);


	//�߰��� ���� ��������Ʈ�� ���������� �׸����ϴ� �޼ҵ尡 �ʿ��ұ�?


	//Animation ����
	void SpriteAnimation(TSprite* sprite , float dtime);

	void DrawAnimation(HDC hdc, int x, int y, TSprite* sprite, float dtime);


public:
	/// �׸��� �Լ���

	// ���ڿ� ��� �Լ�
	void DrawTextT(HDC hdc, int x, int y, COLORREF col, char* msg, ...);


	// �⺻ ������ �׸��� �Լ��� // ����ȯ�������� ������ ���
	void SetStockObject(int value);
	void RemoveBrush();
	void SetTextColor(COLORREF color);
	void SetBKMode(int mode);
	void SetROP2(int rop2);

	// ������ �׸��� �귯�� ����
	void SetBrushColor(unsigned long dwRGBColor);

	// ������ ��ǥ�� �簢���� ����Ѵ�.

	void DrawRectangle(int x, int y, int x1, int y1, COLORREF crBrush);
	void DrawRectangle(int x, int y, int x1, int y1);
	void DrawLine(int x1, int y1, int x2, int y2);

	//10 , 10 ¥�� ���׶�� �׸���
	void DrawEllipse(int x, int y);

	void DrawEllipse(int left, int top, int right, int bottom);

	//�귯���� �� �⺻���õǾ�����
	void DrawSelectRectangle(int x1, int y1, int x2, int y2);
	void DrawSelectedCircle(int x, int y, int size);

};