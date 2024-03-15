#pragma once

class GameObject;
class Player;
class Player2;
class PlatForm;
//���漱��


class CollisionManager
{

public :
	static bool CheckCollision_AABB(RECT source, RECT target);
	static bool CheckCollision_AABB_X(RECT source, RECT target);
	static bool CheckCollision_AABB_Y(RECT source, RECT target);

	static bool CheckCollision(GameObject* source,GameObject* target);

	//source ������Ʈ�� target ������Ʈ�� Y ���������� ������ ��������
	static bool CheckYBeteenCollision(GameObject* source, GameObject* target);
	//source ������Ʈ�� target ������Ʈ�� X ���������� ������ ��������
	static bool CheckXBeteenCollision(GameObject* source, GameObject* target);

	static int CheckPlayerAndItem(GameObject* player, GameObject* item);

	// player�� platform ������ ������ ����ش�.
	static void PpDebug(Player* player, PlatForm* platform);

	// player�� platform ������ ������ ����ش�.
	static void PpDebug(Player2* player, PlatForm* platform);
};

