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
	e.setFrictionCoefficient(0.5f);
	e.setDragCoefficient(0.15f);
	e.setEnttityID(ID);
	e.setVelocity(vel);
	e.setAngleRotationDEGREES(rot);
	e.setSillhueteArea(1);

	if (e.getEntityState() != 0) //only track movable objects
		e.setTrackEntityData(true);

	return e;
}

class Game_System
{
public:
	Game_System(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock clock, sf::Time& elapsed)
	{
		PE physicsEngine;
		physicsEngine.init(50, 50, 500, 500, 50, 50);

		//physicsEngine.loadSimulation("testsave");
	//	physicsEngine.addEntity(getEntitySquare(Vec2D(25, 10), 20, 2, 500, 0.0f, 2, 0, Vec2D(0, 0), 10));
		physicsEngine.addEntity(getEntitySquare(Vec2D(0, 25), 5, 5, 15, 1.0f, 0, 1, Vec2D(10, 0), 0));
		physicsEngine.addEntity(getEntitySquare(Vec2D(50, 25), 1, 1, 5, 1.0f, 1, 1, Vec2D(-10, 0), 0));

		sf::Time logicTime = sf::seconds(1.0f / 60.f);
		sf::Clock logicTimer;
		logicTimer.restart();

		bool game = true;
		while (renderwindow.isOpen() && game)
		{
			while (renderwindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
					renderwindow.close();
			}
			if (logicTimer.getElapsedTime() >= logicTime)
			{
				//logic; TODO; split up timer in smaller segments if time gets too big
				physicsEngine.update(logicTimer.restart().asSeconds() );
			}

			elapsed = clock.getElapsedTime();
			renderwindow.clear();
			physicsEngine.draw(renderwindow);
			renderwindow.display();
		}

	}
};
#endif // ! _GAMESYSTEM: