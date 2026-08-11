#include "GameLevel.h"
#include <Actor/Player.h>

void GameLevel::OnInitialized()
{
	Level::OnInitialized();

	//레벨에 테스트 액터 추가
	SpawnActor<Player>();
	//SpawnActor<Level>(); //정의에서 T타입으로 Actor의 하위 구문이어야 한다는 조건 때문에 SpawnActor<Level>은 호출 불가
}