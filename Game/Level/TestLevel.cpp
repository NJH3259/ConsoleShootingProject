#include "TestLevel.h"
#include <Actor/EnemySpawner.h>
#include <Actor/Player.h>
#include <Actor/CoverSpawner.h>

void TestLevel::OnInitialized()
{
	Level::OnInitialized();

	SpawnActor<CoverSpawner>();
	SpawnActor<Player>();
	SpawnActor<EnemySpawner>();
}
