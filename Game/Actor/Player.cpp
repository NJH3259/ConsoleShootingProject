#include "Player.h"
#include <iostream>
#include <Input/Input.h>
#include <Windows.h>

using namespace Craft;
Player::Player() : Actor("p", Vector2(10, 10), Color::White) {
	image = LoadImageFromFile("Player.txt", "../Assets/");
	sortingOrder = 10;
}

Player::Player(const std::string& image)
	:Actor(image, position, Color::White)
{
	sortingOrder = 10;
}

void Player::Tick(float deltaTime) {
	Actor::Tick(deltaTime);
	
	//if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0) {
		//엔진 종료 처리
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}

	//방향키 이동 처리
	//@Temp: 프레임시간 고려는 나중에
	if (Input::Get().GetKey(VK_LEFT) && position.x > 0) {
		position.x -= 2;
	}

	if (Input::Get().GetKey(VK_RIGHT) && position.x < GetScreenSize().x) {
		position.x += 2;
	}

	if (Input::Get().GetKey(VK_UP) && position.y > 0) {
		position.y -= 1;
	}

	if (Input::Get().GetKey(VK_DOWN) && position.y < GetScreenSize().y) {
		position.y += 1;
	}
}