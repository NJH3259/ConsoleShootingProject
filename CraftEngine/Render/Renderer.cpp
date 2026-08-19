#include "Renderer.h"
#include "ScreenBuffer.h"

#include <cassert>
#include <Windows.h>
#include <iostream>
#include <memory>

namespace Craft 
{
	//--------------------------Frame-------------------------//
	Renderer::Frame::Frame(int bufferCount)
	{
		// 2차원 배열 생성.
		charInfoArray = std::make_unique<CHAR_INFO[]>(bufferCount);
		sortingOrderArray = std::make_unique<int[]>(bufferCount);
	}

	Renderer::Frame::~Frame()
	{}

	// 프레임 초기화 함수.
	void Renderer::Frame::Clear(const Vector2& screenSize)
	{
		// 이중 루프를 순회하면서 값 초기화.
		const int width = screenSize.x;
		const int height = screenSize.y;

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				// 1차원 배열을 2차원 배열로 사용할 때 
				// 필요한 인덱스 좌표 변환.
				const int index = (y * width) + x;

				// 글자 항목 초기화.
				CHAR_INFO& info = charInfoArray[index];
				// 빈문자 설정 - 기존의 설정된 값 지우기.
				info.Char.AsciiChar = ' ';
				// 색상 표기 안함.
				info.Attributes = 0;

				// 그리기 순서 배열 항목 초기화.
				sortingOrderArray[index] = -1;
			}
		}
	}
	//--------------------------Frame-------------------------//

	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer(const Vector2& screenSize)
		:screenSize(screenSize)
	{
		assert(!instance && "instance should not be initialized");

		instance = this;

		//프레임 객체 생성
		const int bufferCount = screenSize.x * screenSize.y;
		frame = std::make_unique<Frame>(bufferCount);

		frame->Clear(screenSize);

		screenBufferArray[0] = std::make_unique<ScreenBuffer>(screenSize);
		screenBufferArray[0]->Clear();

		screenBufferArray[1] = std::make_unique<ScreenBuffer>(screenSize);
		screenBufferArray[1]->Clear();

		// 화면에 0번 콘솔 버퍼 활성화.
		SetConsoleActiveScreenBuffer(screenBufferArray[0]->GetBuffer());
	}

	Renderer::~Renderer()
	{
		instance = nullptr;

		// 콘솔 창 원래대로 복구.
		SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	}

	//todo: 1.전달받은 인자로 Color를 하나 추가해서 background색상을 바꿀 수 있도록 하기(검은색은 0)
	void Renderer::Submit(const std::string image, const Vector2 & position, Color color, int sortingOrder)
	{
		RenderCommand command;
		command.image = image;
		command.position = position;
		command.color = color;
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
		assert(instance && "there's should be an instance here");
		return *instance;
	}

	void Renderer::Clear()
	{
		//프레임 값 초기화
		frame->Clear(screenSize);

		//콘솔 버퍼 초기화
		GetCurrentBuffer()->Clear();
	}

	//todo: 2. 받은 배경 색상도 적용할 수 있도록 배경 색상 변경 명령어 추가하기(배경색상 값이 0이 아니면 배경 색상 변경)
	//todo: 공백 혹은 개행은 프레임에 전달하지 않아서 그리지 않도록 하기
	//todo: 공백이나 개행의 충돌 판정 -> 스크린 버퍼에서 해당 위치에 있는게 개행 혹은 공백이라면 충돌 안하는 조건문으로 처리하면 될듯? 
	void Renderer::DrawRenderQueue()
	{
		for (const RenderCommand& command : renderQueue) {
			if (command.image.empty()) {
				continue;
			}

			if (command.position.y < 0
				|| command.position.y >= screenSize.y)
			{
				continue;
			}

			int currentX = command.position.x;
			int currentY = command.position.y;

			// 파일에서 가져온 텍스트 내의 각각의 문자에 대해 
			for (char image : command.image) {
				// 문자가 개행 문자이면 콘솔 출력도 한줄 띄도록
				if (image == '\n') {
					currentY += 1;
					currentX = command.position.x;
					continue;
				}

				// 그리고자 하는 문자가 Screen범위 내에 있다면
				if (currentX >= 0 && currentX < screenSize.x && currentY >= 0 && currentY < screenSize.y) 
				{
					//index는 그리고자 하는 콘솔의 위치 값
					const int index = (currentY * screenSize.x) + currentX;
					
					// 위치에 존재하는 문자의 sortingOrder가 새로 그리고자 하는 문자의 sortingOrder보다 높으면 건너뜀
					if (frame->sortingOrderArray[index] > command.sortingOrder) {
						//currentX좌표 증가시키지 않으면 끝 문자 뒤로 문자가 사라지는 현상 발생 @고친 오류
						currentX++;
						continue;
					}

					//Player가 어디에 사격했는지 판정하기 위한 이전 문자값
					previousChar = frame->charInfoArray[index].Char.AsciiChar;

					frame->charInfoArray[index].Char.AsciiChar = image;
					frame->charInfoArray[index].Attributes = static_cast<DWORD>(command.color);
					frame->sortingOrderArray[index] = command.sortingOrder;
				}

				currentX++;
			}
		}
		
		// 앞에서 설정한 2차원 배열을 콘솔에 그리기.
		GetCurrentBuffer()->Draw(frame->charInfoArray.get());

		renderQueue.clear();

		// 콘솔 색상 초기화.
		SetConsoleTextAttribute(
			GetCurrentBuffer()->GetBuffer(),
			static_cast<DWORD>(Color::White)
		);
	}

	void Renderer::Present()
	{
		// 현재 순번의 콘솔 버퍼를 활성화.
		SetConsoleActiveScreenBuffer(GetCurrentBuffer()->GetBuffer());

		// 인덱스 업데이트(갱신).
		// 0 -> 1 -> 0 -> 1 ...
		// 마법의 공식 -> One Minus...
		currentBufferIndex = 1 - currentBufferIndex;
	}

	const ScreenBuffer* const Renderer::GetCurrentBuffer() const
	{
		return screenBufferArray[currentBufferIndex].get();
	}
}