#include "Enemy.h"

using namespace Craft;
Enemy::Enemy(const Craft::Vector2& position)
    :Actor("@", position, Color::Green)
{
    image = Util::LoadImageFromFile("Enemy.txt", "../Assets/");
    typeId = 2; //type id 2 = enemy
    sortingOrder = 3;
    lifeTime.SetTargetTime(5.0f);
}

void Enemy::Tick(float deltaTime)
{
    TIME_OUT;

    Actor::Tick(deltaTime);
    
    lifeTime.Tick(deltaTime);

    //적 객체 삭제 1.5초 전 색 변화로 얼마 안남음 안내
    if (lifeTime.GetElapsedTime() >= 3.5f) {
        this->color = Color::Blue;
    }
    
    if (!lifeTime.IsTimeOut())
    {
        return;
    }
    
    lifeTime.Reset();
    
    //설정한 타이머 시간이 되면 본 객체를 삭제
    this->Destroy();
}
