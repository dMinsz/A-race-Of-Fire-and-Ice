#include "stdafx.h"
#include "Trap.h"

void Trap::Init(float x, float y, TSprite* sprite)
{
	GameObject::Init(x, y, sprite);
	
	
	//충돌체 세팅 세부조정해야함
	AABB Collision;
	Collision.m_BoundingVolume.left = 0;
	Collision.m_BoundingVolume.top = 0;
	Collision.m_BoundingVolume.right = sprite->m_Width + 1;
	Collision.m_BoundingVolume.bottom = sprite->m_Height + 1;

	GameObject::m_AABB = Collision;
}

void Trap::Update()
{
	GameObject::Update();

}

void Trap::Draw()
{
	GameObject::Draw();

}

void Trap::Release()
{
	GameObject::Release();
}

void Trap::AutoDown(int downSizeed, float dtime)
{
	GameObject::AutoDown(downSizeed,dtime);
}

int Trap::CheckOutOfBoundary(int locationY)
{
	return GameObject::CheckOutOfBoundary(locationY);
}
