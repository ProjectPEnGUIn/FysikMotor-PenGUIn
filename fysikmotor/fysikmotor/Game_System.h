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
	Game_System(sf::RenderWindow& renderwindow, sf::Event& e, sf::Clock clock, sf::Time& elapsed)
	{
		PE physicsEngine;
		physicsEngine.init(30, 30, 500, 500, 50, 50);


		VertexShape s1, s2;
		s1.addVertexPoint(Vec2D(0, 0));
		s1.addVertexPoint(Vec2D(0, 5));
		s1.addVertexPoint(Vec2D(20, 5));
		s1.addVertexPoint(Vec2D(20, 0));
		s2.addVertexPoint(Vec2D(0, 0));
		s2.addVertexPoint(Vec2D(0, 5));
		s2.addVertexPoint(Vec2D(5, 5));
		s2.addVertexPoint(Vec2D(5, 0));
		Entity e1, e2;
		e1.setVertexShape(s1);
		e2.setVertexShape(s2);
		e1.setEnttityID(1);
		e2.setEnttityID(2);
		e1.setEntityState(0);
		e2.setEntityState(1);
		e1.setPosition(Vec2D(15, 2.5));
		e2.setPosition((Vec2D(15, 27.5)));
		e1.setMass(10);
		e2.setMass(1);
		e2.setVelocity(Vec2D(1, 0));
		e1.setRestitutionCoefficient(0.499f);
		e2.setRestitutionCoefficient(0.499f);
		physicsEngine.addEntity(e1);
		physicsEngine.addEntity(e2);

		sf::Time logicTime = sf::seconds(1 / 60);
		sf::Clock logicTimer;

		bool game = true;
		while (renderwindow.isOpen() && game)
		{
			renderwindow.clear();

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
			physicsEngine.draw(renderwindow);
			renderwindow.display();
		}
	}
};
#endif // ! _GAMESYSTEM: