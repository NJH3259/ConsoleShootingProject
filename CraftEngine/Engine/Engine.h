#pragma once

#include <Core/Core.h>
#include <memory>

namespace Craft {
	class Level;
	class Input;
	class Renderer;

	class CRAFT_API Engine
	{
		struct Setting {
			float framerate = 120.0f;

			int consoleWidth = 0;

			int consoleHeigth = 0;
		};

	public:
		Engine();
		virtual ~Engine();

		void Run();

		void Quit();

		template<typename T,
			typename = std::enable_if_t<std::is_base_of<Level, T>::value>>
			void AddNewLevel()
		{
			// 추가 요청 레벨 객체 생성.
			nextLevel = std::make_shared<T>();
		}

		static Engine& Get();

		inline int GetConsoleWidth() { return setting.consoleWidth; }
		inline int GetConsoleHeigth() { return setting.consoleHeigth; }
		
	protected:
		//엔진에서 해야할 일
		//엔진 초기화
		//입력 처리
		//게임 플레이 초기화
		//업데이트
		//그리기
		//프레임 간 입력 값 저장
		//엔진 종료 시 정리 -> 필요하면 구현
		void OnInitilized();

		void ProcessInput();

		void BeginGamePlay();

		void Tick(float deltaTime);

		void Draw();

		void SavePreviousInputStates();

		void ShutDown();

		void LoadEngineSetting();

	protected:
		//엔진 종료 여부
		bool isQuit = false;

		//설정값
		Setting setting;

		// 전역 접근이 가능하도록 변수 선언.
		static Engine* instance;

		// 메인 레벨.
		std::shared_ptr<Level> mainLevel;

		// 추가 요청된 레벨.
		std::shared_ptr<Level> nextLevel;

		// 입력 시스템 변수.
		std::unique_ptr<Input> input;

		std::unique_ptr<Renderer> renderer;
	};
}
