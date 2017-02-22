
#ifndef  _SPLASHSCREEN_
#define _SPLASHSCREEN_


#include "Sound_system.h"
#include "Texture_System.h"

class SplashScreen
{
public:
	SplashScreen(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock& clock, sf::Time& elapsed)

	{
		Texture_System splashScreen_background("Backgrounds/Main_Menu_Background.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), sf::IntRect(0, 0, 1920, 1080), 1.f, 1.f, true, false);
		Texture_System splashScreen_logo("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(600.0f, 125.0f), sf::IntRect(27, 27, 347, 307), 1.15f, 1.15f, true, false);
		Texture_System splashScreen_PressStart("Textures/Main_menu_sprite_Sheet.png", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(600.0f, 250.0f), sf::IntRect(757, 39, 440, 64), 1.f, 1.f, true, false);

		splashScreen_logo.setScale(1.35f, 1.40f);

		sf::Clock clock2;
		sf::Time time = clock2.getElapsedTime();

		bool pressStart = true;

		while (renderwindow.isOpen() && pressStart)
		{
			renderwindow.clear();

			if (time.asSeconds() < 4)
			{
				splashScreen_background.setColor(sf::Color(255, 255, 255, (time.asSeconds() * 27)));
				splashScreen_logo.setColor(sf::Color(255, 255, 255, (time.asSeconds() * 64)));
			}

			splashScreen_background.draw(renderwindow);
			splashScreen_logo.draw(renderwindow);

			time = clock2.getElapsedTime();

			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					renderwindow.close();

				if (time.asSeconds() > 4)
				{
					if (e.type == sf::Event::Closed)
						renderwindow.close();

					if (e.type == sf::Event::KeyPressed)
					{
						if (e.key.code == sf::Keyboard::Return)
						{
							pressStart = false;
						}
					}
				}

			}

			if (time.asSeconds() > 4)
			{
				splashScreen_background.setColor(sf::Color(255, 255, 255, 62));

				splashScreen_PressStart.setPosition(sf::Vector2f(625.f, 650.f));

				splashScreen_background.draw(renderwindow);
				splashScreen_logo.draw(renderwindow);
				splashScreen_PressStart.draw(renderwindow);
			}
			renderwindow.display();
		}
	}
private:

};

#endif // ! _SPLASHSCREEN_
