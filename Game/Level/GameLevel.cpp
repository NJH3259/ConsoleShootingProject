#include "GameLevel.h"

#include <cassert>
#include <iostream>

void GameLevel::OnInitialized()
{
	Level::OnInitialized();
	
	LoadMap("Stage.txt");
}

void GameLevel::Draw()
{
	Level::Draw();
}

void GameLevel::LoadMap(const std::string& fileName)
{
	std::string filePath = std::string("../Assets/") + fileName;
	
	FILE* file = nullptr;
	fopen_s(&file, filePath.c_str(), "rt");
	
	if (!file)
	{
		assert(false && "Can't read Stage.txt file")
	}
}
