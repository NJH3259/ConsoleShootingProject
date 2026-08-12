#pragma once

#include <Actor/Actor.h>
class Cover : public Craft::Actor
{
public:
    //type Id 3 = Cover, 0 = Actor
    Cover(const Craft::Vector2 position);
};
