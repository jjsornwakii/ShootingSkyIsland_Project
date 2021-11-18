#include "Background.h"

void Background::setBG() {
	backgroundText.loadFromFile("res/pic/bg.png");
	bg.setSize(sf::Vector2f(1920,1080));
	bg.setTexture(&backgroundText);
	
	Skybackground.loadFromFile("res/pic/sky.png");
	skybg.setSize(sf::Vector2f(1920, 1080));
	skybg.setTexture(&Skybackground);

	modelTexture.loadFromFile("res/pic/model.png");
	sf::Vector2u size = modelTexture.getSize();
	model.setSize(sf::Vector2f(size));
	model.setTexture(&modelTexture);
	model.setPosition(70,100);

	MainModel.loadFromFile("res/pic/bgmain.png");
	sf::Vector2u size1 = MainModel.getSize();

	mainModelbg.setSize(sf::Vector2f(size1));
	mainModelbg.setTexture(&MainModel);
	mainModelbg.setPosition(900, 379);

	logoTexture.loadFromFile("res/pic/logo.png");
	sf::Vector2u size2 = logoTexture.getSize();

	Logo.setSize(sf::Vector2f(size2));
	Logo.setTexture(&logoTexture);
	Logo.setPosition(15, 20);

	F.loadFromFile("res/font/MyFont.ttf");
	name.setFillColor(sf::Color::Black);
	name.setCharacterSize(40);
	name.setString("Siwakorn Suriya\n64010850");
	name.setPosition(1600, 10);
	name.setFont(F);

}

void Background::animation(sf::RenderWindow* window) {
	
	getTime = time.getElapsedTime().asMilliseconds();
	if (getTime >= 1500) {
		getTime = time.restart().asMilliseconds();
		dir = !dir;
	}

	if (int(getTime)%5==0) {
		if (dir == 0)
			model.move(0, -.1f);

		if (dir == 1)
			model.move(0, .1f);
	}
	window->draw(model);
}