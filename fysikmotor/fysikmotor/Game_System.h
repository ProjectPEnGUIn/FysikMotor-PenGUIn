#pragma once

#ifndef  _GAMESYSTEM_
#define _GAMESYSTEM_

#include "Sound_system.h"
#include "Texture_System.h"
#include "Font_System.h"
#include "PE.h" //physics engine module
#include "DataLogger.h"

Entity getEntitySquare(Vec2D pos, float width, float height, float mass, float cor, int ID, int state, Vec2D vel, float rot)
{
	Entity e;
	VertexShape s;
	e.setEntityState(state);
	s.addVertexPoint(Vec2D(0, 0));
	s.addVertexPoint(Vec2D(0, height));
	s.addVertexPoint(Vec2D(width, height));
	s.addVertexPoint(Vec2D(width, 0));
	e.setVertexShape(s);
	e.setPosition(pos);
	e.setMass(mass);
	e.setRestitutionCoefficient(cor);
	e.setFrictionCoefficient(0.0f);
	e.setDragCoefficient(0.15f);
	e.setEnttityID(ID);
	e.setVelocity(vel);
	e.setAngleRotationDEGREES(rot);
	e.setSillhueteArea(1);

	if (e.getEntityState() != 0) //only track movable objects
		e.setTrackEntityData(true);

	return e;
}

std::string ID;
std::string Drag;
std::string Mass;
std::string PositionX;
std::string PositionY;
std::string Restitution;
std::string Rotation;
std::string ShapeHeight;
std::string ShapeWidth;
std::string STATE;
std::string Friction;
std::string TrackEntity;
std::string VelocityX;
std::string VelocityY;
std::string SurfaceArea;

class Game_System
{
public:
	Game_System(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock clock, sf::Time& elapsed )
	{
		sf::Font font;
		if( !font.loadFromFile( "Fonts/arial.ttf" ) )
		{
			// error...
		}

		PE physicsEngine;
		physicsEngine.loadSimulation("startup_settings", "startup_entitylist");

		Texture_System background( "Backgrounds/Main_Menu_Background.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 0.0f, 0.0f ), sf::IntRect( 0, 0, 1920 * 1000, 1080 ), 1.f, 1.f, true, true );
		Texture_System border( "Textures/Main screen.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 555.0f, 0.0f ), sf::IntRect( 0, 0, 1031, 756 ), 1.26f, 2.f, true, false );

		Texture_System Box_test( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 10.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test2( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 65.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test3( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 120.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test4( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 175.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test5( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 230.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test6( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 285.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test7( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 340.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test8( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 395.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test9( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 450.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test10( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 505.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test11( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 560.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test12( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 615.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		
		Texture_System Box_test13( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 10.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test14( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 85.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test15( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 160.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );

		Texture_System drag( "Textures/Drag.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 95.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System id( "Textures/ID.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 20.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System mass( "Textures/MASS.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 170.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System posx( "Textures/Position X.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 245.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System posy( "Textures/Position Y.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 320.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System restit( "Textures/Restitution.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 395.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System rotat( "Textures/Rotation.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 470.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System shapeh( "Textures/Shape Height.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 545.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System shapew( "Textures/Shape Width.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 620.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System state( "Textures/STATE.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 695.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System friction( "Textures/FRICTION.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 770.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.4f, 0.4f, true, false );
		Texture_System tracke( "Textures/Track Entity.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 845.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.32f, 0.4f, true, false );
		
		Texture_System velocx( "Textures/Velocity X.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 20.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.32f, 0.4f, true, false );
		Texture_System velocy( "Textures/Velocity Y.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 95.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.32f, 0.4f, true, false );
		Texture_System surfaAr( "Textures/Surface Area.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 25.0f, 170.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.32f, 0.4f, true, false );

		sf::Text T_ID;
		sf::Text T_Drag;
		sf::Text T_Mass;
		sf::Text T_PositionX;
		sf::Text T_PositionY;
		sf::Text T_Restitution;
		sf::Text T_Rotation;
		sf::Text T_ShapeHeight;
		sf::Text T_ShapeWidth;
		sf::Text T_STATE;
		sf::Text T_Friction;
		sf::Text T_TrackEntity;

		sf::Text T_VelocityX;
		sf::Text T_VelocityY;
		sf::Text T_SurfaceArea;

		T_ID.setFont( font );
		T_Drag.setFont( font );
		T_Mass.setFont( font );
		T_PositionX.setFont( font );
		T_PositionY.setFont( font );
		T_Restitution.setFont( font );
		T_Rotation.setFont( font );
		T_ShapeHeight.setFont( font );
		T_ShapeWidth.setFont( font );
		T_STATE.setFont( font );
		T_Friction.setFont( font );
		T_TrackEntity.setFont( font );

		T_SurfaceArea.setFont( font );
		T_VelocityX.setFont( font );
		T_VelocityY.setFont( font );

		T_ID.setFillColor( sf::Color::Red );
		T_Drag.setFillColor( sf::Color::Red );
		T_Mass.setFillColor( sf::Color::Red );
		T_PositionX.setFillColor( sf::Color::Red );
		T_PositionY.setFillColor( sf::Color::Red );
		T_Restitution.setFillColor( sf::Color::Red );
		T_Rotation.setFillColor( sf::Color::Red );
		T_ShapeHeight.setFillColor( sf::Color::Red );
		T_ShapeWidth.setFillColor( sf::Color::Red );
		T_STATE.setFillColor( sf::Color::Red );
		T_Friction.setFillColor( sf::Color::Red );
		T_TrackEntity.setFillColor( sf::Color::Red );

		T_SurfaceArea.setFillColor( sf::Color::Red );
		T_VelocityX.setFillColor( sf::Color::Red );
		T_VelocityY.setFillColor( sf::Color::Red );

		T_ID.setPosition( 255, 20 );
		T_Drag.setPosition( 255, 95 );
		T_Mass.setPosition( 255, 170 );
		T_PositionX.setPosition( 255, 245 );
		T_PositionY.setPosition( 255, 320 );
		T_Restitution.setPosition( 255, 395 );
		T_Rotation.setPosition( 255, 470 );
		T_ShapeHeight.setPosition( 255, 545 );
		T_ShapeWidth.setPosition( 255, 620 );
		T_STATE.setPosition( 255, 695 );
		T_Friction.setPosition( 255, 770 );
		T_TrackEntity.setPosition( 255, 845 );

		T_SurfaceArea.setPosition( 255, 20 );
		T_VelocityX.setPosition( 255, 95 );
		T_VelocityY.setPosition( 255, 170 );

		sf::Time logicTime = sf::seconds(1 / 60);

		sf::Clock logicTimer;
		logicTimer.restart();

		background.setColor( sf::Color( 255, 255, 255, 45 ) );

		int option = 12;
		bool game = true;
		
		while (renderwindow.isOpen() && game)
		{

			renderwindow.clear();

			T_ID.setString( ID );
			T_Drag.setString( Drag );
			T_Mass.setString( Mass );
			T_PositionX.setString( PositionX );
			T_PositionY.setString( PositionY );
			T_Restitution.setString( Restitution );
			T_Rotation.setString( Rotation );
			T_ShapeHeight.setString( ShapeHeight );
			T_ShapeWidth.setString( ShapeWidth );
			T_STATE.setString( STATE );
			T_Friction.setString( Friction );
			T_TrackEntity.setString( TrackEntity );

			elapsed = clock.getElapsedTime();
			background.setPosition( sf::Vector2f( -20 * elapsed.asSeconds(), 0 ) );

			while( renderwindow.pollEvent( e ) )

			while (renderwindow.pollEvent(e))

			{
				if( e.type == sf::Event::TextEntered )
				{
					switch( option )
					{
					case 12:
					{
						if( e.text.unicode < 128 )
							ID += static_cast<char>( e.text.unicode );
					}
					break;
					case 11:
					{
						if( e.text.unicode < 128 )
							Drag += static_cast<char>( e.text.unicode );
					}
					break;
					case 10:
					{
						if( e.text.unicode < 128 )
							Mass += static_cast<char>( e.text.unicode );
					}
					break;
					case 9:
					{
						if( e.text.unicode < 128 )
							PositionX += static_cast<char>( e.text.unicode );
					}
					break;
					case 8:
					{
						if( e.text.unicode < 128 )
							PositionY += static_cast<char>( e.text.unicode );
					}
					break;
					case 7:
					{
						if( e.text.unicode < 128 )
							Restitution += static_cast<char>( e.text.unicode );
					}
					break;
					case 6:
					{
						if( e.text.unicode < 128 )
							Rotation += static_cast<char>( e.text.unicode );
					}
					break;
					case 5:
					{
						if( e.text.unicode < 128 )
							ShapeHeight += static_cast<char>( e.text.unicode );
					}
					break;
					case 4:
					{
						if( e.text.unicode < 128 )
							ShapeWidth += static_cast<char>( e.text.unicode );
					}
					break;
					case 3:
					{
						if( e.text.unicode < 128 )
							STATE += static_cast<char>( e.text.unicode );
					}
					break;
					case 2:
					{
						if( e.text.unicode < 128 )
							Friction += static_cast<char>( e.text.unicode );
					}
					break;
					case 1:
					{
						if( e.text.unicode < 128 )
							TrackEntity += static_cast<char>( e.text.unicode );
					}
					break;
					}
				}

				if( e.type == sf::Event::Closed )
					renderwindow.close();

				if( e.key.code == sf::Keyboard::BackSpace && option == 12 )
					ID = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 11 )
					Drag = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 10 )
					Mass = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 9 )
					PositionX = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 8 )
					PositionY = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 7 )
					Restitution = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 6 )
					Rotation = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 5 )
					ShapeHeight = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 4 )
					ShapeWidth = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 3 )
					STATE = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 2 )
					Friction = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 1 )
					TrackEntity = "";
				

				if( e.type == sf::Event::KeyPressed )
				{
					if( e.key.code == sf::Keyboard::Up && option < 12 )
					{
						option++;
					}
					if( e.key.code == sf::Keyboard::Down && option > 1 )
					{
						option--;
					}
				}
			}
			

			if (logicTimer.getElapsedTime() >= logicTime)
			{
				//if time elapsed since last tick gets too big it will split the time into smaller segments, the max dTime will be 2.5 * tickTime
				float t = logicTimer.restart().asSeconds();
				if(t > 2.5f * logicTime.asSeconds())
					while (t > 2.5f * logicTime.asSeconds())
					{
						physicsEngine.update(logicTime.asSeconds());
						t -= logicTime.asSeconds();
					}

				physicsEngine.update(t);
			}

			switch( option )
			{
			case 12:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 11:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 10:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 9:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 8:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 7:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 6:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 5:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 4:
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 3: 
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 2: 
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 1: 
			{
				Box_test.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test2.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test3.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test4.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test5.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test6.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 255 ) );
			}
			break;
			}

			elapsed = clock.getElapsedTime();
			
			background.draw( renderwindow );
			
			Box_test.draw( renderwindow );
			Box_test2.draw( renderwindow );
			Box_test3.draw( renderwindow );
			Box_test4.draw( renderwindow );
			Box_test5.draw( renderwindow );
			Box_test6.draw( renderwindow );
			Box_test7.draw( renderwindow );
			Box_test8.draw( renderwindow );
			Box_test9.draw( renderwindow );
			Box_test10.draw( renderwindow );
			Box_test11.draw( renderwindow );
			Box_test12.draw( renderwindow );

			id.draw( renderwindow );
			drag.draw( renderwindow );
			mass.draw( renderwindow );
			posx.draw( renderwindow );
			posy.draw( renderwindow );
			restit.draw( renderwindow );
			rotat.draw( renderwindow );
			shapeh.draw( renderwindow );
			shapew.draw( renderwindow );
			state.draw( renderwindow );
			friction.draw( renderwindow );
			tracke.draw( renderwindow );

			renderwindow.draw( T_ID );
			renderwindow.draw( T_Drag );
			renderwindow.draw( T_Mass );
			renderwindow.draw( T_PositionX );
			renderwindow.draw( T_PositionY);
			renderwindow.draw( T_Restitution );
			renderwindow.draw( T_Rotation );
			renderwindow.draw( T_ShapeHeight );
			renderwindow.draw( T_ShapeWidth );
			renderwindow.draw( T_STATE );
			renderwindow.draw( T_Friction );
			renderwindow.draw( T_TrackEntity );

			border.draw( renderwindow );
			physicsEngine.draw(renderwindow);
			renderwindow.display();
		}

	}

	private:
		//misc functions

};
#endif // ! _GAMESYSTEM: