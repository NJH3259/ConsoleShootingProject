#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>
#include <vector>

class CoverSpawner : public Craft::Actor
{
public:
	CoverSpawner();

private:
	void SpawnCover();

	virtual void Tick(float deltaTime);

	void AddImageToList(const std::string& coverImage, const std::string& fileFolder);

	inline void ClearImageList() { coverImageList.clear(); }

	inline void SetIsCoverSpawnedTrue() { isCoverSpawned = true; }

	//최초 1회 스폰 후 스폰 없을 거라 Timer에 따른 스폰은 없음
private:
	std::string coverImage;
	std::vector<std::string> coverImageList;
	bool isCoverSpawned = false;
};

