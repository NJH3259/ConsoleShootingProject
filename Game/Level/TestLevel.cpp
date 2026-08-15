#include "TestLevel.h"
#include <Actor/EnemySpawner.h>
#include <Actor/Player.h>
#include <Actor/CoverSpawner.h>
#include <Render/Renderer.h>
#include <Math/Vector2.h>


using namespace Craft;
TestLevel::TestLevel()
{
	UILine = Util::LoadImageFromFile("UILayout.txt", "../Assets/");
	timer.SetTargetTime(timeLimit);
	timer.Reset();
}

void TestLevel::ResetLevel()
{
	coverSpawner = nullptr;
	player = nullptr;
	enemySpawner = nullptr;

	actorList.clear();

	timer.Reset();

	coverSpawner = SpawnActor<CoverSpawner>();
	player = SpawnActor<Player>();
	enemySpawner = SpawnActor<EnemySpawner>();
}

void TestLevel::OnInitialized()
{
	Level::OnInitialized();

	coverSpawner = SpawnActor<CoverSpawner>();
	player = SpawnActor<Player>();
	enemySpawner = SpawnActor<EnemySpawner>();
}

void TestLevel::Draw()
{
	//기본 게임 UI 서식
	Renderer::Get().Submit(UILine, Vector2(Util::GetScreenSize().x - Util::GetUIOffset() - 1, 0), Color::BrightWhite, 15);

	//UI에 표시할 값들을 문자열로 변환
	score = MakeUIText(player->GetScore(), 4);
	timeLeft = MakeUIText(timeLimit - timer.GetElapsedTime(), 3) + "s";
	bullet = MakeUIBullet(player->GetBulletCount());
	enemyCount = MakeUIText(enemySpawner->GetEnemyCount(), 3);
	killCount = MakeUIText(player->GetKillCount(), 3) + "K";

	//게임 진행에 따라 변화하는 UI정보 (점수, 시간 등)
	Renderer::Get().Submit(score, Vector2(Util::GetScreenSize().x - Util::GetUIOffset() + 15, 4), Color::Yellow, 16);
	
	//남은 시간이 얼마 안남으면 남은 시간 빨간색으로 표시
	if (timeLimit - timer.GetElapsedTime() > 15.0f) 
	{
		Renderer::Get().Submit(timeLeft, Vector2(Util::GetScreenSize().x - Util::GetUIOffset() + 15, 5), Color::Yellow, 16);
	}
	else {
		Renderer::Get().Submit(timeLeft, Vector2(Util::GetScreenSize().x - Util::GetUIOffset() + 15, 5), Color::Red, 16);
	}

	Renderer::Get().Submit(bullet, Vector2(Util::GetScreenSize().x - Util::GetUIOffset() + 4, 9), Color::BrightWhite, 16);

	Renderer::Get().Submit(enemyCount, Vector2(Util::GetScreenSize().x - Util::GetUIOffset() + 15, 13), Color::Yellow, 16);
	Renderer::Get().Submit(killCount, Vector2(Util::GetScreenSize().x - Util::GetUIOffset() + 15, 14), Color::Yellow, 16);

	Level::Draw();

	//제한 시간 종료 시 표시할 UI
	if (isTimeOver) {
		Renderer::Get().Submit("Time Over!", Vector2((((Util::GetScreenSize().x - Util::GetUIOffset()) / 2) - 4), Util::GetScreenSize().y / 2 - 1), Color::White, 15);
	}
}

void TestLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);

	timer.Tick(deltaTime);

	if (!timer.IsTimeOut()) {
		return;
	}

	isTimeOver = true;
	
	for (auto actor : actorList)
	{
		//Level에서 TimeOver가 true가 되면 level 내의 Actor들의 Tick()이 동작하지 않도록 return함 -> Actor.cpp의 Tick()확인
		actor->SetTimeOut();
	}
}

//해당 함수는 int와 float만 받는 것을 전재로 함(점수나 시간 따위를 표시하기 위함)
template<typename T>
std::string TestLevel::MakeUIText(T value, int lengthLimit)
{
	int valueToInteger = static_cast<int>(value);
	std::string newText = std::to_string(valueToInteger);

	while (newText.length() < lengthLimit) {
		newText = "0" + newText;
	}

	return newText;
}

std::string TestLevel::MakeUIBullet(int bulletCount)
{
	std::string newBullet = "";

	int index = 0;
	while (index < bulletCount) {
		newBullet += "  |";
		index += 1;
	}

	return newBullet;
}