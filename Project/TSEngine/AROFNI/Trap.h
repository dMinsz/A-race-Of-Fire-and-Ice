#pragma once
class Trap : public GameObject
{
	// �⺻���� ���� �� �޼ҵ���� ��ӹ޽��ϴ�.

public:
	virtual void Init(float x, float y, TSprite* sprite);
	virtual void Update();

	virtual void Draw();
	virtual void Release();

	virtual void AutoDown(int downSize, float dtime);

	virtual int CheckOutOfBoundary(int locationY);

	virtual AABB GetAABB() const { return GameObject::m_AABB; };
	virtual RECT GetWorldAABB() const { return GameObject::GetWorldAABB(); };

	//�߰��޼ҵ�

};

