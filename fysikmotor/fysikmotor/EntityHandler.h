//handles everything regarding the entities themselves, collision detection, collisions, updating using timestep, applying forces
//drawing the entiies is not handled here, need to take interpolation in consideration

//Erik Magnusson 5/12 2016

#pragma once
#ifndef _ENTITYHANDLER_
#define _ENTITYHANDLER_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "PEVec2D.h"
#include "Entity.h"
#include "AABBCheck.h"

class EntityHandler
{
private:
	//functions

	//collision checks
	bool SATCheck(const Entity& entity1, const Entity& entity2); //does a thurough check using SAT, seperating axis theorem, very resource intensive, lots of math functions, ex sqrt, cosine, sine. very accurate

	//collision countermeasures
	void entityCollision(Entity& inpputEntity1, Entity& inputEntity2, const Vec2D& penentrationVector, const Vec2D& contactPoint); //handles collision between entities

public:
	//functions

	//update funcrions
	void updateEntities(float deltaTime); //updates all entities, checks for collisions, handles collisioons
	void updateForces(); //update forces on all entites
	void updateAcceleration(); //updates acceleration on entitis
	void updateVelocity(); //updates velócitiyes on entiteis

	//add entites
	void addEntity(Entity inputEntity); //adds the entity to the list of entities

	//get functions
	float getWorldMaxX();
	float getworldMinX();
	float getWorldMaxY();
	float getWorldMinY();

	void init(const int inputMaxX, const int inputMinX, const float inputMaxY, const float inputMinY);

	std::vector<Entity> getAllEntities(); //retirives all entiteis in pe    

	EntityHandler();
private:
	//members

	//world boundries in meters
	float worldMaxX, //world max and min cordinates, need to be set before adding entitties. Adds a wall with an entity at those coords
		   worldMinX,
		   worldMaxY,
		   worldMinY;
	
	std::vector<Entity> entities;

	bool automaticDelete; //deletes entities if they exit world boundries
};

#endif // !_ENTITYHANDLER_