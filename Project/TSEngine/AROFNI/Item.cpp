#include "stdafx.h"
#include "Item.h"

void Item::Init(float x, float y, TSprite* sprite)
{
	GameObject::Init(x, y, sprite);

	//충돌체 세팅
	AABB Collision;
	Collision.m_BoundingVolume.left = 0;
	Collision.m_BoundingVolume.top = 0;
	Collision.m_BoundingVolume.right = sprite->m_Width -3;
	Collision.m_BoundingVolume.bottom = sprite->m_Height;

	GameObject::m_AABB = Collision;
}

void Item::Update()
{
	GameObject::Update();

}

void Item::Draw()
{
	GameObject::Draw();
}

void Item::Release()
{
	GameObject::Release();
}

void Item::AutoDown(int downSizeed, float dtime)
{
	GameObject::AutoDown(downSizeed, dtime);
}

int Item::CheckOutOfBoundary(int locationY)
{
	return GameObject::CheckOutOfBoundary(locationY);
}