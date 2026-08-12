#pragma once

#include <Core/Core.h>
#include <Math/Vector2.h>
#include <Math/Color.h>

#include <memory>
#include <string>

namespace Craft
{
	class Level;

	class CRAFT_API Actor
	{
	public:
		Actor(const std::string& image ="", const Vector2& position = Vector2::Zero, Color color = Color::White);
		virtual ~Actor();

		//게임 플레이 이벤트 함수
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void Destroy();

		void QuitGame();

		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return isActive; }
		inline bool HasExpired() const { return hasExpired; }

		//오너를 레벨 객체이고 레벨 객체는 shared_ptr이므로 weak_ptr인 owner를 형변환
		inline std::shared_ptr<Level> GetOwner() const { return owner.lock(); }
		inline void SetOwner(std::weak_ptr<Level> newOwner) { owner = newOwner; }

		inline Vector2 GetPosition() const { return position; }
		void SetPosition(const Vector2& newPosition);

		Vector2 GetScreenSize() const;
		
		inline int GetTypeId() const { return typeId; }
		
		inline void SetTypeId(int newTypeId) { typeId = newTypeId; }

		inline void SetImage(std::string newImage) { image = newImage; }

		std::string LoadImageFromFile(const std::string& fileName, const std::string& fileFolder);

	protected:
		//BeginPlay 이벤트 처리 여부
		bool hasBeganPlay = false;

		bool isActive = true;

		bool hasExpired = false;

		std::shared_ptr<Level> mainLevel;

		std::shared_ptr<Level> nextLevel;

		//액터를 소유하는 레벨 객체
		std::weak_ptr<Level> owner;

		std::string image;
		
		Color color = Color::White;

		int width = 0;

		int sortingOrder = 0;
		
		//typeId 0 = Actor type
		int typeId = 0;

		Vector2 position;
	};
}

