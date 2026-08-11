#include "Renderer.h"

#include <cassert>
#include <Windows.h>
#include <iostream>

namespace Craft 
{
	Renderer* instance = nullptr;

	Renderer::Renderer()
	{}
	Renderer::~Renderer()
	{}
	void Renderer::Submit(const std::string image, const Vector2 & position, Color color, int sortingOrder)
	{
		RenderCommand command;
		command.image = image;
		command.position = position;
		command.sortingOrder = sortingOrder;

		renderQueue.emplace_back(command);
	}

	void Renderer::Draw()
	{
		Clear();

		DrawRenderQueue();

		Present();
	}

	Renderer& Renderer::Get()
	{
		assert(instance);
		return *instance;
	}

	void Renderer::Clear()
	{
		system("cls");
	}

	void Renderer::DrawRenderQueue()
	{
		for (const RenderCommand& command : renderQueue) {
			//윈도우 콘솔 핸들
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

			//그릴 위치로 이동
			SetConsoleCursorPosition(handle, command.position);

			//글자 색상 설정
			SetConsoleTextAttribute(handle, static_cast<WORD>(command.color));

			//@todo: 그리기

			//글자 색상 돌리기
			SetConsoleTextAttribute(handle, static_cast<WORD>(Color::White));
		}

		renderQueue.clear();
	}
	void Renderer::Present()
	{}
}