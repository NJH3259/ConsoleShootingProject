#include "GameLevel.h"
#include <Math/Vector2.h>

#include <cassert>
#include <iostream>

using namespace Craft;
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
		assert(false && "Can't read Stage.txt file");
		return;
	}
	
	//파일 내용을 저장할 버퍼 확인 후 파일 길이 확인
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	
	//파일 제일 끝위치 구한 후 처음으로 이동
	rewind(file);

	//파일을 저장할 버퍼
	char* buffer = new char[fileSize] {};
	
	//파일 읽기
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	assert(readSize > 0 && "No data in the file");

	delete[] buffer;
	buffer = nullptr;

	fclose(file);
}
