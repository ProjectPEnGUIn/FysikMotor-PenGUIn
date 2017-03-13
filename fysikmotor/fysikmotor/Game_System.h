//#pragma once
//
//#ifndef  _GAMESYSTEM_
//#define _GAMESYSTEM_
//
//#include "Sound_system.h"
//#include "Texture_System.h"
//#include "Font_System.h"
//
//#include "PE.h" //physics engine module
//#include "DataLogger.h"
//
//Entity getEntitySquare(Vec2D pos, float width, float height, float mass, float cor, int ID, int state, Vec2D vel, float rot)
//{
//	Entity e;
//	VertexShape s;
//	e.setEntityState(state);
//	s.addVertexPoint(Vec2D(0, 0));
//	s.addVertexPoint(Vec2D(0, height));
//	s.addVertexPoint(Vec2D(width, height));
//	s.addVertexPoint(Vec2D(width, 0));
//	e.setVertexShape(s);
//	e.setPosition(pos);
//	e.setMass(mass);
//	e.setRestitutionCoefficient(cor);
//	e.setFrictionCoefficient(0);
//	e.setDragCoefficient(0);
//	e.setEnttityID(ID);
//	e.setVelocity(vel);
//	e.setAngleRotationDEGREES(rot);
//
//	if (e.getEntityState() != 0) //only track movable objects
//		e.setTrackEntityData(true);
//
//	return e;
//}
//
//class Game_System
//{
//public:
//	Game_System(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock clock, sf::Time& elapsed)
//	{
//
//		PE physicsEngine;
//		physicsEngine.init(10, 10, 500, 500, 50, 50);
//
//		physicsEngine.addEntity(getEntitySquare(Vec2D(5, 3), 5, 1, 100, 0.35, 3, 0, Vec2D(0, 0), 30));
//		physicsEngine.addEntity(getEntitySquare(Vec2D(5, 10), 1, 0.5, 5, 0.35, 2, 1, Vec2D(-1, 0),30));
//	
//		sf::Time logicTime = sf::seconds(1 / 60.f);
//		sf::Clock logicTimer;
//
//		bool game = true;
//		while (renderwindow.isOpen() && game)
//		{
//			renderwindow.clear();
//
//			while (renderwindow.pollEvent(e))
//			{
//				if (e.type == sf::Event::Closed)
//					renderwindow.close();
//			}
//
//			if (logicTimer.getElapsedTime() >= logicTime)
//			{
//				
//				//logic; TODO; split up timer in smaller segments if time gets too big
//				physicsEngine.update(logicTimer.restart().asSeconds() );
//			}
//
//			elapsed = clock.getElapsedTime();
//			physicsEngine.draw(renderwindow);
//			renderwindow.display();
//
//		}
//
//	}
//};
//#endif // ! _GAMESYSTEM: