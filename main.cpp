#include <SFML/Graphics.hpp>
#include<sstream>
#include<ctime>

int main()
{
    float wX = 1920, hY = 1080, scaleF = 0.5f;
	
	wX*=scaleF; hY*=scaleF;
    sf::VideoMode vm(wX, hY);
    sf::RenderWindow window(vm, "Timber!!!");       //Вызов рендера окна с характеристиками
    window.setFramerateLimit(60);

    //sf::VideoMode vm(1920, 1080);
    // sf::Style::Fullscreen - параметр для вывода в полный экран
    //sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

    //Создание и загрузка текстуры фона
    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    //Создание и связывание с текстурой спрайта фона 
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0,0);
    spriteBackground.setScale(scaleF, scaleF);

    //Дерево
    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810*scaleF,0);
    spriteTree.setScale(scaleF, scaleF);

    //Пчела
    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    //spriteBee.setPosition(0, 800*scaleF);
    spriteBee.setPosition(0, 0);
    spriteBee.setScale(scaleF, scaleF);

    bool beeActive = false;     //Активность пчелы
    float beeSpeed = 0.0f;      //Скорость пчелы

    //Облака
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

    bool cloud1_Active = false;     //Активность облаков
    bool cloud2_Active = false;
    bool cloud3_Active = false;

    float cloud1_Speed = 0.0f;      //Скорость облаков
    float cloud2_Speed = 0.0f;
    float cloud3_Speed = 0.0f;

    sf::Clock clock;

	sf::RectangleShape timeBar;
	float timeBarStartWidth = 400.0f;
	float timeBarHeight = 80.0f;
	timeBar.setSize(sf::Vector2f(timeBarStartWidth*scaleF,timeBarHeight*scaleF));
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition((wX-timeBarStartWidth)*scaleF/2, 980*scaleF);

	sf::Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth/timeRemaining;

	bool paused=true;
	int score=0;
	sf::Text messageText, scoreText;
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	messageText.setCharacterSize(75*scaleF);
	scoreText.setCharacterSize(100*scaleF);

	messageText.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);

	sf::FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left + textRect.width/2, textRect.top+textRect.height/2);

	messageText.setPosition(wX/2,hY/2);
	scoreText.setPosition(20*scaleF,20*scaleF);

    while (window.isOpen())
    //Выполнение цикла пока открыто рабочее окно
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        //Провекра на нажатие кнопки
        {
            window.close();
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			paused=false;
			score=0;
			timeRemaining=6.0f;
		}
        
        sf::Time dt = clock.restart();      //Время между двумя кадрами

		/*
		****************
		Обновление сцены
		****************
		*/
		if(!paused)
		{
			sf::Time dt =clock.restart();

			timeRemaining -= dt.asSeconds();
			timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond*timeRemaining, timeBarHeight));

			if(timeRemaining<=0.0f)
			{
				paused=true;
				messageText.setString("Out of time!");
				sf::FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width/2, textRect.top+textRect.height/2);
				messageText.setPosition(wX/2, hY/2);
			}

			if (!beeActive)
			{
				srand(time(0));        //Подготовка с работе с псевдосдучайными числами
				beeSpeed = (rand() % 200) + 200;        //Задание скорости пчелы 
				//beeSpeed=getRandomNumber(100, 200);

				srand(time(0)*10);
				float height = (rand() % 1080) + 100;        //Вычисление псевдослучайной высоты полета
				spriteBee.setPosition(2000 * scaleF, height * scaleF);      //Задание позиции пчелы с учетом новых параметров
				//spriteBee.setPosition(2000 * scaleF, 100);
				//float testPositionYBee = spriteBee.getPosition().y;
				beeActive = true;       //Приводим пчелу в движение
			}
			else
			{
				//Обновление позиции пчелы с учетом её скорости
				spriteBee.setPosition((spriteBee.getPosition().x -(beeSpeed*dt.asSeconds())*scaleF),spriteBee.getPosition().y);
				if (spriteBee.getPosition().x < (-100 * scaleF)) beeActive = false;     //Останавливаем пчелу
			}
			//float testPosBee = spriteBee.getPosition().y;
			//Облака движутся по тому же принципу, что и пчела
			if(!cloud1_Active)
			{
				srand((int)time(0) * 10);
				cloud1_Speed = rand() % 200;

				srand((int)time(0) * 10);
				float height = rand() % 150;
				spriteCloud_1.setPosition(-200, height * scaleF);
				cloud1_Active = true;
			}
			else
			{
				spriteCloud_1.setPosition((spriteCloud_1.getPosition().x + (cloud1_Speed * dt.asSeconds()) * scaleF), spriteCloud_1.getPosition().y);
				if (spriteCloud_1.getPosition().x > wX)
				{
					cloud1_Active = false;
				}
			}

			if (!cloud2_Active)
			{
				srand((int)time(0) * 20);
				cloud2_Speed = rand() % 200;

				srand((int)time(0) * 20);
				float height = (rand() %300)-150;
				spriteCloud_2.setPosition(-200, height * scaleF);
				cloud2_Active = true;
			}
			else
			{
				spriteCloud_2.setPosition((spriteCloud_2.getPosition().x + (cloud2_Speed * dt.asSeconds()) * scaleF), spriteCloud_2.getPosition().y);
				if (spriteCloud_2.getPosition().x > wX)
				{
					cloud2_Active = false;
				}
			}

			if (!cloud3_Active)
			{
				srand((int)time(0) * 30);
				cloud3_Speed = rand() % 200;

				srand((int)time(0) * 30);
				float height = (rand() % 450)-150;
				spriteCloud_3.setPosition(-200, height * scaleF);
				cloud3_Active = true;
			}
			else
			{
				spriteCloud_3.setPosition((spriteCloud_3.getPosition().x + (cloud3_Speed * dt.asSeconds()) * scaleF), spriteCloud_3.getPosition().y);
				if (spriteCloud_3.getPosition().x > wX)
				{
					cloud3_Active = false;
				}
			}
			std::stringstream ss;
			ss<<"Score = "<<score;
			scoreText.setString(ss.str());
		}
		/*
		***************
		Прорисовка сцены
		***************
		*/

		window.clear();
        window.draw(spriteBackground);      //Рисование спрайта фона

        window.draw(spriteCloud_1);     //Рисование спрайта облаков
        window.draw(spriteCloud_2);
        window.draw(spriteCloud_3);

        window.draw(spriteTree);        //Рисование спрайта дерева
        window.draw(spriteBee);     //Рисование спрайта пчелы

		window.draw(scoreText);
		window.draw(timeBar);

		if(paused)
		{
			window.draw(messageText);
		}

        window.display();   //Вывод отрисованного на экран
    }
    return 0;
}