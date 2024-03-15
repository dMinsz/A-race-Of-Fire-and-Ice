#pragma once
class Item : public GameObject
{
public:
	virtual void Init(float x, float y, TSprite* sprite);
	virtual void Update();

	virtual void Draw();
	virtual void Release();

	virtual void AutoDown(int downSize,float dtime);

	virtual int CheckOutOfBoundary(int locationY);

	//충돌체
	virtual AABB GetAABB() const { return GameObject::m_AABB; };
	virtual RECT GetWorldAABB() const { return GameObject::GetWorldAABB(); };

	//추가메소드
};

