#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class UI
{
public:

	/// Main Menu
	sf::Texture mainButton;
	
	sf::RectangleShape PlayButton;
	
	sf::RectangleShape ScoreButton;
	
	sf::RectangleShape ExitButton;
	
	sf::Vector2u buttonSize;

	/// PlayerStatus
	sf::RectangleShape HP;
	float HPplayer = 100;

	sf::RectangleShape SCORE[6];
	sf::Vector2u Ssize;
	sf::Texture Number;
	int s[6];
	int score;

	struct BACKUP {
		int score=0;

		std::string buName;
		std::string buScore;
		
		

		sf::Text N;
		sf::Text S;
	};

	BACKUP backup[5000];
	//
	int LineNumber=0;


	sf::Text number;
	void HPinit();
	void SCOREinit();
	void SCOREchange(int);
	void HPchange(float);

	void initButton();

	void sortScore();
	void getbuScore();
	void showTopScore(sf::RenderWindow*);
	
};

