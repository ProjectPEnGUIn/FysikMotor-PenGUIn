//// Dennis Mårtensson Erik Magnusson gymnasieprojekt fysikmotor 0.01 med sfml 2.4 till grafik

#include <iostream>
#include "Sound_system.h"
#include "Texture_System.h"
#include "Menu_System.h"
#include "Splashscreen.h"
#include "Game_System.h"
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{

	std::string s = "abc", s2 = "-1.23", s3 = "12";
	if(!( s.find_first_not_of( "0123456789.-" ) == std::string::npos ))
		std::cout << "s does not contai nnumbers\n";
	if( !(s2.find_first_not_of( "0123456789.-" ) == std::string::npos ))
		std::cout << "s2 does not contai nnumbers\n";
	if( !(s3.find_first_not_of( "0123456789.-" ) == std::string::npos ))
		std::cout << "s3 does not contai nnumbers\n";

	std::cin.get();

	sf::Event e;
	sf::ContextSettings settings;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Image myicon;
	
	myicon.loadFromFile("Textures/Icon.png");
	settings.antialiasingLevel = 8;
	
	sf::RenderWindow renderWindow(sf::VideoMode(1600, 900, 32), "Project PEnGUIn", sf::Style::Default, settings);
	renderWindow.setIcon(256, 256, myicon.getPixelsPtr());
	
	SplashScreen splashScreen(renderWindow, e, clock, elapsed);
        Main_Menu mainmenu(renderWindow, e, clock, elapsed);
	Game_System game(renderWindow, e, clock, elapsed );

	std::cout << "succesful\nPress enter\n";
	std::cin.get();

	return 0;
}
