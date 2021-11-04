#include "Enemy.h"
#include "Player.h"



void Enemy::initEnimy(int i) {
	EnenyCharactor.loadFromFile("res/pic/AmoungUs2.png");
	E[i].setEneny.setSize(sf::Vector2f(110.f, 150.f));
	E[i].setEneny.setTexture(&EnenyCharactor);

	EnenyTextureSize = EnenyCharactor.getSize();
	EnenyTextureSize.x /= 3;
	EnenyTextureSize.y /= 3;

	E[i].setEneny.setTextureRect(sf::IntRect(EnenyTextureSize.x * 1, EnenyTextureSize.y * 0, EnenyTextureSize.x, EnenyTextureSize.y));
	
}

void Enemy::setSpawn(float X, float Y,int i) {

	E[i].setEneny.setPosition(X,Y);

}

void Enemy::EnemyMove(sf::Vector2f PlayerPos,int nEnemy,int i) {
	
		if (E[i].EnemyState != false && E[i].EnemyMoveState != false) {
			
			if (E[i].setEneny.getPosition().y < PlayerPos.y) {
				E[i].setEneny.move(0.0f, 0.05f * E[i].speed);
				E[i].animationDir = 0;
			}
			if (E[i].setEneny.getPosition().y > PlayerPos.y) {
				E[i].setEneny.move(0.0f, -0.05f * E[i].speed);
				E[i].animationDir = 0;
			}

			if (E[i].setEneny.getPosition().x < PlayerPos.x) {
				E[i].setEneny.move(0.05f * E[i].speed, 0.f);

				E[i].animationDir = 1;

			}
			if (E[i].setEneny.getPosition().x > PlayerPos.x) {
				E[i].setEneny.move(-0.05f * E[i].speed, 0.f);

				E[i].animationDir = 2;
			}
			

		}
	
}

void Enemy::EnemyAnimation(float deltaTime,int nEnemy) {
	if (bounchTime > 0.25) {
		
		for (int i = 0; i < nEnemy; i++) {
			if (E[i].EnemyState != false) {
				if (E[i].animationDir == 1) {
					E[i].current.x++;
					E[i].current.y = 2;
					//std::cout << EnenyTextureSize.x << std::endl;
				}

				if (E[i].animationDir == 2) {
					E[i].current.x++;
					E[i].current.y = 1;
				}

				if (E[i].current.x == 3) {
					E[i].current.x = 0;
				}

				E[i].setEneny.setTextureRect(sf::IntRect(EnenyTextureSize.x * E[i].current.x, float(EnenyTextureSize.y) * float(E[i].current.y), EnenyTextureSize.x, EnenyTextureSize.y));
			}
		}
		bounchTime = EnemyClock.restart().asSeconds();
	}
	bounchTime = EnemyClock.getElapsedTime().asSeconds();
}

