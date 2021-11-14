#include "UI.h"

void UI::HPinit() {
	HPplayer = 100;
	HP.setFillColor(sf::Color::Green);
	HP.setSize(sf::Vector2f(500, 30));
	HP.setPosition(10, 10);
}

void UI::initButton() {

	mainButton.loadFromFile("res/pic/menuButton.png");
	buttonSize = mainButton.getSize();


	PlayButton.setTexture(&mainButton);
	PlayButton.setSize(sf::Vector2f(400,195));
	PlayButton.setTextureRect(sf::IntRect(0, 0, buttonSize.x , buttonSize.y/3));
	PlayButton.setPosition(200,200);


	ScoreButton.setTexture(&mainButton);
	ScoreButton.setSize(sf::Vector2f(400, 195));
	ScoreButton.setTextureRect(sf::IntRect(0, buttonSize.y/3, buttonSize.x, buttonSize.y / 3));	//(sf::IntRect(0, buttonSize.y, buttonSize.x, buttonSize.y/3))
	ScoreButton.setPosition(200, 400);

	ExitButton.setTexture(&mainButton);
	ExitButton.setSize(sf::Vector2f(400, 195));
	ExitButton.setTextureRect(sf::IntRect(0, buttonSize.y*2/3, buttonSize.x, buttonSize.y/3));
	ExitButton.setPosition(200,  600);
}

void UI::SCOREinit() {
	score = 0;
	Number.loadFromFile("res/pic/number.png");
	Ssize = Number.getSize();
	for (int i = 0; i < 6; i++) {
		SCORE[i].setPosition(1850 - (60 * i), 10);
		SCORE[i].setSize(sf::Vector2f(40, 60));
		SCORE[i].setTexture(&Number);
		SCORE[i].setTextureRect(sf::IntRect(0, 0, Ssize.x / 10, Ssize.y));
	}
}

void UI::SCOREchange(int sc) {
	score += sc;
	
	for (int i = 0; i < 6; i++) {
		s[i] = (score / int(pow(10, i)) % 10);
		SCORE[i].setTextureRect(sf::IntRect(Ssize.x / 10 * s[i] , 0, Ssize.x / 10, Ssize.y));
		std::cout << s[i] << std::endl;
	}
}

void UI::HPchange(float change) {

	HPplayer += change;

	if (HPplayer > 100)
		HPplayer = 100;

	HP.setSize(sf::Vector2f(HPplayer*500/100, 30));
}

void UI::getbuScore() {
	

	std::ifstream f;
	f.open("score.txt");
	std::string str;
	int i=0;
	int j = 0;

	while (f >> str) {
		if (i % 2 == 0) {
			backup[j].buName = str;
			
		}
		else {
			
			backup[j].buScore = str;

			int len = backup[j].buScore.length();
			int s = 0;
			for (int k = 0; k < len; k++) {
				if (s == 0) {
					backup[j].score += backup[j].buScore[k] - 48;
					s = 1;
				}
				else {
					backup[j].score *= 10;
					backup[j].score += backup[j].buScore[k] - 48;
				}
			}
			std::cout << backup[j].buName << " ";
			std::cout << backup[j].buScore << std::endl;
			j++;
		}
		std::cout << i << std::endl;
		i++;
	}
	
	f.close();
	/*
	for (int j = 0; j < ((i+1)/2); j++) {		
		std::cout << backup[j].buName << " ";
		std::cout << backup[j].buScore << std::endl;
	}
	*/
	LineNumber = i+1;
}



void UI::sortScore() {
	for (int i=0; i <= LineNumber/2; i++) {
		
		for (int j=0; j < LineNumber/2; j++) {

			if (backup[j].buName != "\0" ) {

				if (backup[j].score < backup[j + 1].score) {
					
					int tempS = backup[j + 1].score;
					backup[j + 1].score = backup[j].score;
					backup[j].score = tempS;

					std::string tempStr;
					tempStr = backup[j + 1].buScore;
					backup[j + 1].buScore = backup[j].buScore;
					backup[j].buScore = tempStr;

					std::string tempN = backup[j + 1].buName;
					backup[j + 1].buName = backup[j].buName;
					backup[j].buName = tempN;
				}
				
			}
		}
	}



	std::cout << "----------------" << std::endl;
	for (int j = 0; j < 10; j++) {
		if (backup[j].buName != "\0") {

			std::cout << backup[j].buName << " ";
			std::cout << backup[j].score << std::endl;
		}
	}
}

void UI::showTopScore(sf::RenderWindow* window)
{
	sf::Font font;
	font.loadFromFile("res/font/MyFont.ttf");
	sf::Text Banner;
	Banner.setFont(font);
	Banner.setPosition(700, 0);
	Banner.setString("TOP 10 SCORE !");
	Banner.setCharacterSize(70);
	Banner.setFillColor(sf::Color::Yellow);
	Banner.setStyle(sf::Text::Bold);

	

	window->draw(Banner);

	for (int i = 0; i < 10; i++) {
		backup[i].N.setFont(font);
		backup[i].N.setCharacterSize(70);
		backup[i].N.setFillColor(sf::Color::Yellow);
		backup[i].N.setString(backup[i].buName);

		backup[i].S.setFont(font);
		backup[i].S.setCharacterSize(70);
		backup[i].S.setFillColor(sf::Color::Yellow);
		backup[i].S.setString(backup[i].buScore);

		number.setFont(font);
		number.setCharacterSize(70);
		number.setFillColor(sf::Color::Yellow);
		
	}

	for (int i = 0; i < 10; i++) {

		if (i != 9) {
			
			number.setString(char(i + '0' + 1));
		}
		else
		{
			number.setString("10");
		}
		number.setPosition(300, 200 + (i * 80));
		window->draw(number);

		backup[i].N.setPosition(500, 200+(i*80));
		window->draw(backup[i].N);

		backup[i].S.setPosition(1300, 200 + (i * 80));
		window->draw(backup[i].S);

	}


}
