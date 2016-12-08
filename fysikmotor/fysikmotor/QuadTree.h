//quad tree object. used for optimastion, an entity in the first quadrant doesnt need to bechecked with an entity in the third quadrant, avoid unneccesary computing
//clear quadtree after each itteration and readd new entities each itteration

//https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374

//Erik Magnusson 8/12 2016

#pragma once
#ifndef  _QUADTREE_
#define _QUADTREE_

#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"
//#include "PEVec2D.h"

constexpr int maxNodeLevel = 5;
constexpr int maxEntitiesPerNode = 4; //max amount of entities a quadtree can have before it splits into a new quadtree

class QuadTree
{
private:

	enum class Type
	{
		LEAF,
		NODE
	};

public:
	//functioons
	void clearQuadTree(); //clears the quadtree of entity objects
	

	//constructor
	QuadTree(int inputNodeLevel, double XMax, double XMin, double YMax, double YMin);

private:
	//membeers
	int nodeLevel;

	double maxX,  //quad tree bounding box of current node
		   minX,
		   maxY,
		   minY;

	std::vector<Entity> entityList; //all the entities in the node

};

#endif // ! _QUADTREE_