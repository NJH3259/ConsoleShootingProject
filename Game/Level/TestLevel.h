#pragma once

#include <Level/Level.h>
#include <Util/Timer.h>

#include <string>
#include <memory>

class Player;
class EnemySpawner;

class TestLevel : public Craft::Level
{
public:
	TestLevel();
	~TestLevel() = default;

private:
	virtual void OnInitialized() override;

	virtual void Draw() override;

	virtual void Tick(float deltaTime) override;

	//해당 함수는 int와 float만 받는 것을 전재로 함(점수나 시간 따위를 표시하기 위함)
	template<typename T>
	std::string MakeUIText(T value, int length);

private:
	Timer timer;
	const float timeLimit = 60.0f;
	bool isTimeOver = false;

	//UI점수 등 집계를 위함
	std::shared_ptr<Player> player;
	std::shared_ptr<EnemySpawner> enemySpawner;

	std::string UILine;

	std::string score;
	std::string timeLeft;

	std::string enemyCount;
	std::string killCount;
};

