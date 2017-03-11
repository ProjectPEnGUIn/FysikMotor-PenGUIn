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
#include "SATCollisionCheck.h"


class EntityHandler
{
private:
	//functions

	
	void impulseCollision( Entity& e1, Entity& e2); //resolves collision
	void elapseEntityTime(Entity& inputEntity, const float time); //elapses time for entity

	void updateResultingForce(Entity& e);
	//void updateAcceleration(Entity& inputEntity); //updates acceleration on entitis
	void updateVelocity(Entity& inputEntity, const float inputDeltaTime); //updates velócitiyes on entiteis
	void updatePosition(Entity& inputEntity, const float deltaTime);
	void updateActingForces(Entity& inputEntity);
	void clearActingForces(Entity& inputEntity);

	void updatePreviousEntityData(Entity& inputEntity);

	float getAirDensity(const float inputHeight) const ;
	Vec2D getAirDragForce(const Vec2D& inputVelocity, const float inputDragCoefficient, const float inputSillhouetteArea, const float inputheight) const; //returns the air resistance force vector

public:
	//functions

	//update funcrions
	void updateEntities(const float deltaTime); //updates all entities, checks for collisions, handles collisioons
	

	void elapseEntityTime(const Entity& inputEntity, const float deltaTime); //elapses time for a single entity

	//add entites
	void addEntity(Entity inputEntity); //adds the entity to the list of entities

	//get functions
	float getWorldMaxX();
	float getworldMinX();
	float getWorldMaxY();
	float getWorldMinY();

	void init(const float inputMaxX, const float inputMinX, const float inputMaxY, const float inputMinY);

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

	//world variables that apply to all entities
	Vec2D gravitationalAcceleration;  


	bool temp;
	float tempElapsedTime;
	Vec2D tempVec;
};

#endif // !_ENTITYHANDLER_