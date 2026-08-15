#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class  Enemy : public Craft::Actor
{
public:
    Enemy(const Craft::Vector2& position);

private:
    virtual void Tick(float deltaTime) override;
    
private:
    Timer lifeTime;
};
