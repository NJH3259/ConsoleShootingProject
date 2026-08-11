#include "Engine.h"

#include <iostream>
#include <Windows.h>


namespace Craft {
	Engine::Engine()
	{}
	Engine::~Engine()
	{}

	void Engine::Run()
	{
		//프레임 레이트 구현
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);

		int64_t current = counter.QuadPart;
		int64_t previous = current;

		float oneFrameTime = 1.0f / setting.framerate;

		//엔진 루프
		while (true) {
			if (isQuit) {
				return;
			}
		}
	}
	void Engine::Quit()
	{}
	void Engine::OnInitilized()
	{}
	void Engine::ProcessInput()
	{}
	void Engine::BeginGamePlay()
	{}
	void Engine::Tick(float deltaTime)
	{}
	void Engine::Draw()
	{}
	void Engine::SavePreviousInputStates()
	{}
	void Engine::ShutDown()
	{}
}