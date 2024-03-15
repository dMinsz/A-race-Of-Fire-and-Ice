#include "stdafx.h"
#include "Gage.h"

void Gage::Init(int x, int y, int* gagehp, TSprite* sprite , int dir)
{
	m_hp = gagehp; 
	m_Pos.x = x; 
	m_Pos.y = y; 
	m_Sprite = sprite;
	m_Direction = dir;

	m_Offsetsize = sprite->m_Width / (*gagehp);
	m_Offset = 0;
	m_time = 0.0f;
}
void Gage::Draw()
{
	HDC backbuffer = TSEngine::GetEngine()->GetBackBufferDC();

	

	if (m_Direction == 0)//오른쪽에서 왼쪽으로
	{
	::TransparentBlt(backbuffer, m_Pos.x, m_Pos.y, ((*m_hp) * m_Offsetsize), m_Sprite->m_Height,
			m_Sprite->m_MemDC, 0, 0, m_Sprite->m_Width, m_Sprite->m_Height, m_Sprite->KeyColor);

	//debug
		//TSEngine::GetEngine()->DrawTextT(TSEngine::GetEngine()->GetBackBufferDC(), 1800, 100, RGB(255, 0, 255), "Gage2 hp : %d", (*m_hp));
	}
	else  //왼쪽에서 오른쪽으로
	{

		//m_Pos.x = (m_Sprite->m_Width - (m_Offsetsize * (*m_hp)));
		 float xLocation = m_Pos.x + (m_Offsetsize * (100-(*m_hp)));

		::TransparentBlt(backbuffer, xLocation, m_Pos.y,  (m_Offsetsize* (*m_hp)), m_Sprite->m_Height,
			m_Sprite->m_MemDC, 0, 0, m_Sprite->m_Width, m_Sprite->m_Height, m_Sprite->KeyColor);
		//debug	
		//TSEngine::GetEngine()->DrawTextT(TSEngine::GetEngine()->GetBackBufferDC(), 1, 100, RGB(255, 0, 255), "Gage1 hp : %d", (*m_hp));
	}
	//::BitBlt(backbuffer, m_Pos.x, m_Pos.y, (m_Sprite->m_Width - m_Offsetsize* m_Offset), m_Sprite->m_Height, m_Sprite->m_MemDC, 0, 0, SRCCOPY);

}

void Gage::Update(float dtime)
{

	/*m_hp -= 1;
	m_Offset++;*/

	m_time += dtime;
	//float fps = 5.0f / ;

	if (m_time > 1.0f)
	{

		if ((*m_hp) >= 0)
		{
			(*m_hp) -= 10;
			m_Offset++;
		}

		m_time = 0.0f;

	}
}

void Gage::Release()
{
	TSEngine::GetEngine()->SpriteRelease(m_Sprite);
}
