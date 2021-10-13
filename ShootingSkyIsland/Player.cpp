#include "Player.h"

void Player::initPlayer(float posX,float posY) {
	charactorPlayer.loadFromFile("res/pic/C2.png");
	player.setSize(sf::Vector2f(150.f, 150.f));
	player.setTexture(&charactorPlayer);

	TextureSize = charactorPlayer.getSize();
	TextureSize.x /= 3;
	TextureSize.y /= 3;

	player.setTextureRect(sf::IntRect(TextureSize.x * currentX , TextureSize.y * currentY, TextureSize.x , TextureSize.y));
	player.setPosition(posX, posY);
}

void Player::PlayerControl()
{
   
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        
        vec.x = 0;
        vec.y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            if (player.getPosition().y > 0.0f) {
                moveY -= 1;
                vec.y += 1;
            }
            currentY = 0;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            if (player.getPosition().y < 860) {
                moveY += 1;
                vec.y -= 1;
            }
            currentY = 0;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            if (player.getPosition().x > 0.0f) {
                moveX -= 1;
                vec.x += 1;
            }
            currentY = 1;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            if (player.getPosition().x < 1780.0f) {
                moveX += 1;
                vec.x -= 1;
            }
            currentY = 2;

        }

        float V = ((abs(moveX) + abs(moveY))/(float)2) ;
        leng = sqrt(vec.x * vec.x + vec.y * vec.y);
        if (leng != 0) {
            speed = abs(V / leng);
        }

        player.move(moveX * (1-speed) * .2f, moveY * (1 - speed) * .2f);
        moveX = 0;
        moveY = 0;
        leng = 0;
        speed = 1;
        switchAnimationState = 1;
    }
       
}


void Player::PlayerAnimation(float deltaTime) {

    if (switchAnimationState == 1) {
        getTime = playerClock.getElapsedTime().asSeconds();
        if (deltaTime < getTime) {
            getTime = playerClock.restart().asSeconds();

            if (currentX >= 2) {
                dirX = 1;
            }
            if (currentX <= 0) {
                dirX = 0;
            }
            if (dirX == 0) {
                currentX++;
            }
            else {
                currentX--;
            }
            
        }
        
    }

    player.setTextureRect(sf::IntRect(TextureSize.x * currentX, TextureSize.y * currentY, TextureSize.x, TextureSize.y));
    
    if (switchAnimationState == false) {
        player.setTextureRect(sf::IntRect(TextureSize.x * 1, TextureSize.y * 0, TextureSize.x, TextureSize.y));
        getTime = playerClock.restart().asSeconds();
    }
    switchAnimationState = false;
}