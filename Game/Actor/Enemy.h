#pragma once

#include <Actor/Actor.h>

class  Enemy : public Craft::Actor
{
public:
    Enemy(const Craft::Vector2& position);
    Enemy(std::string& image, Craft::Vector2& position);
};
