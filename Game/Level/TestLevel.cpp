#include "TestLevel.h"
#include <Actor/EnemySpawner.h>

void TestLevel::OnInitialized()
{
	Level::OnInitialized();

	SpawnActor<EnemySpawner>();
}
