#pragma once
class PlatForm : public GameObject
{

	//�⺻���� �޼ҵ���� ��ӹ޽��ϴ�.

public:
	virtual void Init(float x, float y, TSprite* sprite);
	virtual void Update();

	virtual void Draw();
	virtual void Release();

	virtual void AutoDown(int downSize, float dtime);

	virtual int CheckOutOfBoundary(int locationY);

	//�߰��޼ҵ�
	POSITION GetCurrentPos() { return m_Pos; };

};
