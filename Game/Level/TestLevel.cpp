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
		//todo: 소팅 오더 설정
		Craft::Renderer::Get().Submit("Time Over!", Craft::Vector2(45, 15));
	}
}

void TestLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);

	if (!timeLimit.IsTimeOut()) {
		return;
	}

	isTimeOver = true;

	timeLimit.Reset();
}
