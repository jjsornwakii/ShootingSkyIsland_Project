#pragma once
#include <SFML\Graphics.hpp>


class Background
{
public:
	sf::Texture backgroundText;
	sf::RectangleShape bg;

	sf::Texture Skybackground;
	sf::RectangleShape skybg;

	sf::Texture modelTexture;
	sf::RectangleShape model;
	int dir = 0;

	sf::Clock time;
	float getTime;

	sf::Texture MainModel;
	sf::RectangleShape mainModelbg;

	sf::Texture logoTexture;
	sf::RectangleShape Logo;

	sf::Text name;
	sf::Font F;

	void setBG();
	void cloudMove();
	void animation(sf::RenderWindow* );
};

