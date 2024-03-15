#pragma once
// 한화면에서의 최대 오브젝트 갯수
//	platform 5 +1 // +1 은 미리 한플랫폼에 올라갈 오브젝트들을 만들예정이라서.
//한플랫폼에 들어갈수있는 오브젝트 갯수
//	ITem 8
//플레이어는 최대 두명
//	Player 2
// 플랫폼 하나 당 최대 8개의 아이템 생성 가능
// (8*6) + 2 +6 총 56 개의 오브젝트갯수를 관리한다.

//캐릭터는 제외하고 계산해보자

//Prototype용
#define OBJECT_MAX 54
#define PLATFORM_MAX 6
#define ITEM_MAX 48
#define ITEM_OFFSET 15
#define TRAP_OFFSET 0


//flatform 
//#define LECT_WIDTH 1620 // 비트맵없이 테스트용으로 사각형을 그릴예정
//#define LECT_HEIGHT 40

//#define DEFALT_X 150
#define DEFALT_X 0
#define DEFALT_Y 1000 

#define STARTDOWN -240


#define ITEM_HEIGHT 80

#define PATTERN_MAX 3


enum class MODE
{
	EASY,
	NORMAL,
	HARD0,
	HARD1,
	HARD2,
	HARD3,
	HARD4,
	HELL
};


struct PLAYERINFO 
{
	Player* Player1;
	Player2* Player2;
	float JumpSize;
	float JumpTime;

};

//기본 flatform 간격 200
struct MAPINFO
{
	int FInterval; //flatform 간격
	float ScrollDownSize; //오브젝트들을 계속 아래로 내릴 속도
	TSprite* SprPlatForm;
	TSprite* SprItems[2];//
	TSprite* SprTrap[2];

	ItemPatern* EASYPattern;
	ItemPatern* NORMALPattern;
	ItemPatern* HARD00Pattern;
	ItemPatern* HARD01Pattern;
	ItemPatern* HARD02Pattern;
	ItemPatern* HARD03Pattern;
	ItemPatern* HARD04Pattern;
	ItemPatern* HELLPattern;

	//아이템 스프라이트도 넣어주자;
	//std::vector<PATTERN>PatternArray;
	//int* Pattern[PATTERN_MAX]; // 한플랫폼에 위치할수있는 아이템들에 Y위치 // set 해줘야함
};


//아이템과 플랫폼(발판) 을 관리합니다.
class GameManager
{
public:

	//모든 플랫폼, 아이템 이 변수로 관리합니다.
	std::vector<GameObject*> m_Maps;


	// 맵에 필요한 정보모음
	MAPINFO m_Info;

	//플레이어 관리
	PLAYERINFO m_Player;

	//debuging
	float m_testDebug;

	MODE m_Mode; // 모드 시간관리등은 씬에서처리한다.

public:
	void Init(MAPINFO info, PLAYERINFO Player);

	void Update(float dtime); // 플랫폼 하나가 내려간걸 삭제하고 새로이 위에 플랫폼을하나그립니다.
	void Draw(float dtime);
	void Release();

	//아래로 내려간 플랫폼, 아이템 , 트랩들을 재 세팅하는함수
	void  SetOutObjects();

	//Map 만들기
	void GenerateMap();

	//Map 일부분 바꾸기
	//void ChangePlatform(int location, PlatForm* platform);
	void ChangeItem(int location, PlatForm* platform);

	//오브젝트들 내리기
	void Scrolling(float dtime);
	

	void ChangePattern(int Pattern[8]); // pattern 바꾸기
	void SetScrollSpeed(float ScrollDownSize);
	void SetPlusScrollSpeed(float ScrollDownSize);

};
