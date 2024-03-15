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

	int m_Direction; // 줄어드는 방향 0은 왼쪽에서 오른쪽으로
					// 1은 오른쪽에서 왼쪽으로
public:

	void Init(int x, int y, int* gagehp, TSprite* sprite, int dir);
	void Draw();
	void Update(float dtime);
	void Release();


};

