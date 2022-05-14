#include <SFML/Graphics.hpp>

int main()
{
    double wX = 1920, hY = 1080, scaleF = 0.5;
    sf::VideoMode vm(wX * scaleF, hY * scaleF);
    sf::RenderWindow window(vm, "Timber!!!");

    //sf::VideoMode vm(1920, 1080);
    //sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0,0);
    spriteBackground.setScale(scaleF, scaleF);

    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810*scaleF,0);
    spriteTree.setScale(scaleF, scaleF);

    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800* scaleF);
    spriteBee.setScale(scaleF, scaleF);

    bool beeActive = false;
    double beeSpeed = 0.0;

    sf::Texture textureCloud;

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.display();
    }
    return 0;
}