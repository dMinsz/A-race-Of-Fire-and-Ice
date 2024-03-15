#pragma once
class PlatForm : public GameObject
{

	//기본적인 메소드들은 상속받습니다.

public:
	virtual void Init(float x, float y, TSprite* sprite);
	virtual void Update();

	virtual void Draw();
	virtual void Release();

	virtual void AutoDown(int downSize, float dtime);

	virtual int CheckOutOfBoundary(int locationY);

	//추가메소드
	POSITION GetCurrentPos() { return m_Pos; };

};
