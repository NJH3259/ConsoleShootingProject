#include "Enemy.h"

using namespace Craft;
Enemy::Enemy(const Craft::Vector2& position)
    :Actor("@", position, Color::Green)
{
    lifeTime.SetTargetTime(5.0f);
}

Enemy::Enemy(std::string image, const Craft::Vector2& position, Craft::Color color, int typeId)
{
    this->image = image;
    this->position = position;
    this->color = color;
    this->typeId = typeId;

    lifeTime.SetTargetTime(5.0f);
}

void Enemy::Tick(float deltaTime)
{
    TIME_OUT;

    Actor::Tick(deltaTime);
    
    lifeTime.Tick(deltaTime);

    //적 객체 삭제 1.5초 전 색 변화로 얼마 안남음 안내
    if (this->typeId == 2 && lifeTime.GetElapsedTime() >= 3.5f) {
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
