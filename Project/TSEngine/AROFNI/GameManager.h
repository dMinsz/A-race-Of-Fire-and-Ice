#pragma once
// ��ȭ�鿡���� �ִ� ������Ʈ ����
//	platform 5 +1 // +1 �� �̸� ���÷����� �ö� ������Ʈ���� ���鿹���̶�.
//���÷����� �����ִ� ������Ʈ ����
//	ITem 8
//�÷��̾�� �ִ� �θ�
//	Player 2
// �÷��� �ϳ� �� �ִ� 8���� ������ ���� ����
// (8*6) + 2 +6 �� 56 ���� ������Ʈ������ �����Ѵ�.

//ĳ���ʹ� �����ϰ� ����غ���

//Prototype��
#define OBJECT_MAX 54
#define PLATFORM_MAX 6
#define ITEM_MAX 48
#define ITEM_OFFSET 15
#define TRAP_OFFSET 0


//flatform 
//#define LECT_WIDTH 1620 // ��Ʈ�ʾ��� �׽�Ʈ������ �簢���� �׸�����
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

//�⺻ flatform ���� 200
struct MAPINFO
{
	int FInterval; //flatform ����
	float ScrollDownSize; //������Ʈ���� ��� �Ʒ��� ���� �ӵ�
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

	//������ ��������Ʈ�� �־�����;
	//std::vector<PATTERN>PatternArray;
	//int* Pattern[PATTERN_MAX]; // ���÷����� ��ġ�Ҽ��ִ� �����۵鿡 Y��ġ // set �������
};


//�����۰� �÷���(����) �� �����մϴ�.
class GameManager
{
public:

	//��� �÷���, ������ �� ������ �����մϴ�.
	std::vector<GameObject*> m_Maps;


	// �ʿ� �ʿ��� ��������
	MAPINFO m_Info;

	//�÷��̾� ����
	PLAYERINFO m_Player;

	//debuging
	float m_testDebug;

	MODE m_Mode; // ��� �ð��������� ������ó���Ѵ�.

public:
	void Init(MAPINFO info, PLAYERINFO Player);

	void Update(float dtime); // �÷��� �ϳ��� �������� �����ϰ� ������ ���� �÷������ϳ��׸��ϴ�.
	void Draw(float dtime);
	void Release();

	//�Ʒ��� ������ �÷���, ������ , Ʈ������ �� �����ϴ��Լ�
	void  SetOutObjects();

	//Map �����
	void GenerateMap();

	//Map �Ϻκ� �ٲٱ�
	//void ChangePlatform(int location, PlatForm* platform);
	void ChangeItem(int location, PlatForm* platform);

	//������Ʈ�� ������
	void Scrolling(float dtime);
	

	void ChangePattern(int Pattern[8]); // pattern �ٲٱ�
	void SetScrollSpeed(float ScrollDownSize);
	void SetPlusScrollSpeed(float ScrollDownSize);

};
