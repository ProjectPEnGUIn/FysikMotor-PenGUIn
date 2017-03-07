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
		physicsEngine.init(30, 30, 700, 550, 450, 0);

		Texture_System background( "Backgrounds/Main_Menu_Background.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 0.0f, 0.0f ), sf::IntRect( 0, 0, 1920 * 1000, 1080 ), 1.f, 1.f, true, true );
		background.setColor( sf::Color( 255, 255, 255, 45 ) );

		Texture_System border( "Textures/Main screen.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 425.0f, 0.0f ), sf::IntRect( 0, 0, 1031, 756 ), 0.73f, 0.767, true, false );
		Texture_System pause_button( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 530.0f, 650.0f ), sf::IntRect( 790, 181, 174, 167 ), 1.f, 1.f, true, false );
		Texture_System playTexture_Button( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 580.0f, 695.0f ), sf::IntRect( 694, 169, 87, 82 ), 1.f, 1.f, true, false );

		sf::Time logicTime = sf::seconds(1 / 60);
		sf::Clock logicTimer;

		bool game = true;
		while (renderwindow.isOpen() && game)
		{
			renderwindow.clear();

			elapsed = clock.getElapsedTime();
			background.setPosition( sf::Vector2f( -20 * elapsed.asSeconds(), 0 ) );

			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					renderwindow.close();
			}

			if (logicTimer.getElapsedTime() >= logicTime)
			{
				//logic; TODO; split up timer in smaller segments if it gets too big
				physicsEngine.update(logicTimer.restart().asSeconds());
			}

			elapsed = clock.getElapsedTime();
			
			background.draw( renderwindow );


			physicsEngine.draw( renderwindow );
			

			pause_button.draw( renderwindow );
			playTexture_Button.draw( renderwindow );

			border.draw( renderwindow );
			
			renderwindow.display();
		}
	}
};
#endif // ! _GAMESYSTEM: