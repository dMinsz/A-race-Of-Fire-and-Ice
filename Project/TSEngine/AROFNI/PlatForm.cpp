#include "stdafx.h"
#include "PlatForm.h"

void PlatForm::Init(float x, float y, TSprite* sprite)
{
	GameObject::Init(x, y, sprite);

	//충돌체 세팅
	AABB Collision;
	Collision.m_BoundingVolume.left = 0;
	Collision.m_BoundingVolume.top = 0;
	Collision.m_BoundingVolume.right = sprite->m_Width + 1;
	Collision.m_BoundingVolume.bottom = sprite->m_Height+ 1;
	
	GameObject::m_AABB = Collision;
}

void PlatForm::Update()
{
	GameObject::Update();

}

void PlatForm::Draw()
{
	GameObject::Draw();
}

void PlatForm::Release()
{
	GameObject::Release();
}

void PlatForm::AutoDown(int downSizeed, float dtime)
{
	GameObject::AutoDown(downSizeed, dtime);
}

int PlatForm::CheckOutOfBoundary(int locationY)
{
	return GameObject::CheckOutOfBoundary(locationY);
}
