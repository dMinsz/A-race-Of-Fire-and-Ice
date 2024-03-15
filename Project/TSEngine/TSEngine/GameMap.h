#pragma once
#define MAP_MAX 3

//vertical Scroll
class GameMap
{
public:
	//엔진과 동기화해주자.
	HDC m_BackBuffer; // 맵을 뿌릴 곳 

	TSMap* m_Maps[MAP_MAX]; // 맵을 총 세개 기준으로 세팅해보자.

	int m_ScrollSize; // 내릴크기 Y값이겠지?
	float m_ScrollSpeed; // 스크롤속도

public:
	GameMap();

	void Init(HDC backBuffer, TSMap* maps[3], int scrollSize, float scrollSpeed = 1.0f);
	void Update(float dtime);
	void Draw();

	//맵을 세개로 나눠서 그리기때문에 첫 맵이 화면에서 나가면
	// 첫맵은 쓸모가없어지니 새로운 맵을 추가시켜줘야한다.
	void SwapMap(TSMap* addMap);

	
	void SetScrollSize(int scrollSize) { m_ScrollSize = scrollSize; };
	void SetScrollSpeed(float scrollSpeed) { m_ScrollSpeed = scrollSpeed; };
	

};