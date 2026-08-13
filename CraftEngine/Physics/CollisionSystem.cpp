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

	for (int idx = 0; idx < actorCount; idx++) {
		if (actorList[idx].get()->GetTypeId() == 3) {
			continue;
		}

		
	}
}

void Craft::CollisionSystem::CheckCollision(std::shared_ptr<Actor>& enemyActor)
{
	Vector2 playerPosition = playerActor->GetPosition();
	Vector2 enemyPosition = enemyActor->GetPosition();

	//Enemy이미지의 크기는 5*5, 하드코딩으로 범위 지정
	for (int yPos = enemyPosition.y; yPos < enemyPosition.y + 5; yPos++) {
		if(enemyPosition.x + 1 <= playerPosition.x + 1 <= enemyPosition.x + 4){
		
		}
	}

}
