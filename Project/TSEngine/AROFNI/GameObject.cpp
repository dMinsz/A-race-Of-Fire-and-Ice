#include "stdafx.h"
#include "GameObject.h"

void GameObject::Init(float x, float y, TSprite* sprite)
{
	POSITION tempPos;
	tempPos.x = x;
	tempPos.y = y;

	m_Pos = tempPos;
	m_Sprite = sprite;
}

void GameObject::Update()
{
	//안씀
}

void GameObject::Draw()
{
	HDC backbuffer = TSEngine::GetEngine()->GetBackBufferDC();

	TSEngine::GetEngine()->DrawSprite(backbuffer, m_Pos.x, m_Pos.y, m_Sprite);

	//충돌체세팅 및 디버그용 
	/*RECT worldRECT;
	worldRECT = GetWorldAABB();
	TSEngine::GetEngine()->DrawRectangleDebug(worldRECT.left, worldRECT.top, worldRECT.right, worldRECT.bottom, RGB(0, 255, 0));*/
}

void GameObject::Release()
{
	TSEngine::GetEngine()->SpriteRelease(m_Sprite);
}

void GameObject::AutoDown(int downSize, float dtime)
{
	//좌표상 내려가는건 +
	//m_Pos.y += (downSpeed * dtime);
	m_Pos.y += ((float)downSize * dtime);
}

int GameObject::CheckOutOfBoundary(float locationY)
{
	if (m_Pos.y >= locationY)
	{
		return (m_Pos.y - locationY);
	}

	return -999;
}

RECT GameObject::GetWorldAABB() const
{
	RECT _worldAABB;
	_worldAABB.left = m_AABB.m_BoundingVolume.left + m_Pos.x;
	_worldAABB.right = m_AABB.m_BoundingVolume.right + m_Pos.x;
	_worldAABB.top = m_AABB.m_BoundingVolume.top + m_Pos.y;
	_worldAABB.bottom = m_AABB.m_BoundingVolume.bottom + m_Pos.y;

	return _worldAABB;
}

void GameObject::DrawBoundingVolume()
{
	if (m_IsCollidedX == true && m_IsCollidedY == true)
	{
		TSEngine::GetEngine() ->DrawRectangleDebug(m_Pos.x + m_AABB.m_BoundingVolume.left,
			m_Pos.y + m_AABB.m_BoundingVolume.top,
			m_Pos.x + m_AABB.m_BoundingVolume.right,
			m_Pos.y + m_AABB.m_BoundingVolume.bottom, RGB(255, 0, 255));

	}
	else if (m_IsCollidedX == true)
	{
		TSEngine::GetEngine()->DrawRectangleDebug(m_Pos.x + m_AABB.m_BoundingVolume.left,
			m_Pos.y + m_AABB.m_BoundingVolume.top,
			m_Pos.x + m_AABB.m_BoundingVolume.right,
			m_Pos.y + m_AABB.m_BoundingVolume.bottom, RGB(255, 0, 0));
	}
	else if (m_IsCollidedY == true)
	{
		TSEngine::GetEngine()->DrawRectangleDebug(m_Pos.x + m_AABB.m_BoundingVolume.left,
			m_Pos.y + m_AABB.m_BoundingVolume.top,
			m_Pos.x + m_AABB.m_BoundingVolume.right,
			m_Pos.y + m_AABB.m_BoundingVolume.bottom, RGB(0, 0, 255));
	}
	else
	{
		TSEngine::GetEngine()->DrawRectangleDebug(m_Pos.x + m_AABB.m_BoundingVolume.left,
			m_Pos.y + m_AABB.m_BoundingVolume.top,
			m_Pos.x + m_AABB.m_BoundingVolume.right,
			m_Pos.y + m_AABB.m_BoundingVolume.bottom, RGB(0, 0, 0));
	}
}

