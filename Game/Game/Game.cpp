#include "Game.h"
#include <Level/TestLevel.h>
#include <Level/TitleLevel.h>

Game::Game()
{
	// 두 레벨 생성 및 배열에 추가.
	levelList.emplace_back(std::make_shared<TitleLevel>());
	levelList.emplace_back(std::make_shared<TestLevel>());

	// 시작 상태 설정.
	state = State::GamePlay;

	// 게임 시작시 활성화할 레벨 설정.
	mainLevel = levelList[(int)state];
}

void Game::ToggleMenu()
{
	int stateIndex = static_cast<int>(state);
	// 인덱스를 1->0, 0->1로 토글하는 공식.
	int nextState = 1 - stateIndex;

	// 레벨 설정 및 상태 값 업데이트.
	nextLevel = levelList[nextState];
	state = static_cast<State>(nextState);
}