#include "Engine.h"
#include <Level/Level.h>
#include <Input/Input.h>
#include <Render/Renderer.h>

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

		//엔진 설정 로드
		LoadEngineSetting();

		// 입력 객체 생성.
		input = std::make_unique<Input>();
		
		renderer = std::make_unique<Renderer>(Vector2(setting.consoleWidth, setting.consoleHeight));
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
		return *instance;
	}

	void Engine::OnInitilized()
	{
		if (!mainLevel || mainLevel->HasInitialized()) {
			return;
		}
		mainLevel->OnInitialized();
	}

	void Engine::ProcessInput()
	{
		assert(input && "input should not be null");
		if (!input) {
			return;
		}

		input->ProcessInput();
	}

	void Engine::BeginGamePlay()
	{}

	void Engine::Tick(float deltaTime)
	{
		if (!mainLevel) {
			return;
		}

		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		//assert(mainLevel && "there's no main level");
		if (!mainLevel) {
			return;
		}

		//레벨이 소유하는 활성화된 Actor 객체의 Draw를 호출하여 Renderer에 그려야 할 정보들을 넘겨줌
		mainLevel->Draw();

		assert(renderer && "renderer should not be null");
		if (!renderer) {
			return;
		}

		//위에서 받은 정보를 바탕으로 화면에 그림
		renderer->Draw();
	}

	void Engine::SavePreviousInputStates()
	{
		assert(input && "input should not be null");
		if (!input) {
			return;
		}
		input->SavePreviousKeyStates();
	}

	void Engine::ShutDown()
	{}

	void Engine::LoadEngineSetting()
	{
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt");

		if (!file) {
			std::cout << "filed to open setting.txt";

			__debugbreak();
			return;
		}

		const int bufferSize = 2048;
		char buffer[bufferSize] = {};

		size_t readSize = fread(buffer, sizeof(char), bufferSize, file);

		char* context = nullptr;
		char* token = nullptr;

		token = strtok_s(buffer, "\n", &context);

		while (token) {
			// 공백 전까지 읽은 문자열을 저장할 변수.
			char key[15] = {};

			// 포맷을 지정한 문자열 읽기.
			// 공백 문자를 만나면 그 전까지 읽어서 저장.
			sscanf_s(token, "%s", key, 15);

			// 키 값을 비교해서 값 설정.
			if (strcmp(key, "framerate") == 0)
			{
				sscanf_s(token, "framerate = %f", &setting.framerate);
			}
			else if (strcmp(key, "consoleWidth") == 0)
			{
				sscanf_s(token, "consoleWidth = %d", &setting.consoleWidth);
			}
			else if (strcmp(key, "consoleHeight") == 0)
			{
				sscanf_s(token, "consoleHeight = %d", &setting.consoleHeight);
			}

			// 나머지 문자열 자르기(개행 문자 기준으로).
			token = strtok_s(nullptr, "\n", &context);
		}

		fclose(file);
		file = nullptr;
	}
}