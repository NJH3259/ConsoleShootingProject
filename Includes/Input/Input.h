#pragma once

#include <Core/Core.h>

namespace Craft
{
	class CRAFT_API Input
	{
		friend class Engine;

		struct KeyState
		{
			bool isKeyDown = false;

			bool wasKeyDown = false;
		};

	public:
		Input();
		~Input() = default;

		bool GetKeyDown(int keyCode) const;
		bool GetKey(int keyCode) const;
		bool GetKeyUp(int keyCode) const;

		static Input& Get();

	private:
		void ProcessInput();

		void SavePreviousKeyStates();

	private:
		//가상 키의 수
		const int keyCount = 256;

		KeyState keyStates[256] = {  };

		//전역 접근을 위한 변수
		static Input* instance;
	};
}

