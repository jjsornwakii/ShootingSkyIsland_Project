#include "game.h"


   sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shooting Sky Island!", sf::Style::Close | sf::Style::Resize);

    sf::CircleShape MousePointer(5);


    Background BG;
    Player P;
    Enemy En;
    item Item;
    UI ui;




void game::run()
{
 

    int SelectMenu = 0;
    bool pauseMenu = false;

    sf::View view = window.getDefaultView();
    
    ui.getbuScore();
    ui.sortScore();
    sf::Font font;
    font.loadFromFile("res/font/MyFont.ttf");
    sf::Text Banner;
    Banner.setFont(font);
    Banner.setString("PLAY!");
    Banner.setCharacterSize(50);
    Banner.setFillColor(sf::Color::Red);
    Banner.setStyle(sf::Text::Bold );
    
    
    Banner.setPosition(sf::Vector2f(300.f,300.f));
    
    sf::String namePlayer;
    sf::Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(60);

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
    ui.HPinit();
    ui.SCOREinit();

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
        

        sf::Event EVNT;
        while (window.pollEvent(EVNT)) {
            switch (EVNT.type) {
            case sf::Event::Closed: window.close(); break;
                /*case sf::Event::Resized: std::cout << EVNT.size.width << "     " << EVNT.size.height << std::endl;
                
                view.setSize({
                     static_cast<float>(EVNT.size.width),
                     static_cast<float>(EVNT.size.height)
                });
                window.setView(view);
                
                break;*/
            case sf::Event::EventType::KeyPressed:
                if (SelectMenu == 3) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

                    SelectMenu = 0;

                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

                    pauseMenu = !pauseMenu;

                }
                break;

            }

            if (SelectMenu == 2) {
                window.clear();



                if (EVNT.type == sf::Event::TextEntered) {
                    if (EVNT.text.unicode == 8 && namePlayer.getSize() > 0) {
                        namePlayer.erase(int(namePlayer.getSize()) - 1);
                    }
                    else
                        namePlayer += EVNT.text.unicode;

                    //printf("%c", EVNT.text.unicode);



                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        std::string temp = namePlayer;
                        std::ofstream myScore;
                        myScore.open("score.txt", std::ios::app);
                        myScore << temp;
                        myScore << ui.score << "\r";


                        myScore.close();
                        temp = "";
                        namePlayer = "";
                        //nameText.setString("");
                        SelectMenu = 0;
                        ui.getbuScore();
                        
                    }

                    
                    ui.sortScore();

                }

                nameText.setString(namePlayer);


                window.draw(nameText);

                window.display();
            }

            
        }

        if (SelectMenu == 1) {
            window.clear();
            window.draw(BG.bg);
            if (pauseMenu == false) {
                

                


                // UPDATE BULLET

                P.UpdateBullet(sf::Vector2f(sf::Mouse::getPosition(window)), numBullet);


                
                for (int i = 0; i < numBullet; i++) {
                    for (int j = 0; j < numEnemy; j++) {

                        // bullet conllision
                        if (P.B[i].bulletShape.getGlobalBounds().intersects(En.E[j].setEneny.getGlobalBounds()) && P.B[i].state == true && En.E[j].EnemyState == true) {
                            ;
                            P.B[i].state = false;
                            En.E[j].hpEnemy -= 45;
                           
                        }
                        else
                            En.E[j].EnemyMoveState = true;
 
                    }

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

                    // get droped item

                    for (int i = 0; i < 5; i++) {
                        if (P.player.getGlobalBounds().intersects(Item.med[i].medic.getGlobalBounds())&& Item.med[i].itemState == true) {
                            Item.med[i].itemState = false;
                            ui.HPchange(10.0);
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

                    for (int i = 0; i < 3; i++) {
                        // get
                        if (P.player.getGlobalBounds().intersects(Item.bom[i].bomb.getGlobalBounds()) && Item.bom[i].itemState == true && Item.bom[i].planState == false){
                            Item.bom[i].itemState = false;
                            Item.bom[i].getItemState = true;
                            Item.nBomb++;
                        }
                        
                    }

                }



                // use BOMB!!!
                Item.delayBomb = Item.BombUseDelayTime.getElapsedTime().asSeconds();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    if (Item.delayBomb > 1) {
                        //std::cout << "oooo";
                        Item.planBomb(P.player.getPosition());
                        Item.delayBomb = Item.BombUseDelayTime.restart().asSeconds();
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


                // Enemy Collison

                for (int i = 0; i < numEnemy; i++) {
                    for (int j = 0; j < 3;j ++) {
                        // bomb collision
                        if (En.E[i].setEneny.getGlobalBounds().intersects(Item.bom[j].bomb.getGlobalBounds()) == true && Item.bom[j].planState == true && Item.bom[j].itemState == true ) {

                            
                            Item.bom[j].BombActivate = true;
                            break;
                        }
                    }

                }

                
                
                

                for (int i = 0; i < numEnemy; i++) {

                    if (En.E[i].setEneny.getGlobalBounds().intersects(P.player.getGlobalBounds()) == false) {

                        En.EnemyMove(P.player.getPosition(), numEnemy, i); // 5 EA
                        
                        En.E[i].EnemyMoveState = true;
                    }
                    else {
                        ui.HPchange(-0.005);
                    }

                    

                    if (En.E[i].hpEnemy <= 0) {

                        En.E[i].EnemyMoveState = false;
                        
                        En.E[i].EnemyState = false;
                        
                        // random drop item
                        int randNum = rand() % 10;

                        if (randNum >= 0 && randNum <= 3)
                            Item.randomItem(randNum, En.E[i].setEneny.getPosition());


                        ui.SCOREchange(23);
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

                
                for (int j = 0; j < 3; j++) {
                    // bomb collision
                    if (Item.bom[j].BombActivate == true) {
                        Item.bom[j].BOOMgetTime = Item.bom[j].BOOMTime.getElapsedTime().asMilliseconds();
                        if (Item.bom[j].BOOMgetTime >= 200) {
                            Item.bom[j].BOOMgetTime = Item.bom[j].BOOMTime.restart().asMilliseconds();
                            Item.BOOMBAYAH(j, Item.bom[j].bomb.getPosition());

                            for (int i = 0; i < numEnemy; i++) {
                                if (En.E[i].setEneny.getGlobalBounds().intersects(Item.bom[j].BOOM.getGlobalBounds()) == true) {

                                    //En.E[i].EnemyState = false;
                                    En.E[i].hpEnemy = 0;
                                }
                            }
                        }

                        window.draw(Item.bom[j].BOOM);

                    }
                }

                // ANIMATION

                Item.BombAnimation();
                
            /*
            window.draw(P.player);
            window.draw(P.aimPlayer);
            */
            /*
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                
                    if (deBou.getElapsedTime().asMilliseconds() > 500.f) {
                        deBouTime = deBou.restart().asMilliseconds();
                        pauseMenu = !pauseMenu;
                    }
                
                
            }
            */
            


            

            // HP


            window.draw(ui.HP);

            // SCORE

            for(int i=0;i<6;i++)
            window.draw(ui.SCORE[i]);

            // Game over

            if (ui.HPplayer <= 0) {//////////////////////////////////////////////////////////////
                SelectMenu = 2;
                window.clear();
            }

            if (pauseMenu == true) {
                window.draw(pauseText);

                

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (pauseText.getGlobalBounds().intersects(MousePointer.getGlobalBounds())) {
                        SelectMenu = 0;

                    }
                }

            }

            

            window.display();
        }

        else if(SelectMenu == 3){
        
            
            window.clear();
            ui.showTopScore(&window);
           

            window.display();
        }

        else if (SelectMenu == 0) {
                window.clear();
            
                

                 MousePointer.setPosition(sf::Vector2f(sf::Mouse::getPosition()));
                if (ui.PlayButton.getGlobalBounds().intersects(MousePointer.getGlobalBounds())) {
                    
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    SelectMenu = 1;
                    pauseMenu = false;
                    checkEnemy = 0;
                    countEnemy = 0;
                    


                    MousePointer.setPosition(-1,-1);
                    }
                
                }

                if (ui.ScoreButton.getGlobalBounds().intersects(MousePointer.getGlobalBounds())) {
                    
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        SelectMenu = 3;
                        MousePointer.setPosition(-1, -1);
                    }

                }
                
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

            // Background
            BG.setBG();

            // player

            P.initPlayer(window.getSize().x / 2, window.getSize().y / 2);
            Item.initItem();
            ui.HPinit();
            ui.SCOREinit();
            ui.initButton();

            // Random
            srand(time(NULL));

            for (int i = 0; i < numEnemy; i++) {
                En.initEnimy(i);
            }

            
            
            window.draw(ui.PlayButton);
            window.draw(ui.ScoreButton);
            window.draw(ui.ExitButton);

            window.display();
        }
        /*
        else if (SelectMenu == 2) {
            sf::String namePlayer;
            sf::Text nameText;
            nameText.setFont(font);
            nameText.setCharacterSize(60);

            if (EVNT.type == sf::Event::TextEntered) {
                namePlayer += EVNT.text.unicode;
                nameText.setString(namePlayer);
            }

            window.draw(nameText);
        }
        */

        

        



       
    }
   
}

