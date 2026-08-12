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
    timer.SetTargetTime(4.0f); //4초 후 자동으로 객체 삭제
}

void Enemy::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
    
    timer.Tick(deltaTime);
    
    if (!timer.IsTimeOut())
    {
        return;
    }
    
    timer.Reset();
    
    //설정한 타이머 시간이 되면 본 객체를 삭제
    this->Destroy();
    
    //todo: 실제 테스트 돌려봐야함
}
