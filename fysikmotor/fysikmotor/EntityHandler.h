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
#include "DataLogger.h"


class EntityHandler
{
private:
	//functions

	void logEntityData(const Entity& e, const float currentDeltaTime, const float totalElapsedTime); //logs entity data onto storedentitydata
	
	void impulseCollision( Entity& e1, Entity& e2); //resolves collision
	//void elapseEntityTime(Entity& inputEntity, const float time); //elapses time for entity

	void updateResultingForce(Entity& e);
	void updateVelocity(Entity& inputEntity, const float inputDeltaTime); //updates velócitiyes on entiteis
	void updatePosition(Entity& inputEntity, const float deltaTime);
	void updateActingForces(Entity& inputEntity);
	void clearActingForces(Entity& inputEntity); //removes all forces acring o nentity and sets resultignforce to 0

	void updatePreviousEntityData(Entity& inputEntity);

	float getAirDensity(const float inputHeight) const ;
	Vec2D getAirDragForce(const Vec2D& inputVelocity, const float inputDragCoefficient, const float inputSillhouetteArea, const float inputheight) const; //returns the air resistance force vector

public:
	//functions

	void setLogData(const bool inputBool);
	void setDataLoggerIntervall(const float intervall);
	void initDataLogger(const std::string& inputFilename, const bool inputOverwriteStatus);

	//void resetTimeCounter();
	//float getTimeCounter() const;

	//update funcrions
	void updateEntities(const float deltaTime); //updates all entities, checks for collisions, handles collisioons

	//add entites
	void addEntity(Entity inputEntity); //adds the entity to the list of entities
	void removeAllEntities();

	//get functions
	float getWorldMaxX();
	float getworldMinX();
	float getWorldMaxY();
	float getWorldMinY();

	std::vector<Entity> getAllEntities(); //retirives all entiteis in pe    

	void init(const float inputMaxX, const float inputMinX, const float inputMaxY, const float inputMinY);
	EntityHandler();
	~EntityHandler(); //default destructor
private:
	//members

	//world boundries in meters
	float worldMaxX, //world max and min cordinates, need to be set before adding entitties. Adds a wall with an entity at those coords
		   worldMinX,
		   worldMaxY,
		   worldMinY;
	
	std::vector<Entity> entities;

	//world variables that apply to all entities
	Vec2D gravitationalAcceleration;  

	float elapsedTime; //total elapsed time
	float timeCounter;

	bool logData;
	float dataLoggerIntervall; //in seconds, will take entity data and log it in that interval
	DataLogger storedEntityData;
};


#endif // !_ENTITYHANDLER_