#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class Player : public Craft::Actor
{
public:
	Player();
	//Player(const std::string& image);
	virtual void Tick(float deltaTime) override;

	//Level에서 가져가서 UI에 표시하기 위한 Getter
	inline int GetBulletCount() const { return bulletCount; }
	inline int GetHitCounter() const { return hitCounter; }
	inline int GetScore() const { return score; }
	inline int GetKillCount() const { return killCount; }

private:
	void Shoot();
	void Reload();

private:
	int bulletCount;
	const int maxBullet = 6;
	int hitCounter = 0;

	bool isShootable = true;
	//UI로 재장전 완료 후 총알이 차는 것을 보여주기 위해 선언한 플래그
	bool wasPressedReload = false;

	int score = 0;
	int killCount = 0;
	
	std::string idleImage;
	std::string shotImage;

	Timer reloadTimer;
	Timer shotDelay;
};

