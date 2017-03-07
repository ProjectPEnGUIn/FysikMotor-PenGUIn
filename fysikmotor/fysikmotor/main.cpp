//// Dennis Mårtensson Erik Magnusson gymnasieprojekt fysikmotor 0.01 med sfml 2.4 till grafik

#include <iostream>
#include "Sound_system.h"
#include "Texture_System.h"
#include "Menu_System.h"
#include "Splashscreen.h"
#include "Game_System.h"
#include <fstream>
#include <vector>

int main()
{
	sf::Event e;
	sf::ContextSettings settings;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Image myicon;
	
	myicon.loadFromFile("Textures/Icon.png");
	settings.antialiasingLevel = 8;
	
	sf::RenderWindow renderWindow(sf::VideoMode(1600, 900, 32), "Project PEnGUIn", sf::Style::Default, settings);
	renderWindow.setIcon(256, 256, myicon.getPixelsPtr());
	
	//SplashScreen splashScreen(renderWindow, e, clock, elapsed);
	//Main_Menu mainmenu(renderWindow, e, clock, elapsed);
	Game_System game(renderWindow, e, clock, elapsed);

	return 0;
}
