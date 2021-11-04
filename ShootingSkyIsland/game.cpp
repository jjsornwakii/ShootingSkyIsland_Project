#include "game.h"


sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shooting Sky Island!", sf::Style::Close | sf::Style::Resize);

sf::CircleShape MousePointer(5);


Background BG;
Player P;
Enemy En;
item Item;

int SelectMenu = 0;
bool pauseMenu = false;
bool lastStatePause;
bool StatePause = false;
long float deBouTime=0;


long float ItemTime = 0;
sf::Clock deBou;



bool itemActivate[2];


void game::run()
{
    

    sf::Font font;
    font.loadFromFile("res/font/MyFont.ttf");
    sf::Text Banner;
    Banner.setFont(font);
    Banner.setString("PLAY!");
    Banner.setCharacterSize(50);
    Banner.setFillColor(sf::Color::Red);
    Banner.setStyle(sf::Text::Bold );
    
    
    Banner.setPosition(sf::Vector2f(300.f,300.f));
    

    sf::Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("Exit");
    pauseText.setCharacterSize(60);
    pauseText.setFillColor(sf::Color::Blue);
    pauseText.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    


    int checkEnemy = 0;
    int countEnemy = 0;
    int numBullet = 20;
    int numEnemy = 5;
    int nE = numEnemy;
    // var test
    

    // Background
    BG.setBG();

    // player
    P.initPlayer(window.getSize().x/2, window.getSize().y/2);
    Item.initItem();


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
        MousePointer.setPosition(sf::Vector2f(sf::Mouse::getPosition()));
        window.clear();

        sf::Event EVNT;
        while (window.pollEvent(EVNT)) {
            switch (EVNT.type) {
            case sf::Event::Closed: window.close(); break;
            case sf::Event::Resized: std::cout << EVNT.size.width << "     " << EVNT.size.height << std::endl; break;   
            }
        }

        if (SelectMenu == 1) {

            if (pauseMenu == false) {
                // spawn
                for (int i = 0; i < numEnemy; i++) {
                    if (En.E[i].EnemyState == false /* && countEnemy < 20*/) {
                        if (rand() % 2 == 0) {
                            En.setSpawn((float)(0 + rand() % (1920)), (float)(0), i);
                        }
                        else {
                            En.setSpawn((float)(0 + rand() % (1920)), (float)(900), i);
                        }
                        En.E[i].hpEnemy = 500.0f;
                        En.E[i].EnemyState = true;
                        En.E[i].EnemyMoveState = true;
                        countEnemy++;
                    }
                }




                // UPDATE BULLET

                P.UpdateBullet(sf::Vector2f(sf::Mouse::getPosition(window)), numBullet);


                // bullet conllision
                for (int i = 0; i < numBullet; i++) {
                    for (int j = 0; j < numEnemy; j++) {
                        if (P.B[i].bulletShape.getGlobalBounds().intersects(En.E[j].setEneny.getGlobalBounds()) && P.B[i].state == true && En.E[j].EnemyState == true) {
                            //std::cout << "SHOT!" << std::endl;
                            P.B[i].state = false;
                            En.E[j].hpEnemy -= 45;

                            if (En.E[j].hpEnemy <= 0) {
                                En.E[j].EnemyState = false;
                                
                                int randNum = rand() % 10;
                                
                                if(randNum >=0 && randNum <=3)
                                    Item.randomItem(randNum, En.E[j].setEneny.getPosition());
                            }
                            En.E[j].EnemyMoveState = false;


                        }
                        else
                            En.E[j].EnemyMoveState = true;
                    }

                    // get droped item

                    for (int i = 0; i < 5; i++) {
                        if (P.player.getGlobalBounds().intersects(Item.med[i].medic.getGlobalBounds())&& Item.med[i].itemState == true) {
                            Item.med[i].itemState = false;
                        }
                    }

                    for (int i = 0; i < 2; i++) {
                        if (P.player.getGlobalBounds().intersects(Item.crys[i].crystal.getGlobalBounds()) && Item.crys[i].itemState == true) {
                            Item.crys[i].itemState = false;

                            Item.CrystalActivate = true;

                            Item.CryTime = Item.CrystalDelay.restart().asSeconds();
                            Item.CryTime = 0.f;
                        }
                    }


                }

                

                // UPDATE PLAYER

                P.PlayerControl();
                P.PlayerAnimation(0.25);

                // UPDATE ENEMY

                if (Item.CrystalActivate == true) {
                    Item.CryTime = Item.CrystalDelay.getElapsedTime().asSeconds();
                
                    if (Item.CryTime <= 5.f) {
                        for (int i = 0; i < 5; i++)
                            En.E[i].speed = 0.2f;
                        
                    }
                    else {
                        for (int i = 0; i < 5; i++)
                            En.E[i].speed = 0.4f;

                       
                        Item.CrystalActivate = false;
                    }
                }


                // Collison

                for (int i = 0; i < numEnemy; i++) {

                    if (En.E[i].setEneny.getGlobalBounds().intersects(P.player.getGlobalBounds()) == false) {

                        En.EnemyMove(P.player.getPosition(), numEnemy, i); // 5 EA
                        
                        En.E[i].EnemyMoveState = true;
                    }
                }

                

                En.EnemyAnimation(0.25, numEnemy);

                if (countEnemy == 20) {
                    for (int i = 0; i < numEnemy; i++) {
                        if (En.E[i].EnemyState == true) {
                            checkEnemy = 0;
                            break;
                        }
                        else
                            checkEnemy = 1;
                    }
                    if (checkEnemy == 1)
                        SelectMenu = 0;
                }

            }

                //DRAW

                window.draw(BG.bg);




                
                // draw item random

                

                





                for (int i = 0; i < numEnemy; i++) {

                    if (P.player.getPosition().y > En.E[i].setEneny.getPosition().y) {
                        if (En.E[i].EnemyState == true) {

                            window.draw(En.E[i].setEneny);

                        }
                    }

                    window.draw(P.player);

                    if (P.player.getPosition().y < En.E[i].setEneny.getPosition().y) {
                        if (En.E[i].EnemyState == true) {

                            window.draw(En.E[i].setEneny);

                        }
                    }
                }
                
                // draw Item

                for (int i = 0; i < 5; i++) {
                    if (Item.med[i].itemState == true)
                        window.draw(Item.med[i].medic);
                    
                }
                for (int i = 0; i < 2; i++) {
                    if (Item.crys[i].itemState == true)
                        window.draw(Item.crys[i].crystal);

                }
                for (int i = 0; i < 3; i++) {
                    if (Item.bom[i].itemState == true) {
                        window.draw(Item.bom[i].bomb);
                    }
                }
                
                
                for (int i = 0; i < numBullet; i++) {
                    if (P.B[i].state == true) {
                        window.draw(P.B[i].bulletShape);
                        
                    }
                }

                

                
            /*
            window.draw(P.player);
            window.draw(P.aimPlayer);
            */
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                
                    if (deBou.getElapsedTime().asMilliseconds() > 500.f) {
                        deBouTime = deBou.restart().asMilliseconds();
                        pauseMenu = !pauseMenu;
                    }
                
                
            }

            // Game over

            if (P.hp <= 0) {//////////////////////////////////////////////////////////////
                SelectMenu = 0;
            }


            if (pauseMenu == true) {
                window.draw(pauseText);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (pauseText.getGlobalBounds().intersects(MousePointer.getGlobalBounds())) {
                        SelectMenu = 0;
                    }
                }

            }

            
        }


        else if (SelectMenu == 0) {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                
                if (Banner.getGlobalBounds().intersects(MousePointer.getGlobalBounds())) {

                    SelectMenu = 1;
                    pauseMenu = false;
                    checkEnemy = 0;
                    countEnemy = 0;
                    


                    /////////////// Reset MainMenu

                    for (int i = 0; i < 5; i++) {
                        if (rand() % 2 == 0) {
                            En.setSpawn((float)(0 + rand() % (1920)), (float)(0), i);
                        }
                        else {
                            En.setSpawn((float)(0 + rand() % (1920)), (float)(900), i);
                        }
                        En.E[i].hpEnemy = 500.0f;
                        En.E[i].EnemyState = true;
                        countEnemy++;
                    }
                    for (int i = 0; i < numBullet; i++) {
                        P.B[i].state = false;
                    }

                }
                MousePointer.setPosition(0.0f, 0.0f);
            }

            

            window.draw(Banner);
        }







        window.display();
    }
   
}

