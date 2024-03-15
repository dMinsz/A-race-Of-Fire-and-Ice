#pragma once

class GameObject;
class Player;
class Player2;
class PlatForm;
//전방선언


class CollisionManager
{

public :
	static bool CheckCollision_AABB(RECT source, RECT target);
	static bool CheckCollision_AABB_X(RECT source, RECT target);
	static bool CheckCollision_AABB_Y(RECT source, RECT target);

	static bool CheckCollision(GameObject* source,GameObject* target);

	//source 오브젝트가 target 오브젝트를 Y 값기준으로 완전히 감쌋을때
	static bool CheckYBeteenCollision(GameObject* source, GameObject* target);
	//source 오브젝트가 target 오브젝트를 X 값기준으로 완전히 감쌋을때
	static bool CheckXBeteenCollision(GameObject* source, GameObject* target);

	static int CheckPlayerAndItem(GameObject* player, GameObject* item);

	// player와 platform 사이의 오차를 잡아준다.
	static void PpDebug(Player* player, PlatForm* platform);

	// player와 platform 사이의 오차를 잡아준다.
	static void PpDebug(Player2* player, PlatForm* platform);
};

