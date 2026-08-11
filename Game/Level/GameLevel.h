#pragma once
#include <Level/Level.h>
#include <string>

class GameLevel : public Craft::Level
{
private:
	//레벨 초기화
	virtual void OnInitialized() override;
	
	//레벨 그리기
	virtual void Draw() override;
	
	//파일로부터 맵 불러오기
	void LoadMap(const std::string& fileName);
	
private:
	//스테이지 제한시간
	float timeLimit = 0.0f;
	
	//스테이지에서 달성한 점수
	int score = 0;
	
	//게임 종료 여부
	bool isGameOver = false;
};

