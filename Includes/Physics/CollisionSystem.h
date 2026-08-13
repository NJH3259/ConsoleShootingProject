#pragma once

#include <vector>
#include <memory>

namespace Craft
{
	class Actor;

	class CollisionSystem
	{
	public:
		CollisionSystem() = default;
		~CollisionSystem() = default;

		//플레이어를 제외한 액터들을 순회하며 Enemy액터를 탐색하고 플레이어와 충돌하는지 판단
		void ProcessCollision(const std::vector<std::shared_ptr<Actor>>& actorList);

		//Enemy객체 하나가 플레이어와 충돌하는지 검사
		void CheckCollision(std::shared_ptr<Actor>& enemyActor);

	private:
		bool isPlayerOnCover = false;
		std::shared_ptr<Actor> playerActor;
	};
}

