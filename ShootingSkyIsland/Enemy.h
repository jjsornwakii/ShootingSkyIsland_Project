#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <conio.h>

class Enemy
{

public:
	
	sf::Texture EnenyCharactor;
	sf::Vector2u EnenyTextureSize;
	sf::Vector2f vec;

	int i = 0;
	int EnemyNumber=20;

	sf::Clock EnemyClock;
	float bounchTime = 0;
	struct enemy
	{
		sf::RectangleShape setEneny;
		sf::Vector2f position;
		sf::Vector2f vec;
		sf::Vector2u current;
		

		//staus
		int animationDir = 0;
		bool animationstate = 0;
		float speed = 0.4f;
		float vectorSpeed;
		float leng;

		float hpEnemy = 500.0f;
		bool EnemyState =false;
	};

	enemy E[5];

	void initEnimy(int i);
	void setSpawn(float x,float y,int i);
	void EnemyMove(sf::Vector2f PlayerPos,int nEnemy);
	void EnemyAnimation(float deltaTime,int nEnemy);

};

