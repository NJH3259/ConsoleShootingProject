#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class Player : public Craft::Actor
{
public:
	Player();
	//Player(const std::string& image);
	virtual void Tick(float deltaTime) override;

private:
	void Shoot();
	void Reload();

private:
	int bulletCount;
	const int maxBullet = 6;

	bool isShootable = true;
	
	std::string idleImage;
	std::string shotImage;

	Timer reloadTimer;
	Timer shotDelay;
};

