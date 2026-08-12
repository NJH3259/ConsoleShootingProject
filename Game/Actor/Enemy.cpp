#include "Enemy.h"

using namespace Craft;
Enemy::Enemy(const Craft::Vector2& position)
    :Actor("@", position, Color::Blue)
{
    SetTypeId(2); //type id 2 = enemy
    sortingOrder = 3;
}

Enemy::Enemy(std::string& image, Craft::Vector2& position)
    :Actor(image, position, Color::Blue)
{
    SetTypeId(2); //type id 2 = enemy
    sortingOrder = 3;
}
