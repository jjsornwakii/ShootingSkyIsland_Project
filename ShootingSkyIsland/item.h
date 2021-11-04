#pragma once
#include <SFML\Graphics.hpp>

class item
{

public:
	
	sf::Clock CrystalDelay;
	float CryTime=0;

	bool CrystalActivate;

	struct Medic {
		sf::RectangleShape medic;
		
		sf::Vector2u TextureSize1;
		bool itemState;
		
	};
	sf::Texture medicTexture;
	Medic med[5];

	struct Crystal {
		sf::RectangleShape crystal;
		sf::Vector2u TextureSize2;
		bool itemState;
		
	};

	sf::Texture crystalTexture;
	Crystal crys[2];

	struct Bomb {
		sf::RectangleShape bomb;
		sf::Vector2u TextureSize;
		bool itemState;
		sf::Clock bombCl;
		float getTime = 0;
		int currentX = 0;
	};
	
	sf::Texture bombTexture;
	sf::Vector2u bombSize = bombTexture.getSize();

	Bomb bom[3];
	
	int selectItem;
	
	



	void initItem();
	void randomItem(int n, sf::Vector2f Pos);
	void animationItem();
	
	///////////////////////////// use the bomb

	void planBomb(bool buttonPress,sf::Vector2f pos){
		for (int i = 0; i < 3; i++) {

		}
	}

};

