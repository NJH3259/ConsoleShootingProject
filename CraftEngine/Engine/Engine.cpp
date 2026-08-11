#include "Engine.h"
#include <Level/Level.h>
#include <Input/Input.h>

#include <iostream>
#include <cassert>
#include <Windows.h>


namespace Craft 
{
	// 전역 변수 초기화.
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{

		// instance 초기화.
		assert(!instance && "instance is not null");
		instance = this;

		// 입력 객체 생성.
		input = std::make_unique<Input>();
	}

	Engine::~Engine()
	{
		instance = nullptr;
	}

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
				break;
			}

			//입력 처리
			ProcessInput();

			//프레임 시간 계산
			QueryPerformanceCounter(&counter);
			current = counter.QuadPart;

			//프레임 시간을 초 단위로 변환
			float deltaTime = static_cast<float>(current - previous) / static_cast<float>(frequency.QuadPart);

			//고정 프레임 처리
			if (deltaTime >= oneFrameTime) 
			{
				//게임 이벤트 함수 호출
				OnInitilized();

				//게임 이벤트의 초기화
				BeginGamePlay();

				Tick(deltaTime);

				Draw();

				if (nextLevel)
				{
					// 기존 레벨 정리.
					if (mainLevel)
					{
						mainLevel.reset();
					}

					// 추가 요청된 레벨을 메인 레벨로 설정.
					mainLevel = nextLevel;

					// 포인터 정리.
					nextLevel.reset();
				}

				// 추가/제거 요청된 액터 정리.
				if (mainLevel)
				{
					mainLevel->ProcessAddAndDestroyActors();
				}


				SavePreviousInputStates();

				previous = current;
			}
		}

		ShutDown();
	}
	void Engine::Quit()
	{
		isQuit = true;
	}
	Engine& Engine::Get()
	{
		// TODO: insert return statement here
	}

	void Engine::OnInitilized()
	{}
	void Engine::ProcessInput()
	{}
	void Engine::BeginGamePlay()
	{}

	void Engine::Tick(float deltaTime)
	{
		
	}

	void Engine::Draw()
	{}
	void Engine::SavePreviousInputStates()
	{}
	void Engine::ShutDown()
	{}
}