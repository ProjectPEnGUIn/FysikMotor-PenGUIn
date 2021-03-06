/*
Physics Engine
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

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 

#include "EntityHandler.h"
#include "DrawHandler.h"
#include "ReadFile.h"

class PE
{
private:
	//functions

public:
	//functions

	void init(const float inputSimulationWidth, const float inputSimulationHeight, const int imageWidth, const int imageHeight, const float imageScreenXPos, const float imageScreenYPos);
	void addEntity(const Entity& inputEntity);
	void clearEntities();
	void draw(sf::RenderWindow& inputRenderwindow);
	void update(const float& deltaTime);
	Entity getEntity(const int ID);
	void setEnttiy(const Entity& e, const int ID);

	void loadSimulation(const std::string& settingsFilename, const std::string& entitylistFilename); //loads simulation scenario
	void saveSimulation(const std::string& filename, bool allowToOverwritePreviousData); //saves current

	PE();

private:
	//members

	EntityHandler entityHandler; //handles everything with entities, moving them around and checking for collisions -> handle collisions etc
	DrawHandler drawHandler; //does all the drawing with use of entities from entityhandler
};

#endif // !_PE_