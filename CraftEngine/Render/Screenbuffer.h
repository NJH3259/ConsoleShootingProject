#pragma once

#include <Math/Vector2.h>

#include <Windows.h>

namespace Craft
{
	class Screenbuffer
	{
	public:
		Screenbuffer(const Vector2& screenSize);
		~Screenbuffer();

		//콘솔 초기화
		void Clear() const;

		//전달된 글자 값 그리기
		void Draw(const CHAR_INFO* const charInfo) const;

		inline HANDLE GetBuffer() const { return buffer; }

	private:
		//화면 버퍼 핸들
		HANDLE buffer = nullptr;

		Vector2 size;
	};
}

