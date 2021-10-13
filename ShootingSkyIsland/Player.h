#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <conio.h>

class Player
{
public:
	sf::RectangleShape player;
	sf::Texture charactorPlayer;
	sf::Vector2u TextureSize;
	sf::Clock playerClock;
	sf::Vector2f vec;

	float speed=1;
	float leng;
	float moveX, moveY;
	

	int currentX=0,currentY=0;
	bool switchAnimationState;
	int dirX=0;
	float getTime=0;

private:


public :
	void initPlayer(float posX,float posY);
	void PlayerControl();
	void PlayerAnimation(float deltaTime);
	
};

