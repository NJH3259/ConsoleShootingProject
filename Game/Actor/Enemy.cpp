#include "Enemy.h"

using namespace Craft;
Enemy::Enemy(const Craft::Vector2& position)
    :Actor("@", position, Color::Green)
{
    typeId = 2; //type id 2 = enemy
    sortingOrder = 3;
}

Enemy::Enemy(std::string& image, Craft::Vector2& position)
    :Actor(image, position, Color::Green)
{
    typeId = 2; //type id 2 = enemy
    sortingOrder = 3;
    timer.SetTargetTime(5.0f); //4초 후 자동으로 객체 삭제
}

void Enemy::Tick(float deltaTime)
{
    TIME_OUT;

    Actor::Tick(deltaTime);
    
    timer.Tick(deltaTime);

    //적 객체 삭제 1.5초 전 색 변화로 얼마 안남음 안내
    if (timer.GetElapsedTime() >= 3.5f) {
        this->color = Color::Blue;
    }
    
    if (!timer.IsTimeOut())
    {
        return;
    }
    
    timer.Reset();
    
    //설정한 타이머 시간이 되면 본 객체를 삭제
    this->Destroy();
}
