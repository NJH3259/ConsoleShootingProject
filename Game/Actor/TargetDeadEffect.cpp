#include "TargetDeadEffect.h"
#include <Util/Util.h>

using namespace Craft;
TargetDeadEffect::TargetDeadEffect(const Vector2& position)
{
	image = Util::LoadImageFromFile("EnemyDead.txt", "../Assets/");
	color = Color::Red;
	this->position = position;
	sortingOrder = 2;
	typeId = 9;

	lifeTime.SetTargetTime(1.0f);
}

void TargetDeadEffect::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	lifeTime.Tick(deltaTime);

	if (!lifeTime.IsTimeOut()) {
		return;
	}

	this->Destroy();
}


