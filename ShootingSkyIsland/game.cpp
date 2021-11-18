#include "game.h"


   sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shooting Sky Island!", sf::Style::Close | sf::Style::Resize);

    sf::CircleShape MousePointer(5);


    Background BG;
    Player P;
    Enemy En;
    item Item;
    UI ui;

    float speedE = 0;
    float hpE = 1;

    float bulletSpeed = 1.5;

    int checkEnemy = 0;
    int countEnemy = 0;
    int numBullet = 200;
    int numEnemy = 5;
    int countKill = 0;
    float t = 0;
    sf::Clock T;

    int SelectMenu = 0;
    bool pauseMenu = false;

    sf::Font font;
    sf::String namePlayer;
    sf::Text nameText;
    sf::Text pauseText;
    sf::Text Banner;
    sf::Text text1;
    sf::Text showS;
    std::string temp="\0";

    void reset() {
  
        pauseMenu = false;

        font.loadFromFile("res/font/MyFont.ttf");
        
        Banner.setFont(font);
        Banner.setString("PLAY!");
        Banner.setCharacterSize(50);
        Banner.setFillColor(sf::Color::Red);
        Banner.setStyle(sf::Text::Bold);


        Banner.setPosition(sf::Vector2f(300.f, 300.f));

        

        nameText.setFont(font);
        nameText.setCharacterSize(60);

        text1.setCharacterSize(60);
        text1.setFillColor(sf::Color::Yellow);
        text1.setPosition(600, 500);
        text1.setString("Enter Name :");
        text1.setFont(font);

        showS.setCharacterSize(60);
        showS.setFillColor(sf::Color::Yellow);
        showS.setPosition(1100, 300);
        showS.setFont(font);
        
        pauseText.setFont(font);
        pauseText.setString("Exit");
        pauseText.setCharacterSize(60);
        pauseText.setFillColor(sf::Color::Red);
        pauseText.setPosition((window.getSize().x / 2)-50, (window.getSize().y / 2)-50);

        speedE = 0;
        hpE = 1;

        bulletSpeed = 1.5;

        checkEnemy = 0;
        countEnemy = 0;
        numBullet = 200;
        numEnemy = 5;
        countKill = 0;
        t = T.restart().asSeconds();

        // var test


        // Background
        BG.setBG();

        // player
        P.initPlayer(window.getSize().x / 2, window.getSize().y / 2);
        Item.initItem();
        ui.HPinit();
        ui.SCOREinit();
        ui.CLOCKinit();

        // Random
        srand(time(NULL));

        for (int i = 0; i < numEnemy; i++) {
            En.initEnimy(i);
        }
    }


void game::run()
{
    ui.getbuScore();
    ui.sortScore(temp);
    window.setFramerateLimit(800);

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

            if (SelectMenu == 0) {
                window.clear();

                

                MousePointer.setPosition(sf::Vector2f(sf::Mouse::getPosition()));
                if (ui.PlayButton.getGlobalBounds().intersects(MousePointer.getGlobalBounds())) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        
                        reset();
                        SelectMenu = 1;
                        
                    }

                }

                if (ui.ScoreButton.getGlobalBounds().intersects(MousePointer.getGlobalBounds())) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        SelectMenu = 3;
                        ui.getbuScore();
                        //ui.sortScore();
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


                window.draw(BG.skybg);
                window.draw(BG.mainModelbg);
                window.draw(BG.Logo);
                window.draw(BG.name);

                window.draw(ui.PlayButton);
                window.draw(ui.ScoreButton);
                window.draw(ui.ExitButton);

                window.display();
            }

            if (SelectMenu == 2) {
                if (EVNT.type == sf::Event::TextEntered) {
                    if (EVNT.text.unicode == 8 && namePlayer.getSize() > 0) {
                        namePlayer.erase(int(namePlayer.getSize()) - 1);
                    }
                    else if (namePlayer.getSize() <= 12 && EVNT.text.unicode != 8)
                        namePlayer += EVNT.text.unicode;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        std::cout << "----BeforeWriteNew-----" << std::endl;
                        temp = namePlayer;

                        //std::ofstream myScore;
                        //myScore.open("score.txt", std::ios::app);
                        //myScore << temp;
                        //myScore << ui.score << std::endl;
                        ui.LineNumber += 1;

                        std::cout << temp;
                        std::cout << " " << ui.score << std::endl;

                        //myScore.close();

                        
                        namePlayer = "";

                        //nameText.setString("");
                        SelectMenu = 0;
                        ui.getbuScore();
                        ui.sortScore(temp);
                        temp = "\0";
                    }

                }
            }
            

            
        }

        if (SelectMenu == 2) {

            window.clear();
            window.draw(BG.skybg);
            BG.animation(&window);

            

            text1.setPosition(600, 500);
            text1.setString("Enter Name :");
            window.draw(text1);

            text1.setPosition(800, 300);
            text1.setString("SCORE : ");
            window.draw(text1);

            nameText.setString(namePlayer);
            nameText.setPosition(1000, 500);

            auto str = std::to_string(ui.score);
            sf::String T = str;
            showS.setString(T);

            window.draw(showS);
            window.draw(nameText);


            window.display();
        }

        if (SelectMenu == 1) {
            window.clear();

            window.draw(BG.skybg);
            window.draw(BG.bg);
            

            if (pauseMenu == false) {
                
                // UPDATE BULLET

                P.UpdateBullet(sf::Vector2f(sf::Mouse::getPosition(window)), numBullet,bulletSpeed, Item.weaponUp.activate);

                t = T.getElapsedTime().asSeconds();
                
                for (int i = 0; i < numBullet; i++) {
                    for (int j = 0; j < numEnemy; j++) {

                        // bullet conllision
                        if (P.B[i].bulletShape.getGlobalBounds().intersects(En.E[j].setEneny.getGlobalBounds()) && P.B[i].state == true && En.E[j].EnemyState == true) {
                            ;
                            P.B[i].state = false;
                            En.E[j].hpEnemy -= P.damage;
                           
                        }
                        else
                            En.E[j].EnemyMoveState = true;
 
                    }

                    // spawn
                    for (int i = 0; i < numEnemy; i++) {
                        if (En.E[i].EnemyState == false /* && countEnemy < 20*/) {

                            En.randomEnemy(rand() % 3, i, hpE);


                            if (rand() % 2 == 0) {
                                En.setSpawn((float)(0 + rand() % (1920)), (float)(0), i);
                            }
                            else {
                                En.setSpawn((float)(0 + rand() % (1920)), (float)(900), i);
                            }
                            
                            
                        
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

                    if (P.player.getGlobalBounds().intersects(Item.weaponUp.WeaponU.getGlobalBounds()) && Item.weaponUp.itemState == true) {
                        Item.weaponUp.activate = true;
                        Item.weaponUp.itemState = false;
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

                if (Item.weaponUp.T < 10 && Item.weaponUp.activate == true) {
                    Item.weaponUp.T = Item.weaponUp.clock.getElapsedTime().asSeconds();
                    P.damage = 500;
                }
                else {
                    Item.weaponUp.T = Item.weaponUp.clock.restart().asSeconds();
                    Item.weaponUp.activate = false;
                    P.damage = 50;
                }
                
                // UPDATE ENEMY

                if (Item.CrystalActivate == true) {
                    Item.CryTime = Item.CrystalDelay.getElapsedTime().asSeconds();

                    if (Item.CryTime <= 5.f) {
                        for (int i = 0; i < 5; i++)
                            En.E[i].speed = 0.2f;

                    }
                    else {
                        for (int i = 0; i < 5; i++) {
                            if(En.E[i].SelectE==0)
                                En.E[i].speed = 1.0f;

                            else if(En.E[i].SelectE == 1)
                                En.E[i].speed = 0.5f;

                            else if (En.E[i].SelectE == 2)
                                En.E[i].speed = 5.f;
                        }

                        Item.CrystalActivate = false;
                    }
                }

                // UPDATE PLAYER

                P.PlayerControl();
                P.PlayerAnimation(0.25);




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

                        En.EnemyMove(P.player.getPosition(), numEnemy, i,speedE); // 5 EA
                        
                        En.E[i].EnemyMoveState = true;
                    }
                    else {
                        if(En.E[i].SelectE==0)
                            ui.HPchange(-0.007);
                        
                        if (En.E[i].SelectE == 1)
                            ui.HPchange(-0.005);

                        if (En.E[i].SelectE == 2)
                            ui.HPchange(-0.01);
                    }

                    /// if Ememy dead

                    if (En.E[i].hpEnemy <= 0) {

                        countKill++;

                        //std::cout << "c";

                        if (countKill >= 20) {
                            //std::cout << "d";
                            countKill = 0;
                            hpE += 0.05f;
                            speedE += 0.1f;
                            P.damage += 10;
                            t = T.restart().asSeconds();

                            //sf::Vector2f pp = { 100 + rand() % 1500,100 + rand() % 700 };
                            if(rand()%2==0)
                                Item.randomItem(-1, sf::Vector2f(100 + rand() % 1000, 100 + rand() % 700));
                        }

                        En.E[i].EnemyMoveState = false;
                        
                        En.E[i].EnemyState = false;
                        
                        // random drop item
                        int randNum = rand() % 15;
                            Item.randomItem(randNum, En.E[i].setEneny.getPosition());

                        
                        ui.SCOREchange(En.E[i].SelectE);
                    }
                }

                

                En.EnemyAnimation(0.25, numEnemy);

            }






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
                if (Item.weaponUp.itemState == true) {
                    window.draw(Item.weaponUp.WeaponU);
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
            
            window.draw(ui.clockUI);
            
            ui.updateTime(t, countKill, &window);

            if (t >= 60) {
                SelectMenu = 2;
            }

            

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

        
        

        

        



       
    }
   
}

