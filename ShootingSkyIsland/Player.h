#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <conio.h>
#include "Enemy.h"

class Player:public Enemy
{
public:
	sf::RectangleShape player;
	sf::Texture charactorPlayer;
	sf::Vector2u TextureSize;
	sf::Clock playerClock,delayShoot;
	sf::Vector2f vec;

	// player status
	int weaponSelect = 0;
	float speed = 1;
	float vectorSpeed;
	float leng;
	float moveX, moveY;
	float hp = 3;
	

	int currentX=0,currentY=0;
	bool switchAnimationState;
	int dirX=0;
	float getTime=0;
	float getTimeDelay = 0;

	sf::CircleShape aimPlayer;

	//bullet

	sf::Vector2f MousePositonWindow;
	sf::Vector2f playerCenter;
	int nBullet=0;


	struct Heart {
		sf::CircleShape bulletShape;
		bool state = false;
	};
	Heart HP[5];


	struct bullet {
		sf::CircleShape bulletShape;
		sf::Vector2f aimDir;
		sf::Vector2f aimDirNorm;
		sf::Vector2f currVelocity;
		float maxSpeed = 0.25;
		bool state=false;
	};
	bullet B[20];

public :
	void initPlayer(float posX,float posY);
	void HpPlayer();
	void PlayerControl();
	void PlayerAnimation(float deltaTime);
	void UpdateBullet(sf::Vector2f MousePos,int numBullet);

	

};
