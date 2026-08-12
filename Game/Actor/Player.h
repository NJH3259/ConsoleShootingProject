#pragma once

#include <Actor/Actor.h>

class Player : public Craft::Actor
{
public:
	Player();
	Player(const std::string& image);
	virtual void Tick(float deltaTime) override;
};

