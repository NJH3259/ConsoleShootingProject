#include "TestLevel.h"
#include <Actor/EnemySpawner.h>
#include <Actor/Player.h>
#include <Actor/CoverSpawner.h>
#include <Render/Renderer.h>
#include <Math/Vector2.h>

TestLevel::TestLevel()
{
	timeLimit.SetTargetTime(45.0f);
}

void TestLevel::OnInitialized()
{
	Level::OnInitialized();

	SpawnActor<CoverSpawner>();
	SpawnActor<Player>();
	SpawnActor<EnemySpawner>();
}

void TestLevel::Draw()
{
	Level::Draw();

	if (isTimeOver) {
		Craft::Renderer::Get().Submit("Time Over!", Craft::Vector2(45, 15), Craft::Color::White, 15);
	}
}

void TestLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);

	if (!timeLimit.IsTimeOut()) {
		return;
	}

	isTimeOver = true;
	
	for (auto actor : actorList)
	{
		//todo: Level에서 TimeOver가 true가 되면 level 내의 Actor들의 Tick()이 동작하지 않도록 return함 -> Actor.cpp의 Tick()확인
		actor->SetTimeOut();
	}

	timeLimit.Reset();
}
