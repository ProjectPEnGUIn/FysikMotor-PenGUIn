// Dennis Mårtensson Erik Magnusson gymnasieprojekt fysikmotor 0.01 med sfml 2.4 till grafik

//entityhandler ->rectangleentity/triangleentity/circleentity
//eventhandler -> -||-

//sfml library includes
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>

#include "PEVec2D.h" //2d vector
#include "Entity.h" //boxes or circles

//global variables
int screenWidth = 1280;
int screenHeight = 720;
int drawTickrate = 60; //amount of times it tries to draw each second, min = 1 tick/sec
int logicTickrate = 60; //amount of times it tries to do logic each seconds, min = 1 tick/sec
sf::Time drawTime = sf::seconds((float)(1 / drawTickrate));
sf::Time logicTime = sf::seconds((float)(1 / logicTickrate));



int main()
{

	std::cout << "Press enter\n";
	std::cin.get();

	bool runProgram = true;
	//runs while runProgram == true, program able to run without the sf::renderwindow, able to redefine it etc,
	while (runProgram)
	{

		sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "PEnGUIn");  //creates the sfml window  //Physics Engine (a)n(d) Graphical User Interface n(noegenesis)
		window.setPosition(sf::Vector2i(0, 0));
		sf::Clock drawClock;  //clock that keeps track of how much time has passed from last time it was restarted
		sf::Clock logicClock;

		drawClock.restart();  //starts timer
		logicClock.restart();

		//runs while the window is open
		while (window.isOpen())
		{
			sf::Event programEvent;
			while (window.pollEvent(programEvent)) //processes events
			{
				if (programEvent.type == sf::Event::Closed) //if x window has been pressed
				{
					window.close();
					runProgram = false;
				}

				//exits/cloeses the program
				if (programEvent.type == sf::Event::KeyPressed)
					if (programEvent.key.code == sf::Keyboard::Escape)
					{
						window.close();
						runProgram = false;
					}

				//general event handling

				//keyboard events
				if (programEvent.type == sf::Event::KeyPressed)
				{
					//if a key on keyboard is pressed down
					//procces these events further
				}

				if (programEvent.type == sf::Event::KeyReleased)
				{
					//if a key on keyboard has been released
					//process these evetns further
				}

				//mouse events
				if (programEvent.type == sf::Event::MouseButtonPressed)
				{
					//if a mouse button has been pressed down
				}

				if (programEvent.type == sf::Event::MouseButtonReleased)
				{
					//if a mosue button has been released
				}

				if (programEvent.type == sf::Event::MouseMoved)
				{
					//if the mouse has moved

				}
			}

			if (logicClock.getElapsedTime() >= logicTime) //the programs logic part, all programs logic happens here at a certain rate
			{
				logicClock.restart(); //restarts the clock

			}

			if (drawClock.getElapsedTime() >= drawTime) //the programs drawing part, draws things to the screen at a certain rate
			{
				drawClock.restart(); //restarts the clock

				window.clear(sf::Color::Black);  //clears screen to black
				//starts to draw the current frame


				window.display(); //displays the current drawn frame
			}


		}
	}

	return 0;
}