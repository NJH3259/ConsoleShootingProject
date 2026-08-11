#pragma once

#include <Actor/Actor.h>

class Player : public Craft::Actor
{
public:
	Player();
	virtual void Tick(float deltaTime) override;
};

