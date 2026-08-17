#include <Engine/Engine.h>
#include <Game/Game.h>
#include <Level/TestLevel.h>
#include <Util/Util.h>

int main()
{
	//Craft::Engine engine;
	//Util::SetRandomSeed();
	//engine.AddNewLevel<TestLevel>();
	//engine.Run();

	Game game;
	Util::SetRandomSeed();
	game.Run();
}