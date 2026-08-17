#include "PauseLevel.h"
#include <Game/Game.h>
#include <Input/Input.h>
#include <Render/Renderer.h>
#include <cassert>

using namespace Craft;
PauseLevel::PauseLevel()
{
	// 메뉴 아이템 생성.
	itemList.emplace_back(std::make_unique<PauseItem>("Resume Game",
			[]()
			{
				// 메뉴 토글 함수 호출.
				Game& game = dynamic_cast<Game&>(Engine::Get());
				game.ToggleMenu(State::GamePlay);
			}
		)
	);

	itemList.emplace_back(std::make_unique<PauseItem>("Restart Game",
			[]()
			{
				//타이틀 화면 복귀
				Game& game = dynamic_cast<Game&>(Engine::Get());
				game.ResetGameLevel();
				game.ToggleMenu(State::GamePlay);
			}
		)
	);

	itemList.emplace_back(std::make_unique<PauseItem>("Return To Title",
			[]()
			{
				//타이틀 화면 복귀
				Game& game = dynamic_cast<Game&>(Engine::Get());
				game.ToggleMenu(State::Title);
			}
		)
	);
}

void PauseLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);

	// 입력 처리(위/아래 방향키, 엔터, ESC 키).
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu(State::GamePlay);

		// 인덱스 초기화.
		currentIndex = 0;
	}

	// 배열의 요소 개수.
	const int length = static_cast<int>(itemList.size());
	if (Input::Get().GetKeyDown('S'))
	{
		// 인덱스 돌리기 (-방향).
		currentIndex = (currentIndex + 1 + length) % length;
	}

	if (Input::Get().GetKeyDown('W'))
	{
		// 인덱스 돌리기 (+방향).
		currentIndex = (currentIndex - 1 + length) % length;
	}

	// 엔터 입력 처리 -> 현재 선택된 메뉴의 로직 실행.
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 어써트.
		assert(currentIndex >= 0
			&& currentIndex < (int)itemList.size()
			&& itemList[currentIndex]->onSelected
		);

		// 메뉴 아이템에 저장된 로직 실행.
		itemList[currentIndex]->onSelected();
	}
}

void PauseLevel::Draw()
{

	// 제목 그리기.
	Renderer::Get().Submit("Pause", Vector2((Engine::Get().GetConsoleWidth()) / 2 - 3, Engine::Get().GetConsoleHeight() / 2 - 4));

	// 메뉴 아이템 그리기.
	const int count = static_cast<int>(itemList.size());
	for (int ix = 0; ix < count; ++ix)
	{
		// 선택/미선택된 아이템 색상 처리.
		Color textColor = (ix == currentIndex)
			? selectedColor : unselectedColor;

		// 아이템 그리기.
		Renderer::Get().Submit(itemList[ix]->text, Vector2((Engine::Get().GetConsoleWidth() - itemList[ix]->text.length() - 1 ) / 2, Engine::Get().GetConsoleHeight() / 2 + ix), textColor);
	}
}