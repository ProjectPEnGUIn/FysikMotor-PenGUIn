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

public:
	//functions

	void init(float inputMaxX, float inputMinX, float inputMaxY, float inputMinY);
	void addEntity(const Entity& inputEntity);
	void draw(sf::RenderWindow& inputRenderwindow);
	void update(const float& deltaTime);
	void getEvent(sf::Event& inputEvent);

	PE();

private:
	//members

	EntityHandler entityHandler;
	DrawHandler drawHandler;

};

#endif // !_PE_