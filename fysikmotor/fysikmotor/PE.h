/*
object that has inherits all the objects
object to interface wirh all the other objects

Erik Magnusson 15/1 2017
*/

#pragma once
#ifndef _PE_
#define _pe_

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include "EntityHandler.h"
#include "DrawHandler.h"

class PE
{
private:
	//functions

	void updateEntityHandlerLogic();
	void updateDrawHandlerLogic();

public:
	//functions

	void init(const float inputSimulationWidth, const float inputSimulationHeight, const int imageWidth, const int imageHeight, const float imageScreenXPos, const float imageScreenYPos);
	void addEntity(const Entity& inputEntity);
	void clearEntities();
	void draw(sf::RenderWindow& inputRenderwindow);
	void update(const float& deltaTime);
	void inputEvent(sf::Event& inputEvent);

	PE();

private:
	//members

	EntityHandler entityHandler; //handles everything with entities, moving them around and checking for collisions -> handle collisions etc
	DrawHandler drawHandler; //does all the drawing with use of entities from entityhandler
	//LogicHandler logicHandler; //handles all the PE logic, takes input etc
};

#endif // !_PE_