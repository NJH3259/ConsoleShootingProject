#include "Actor.h"
#include <Engine/Engine.h>
#include <Render/Renderer.h>

#include <cassert>

namespace Craft
{
	Actor::Actor(
		const std::string& image,
		const Vector2& position,
		Color color)
		: image(image), position(position), color(color),
		width(static_cast<int>(image.length()))
	{}

	Actor::~Actor()
	{}

	void Actor::BeginPlay()
	{
		// 이벤트 처리했다고 설정.
		hasBeganPlay = true;
	}

	void Actor::Tick(float deltaTime)
	{
		//스테이지 제한시간이 끝나면 Actor가 동작하지 않도록 함
		if (isTimeOut)
		{
			return;
		}
	}

	void Actor::Draw()
	{
		// 비활성 상태이면 종료.
		if (!IsActive())
		{
			return;
		}

		// 렌더러에 필요한 데이터 제출.
		Renderer::Get().Submit(image, position, color, sortingOrder);
	}

	void Actor::Destroy()
	{
		// 삭제 예약 설정.
		hasExpired = true;
	}

	void Actor::QuitGame()
	{
		// 엔진 종료 요청.
		Engine::Get().Quit();
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		// 변경하려는 위치 값이 기존 값과 동일하면 종료.
		if (position == newPosition)
		{
			return;
		}

		position = newPosition;
	}
	Vector2 Actor::GetScreenSize() const
	{
		return Vector2(Engine::Get().GetConsoleWidth(), Engine::Get().GetConsoleHeight());
	}

	std::string Actor::LoadImageFromFile(const std::string& fileName, const std::string& fileFolder)
	{
		std::string filePath = fileFolder + fileName;

		FILE* file = nullptr;
		fopen_s(&file, filePath.c_str(), "rt");

		if (!file)
		{
			assert(false && "Can't read Enemy.txt file");
			return nullptr;
		}

		//파일 내용을 저장할 버퍼 확인 후 파일 길이 확인
		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);

		//파일 제일 끝위치 구한 후 처음으로 이동
		rewind(file);

		//파일을 저장할 버퍼
		char* buffer = new char[fileSize] {};

		//파일 읽기
		size_t readSize = fread(buffer, sizeof(char), fileSize, file);

		assert(readSize > 0 && "No data in the file");

		std::string actorImage(buffer, readSize);

		delete[] buffer;
		buffer = nullptr;

		fclose(file);

		return actorImage;
	}
}