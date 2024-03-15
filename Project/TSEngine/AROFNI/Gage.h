#pragma once

struct POSITION;
struct TSprite;


class Gage
{

public:
	POSITION m_Pos;
	TSprite* m_Sprite;
	int* m_hp;

	int m_Offsetsize;
	int m_Offset;

	float m_time;

	int m_Direction; // �پ��� ���� 0�� ���ʿ��� ����������
					// 1�� �����ʿ��� ��������
public:

	void Init(int x, int y, int* gagehp, TSprite* sprite, int dir);
	void Draw();
	void Update(float dtime);
	void Release();


};

