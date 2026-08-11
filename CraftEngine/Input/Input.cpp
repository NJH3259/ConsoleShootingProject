#include "Input.h"

#include <cassert>
#include <Windows.h>


namespace Craft 
{
	Input* Input::instance = nullptr;

	Input::Input()
	{
		assert(!instance && "instance should not be initialized");
		instance = this;
	}

	bool Craft::Input::GetKeyDown(int keyCode) const
	{
		return !keyStates[keyCode].wasKeyDown && keyStates[keyCode].isKeyDown;
	}
	bool Input::GetKey(int keyCode) const
	{
		return keyStates[keyCode].wasKeyDown && keyStates[keyCode].isKeyDown;
	}
	bool Input::GetKeyUp(int keyCode) const
	{
		return keyStates[keyCode].wasKeyDown && !keyStates[keyCode].isKeyDown;
	}

	Input& Input::Get()
	{
		assert(instance && "instance should not be initialized");
		return *instance;
	}

	void Input::ProcessInput()
	{
	
		for (int ix = 0; ix < keyCount; ++ix)
		{
			// 키 눌림 여부 저장.
			keyStates[ix].isKeyDown = ((GetAsyncKeyState(ix) & 0x8000) != 0);
		}
	}
	void Input::SavePreviousKeyStates()
	{
		for (KeyState& state : keyStates)
		{
			// 현재 프레임 입력 값을 이전 프레임 값으로 저장.
			state.wasKeyDown = state.isKeyDown;
		}
	}
}