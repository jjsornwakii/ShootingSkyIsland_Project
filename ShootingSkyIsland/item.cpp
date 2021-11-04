#include "item.h"

void item::initItem() {

	medicTexture.loadFromFile("res/pic/madic.png");
	
	for (int i = 0; i < 5; i++) {
		
		med[i].medic.setSize(sf::Vector2f(50.f, 50.f));
		med[i].medic.setTexture(&medicTexture);
		sf::Vector2u medicSize = medicTexture.getSize();
		med[i].medic.setTextureRect(sf::IntRect(0, 0, medicSize.x, medicSize.y));
	}
	
	crystalTexture.loadFromFile("res/pic/crystal.png");
	
	for (int i = 0; i < 2; i++) {
		
		crys[i].crystal.setSize(sf::Vector2f(50.f, 50.f));
		crys[i].crystal.setTexture(&crystalTexture);
		sf::Vector2u crystalSize = crystalTexture.getSize();
		crys[i].crystal.setTextureRect(sf::IntRect(0, 0, crystalSize.x, crystalSize.y));
	}

	bombTexture.loadFromFile("res/pic/bomb.png");

	for (int i = 0; i < 3;i++) {
		bom[i].bomb.setSize(sf::Vector2f(90.f,50.f));
		bom[i].bomb.setTexture(&bombTexture);
		bombSize = bombTexture.getSize();
		bom[i].bomb.setTextureRect(sf::IntRect(0,0,bombSize.x/2,bombSize.y));
	}

}


void item::animationItem() {
	for (int i = 0; i < 2; i++) {
		if (bom[i].itemState == true) {
			bom[i].getTime = bom[i].bombCl.getElapsedTime().asSeconds();

			if (bom[i].getTime >= 1) {
				
				bom[i].getTime = bom[i].bombCl.restart().asSeconds();
				bom[i].currentX++;
				bom[i].bomb.setTextureRect(sf::IntRect(0, 0, bombSize.x / 2 * bom[i].currentX, bombSize.y));

			}
		}
	}
}


void item::randomItem(int n,sf::Vector2f Pos) {
	
	
		if (n == 0) {
			for (int i = 0; i < 5; i++) {
				if (med[i].itemState == false) {
					med[i].itemState = true;
					med[i].medic.setPosition(Pos);
					break;
				}
			}
		}
		else if (n==1) {
			for (int i = 0; i < 2 ; i++) {
				if (crys[i].itemState == false) {
					crys[i].itemState = true;
					crys[i].crystal.setPosition(Pos);
					break;
				}
			}
		}
		else if (n == 2) {
			for (int i = 0; i < 3; i++) {
				if (bom[i].itemState == false) {
					bom[i].itemState = true;
					bom[i].bomb.setPosition(Pos);
					break;
				}
			}
		}
		
}