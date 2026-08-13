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

		//플레이어를 제외한 액터들을 순회하며 플레이어와 충돌 여부 확인
		void CheckCollision(const std::vector<std::shared_ptr<Actor>>& actorList);
	};
}

