#pragma once
struct POSITION
{
	float x; 
	float y;
};


class GameObject
{
public:
	POSITION m_Pos;
	TSprite* m_Sprite;


	//충돌체 관련
	AABB m_AABB;
	bool m_IsCollided;
	bool m_IsCollidedX;
	bool m_IsCollidedY;


public:
	virtual void Init(float x, float y, TSprite* sprite);
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	//현재 게임내의 오브젝트들은 모두 계속 내려갑니다. 마치 중력처럼?
	// update 를 이용할수도있지만 엔진타임기준으로 계속내릴예정이라 따로 만듭니다.
	virtual void AutoDown(int downSize, float dtime);

	// 현재 오브젝트의 위치가 location 아래로 내려갔는지 체크합니다.
	// -999 값은 절대안나오는값
	virtual int CheckOutOfBoundary(float locationY);


	//충돌체
	virtual AABB GetAABB() const { return m_AABB; }
	virtual RECT GetWorldAABB() const;

	void IsCollided(bool val) { m_IsCollided = val; }
	void IsCollidedX(bool val) { m_IsCollidedX = val; }
	void IsCollidedY(bool val) { m_IsCollidedY = val; }

	void DrawBoundingVolume();
};

