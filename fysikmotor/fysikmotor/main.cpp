// Dennis Mårtensson Erik Magnusson gymnasieprojekt fysikmotor 0.01 med sfml 2.4 till grafik

//sfml library includes
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>

#include "PE.h"

//global variables
const int screenWidth = 1280;
const int screenHeight = 720;
const int drawTickrate = 60; //amount of times it tries to draw each second, min = 1 tick/sec
const int logicTickrate = 60; //amount of times it tries to do logic each seconds, min = 1 tick/sec
sf::Time drawTime = sf::seconds((1.0f / drawTickrate));
sf::Time logicTime = sf::seconds((1.0f / logicTickrate));

int main()
{
	std::cout << "Press enter\n";
	std::cin.get();

	bool runProgram = true;
	//runs while runProgram == true, program able to run without the sf::renderwindow, able to redefine it etc,
	while (runProgram)
	{

		PE testEngine;
		testEngine.init(20.0f, 20.0f, 500 ,500, 50, 50);

		VertexShape tShape1, tShape2; 
		float radius = 2.0f;


	//for (float i = 0.0f; i < 2*3.14159265f; i+= (2.0f * 3.14159265f)/4.0f)
	//{
	//	tShape1.addVertexPoint(Vec2D(cos(i) * radius, sin(i) * radius));
	//
	//
	//	tShape2.addVertexPoint(Vec2D(cos(i) * radius, sin(i) * radius));
	//
	//}

		tShape1.addVertexPoint(Vec2D(0, 0));
		tShape1.addVertexPoint(Vec2D(0, 2));
		tShape1.addVertexPoint(Vec2D(2, 2));
		tShape1.addVertexPoint(Vec2D(2, 0));

		tShape2.addVertexPoint(Vec2D(0, 0));
		tShape2.addVertexPoint(Vec2D(0, 2));
		tShape2.addVertexPoint(Vec2D(2, 2));
		tShape2.addVertexPoint(Vec2D(2, 0));

		tShape1.setRotationDEGREES(45.0f);
	//	tShape2.setRotationDEGREES(270.0f);


		Entity tEntity1, tEntity2;
		tEntity1.setVertexShape(tShape1);
		tEntity2.setVertexShape(tShape2);

		tEntity1.setEnttityID(1);
		tEntity2.setEnttityID(2);

		tEntity1.setEntityState(1);
		tEntity2.setEntityState(0);

		tEntity1.setPosition(Vec2D(12.35f, 19.0f));
		tEntity2.setPosition(Vec2D(10.f, 3.f));

		testEngine.addEntity(tEntity1);
		testEngine.addEntity(tEntity2);

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
				testEngine.update(logicClock.restart().asSeconds()); // updates and restarts the clock
			}

			//if (drawClock.getElapsedTime() >= drawTime) //the programs drawing part, draws things to the screen at a certain rate
			//{
				//drawClock.restart(); //restarts the clock

				window.clear(sf::Color::Black);  //clears screen to black
				//starts to draw the current frame

				testEngine.draw(window);

				window.display(); //displays the current drawn frame
			//}
		}
	}

	return 0;
}