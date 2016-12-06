//handles everything regarding the entities themselves, collision detection, collisions, updating using timestep, applying forces
//drawing the entiies is not handled here, need to take interpolation in consideration

//split upp entities in different sectors on a quad tree

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

class EntityHandler
{
private:
	//functions

	//setup functions
	void setupQuadTree(); //inits and sets up the quad tree

	//collision checks, takes in consideration of what type both of the enttiies are
	bool aabbCheck(const Entity& entity1, const Entity& entity2); //does a quick aabb check to see if its posible for the two entites to colide, axis alinged bounding box, not resource intensive
	bool satCheck(const Entity& entity1, const Entity& entity2); //does a thurough check using SAT, seperating axis theorem, very resource intensive, lots of math functions, ex sqrt, cosine, sine. very accurate

	//collision countermeasures
	void entityCollision(const Entity& entity1, const Entity& entity2); //handles collision between entities

	//update functions
	void updateQuadTree(); //updates quadtree with entities, reorgnisies entities IF needed
	
public:
	//functions

	EntityHandler();
private:
	//members

	//world boundries in meters
	double worldXMax, //world max and min cordinates, need to be set before adding entitties. Adds a wall with an entity at those coords
		   worldXMin,
		   worldYMax,
		   worldYMin;
	
	int quadTreeMaxEntities; //max amont of entities in the same part of quadtree

	std::vector<std::vector<Entity>> entitys; //all entities that exists, split into different vectors depending on where on the gameworld they are, using quadtree

};

#endif // !_ENTITYHANDLER_