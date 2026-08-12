#include <Engine/Engine.h>
#include <Level/TestLevel.h>
#include <Util/Util.h>

int main()
{
	Craft::Engine engine;
	Util::SetRandomSeed();
	engine.AddNewLevel<TestLevel>();
	engine.Run();
}