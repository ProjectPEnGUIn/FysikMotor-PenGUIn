#pragma once

#ifndef  _GAMESYSTEM_
#define _GAMESYSTEM_



#include "Sound_system.h"
#include "Texture_System.h"
#include "Font_System.h"

#include "PE.h" //physics engine module

class Game_System
{
public:
	Game_System(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock clock, sf::Time& elapsed )
	{
		PE physicsEngine;
		physicsEngine.init(30, 30, 500, 500, 50, 50);

		Texture_System background( "Backgrounds/Main_Menu_Background.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 0.0f, 0.0f ), sf::IntRect( 0, 0, 1920 * 1000, 1080 ), 1.f, 1.f, true, true );
		background.setColor( sf::Color( 255, 255, 255, 85 ) );
		
		sf::Time logicTime = sf::seconds(1 / 60);
		sf::Clock logicTimer;

		bool game = true;
		while (renderwindow.isOpen() && game)
		{
			renderwindow.clear();

			elapsed = clock.getElapsedTime();
			background.setPosition( sf::Vector2f( -40 * elapsed.asSeconds(), 0 ) );

			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					renderwindow.close();
			}

			if (logicTimer.getElapsedTime() >= logicTime)
			{
				//logic; TODO; split up timer in smaller segments if it ets too big
				physicsEngine.update(logicTimer.restart().asSeconds());
			}

			elapsed = clock.getElapsedTime();
			
			background.draw( renderwindow );
			physicsEngine.draw(renderwindow);
			
			renderwindow.display();
		}
	}
};
#endif // ! _GAMESYSTEM: