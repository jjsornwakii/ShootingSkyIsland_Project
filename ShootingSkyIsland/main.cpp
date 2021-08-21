#include <SFML/Graphics.hpp>
#include <time.h>
#include <windows.h>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shooting Sky Island!");


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({ 200.f , 200.f });


    sf::Texture character;
    if (!character.loadFromFile("res/pic/C1.png")) {

        printf("Load Failed!");

    }


    sf::Sprite shapeCharacter;
    shapeCharacter.setTexture(character);
    shapeCharacter.setTextureRect(sf::IntRect(96, 0, 96, 96));


    int MoveX = character.getSize().x / 3;
    int MoveY = character.getSize().y / 4;
    int cFrame = 0;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        window.draw(shape);
        window.draw(shapeCharacter);


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

            shapeCharacter.setTextureRect(sf::IntRect((MoveX)*cFrame, 287, 96, 95));
            shapeCharacter.move(0.f, -.5f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

            shapeCharacter.setTextureRect(sf::IntRect((MoveX)*cFrame, 0, 96, 95));
            shapeCharacter.move(0.f, .5f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

            shapeCharacter.setTextureRect(sf::IntRect((MoveX)*cFrame, 193, 96, 94));
            shapeCharacter.move(1.f, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

            shapeCharacter.setTextureRect(sf::IntRect((MoveX)*cFrame, 97, 96, 95));
            shapeCharacter.move(-1.f, 0.f);
        }

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

            window.close();
        }

        cFrame++;

        if (cFrame > 2)
            cFrame = 0;

        

        window.display();
        window.clear();
    }

    return 0;
}