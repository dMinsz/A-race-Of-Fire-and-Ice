#include "stdafx.h"
#include "Input.h"

KeyState mKeyStateArr[256];


void KeyState::KeyUpdate()
{
	for (int index = 0; index < 255; index++)
	{
		mKeyStateArr[index].prev = mKeyStateArr[index].current;
		mKeyStateArr[index].current = HIWORD(GetAsyncKeyState(index));
	}
}

bool KeyState::InputKey(int vk)
{
	return mKeyStateArr[vk].current;
}

bool KeyState::InputKeyDown(int vk)
{
	return !mKeyStateArr[vk].prev && mKeyStateArr[vk].current;
}

bool KeyState::InputKeyUp(int vk)
{
	return mKeyStateArr[vk].prev && !mKeyStateArr[vk].current;
}
