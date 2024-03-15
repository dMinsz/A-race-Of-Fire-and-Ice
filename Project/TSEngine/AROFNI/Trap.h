#pragma once
class Trap : public GameObject
{
	// 기본적인 변수 및 메소드들은 상속받습니다.

public:
	virtual void Init(float x, float y, TSprite* sprite);
	virtual void Update();

	virtual void Draw();
	virtual void Release();

	virtual void AutoDown(int downSize, float dtime);

	virtual int CheckOutOfBoundary(int locationY);

	virtual AABB GetAABB() const { return GameObject::m_AABB; };
	virtual RECT GetWorldAABB() const { return GameObject::GetWorldAABB(); };

	//추가메소드

};

