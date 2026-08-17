#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class EnemySpawner : public Craft::Actor
{
public:
	EnemySpawner();

	inline int GetEnemyCount() const { return enemyCount; }

private:
	virtual void Tick(float deltaTime) override;

	void SpawnEnemy();

private:
	Timer timer;

	int enemyCount = 0;

	std::string enemyImage;
	std::string citizenImage;
};

