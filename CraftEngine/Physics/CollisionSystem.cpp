#include "CollisionSystem.h"
#include <Actor/Actor.h>
#include <Math/Vector2.h>

using namespace Craft;
void CollisionSystem::ProcessCollision(const std::vector<std::shared_ptr<Actor>>& actorList)
{
	if (actorList.empty()) {
		return;
	}

	const int actorCount = actorList.size();

	//플레이어 액터 탐색
	for (int idx = 0; idx < actorCount; idx++) {
		if (actorList[idx]->GetTypeId() == 1) {
			playerActor = actorList[idx];
			break;
		}
	}


	for (int idx = 0; idx < actorCount; idx++) {
		if (actorList[idx]->GetTypeId() == 1 || actorList[idx]->GetTypeId() == 3) {
			continue;
		}

		std::shared_ptr<Actor> collidedActor = actorList[idx];
		if (CheckCollision(collidedActor)) {
			//todo: Enemy 사망 이펙트 추가
			actorList[idx]->Destroy();
		}
	}
}

//엑터가 플레이어와 충돌했는지 여부 검사
bool Craft::CollisionSystem::CheckCollision(std::shared_ptr<Actor>& collidedActor)
{
	Vector2 playerPosition = playerActor->GetPosition();
	Vector2 collidedPosition = collidedActor->GetPosition();

	//플레이어가 Enemy의 y위치 밖에 있으면 절대 겹치지 않음(플레이어는 한줄이므로)
	if(collidedPosition.y > playerPosition.y || collidedPosition.y + 4 < playerPosition.y)
	{
		return false;
	}

	//플레이어의 x+1~x+3의 위치가 Enemy의 x+1~x+3중 하나라도 겹친다면 충돌 판정
	if (collidedPosition.x < playerPosition.x + 3 && playerPosition.x + 1 < collidedPosition.x + 4) {
		return true;
	}

	return false;
}
