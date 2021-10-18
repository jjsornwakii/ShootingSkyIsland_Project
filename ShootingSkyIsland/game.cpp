#include <SFML\Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "game.h"
#include "Player.h"
#include "time.h"


Player P;
Enemy En;



void game::run()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shooting Sky Island!", sf::Style::Close | sf::Style::Resize);
    int numBullet = 20;
    int numEnemy = 5;
    int nE = numEnemy;
    // var test
    

    // player
    P.initPlayer(window.getSize().x/2, window.getSize().y/2);
    
    // Random
    srand(time(NULL));

    for (int i = 0; i < numEnemy;i++) {
        En.initEnimy(i);
    }

    //spawn 
    /*
    for (int i = 0; i < 5; i++) {
        if (rand() % 2 == 0) {
            En.setSpawn((float)(0 + rand() % (1920)), (float)(0), i);
        }
        else {
            En.setSpawn((float)(0 + rand() % (1920)), (float)(900), i);
        }
        
    }
*/

    while (window.isOpen()) {

        window.clear();

        sf::Event EVNT;
        while (window.pollEvent(EVNT)) {
            switch (EVNT.type) {
            case sf::Event::Closed: window.close(); break;
            case sf::Event::Resized: std::cout << EVNT.size.width << "     " << EVNT.size.height << std::endl; break;   
            }
        }

        // spawn
        for (int i = 0; i < numEnemy; i++) {
            if (En.E[i].EnemyState == false) {
                if (rand() % 2 == 0) {
                    En.setSpawn((float)(0 + rand() % (1920)), (float)(0), i);
                }
                else {
                    En.setSpawn((float)(0 + rand() % (1920)), (float)(900), i);
                }
                En.E[i].hpEnemy = 500.0f;
                En.E[i].EnemyState = true;
            }
        }



        
        // UPDATE BULLET

        P.UpdateBullet(sf::Vector2f(sf::Mouse::getPosition(window)),numBullet);
        

        // bullet conllision
        for (int i = 0; i < numBullet; i++) {
            for (int j = 0; j < numEnemy; j++) {
                if (P.B[i].bulletShape.getGlobalBounds().intersects(En.E[j].setEneny.getGlobalBounds()) && P.B[i].state == true && En.E[j].EnemyState == true) {
                    //std::cout << "SHOT!" << std::endl;
                    P.B[i].state = false;
                    En.E[j].hpEnemy -= 45;

                    if(En.E[j].hpEnemy<=0)
                        En.E[j].EnemyState = false;

                    
                    
                }
            }
            
        }
        

        // UPDATE PLAYER
  
        P.PlayerControl();
        P.PlayerAnimation(0.25);

        // UPDATE ENEMY
    
        En.EnemyMove(P.player.getPosition(), numEnemy); // 5 EA
        En.EnemyAnimation(0.25, numEnemy);

        //DRAW
        for (int i = 0; i < numEnemy; i++) {
            if(En.E[i].EnemyState==true)
                window.draw(En.E[i].setEneny); 
        }

        

        for (int i = 0; i < numBullet; i++) {
            if (P.B[i].state == true) {
                window.draw(P.B[i].bulletShape);
                //std::cout << i << "    B!" << std::endl;
            }
        }

        
        
        window.draw(P.player);
        window.draw(P.aimPlayer);
        window.display();
    }
   
}

