#pragma once

#define PLAYER_X_MAX 720

enum
{
	MOVERIGHT, //�����������̵�
	MOVELEFT, // ���������̵�
	JUMPR, // ������ �������
	JUMPL, // ���� �������
	MISSEAT, // �Դ´� �̽� �� ���
	GOODEAT //�߸�����
	//READYEAT // <-- �ڵ������ �� �ʿ���
};


class Player : public GameObject
{
public:
	//�⺻���� ������ gameobject���� ��ӹ���

	std::vector<TSprite*> m_SpriteAni; //� ��������Ʈ�� �������� enumȮ��
	std::vector<AABB*> m_PlayerAABB; //�浹ü
	
	int m_Hp;

	Gage* m_gage;
	TSprite* m_SprGage;

	int m_PrevedJumpStatus; // ������ ���� �̵� ���¸� �������־�� �ٽ� ���ƿü�����
	int m_CurrentStatus; // �ִϸ��̼Ǽ��� //�����������̵���
	int m_PrevedStatus;

	int m_VerticalMoveSize; // �ڵ����� ������ ũ�� // �����Ӵ� ũ��

	int m_VerticalStart;
	int m_VeticalBoundary;

	float m_JumpSize;
	float m_JumpTargetTime;

	float m_JumpTime;
	float m_Debug_jump;

	float m_EatTime;
	float m_EatTargetTime;

	//�浹üũ��
	PlatForm* m_nowPlatform; //�ö� ���� // ���� ����
	//float m_PlatformOffset;
	GameObject* m_hitObject; // ���� �浹���� ������Ʈ //������, Ʈ�� ��

	//������ ���ſ�
	std::vector<GameObject*>* m_CurrentMaps;


public:

	virtual void Init(int x, int y, int vMoveSize , float jumpsize, float jumpTarget, int status, TSprite* sprite[], int arrsize, TSprite* sprGage);
	virtual void Update(float dtime);
	virtual void Draw(float dtime);
	virtual void Release();

	//���� ���ӳ��� ������Ʈ���� ��� ��� �������ϴ�. ��ġ �߷�ó��?
	// update �� �̿��Ҽ��������� ����Ÿ�ӱ������� ��ӳ��������̶� ���� ����ϴ�.
	virtual void AutoDown(int downSize, float dtime);

	// ���� ������Ʈ�� ��ġ�� location �Ʒ��� ���������� üũ�մϴ�.
	virtual int CheckOutOfBoundary(int locationY);


	//�߰��Լ���
	void KeyInput();


	//ĳ���Ͱ� �¿�� �����̰��� üũ // Ⱦ���� üũ
	int CheckOutOfXRight();
	int CheckOutOfXLeft();
	void AutoVerticalMove();

	void Jump(float dtime);
	void Eating();


	//
	virtual RECT GetWorldAABB();
	virtual AABB GetAABB(){ return *m_PlayerAABB[m_CurrentStatus]; }
};

