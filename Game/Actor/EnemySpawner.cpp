#include "EnemySpawner.h"
#include <Util/Util.h>
#include <Level/Level.h>
#include <Actor/Enemy.h>

#include <cassert>

using namespace Craft;

EnemySpawner::EnemySpawner()
{
	enemyImage = Util::LoadImageFromFile("Enemy.txt", "../Assets/");
	citizenImage = Util::LoadImageFromFile("Citizen.txt", "../Assets/");

	timer.SetTargetTime(Util::RandomRange(1.2f, 2.0f));
	enemyCount = 0;
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
	timer.SetTargetTime(Util::RandomRange(0.8f, 1.35f));

	//적 생성
	SpawnEnemy();
	enemyCount += 1;
}

void EnemySpawner::SpawnEnemy()
{
	int targetTypeId = 2;

	float targetFlag = Util::RandomRange(0.0f, 10.0f);
	if (targetFlag <= 2.0f) {
		targetTypeId = 4;
	}

	int xPosition = Util::RandomRange(10, (Util::GetScreenSize().x - Util::GetUIOffset()) / 2 - 10);
	int yPosition = Util::RandomRange(1, Util::GetScreenSize().y - 10);
	
	Vector2 spawnPosition = Vector2(xPosition, yPosition);

	std::shared_ptr<Level> owner = GetOwner();
	if (owner)
	{
		if(targetTypeId == 2)
		{
			owner->SpawnActor<Enemy>(enemyImage, spawnPosition, Color::Green, 2);
		}
		else
		{
			owner->SpawnActor<Enemy>(citizenImage, spawnPosition, Color::Yellow, 4);
		}
	}
}