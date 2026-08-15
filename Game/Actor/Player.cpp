#include "Player.h"
#include <Engine/Engine.h>
#include <Actor/TargetDeadEffect.h>
#include <Level/Level.h>

#include <iostream>
#include <Input/Input.h>
#include <Windows.h>

using namespace Craft;
Player::Player() : Actor("p", Vector2(10, 10), Color::White) {
	position = Vector2(((Util::GetScreenSize().x - Util::GetUIOffset())/ 2 - 2), Util::GetScreenSize().y / 2);

	idleImage = Util::LoadImageFromFile("Player.txt", "../Assets/");
	shotImage = Util::LoadImageFromFile("PlayerShot.txt", "../Assets/");
	image = idleImage;

	sortingOrder = 10;
	typeId = 1;

	score = 0;
	killCount = 0;

	bulletCount = maxBullet;

	reloadTimer.SetTargetTime(1.3f);
	//초기화 시 재장전 시간을 없애기 위한 함수 호출
	reloadTimer.SetElapsedTimer(1.3f);
	shotDelay.SetTargetTime(0.7f);
}

void Player::Tick(float deltaTime)
{

	Actor::Tick(deltaTime);

	reloadTimer.Tick(deltaTime);
	shotDelay.Tick(deltaTime);

	//ESC입력 시 일시 중지
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}

	TIME_OUT;

	//방향키 이동 처리
	if (Input::Get().GetKey('A') && position.x > 1) {
		position.x -= 2;
	}

	if (Input::Get().GetKey('D') && position.x < (Util::GetScreenSize().x - Util::GetUIOffset()) - image.length() - 2) {
		position.x += 2;
	}

	if (Input::Get().GetKey('W') && position.y > 0) {
		position.y -= 1;
	}

	if (Input::Get().GetKey('S') && position.y < Util::GetScreenSize().y - 1) {
		position.y += 1;
	}

	if (reloadTimer.IsTimeOut()) {

		//사격
		if (Input::Get().GetKeyDown('K')) {
			Shoot();
		}

		//재장전
		if (Input::Get().GetKeyDown('R')) {
			if (bulletCount < maxBullet) {
				Reload();
			}
		}
	}

	if (bulletCount <= 0) { isShootable = false; }

	//사격 딜레이가 종료된경우
	if(isShootable == false)
	{
		//사격 딜레이 이후 플레이어 조준경 원복
		if (shotDelay.IsTimeOut() && reloadTimer.IsTimeOut())
		{
			//본래 총알 채우는 것은 Reload() 내부에서 했었으나 UI의 총알 채워지는 모습을 재장전 시간이 끝나는 시점으로
			//보여주기 위해 wasPressedReload라는 플래그를 추가하고 true false를 전환하여 Tick에서 총알 채우도록 함
			if (wasPressedReload) 
			{
				bulletCount = maxBullet;
				wasPressedReload = false;
			}
			else
			{
				isShootable = true;
				if (image != idleImage) {
					image = idleImage;
					color = Color::White;
				}
			}
		}
	}
}

void Player::Shoot()
{
	//플레이어 사격
	// 남은 장탄이 있고 사격할 수 있는 상태라면
	// 1. 플레이어 이미지를 -(O)-로 변경하고 색상도 변경한다
	// 2. 플레이어 3번째 글자 자리에 Enemy가 있었다면 Enemy를 Destroy()처리하고 점수를 증가시킨다
	// 3. 플레이어 잔탄 수를 1감소시킨다
	// 4. 딜레이 시간이 끝나면 색상과 이미지를 원래대로 돌린다.
	//

	//사격 불가 시 사격 안함
	if (!isShootable) {
		return;
	}

	//잔탄 없을 시 장탄 없음을 표시
	if (bulletCount <= 0) {
		image = "Empty";
		shotDelay.Reset();
		return;
	}

	//사격 후 이미지 변경
	image = shotImage;
	color = Color::Yellow;

	//사격 시 맞은 적이 있는지 탐색
	Engine::Get().ProcessCollision();

	//맞춘 타겟이 없으면 연속 명중 보너스 초기화
	if (collisionList.empty()) 
	{
		hitCounter = 0;
		return;
	}

	for (auto collidedActor : collisionList) {
		//명중한게 적인 경우
		if(collidedActor->GetTypeId() == 2)
		{
			score += 10;
			//5연속 명중 이상 시 추가보너스 점수
			if (hitCounter >= 5) {
				score += (hitCounter - 4) * 5;
			}

			killCount += 1;
			hitCounter += 1;
		}

		//명중한게 시민인 경우
		if (collidedActor->GetTypeId() == 4) {
			score -= 50;
			hitCounter = 0;
		}

		//타격 이펙트
		Vector2 pos = collidedActor->GetPosition();

		collidedActor->Destroy();

		GetOwner()->SpawnActor<TargetDeadEffect>(pos);
	}


	//플레이어 액터의 충돌 목록 비우기(매 사격마다 새로 탐색하기 위함)
	//GetCollisionList().clear();

	bulletCount -= 1;

	isShootable = false;

	//사격 딜레이 재시작
	shotDelay.Reset();
}

void Player::Reload() {
	//장탄 최대치면 장전 안함
	if (bulletCount == maxBullet) {
		return;
	}

	isShootable = false;

	image = "-(+)-";
	color = Color::Red;

	reloadTimer.Reset();

	wasPressedReload = true;
}
