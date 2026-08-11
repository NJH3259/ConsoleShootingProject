#pragma once

#include <memory>

namespace Craft
{
	class Level;

	class Actor
	{
	public:
		Actor();
		virtual ~Actor();

		//게임 플레이 이벤트 함수
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void Destroy();

		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return IsActive; }
		inline bool HasExpired() const { return HasExpired; }

		//오너를 레벨 객체이고 레벨 객체는 shared_ptr이므로 weak_ptr인 owner를 형변환
		inline std::shared_ptr<Level> GetOwner() const { return owner.lock(); }
		inline void SetOwner(std::weak_ptr<Level> newOwner) { owner = newOwner; }

	protected:
		//BeginPlay 이벤트 처리 여부
		bool hasBeganPlay = false;

		bool isActive = true;

		bool hasExpired = false;

		std::shared_ptr<Level> mainLevel;

		std::shared_ptr<Level> nextLevel;

		//액터를 소유하는 레벨 객체
		std::weak_ptr<Level> owner;
	};
}

