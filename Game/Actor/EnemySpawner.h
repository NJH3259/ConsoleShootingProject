#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class EnemySpawner : public Craft::Actor
{
public:
	EnemySpawner();

private:
	virtual void Tick(float deltaTime) override;

	void SpawnEnemy();

private:
	Timer timer;

	std::string enemyImage;
};

