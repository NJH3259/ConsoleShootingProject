#pragma once

#include <Actor/Actor.h>

#include <memory>
#include <vector>

namespace Craft
{
	//게임에 배치된 모든 액터를 관리하는 클래스
	class Level : public std::enable_shared_from_this<Level>
	{
	public:
		Level();
		virtual ~Level();

		virtual void OnInitialized();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		//액터 추가 함수
		//Level이 여러 Actor를 관리하므로 Actor들을 shared_ptr로 생성
		template<typename T, typename ...Args, typename = std::enable_if<std::is_base_of<Actor, T>::value>>
		std::shared_ptr<T> SpawnActor(Args&& ...args) 
		{
			//인자로 R-Value Ref, L-Value Ref모두 올 수 있으므로 원래 값을 가져오기 위해 forward 선언
			std::shared_ptr<T> newActor = std::make_shared<T>(std::forward<Args>(args)...);

			addRequestedActorList.emplace_back(newActor);

			newActor->SetOwner(weak_from_this());

			return newActor;
		}

		template<typename T,
			typename = std::enable_if_t<std::is_base_of<Actor, T>::value>>
			std::shared_ptr<T> FindActor()
		{
			for (const auto& actor : actorList)
			{
				// T 타입으로 형변환 시도, T타입 아닌 경우 null 반환
				std::shared_ptr<T> targetActor
					= std::dynamic_pointer_cast<T>(actor);
				if (targetActor)
				{
					return targetActor;
				}
			}
			// 못찾은 경우 null 반환.
			return nullptr;
		}

		inline bool HasInitialized() const { return hasInitialized; }

	protected:
		void ProcessAddAndDestroy();

	protected:
		bool hasInitialized = false;

		//레벨에 배치된 모든 액터
		std::vector<std::shared_ptr<Actor>> actorList;

		//추가 요청된 액터를 저장하고 현재 프레임 모두 처리 후 생성하도록 하기 위한 목록
		std::vector<std::shared_ptr<Actor>> addRequestedActorList;
	};
}

