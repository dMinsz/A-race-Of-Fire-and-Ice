#include "Framework.h"
#include "TSEngine.h"
#include "AniInfo.h"
#include "TSprite.h"
#include "TSMap.h"
#include "GameMap.h"

GameMap::GameMap()
	:m_BackBuffer(NULL), m_ScrollSpeed(1.0f), m_ScrollSize(0)
{
	for (int i = 0; i < MAP_MAX; i++)
	{
		m_Maps[i] = NULL;
	}

}

void GameMap::Init(HDC backBuffer, TSMap* maps[3], int scrollSize, float scrollSpeed)
{
	m_BackBuffer = backBuffer;
	m_ScrollSize = scrollSize;
	m_ScrollSpeed = scrollSpeed;

	for (int i = 0; i < MAP_MAX; i++)
	{
		m_Maps[i] = maps[i];
	}


}

void GameMap::Update(float dtime)
{
	for (int i = 0; i < MAP_MAX; i++)
	{
		m_Maps[i]->Pos.y = (m_Maps[i]->Pos.y + m_ScrollSize) * m_ScrollSpeed * dtime;
	}

}

void GameMap::Draw()
{
	for (int i = 0; i < MAP_MAX; i++)
	{
		::BitBlt(m_BackBuffer, m_Maps[i]->Pos.x, m_Maps[i]->Pos.y,
			m_Maps[i]->m_Width, m_Maps[i]->m_Height,
			m_Maps[i]->m_MemDC, 0, 0, SRCCOPY);
	}

}

void GameMap::SwapMap(TSMap* addMap)
{

	//지워질 Map을 냅두고 한칸씩 다 땡겨서 
	//새로운 맵을 마지막에 넣어준다.
	m_Maps[0] = m_Maps[1];
	m_Maps[1] = m_Maps[2];

	m_Maps[2] = addMap;


}
