#include "Screenbuffer.h"

#include <cassert>
#include <iostream>

namespace Craft
{
	ScreenBuffer::ScreenBuffer(const Vector2& screenSize)
		:size(screenSize)
	{
		//콘솔 버퍼 생성
		buffer = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			nullptr,
			CONSOLE_TEXTMODE_BUFFER,
			nullptr
		);

		assert(buffer != INVALID_HANDLE_VALUE);

		SMALL_RECT rect = {};
		rect.Top = 0;
		rect.Left = 0;
		rect.Right = static_cast<short>(size.x - 1);
		rect.Bottom = static_cast<short>(size.y - 1);
		BOOL result = SetConsoleWindowInfo(buffer, TRUE, &rect);

		assert(result == TRUE);

		result = SetConsoleScreenBufferSize(buffer, size);
		assert(result == TRUE);

		//만든 콘솔의 커서 끄기
		CONSOLE_CURSOR_INFO info;
		result = GetConsoleCursorInfo(buffer, &info);
		assert(result == TRUE);

		//커서 끄기
		info.bVisible = false;
		result = SetConsoleCursorInfo(buffer, &info);
		assert(result == TRUE);
	}

	ScreenBuffer::~ScreenBuffer()
	{
		if (buffer) {
			CloseHandle(buffer);
		}
	}

	void ScreenBuffer::Clear() const
	{
		//콘솔 전체를 지우는 함수 => 화면 전체에 공백 문자 한번에 설정
		DWORD writtenCount = 0;

		BOOL result = FillConsoleOutputCharacterA(buffer, ' ', size.x * size.y, Vector2::Zero, &writtenCount);

		assert(result == TRUE);
	}

	void ScreenBuffer::Draw(const CHAR_INFO* const charInfo) const
	{
	
		// charInfo는 2차원 배열 (1차원 배열에 2차원 배열 정보를 기록).

			// 설정할 글자 영역.
		SMALL_RECT rect = {
			0,							// Left
			0,							// Top
			static_cast<short>(size.x - 1),	// Right
			static_cast<short>(size.y - 1)	// Bottom
		};

		// 콘솔에 CHAR_INFO 타입으로 글자 쓰는 함수.
		BOOL result = WriteConsoleOutputA(
			buffer,
			charInfo,
			size,
			Vector2::Zero,
			&rect
		);

		assert(result == TRUE);
	}
}