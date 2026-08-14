#include "EnemySpawner.h"
#include <Util/Util.h>
#include <Level/Level.h>
#include <Actor/Enemy.h>

#include <cassert>

using namespace Craft;

EnemySpawner::EnemySpawner()
{
	timer.SetTargetTime(Util::RandomRange(1.2f, 2.0f));
	enemyImage = Util::LoadImageFromFile("Enemy.txt", "../Assets/");
}

void EnemySpawner::Tick(float deltaTime)
{
	TIME_OUT;

	Actor::Tick(deltaTime);

	//타이머 업데이트
	timer.Tick(deltaTime);

	if (!timer.IsTimeOut()) {
		return;
	}

	//타이머 초기화
	timer.Reset();

	//적 생성마다 생성 간격 조절
	timer.SetTargetTime(Util::RandomRange(0.8f, 1.5f));

	//적 생성
	SpawnEnemy();
}

void EnemySpawner::SpawnEnemy()
{
	int xPosition = Util::RandomRange(10, (Util::GetScreenSize().x - Util::GetUIOffset()) / 2 - 10);
	int yPosition = Util::RandomRange(1, Util::GetScreenSize().y - 10);
	
	Vector2 spawnPosition = Vector2(xPosition, yPosition);

	std::shared_ptr<Level> owner = GetOwner();
	if (owner)
	{
		owner->SpawnActor<Enemy>(enemyImage, spawnPosition);
	}
}