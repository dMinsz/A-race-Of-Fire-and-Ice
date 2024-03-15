#pragma once
class KeyState
{
public:
	KeyState() : current(false), prev(false) {};

public:
	bool current;
	bool prev;


	int m_keystate;

public:
	static void KeyUpdate();
	static bool InputKey(int vk);
	static bool InputKeyDown(int vk);
	static bool InputKeyUp(int vk);
};