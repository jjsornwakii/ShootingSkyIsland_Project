#include <SFML\Graphics.hpp>
#include <iostream>
#include "game.h"
#include "Player.h"

Player P;

void game::run()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shooting Sky Island!", sf::Style::Close | sf::Style::Resize);
    
    P.initPlayer(300,300);
    int checkKey=0;

    while (window.isOpen()) {

        window.clear();

        sf::Event EVNT;
        while (window.pollEvent(EVNT)) {
            switch (EVNT.type) {
            case sf::Event::Closed: window.close(); break;
            case sf::Event::Resized: std::cout << EVNT.size.width << "     " << EVNT.size.height << std::endl; break;
            
            
            
            }

            
            


        }

        P.PlayerControl();
       

        P.PlayerAnimation(0.25);

        window.draw(P.player);
        window.display();
    }
   
}

