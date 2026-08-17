#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class TargetDeadEffect : public Craft::Actor
{
public:
	TargetDeadEffect(const Craft::Vector2& position);

private:
	virtual void Tick(float deltaTime) override;

private:
	Timer lifeTime;
};

