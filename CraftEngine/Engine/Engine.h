#pragma once


namespace Craft {
	class Engine
	{
		struct Setting {
			float framerate;
		};

	public:
		Engine();
		virtual ~Engine();

		void Run();

		void Quit();

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

	protected:
		//엔진 종료 여부
		bool isQuit = false;

		//설정값
		Setting setting;
	};
}
