#include "EnemySpawner.h"
#include <Util/Util.h>
#include <Level/Level.h>
#include <Actor/Enemy.h>

#include <cassert>

using namespace Craft;

EnemySpawner::EnemySpawner()
{
	timer.SetTargetTime(Util::RandomRange(0.8f, 2.0f));
	enemyImage = LoadEnemyImage("Enemy.txt");
}

void EnemySpawner::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	//타이머 업데이트
	timer.Tick(deltaTime);

	if (!timer.IsTimeOut()) {
		return;
	}

	//타이머 초기화
	timer.Reset();

	//적 생성
	SpawnEnemy();
}

void EnemySpawner::SpawnEnemy()
{
	int xPosition = Util::RandomRange(1, 50);
	int yPosition = Util::RandomRange(1, 20);
	
	Vector2 spawnPosition = Vector2(xPosition, yPosition);

	std::shared_ptr<Level> owner = GetOwner();
	if (owner)
	{
		owner->SpawnActor<Enemy>(enemyImage, spawnPosition);
	}
}

std::string EnemySpawner::LoadEnemyImage(const std::string & fileName)
{
	std::string filePath = std::string("../Assets/") + fileName;

	FILE* file = nullptr;
	fopen_s(&file, filePath.c_str(), "rt");

	if (!file)
	{
		assert(false && "Can't read Enemy.txt file");
		return nullptr;
	}

	//파일 내용을 저장할 버퍼 확인 후 파일 길이 확인
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);

	//파일 제일 끝위치 구한 후 처음으로 이동
	rewind(file);

	//파일을 저장할 버퍼
	char* buffer = new char[fileSize] {};

	//파일 읽기
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	assert(readSize > 0 && "No data in the file");

	std::string enemyImage(buffer, readSize);

	delete[] buffer;
	buffer = nullptr;

	fclose(file);

	return enemyImage;
}
