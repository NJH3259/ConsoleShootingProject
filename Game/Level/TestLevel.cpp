#include "TestLevel.h"
#include <Actor/EnemySpawner.h>
#include <Actor/Player.h>
#include <Actor/CoverSpawner.h>

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
