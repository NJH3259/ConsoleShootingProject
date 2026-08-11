#pragma once

#include <Core/Core.h>
#include <Math/Vector2.h>
#include <Math/Color.h>

#include <string>
#include <vector>

namespace Craft
{
	class CRAFT_API	Renderer
	{
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
		void Submit(const std::string image, const Vector2& position, Color color = Color::White, int sortingOder);

		void Draw();

		static Renderer& Get();

	private:
		//그리기 시작할 때 화면 프레임 지움
		void Clear();

		void DrawRenderQueue();

		//결과 표시
		void Present();

	private:
		static Renderer* instance;
		
		std::vector<RenderCommand> renderQueue;
	};
}

