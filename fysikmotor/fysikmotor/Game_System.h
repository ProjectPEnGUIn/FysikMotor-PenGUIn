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
		physicsEngine.init(30, 30, 1000, 899, 600, 0);

		Texture_System background( "Backgrounds/Main_Menu_Background.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 0.0f, 0.0f ), sf::IntRect( 0, 0, 1920 * 1000, 1080 ), 1.f, 1.f, true, true );
		
		Texture_System border( "Textures/Main screen.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 555.0f, 0.0f ), sf::IntRect( 0, 0, 1031, 756 ), 1.26f, 2.f, true, false );
		Texture_System pause_button( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 530.0f, 650.0f ), sf::IntRect( 790, 181, 174, 167 ), 1.f, 1.f, true, false );
		
		Texture_System playTexture_Button( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 580.0f, 695.0f ), sf::IntRect( 694, 169, 87, 82 ), 1.f, 1.f, true, false );
		Texture_System pauseTexture_Button( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 585.0f, 690.0f ), sf::IntRect( 690, 269, 87, 72 ), 1.f, 1.f, true, false );

		Texture_System Box_test( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 55.0f, 750.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.35f, 0.35f, true, false );
		Texture_System Box_test2( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 55.0f, 610.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.35f, 0.35f, true, false );
		Texture_System Box_test3( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 55.0f, 470.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.35f, 0.35f, true, false );

		sf::Time logicTime = sf::seconds(1 / 60);
		sf::Clock logicTimer;

		background.setColor( sf::Color( 255, 255, 255, 45 ) );

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
			
			Box_test.draw( renderwindow );
			Box_test2.draw( renderwindow );
			Box_test3.draw( renderwindow );

			pause_button.draw( renderwindow );
			pauseTexture_Button.draw( renderwindow );
			playTexture_Button.draw( renderwindow );

			border.draw( renderwindow );
			
			renderwindow.display();
		}
	}
};
#endif // ! _GAMESYSTEM: