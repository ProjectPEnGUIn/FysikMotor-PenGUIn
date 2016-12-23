//quad tree object. used for optimastion, an entity in the first quadrant doesnt need to bechecked with an entity in the third quadrant, avoid unneccesary computing
//clear quadtree after each itteration and readd new entities each itteration

//https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
//http://gamedev.stackexchange.com/questions/63536/how-do-shapes-rectangles-work-in-quad-trees 15/12 2016

//-----------------------------------------------------

//quadtree attempt two, first version got messy, still use previously mentioned links
//Erik Magnusson 20/12 2016

/*
a quadtree object contains entity objects until a certain amount, then it will split into sub quadtree objects and try to send
the entity objects down the tree to new designated sub quadtrees, if a entity's shape can be fully contain within the given 
quadtree regions it will be sent down to that sub quadtree. If it can't fully fit it will stay in the parrent quadtree.

used for minimizing the amount of checks between entities for collison, an entity only needs to check collisions with other
entities within the same sub quadtree AND entieies that couldn't be sent down the quadtree system in higher aerchy quadtrees

basiclly split the world into quadrants and the quadrants into subquadrants

use entity's aabb pos for entity position in quadtree, does not have to be very accurate because quadtreecheck is jsut a quick check to eliminate
>>very<< unnessecary collisionchecks, for example entities in oposite corners, there is no way they can colide

-inputentity function - add entity to quadtree object, if needed it will push the entity down into its sub node and so on
-does entity fit in current quadtree object? function - used to check if the entity can be sent down into its sub node
-getnearbyentites function - input a entity object and it will go down the hiarchy of quadtrees to find all nearby enties to the inputentity
-clear quadtree function - clear quadtree object and all its sub quadtrees, needs to be done every tick
-send entity down quadtree sub nodes IF possilble
*/


#pragma once
#ifndef  _QUADTREE_
#define _QUADTREE_

#include <vector>

#include "Entity.h"
#include "PEVec2D.h"

class Quadtree
{
public:
	//enums

	enum SubTree //easier naming scheme of sub quadtree objects
	{
		ERROR = -1, //something most likely went wrong
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT,
		CANNOTBEFULLYCONTAINED //if entity can not be fully contained within the quadtree
	};

private:
	//functions

	void splitQuadtree();
	int getEntityBelonging(const Entity& inputEntity) const; //returns a belonging enum from subtree enum
	bool canFullyContainEntity(const Entity& inputEntity, const float& inputMaxX, const float& inputMinX, const float& inputMaxY, const float& inputMinY) const;
	bool canPartiallyContainEntity(const Entity& inputEntity, const float& inputMaxX, const float& inputMinX, const float& inputMaxY, const float& inputMinY) const;

public:
	//functions

	void addEntity(const Entity& inputEntity);
	void clearEntities();
	std::vector<Entity> getNearbyEntities(const Entity& inputEntity);

	Quadtree(int inputCurrentQuadtreeDepth, float maxX, float minX, float maxY, float minY);

private:
	//members

	//quadtree boundries
	float maxX,
		minX,
		maxY,
		minY;
	
	unsigned int currentQuadtreeDepth;

	std::vector<Entity> entitiesStored; //all the entities that the current quadtree object is storing at the moment

	std::vector<Quadtree> subQuadtrees; //sub quadtree objects of current quadtree, four quadrants of current quadtree

	unsigned int entityThreshold; //the max amount of entityies the quadtree object can have without trying to create sub nodes and push the entites down into them
	unsigned int maxQuadtreeDepth; //the maximum amount of levels the quadtree can have, else it will expand infinitly.

};

#endif // ! _QUADTREE_

