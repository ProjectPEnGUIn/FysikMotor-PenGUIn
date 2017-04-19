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

std::string ID("");
std::string Drag( "" );
std::string Mass( "" );
std::string PositionX( "" );
std::string PositionY( "" );
std::string Restitution( "" );
std::string Rotation( "" );
std::string ShapeHeight( "" );
std::string ShapeWidth( "" );
std::string STATE( "" );
std::string Friction( "" );
std::string TrackEntity( "" );
std::string VelocityX( "" );
std::string VelocityY( "" );
std::string SurfaceArea( "" );

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
		Texture_System Box_test2( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 70.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test3( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 130.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test4( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 190.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test5( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 250.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test6( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 310.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test7( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 370.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test8( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 430.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test9( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 490.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test10( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 550.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test11( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 610.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test12( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 670.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test13( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 730.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test14( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 790.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );
		Texture_System Box_test15( "Textures/Main_menu_sprite_Sheet.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 225.0f, 850.0f ), sf::IntRect( 224, 496, 1041, 215 ), 0.22f, 0.22f, true, false );

		Texture_System drag( "Textures/Drag.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 75.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System id( "Textures/ID.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 15.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System mass( "Textures/MASS.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 135.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System posx( "Textures/Position X.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 195.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System posy( "Textures/Position Y.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 255.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System restit( "Textures/Restitution.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 315.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System rotat( "Textures/Rotation.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 375.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System shapeh( "Textures/Shape Height.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 435.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System shapew( "Textures/Shape Width.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 495.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System state( "Textures/STATE.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 555.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System friction( "Textures/FRICTION.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 615.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System tracke( "Textures/Track Entity.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 675.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		
		Texture_System velocx( "Textures/Velocity X.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 735.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System velocy( "Textures/Velocity Y.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 795.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );
		Texture_System surfaAr( "Textures/Surface Area.png", sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 35.0f, 855.0f ), sf::IntRect( 0, 0, 1000, 300 ), 0.3f, 0.3f, true, false );

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
		T_Drag.setPosition( 255, 80 );
		T_Mass.setPosition( 255, 140 );
		T_PositionX.setPosition( 255, 200 );
		T_PositionY.setPosition( 255, 260 );
		T_Restitution.setPosition( 255, 320 );
		T_Rotation.setPosition( 255, 380 );
		T_ShapeHeight.setPosition( 255, 440 );
		T_ShapeWidth.setPosition( 255, 500 );
		T_STATE.setPosition( 255, 560 );
		T_Friction.setPosition( 255, 620 );
		T_TrackEntity.setPosition( 255, 680 );
		T_VelocityX.setPosition( 255, 740 );
		T_VelocityY.setPosition( 255, 800 );
		T_SurfaceArea.setPosition( 255, 860 );

		T_ID.setCharacterSize( 18 );
		T_Drag.setCharacterSize( 18 );
		T_Mass.setCharacterSize( 18 );
		T_PositionX.setCharacterSize( 18 );
		T_PositionY.setCharacterSize( 18 );
		T_Restitution.setCharacterSize( 18 );
		T_Rotation.setCharacterSize( 18 );
		T_ShapeHeight.setCharacterSize( 18 );
		T_ShapeWidth.setCharacterSize( 18 );
		T_STATE.setCharacterSize( 18 );
		T_Friction.setCharacterSize( 18 );
		T_TrackEntity.setCharacterSize( 18 );
		T_SurfaceArea.setCharacterSize( 18 );
		T_VelocityX.setCharacterSize( 18 );
		T_VelocityY.setCharacterSize( 18 );
		
		sf::Time logicTime = sf::seconds(1.0f / 60.0f);

		sf::Clock logicTimer;
		logicTimer.restart();

		background.setColor( sf::Color( 255, 255, 255, 45 ) );

		int option = 12;
		bool game = true;

		while (renderwindow.isOpen() && game)
		{


			Entity tempEntity;
			if( getFloatValue( ID ) != FLT_MAX && ID != "" )
				tempEntity.setEnttityID( getFloatValue( ID ));
			if( getFloatValue( Drag ) != FLT_MAX )
				tempEntity.setDragCoefficient( getFloatValue( Drag ) );
			if( getFloatValue( Mass ) != FLT_MAX )
				tempEntity.setMass( getFloatValue( Mass ) );
			if( getFloatValue( PositionX ) != FLT_MAX && PositionX != "" )
				tempEntity.setPosition( Vec2D( getFloatValue( PositionX), tempEntity.getPosition().getY() ) );
		

//			physicsEngine.addEntity( tempEntity );

			T_ID.setString( ID );
			T_Drag.setString( Drag);
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
			T_VelocityX.setString( VelocityX );
			T_VelocityY.setString( VelocityY);
			T_SurfaceArea.setString( SurfaceArea );
			
			elapsed = clock.getElapsedTime();
			background.setPosition( sf::Vector2f( -20 * elapsed.asSeconds(), 0 ) );

			while ( renderwindow.pollEvent(e) )
			{

				std::cout << "loop\n";

				if( e.type == sf::Event::TextEntered )
				{
					switch( option )
					{
					case 15:
					{
						if( e.text.unicode < 128 )
							ID += static_cast<char>( e.text.unicode );
					}
					break;
					case 14:
					{
						if( e.text.unicode < 128 )
							Drag += static_cast<char>( e.text.unicode );
					}
					break;
					case 13:
					{
						if( e.text.unicode < 128 )
							Mass += static_cast<char>( e.text.unicode );
					}
					break;
					case 12:
					{
						if( e.text.unicode < 128 )
							PositionX += static_cast<char>( e.text.unicode );
					}
					break;
					case 11:
					{
						if( e.text.unicode < 128 )
							PositionY += static_cast<char>( e.text.unicode );
					}
					break;
					case 10:
					{
						if( e.text.unicode < 128 )
							Restitution += static_cast<char>( e.text.unicode );
					}
					break;
					case 9:
					{
						if( e.text.unicode < 128 )
							Rotation += static_cast<char>( e.text.unicode );
					}
					break;
					case 8:
					{
						if( e.text.unicode < 128 )
							ShapeHeight += static_cast<char>( e.text.unicode );
					}
					break;
					case 7:
					{
						if( e.text.unicode < 128 )
							ShapeWidth += static_cast<char>( e.text.unicode );
					}
					break;
					case 6:
					{
						if( e.text.unicode < 128 )
							STATE += static_cast<char>( e.text.unicode );
					}
					break;
					case 5:
					{
						if( e.text.unicode < 128 )
							Friction += static_cast<char>( e.text.unicode );
					}
					break;
					case 4:
					{
						if( e.text.unicode < 128 )
							TrackEntity += static_cast<char>( e.text.unicode );
					}
					break;
					case 3:
					{
						if( e.text.unicode < 128 )
							VelocityX += static_cast<char>( e.text.unicode );
					}
					break;
					case 2:
					{
						if( e.text.unicode < 128 )
							VelocityY += static_cast<char>( e.text.unicode );
					}
					break;
					case 1:
					{
						if( e.text.unicode < 128 )
							SurfaceArea += static_cast<char>( e.text.unicode );
					}
					break;
					}
				}

				if( e.type == sf::Event::Closed )
					renderwindow.close();

				if( e.key.code == sf::Keyboard::BackSpace && option == 15 )
					ID = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 14 )
					Drag = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 13 )
					Mass = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 12 )
					PositionX = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 11 )
					PositionY = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 10 )
					Restitution = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 9 )
					Rotation = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 8 )
					ShapeHeight = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 7 )
					ShapeWidth = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 6 )
					STATE = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 5 )
					Friction = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 4 )
					TrackEntity = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 3 )
					VelocityX = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 2 )
					VelocityY = "";
				if( e.key.code == sf::Keyboard::BackSpace && option == 1 )
					SurfaceArea = "";
				

				if( e.type == sf::Event::KeyPressed )
				{
					if( e.key.code == sf::Keyboard::Up && option < 15 )
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
			case 15:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 14:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 13:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 12:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 11:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 10:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 9:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 8:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
			}
			break;
			case 7:
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
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
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
				Box_test7.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
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
				Box_test8.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
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
				Box_test9.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
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
				Box_test10.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test13.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
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
				Box_test11.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 255 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 100 ) );
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
				Box_test12.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test13.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test14.setColor( sf::Color( 255, 255, 255, 100 ) );
				Box_test15.setColor( sf::Color( 255, 255, 255, 255 ) );
			}
			break;
			}

			elapsed = clock.getElapsedTime();
			
			renderwindow.clear();
			background.draw( renderwindow );
			physicsEngine.draw( renderwindow );

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
			Box_test13.draw( renderwindow );
			Box_test14.draw( renderwindow );
			Box_test15.draw( renderwindow );


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
			velocx.draw( renderwindow );
			velocy.draw( renderwindow );
			surfaAr.draw( renderwindow );

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
			renderwindow.draw( T_VelocityX );
			renderwindow.draw( T_VelocityY );
			renderwindow.draw( T_SurfaceArea );

			border.draw( renderwindow );
			
			renderwindow.display();
		}

	}

	private:
		//misc functions

		float getFloatValue( const std::string& inputString )
		{
			std::string s = inputString;

			std::transform( s.begin(), s.end(), s.begin(), ::tolower );
			if( !(s.find_first_not_of( "0123456789.-" ) == std::string::npos ))
				return FLT_MAX;

			return std::stof( inputString );
		}

};
#endif // ! _GAMESYSTEM: