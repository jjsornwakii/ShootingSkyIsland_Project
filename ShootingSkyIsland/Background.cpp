#include "Background.h"

void Background::setBG() {
	backgroundText.loadFromFile("res/pic/bg.png");
	bg.setSize(sf::Vector2f(1920,1080));
	bg.setTexture(&backgroundText);
	
}