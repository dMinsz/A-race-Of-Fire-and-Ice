#pragma once
#define MAP_MAX 3

//vertical Scroll
class GameMap
{
public:
	//������ ����ȭ������.
	HDC m_BackBuffer; // ���� �Ѹ� �� 

	TSMap* m_Maps[MAP_MAX]; // ���� �� ���� �������� �����غ���.

	int m_ScrollSize; // ����ũ�� Y���̰���?
	float m_ScrollSpeed; // ��ũ�Ѽӵ�

public:
	GameMap();

	void Init(HDC backBuffer, TSMap* maps[3], int scrollSize, float scrollSpeed = 1.0f);
	void Update(float dtime);
	void Draw();

	//���� ������ ������ �׸��⶧���� ù ���� ȭ�鿡�� ������
	// ù���� ���𰡾������� ���ο� ���� �߰���������Ѵ�.
	void SwapMap(TSMap* addMap);

	
	void SetScrollSize(int scrollSize) { m_ScrollSize = scrollSize; };
	void SetScrollSpeed(float scrollSpeed) { m_ScrollSpeed = scrollSpeed; };
	

};