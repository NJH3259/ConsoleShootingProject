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

	//플레이어 액터에 어떤 액터가 플레이어 액터와 충돌한 상태인지 vector에 저장
	for (int idx = 0; idx < actorCount; idx++) {
		if (actorList[idx]->GetTypeId() == 1) {
			continue;
		}

		std::shared_ptr<Actor> collidedActor = actorList[idx];
		CheckCollision(collidedActor);
	}

	//충돌중인(겹치는 위치인)액터 중 하나라도 cover가 있다면 적을 제거할 수 없음
	for (auto actor : playerActor->GetCollisionList()) {
		if (actor->GetTypeId() == 3) {
			playerActor->GetCollisionList().clear();
			return;
		}
	}

	//충돌중인 액터 중 cover가 없다면 사격 위치의 액터 모두 제거
	for (auto actor : playerActor->GetCollisionList()) {
		actor->Destroy();
	}

	//플레이어 액터의 충돌 목록 비우기(매 사격마다 새로 탐색하기 위함)
	playerActor->GetCollisionList().clear();
}

//엑터가 플레이어와 충돌했는지 여부 검사
void Craft::CollisionSystem::CheckCollision(std::shared_ptr<Actor>& collidedActor)
{
	Vector2 playerPosition = playerActor->GetPosition();
	Vector2 collidedPosition = collidedActor->GetPosition();

	//y축 길이 계산
	int lengthY = 1;
	std::string collidedImage = collidedActor->GetImage();
	//개행문자 개수로 y축 길이 계산
	for (int idx = 0; idx < collidedImage.length(); idx++) 
	{
		if (collidedImage[idx] == '\n') {
			lengthY += 1;
		}
	}

	//x축 길이 계산 (전제: 액터 이미지에서 모든 y좌표의 x축 길이는 동일하다)
	//(전체길이 - (개항문자 개수)) / y축 길이
	int lengthX = (collidedImage.length() - (lengthY - 1)) / lengthY;

	//플레이어가 Enemy의 y위치 밖에 있으면 절대 겹치지 않음(플레이어는 한줄이므로)
	if(collidedPosition.y > playerPosition.y || collidedPosition.y + (lengthY - 1) < playerPosition.y)
	{
		return;
	}

	//플레이어의 x+2(중앙)의 위치가 다른 액터의 x좌표 중 x와 x+(x의 길이-1) 제외하고 겹치면 충돌이라고 판정
	if (collidedPosition.x <= playerPosition.x + 2 && playerPosition.x + 2 <= collidedPosition.x + lengthX) {
		playerActor->GetCollisionList().emplace_back(collidedActor);
	}

	return;
}
