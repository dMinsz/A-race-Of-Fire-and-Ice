#include "stdafx.h"
#include "CollisionManager.h"



bool CollisionManager::CheckCollision_AABB(RECT source, RECT target)
{
	// x���� ������ ��ģ��.
	if (source.left < target.right
		&& target.left < source.right)
	{
		// y���� ������ ��ģ��.
		if (source.top < target.bottom
			&& target.top < source.bottom)
		{
			// �簢���� ��ġ�� ���̴�.
			return true;
		}
	}
    return false;
}

bool CollisionManager::CheckCollision_AABB_X(RECT source, RECT target)
{
	// x���� ������ ��ģ��.
	if (source.left < target.right
		&& target.left < source.right)
	{
		return true;
	}
	return false;
}

bool CollisionManager::CheckCollision_AABB_Y(RECT source, RECT target)
{
	// y���� ������ ��ģ��.
	if (source.top < target.bottom
		&& target.top < source.bottom)
	{
		// �簢���� ��ġ�� ���̴�.
		return true;
	}
	return false;
}

bool CollisionManager::CheckCollision(GameObject* source, GameObject* target)
{
	bool resultx = false;
	bool resulty = false;

	if (CheckCollision_AABB_X(source->GetWorldAABB(), target->GetWorldAABB()) == true)
	{
		resultx = true;
	}


	if (CheckCollision_AABB_Y(source->GetWorldAABB(), target->GetWorldAABB()) == true)
	{
		resulty = true;
	}

	return resultx && resulty;
}

bool CollisionManager::CheckYBeteenCollision(GameObject* source, GameObject* target)
{

	if (source->GetWorldAABB().top < target->GetWorldAABB().top &&
		source->GetWorldAABB().bottom < target->GetWorldAABB().bottom)
	{

		return true;
	}

	return false;
}

bool CollisionManager::CheckXBeteenCollision(GameObject* source, GameObject* target)
{
	if (source->GetWorldAABB().left <= target->GetWorldAABB().left &&
		source->GetWorldAABB().right >= target->GetWorldAABB().right)
	{
		return true;
	}
	return false;
}

int CollisionManager::CheckPlayerAndItem(GameObject* player, GameObject* item)
{
	if (CheckXBeteenCollision(player, item))
	{
		return 2; // perfect

	}
	else if (CheckCollision_AABB(player->GetWorldAABB(), item->GetWorldAABB()))
	{
		return 1; // good

	}

	//error
	return 0;
}


void CollisionManager::PpDebug(Player* player, PlatForm* platform)
{
	if (player->GetWorldAABB().bottom >= platform->GetWorldAABB().top ||
		player->GetWorldAABB().bottom >= platform->GetWorldAABB().bottom
		)
	{
		float debug = player->GetWorldAABB().bottom - platform->GetWorldAABB().top;

		player->m_Pos.y -=(debug+2);

	}

}

void CollisionManager::PpDebug(Player2* player, PlatForm* platform)
{
	if (player->GetWorldAABB().bottom >= platform->GetWorldAABB().top ||
		player->GetWorldAABB().bottom >= platform->GetWorldAABB().bottom
		)
	{
		float debug = player->GetWorldAABB().bottom - platform->GetWorldAABB().top;

		player->m_Pos.y -= (debug);

	}
}
