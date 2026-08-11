#pragma once

#include <Core/Core.h>
#include <Math/Vector2.h>
#include <Math/Color.h>

#include <string>
#include <vector>
#include <memory>

namespace Craft
{
	class ScreenBuffer;

	class CRAFT_API	Renderer
	{
		//이미지 데이터 구조체
		struct Frame {
			Frame(int bufferCount);
			~Frame();

			void Clear(const Vector2& screenSize);

			//화면에 그릴 2차원 배열 문자값
			std::unique_ptr<CHAR_INFO[]> charInfoArray;

			//그리기 정렬 값 이차원 배열
			std::unique_ptr<int[]> sortingOrderArray;
		};

		struct RenderCommand {
			std::string image;

			Vector2 position = Vector2::Zero;

			Color color = Color::White;

			int sortingOrder = -1;
		};

	public:
		Renderer();
		~Renderer();

		//그릴 데이터 제출
		void Submit(const std::string image, const Vector2& position, Color color = Color::White, int sortingOrder = 0);

		void Draw();

		static Renderer& Get();

	private:
		//그리기 시작할 때 화면 프레임 지움
		void Clear();

		void DrawRenderQueue();

		//결과 표시
		void Present();

		const ScreenBuffer* const GetCurrentBuffer() const;

	private:
		static Renderer* instance;
		
		std::vector<RenderCommand> renderQueue;

		Vector2 screenSize;

		//charInfoArray와 sortingOrderArray를 관리하는 프레임 객체
		std::unique_ptr<Frame> frame;
		
		//이중 버퍼링 화면 두개
		std::unique_ptr<ScreenBuffer> screenBufferArray[2];

		int currentBufferIndex = 0;
	};
}

