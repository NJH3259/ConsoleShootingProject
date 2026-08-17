#include "CoverSpawner.h"
#include <Actor/Cover.h>
#include <Actor/Actor.h>
#include <Level/Level.h>
#include <Math/Vector2.h>
#include <Util/Util.h>
#include <memory>

using namespace Craft;
CoverSpawner::CoverSpawner()
{
	ClearImageList();
	AddImageToList("Cover1.txt", "../Assets/");
	AddImageToList("Cover2.txt", "../Assets/");
}


void CoverSpawner::SpawnCover()
{
	//무작위 생성 개수
	int randomCount = Util::RandomRange(4, 6);

	for (int idx = 0; idx < randomCount; idx++) 
	{
		//CoverList에서 무작위로 에셋을 가져다 생성하기 위한 인덱스
		int randomIndex = Util::RandomRange(0, coverImageList.size() - 1);

		coverImage = coverImageList[randomIndex];

		int screenX = Util::GetScreenSize().x;
		Vector2 spawnPosition = Vector2(Util::RandomRange(20, Util::GetScreenSize().x - Util::GetUIOffset() - 20), Util::RandomRange(5, Util::GetScreenSize().y - 5));

		std::shared_ptr<Level> owner = GetOwner();
		if (owner)
		{
			owner->SpawnActor<Cover>(coverImage, spawnPosition);
		}
	}
}

void CoverSpawner::Tick(float deltaTime)
{
	if (isCoverSpawned) {
		return;
	}

	SpawnCover();

	SetIsCoverSpawnedTrue();
}

void CoverSpawner::AddImageToList(const std::string& fileName, const std::string& fileFolder)
{
	coverImage = Util::LoadImageFromFile(fileName, "../Assets/");
	coverImageList.emplace_back(coverImage);
}


