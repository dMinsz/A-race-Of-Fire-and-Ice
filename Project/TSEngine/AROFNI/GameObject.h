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


	//�浹ü ����
	AABB m_AABB;
	bool m_IsCollided;
	bool m_IsCollidedX;
	bool m_IsCollidedY;


public:
	virtual void Init(float x, float y, TSprite* sprite);
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	//���� ���ӳ��� ������Ʈ���� ��� ��� �������ϴ�. ��ġ �߷�ó��?
	// update �� �̿��Ҽ��������� ����Ÿ�ӱ������� ��ӳ��������̶� ���� ����ϴ�.
	virtual void AutoDown(int downSize, float dtime);

	// ���� ������Ʈ�� ��ġ�� location �Ʒ��� ���������� üũ�մϴ�.
	// -999 ���� ����ȳ����°�
	virtual int CheckOutOfBoundary(float locationY);


	//�浹ü
	virtual AABB GetAABB() const { return m_AABB; }
	virtual RECT GetWorldAABB() const;

	void IsCollided(bool val) { m_IsCollided = val; }
	void IsCollidedX(bool val) { m_IsCollidedX = val; }
	void IsCollidedY(bool val) { m_IsCollidedY = val; }

	void DrawBoundingVolume();
};

