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

class Game_System
{
public:
	Game_System(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock clock, sf::Time& elapsed)
	{
		PE physicsEngine;
	//	physicsEngine.init(20, 20, 500, 500, 50, 50);

		//physicsEngine.addEntity(getEntitySquare(Vec2D(10, 2), 20, 0.5, 10, 1.0f, 0, 0, Vec2D(0, 0), 35));
		//physicsEngine.addEntity(getEntitySquare(Vec2D(10, 20), 3, 1, 5, 1.0f, 1, 1, Vec2D(0, 0), 0));
	//	physicsEngine.addEntity(getEntitySquare(Vec2D(16, 10), 2, 4, 7, 1.0f, 2, 1, Vec2D(0, 0), 35));

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

			elapsed = clock.getElapsedTime();
			renderwindow.clear();
			physicsEngine.draw(renderwindow);
			renderwindow.display();
		}

	}
};
#endif // ! _GAMESYSTEM: