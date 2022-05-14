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
    spriteBee.setPosition(0, 800*scaleF);
    spriteBee.setScale(scaleF, scaleF);

    bool beeActive = false;
    double beeSpeed = 0.0;

    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    sf::Sprite spriteCloud_1;
    sf::Sprite spriteCloud_2;
    sf::Sprite spriteCloud_3;
    spriteCloud_1.setTexture(textureCloud);
    spriteCloud_2.setTexture(textureCloud);
    spriteCloud_3.setTexture(textureCloud);
    spriteCloud_1.setPosition(0, 0);
    spriteCloud_2.setPosition(0, 250 * scaleF);
    spriteCloud_3.setPosition(0, 500 * scaleF);
    spriteCloud_1.setScale(scaleF, scaleF);
    spriteCloud_2.setScale(scaleF, scaleF);
    spriteCloud_3.setScale(scaleF, scaleF);

    bool cloud1_Active = false;
    bool cloud2_Active = false;
    bool cloud3_Active = false;

    double cloud1_Speed = 0.0;
    double cloud2_Speed = 0.0;
    double cloud3_Speed = 0.0;

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        window.clear();
        window.draw(spriteBackground);

        window.draw(spriteCloud_1);
        window.draw(spriteCloud_2);
        window.draw(spriteCloud_3);

        window.draw(spriteTree);
        window.draw(spriteBee);
        window.display();
    }
    return 0;
}