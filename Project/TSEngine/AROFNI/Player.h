#pragma once

#define PLAYER_X_MAX 720

enum
{
	MOVERIGHT, //오른쪽으로이동
	MOVELEFT, // 왼쪽으로이동
	JUMPR, // 오른쪽 점프모션
	JUMPL, // 왼쪽 점프모션
	MISSEAT, // 먹는대 미스 난 모션
	GOODEAT //잘먹을때
	//READYEAT // <-- 코드상으로 만 필요함
};


class Player : public GameObject
{
public:
	//기본적인 변수는 gameobject에서 상속받음

	std::vector<TSprite*> m_SpriteAni; //어떤 스프라이트를 쓸건지는 enum확인
	std::vector<AABB*> m_PlayerAABB; //충돌체
	
	int m_Hp;

	Gage* m_gage;
	TSprite* m_SprGage;

	int m_PrevedJumpStatus; // 점프시 이전 이동 상태를 가지고있어야 다시 돌아올수있음
	int m_CurrentStatus; // 애니메이션선택 //오른쪽으로이동등
	int m_PrevedStatus;

	int m_VerticalMoveSize; // 자동으로 움직일 크기 // 프레임당 크기

	int m_VerticalStart;
	int m_VeticalBoundary;

	float m_JumpSize;
	float m_JumpTargetTime;

	float m_JumpTime;
	float m_Debug_jump;

	float m_EatTime;
	float m_EatTargetTime;

	//충돌체크용
	PlatForm* m_nowPlatform; //올라갈 발판 // 오차 잡기용
	//float m_PlatformOffset;
	GameObject* m_hitObject; // 현재 충돌중인 오브젝트 //아이템, 트랩 등

	//아이템 제거용
	std::vector<GameObject*>* m_CurrentMaps;


public:

	virtual void Init(int x, int y, int vMoveSize , float jumpsize, float jumpTarget, int status, TSprite* sprite[], int arrsize, TSprite* sprGage);
	virtual void Update(float dtime);
	virtual void Draw(float dtime);
	virtual void Release();

	//현재 게임내의 오브젝트들은 모두 계속 내려갑니다. 마치 중력처럼?
	// update 를 이용할수도있지만 엔진타임기준으로 계속내릴예정이라 따로 만듭니다.
	virtual void AutoDown(int downSize, float dtime);

	// 현재 오브젝트의 위치가 location 아래로 내려갔는지 체크합니다.
	virtual int CheckOutOfBoundary(int locationY);


	//추가함수들
	void KeyInput();


	//캐릭터가 좌우로 움직이게함 체크 // 횡으로 체크
	int CheckOutOfXRight();
	int CheckOutOfXLeft();
	void AutoVerticalMove();

	void Jump(float dtime);
	void Eating();


	//
	virtual RECT GetWorldAABB();
	virtual AABB GetAABB(){ return *m_PlayerAABB[m_CurrentStatus]; }
};

