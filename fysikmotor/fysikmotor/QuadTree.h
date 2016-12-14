//quad tree object. used for optimastion, an entity in the first quadrant doesnt need to bechecked with an entity in the third quadrant, avoid unneccesary computing
//clear quadtree after each itteration and readd new entities each itteration

//https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374

//the leaves contains all the entities, nodes only point to the leaf nodes

//Erik Magnusson 8/12 2016

#pragma once
#ifndef  _QUADTREE_
#define _QUADTREE_

#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"
//#include "PEVec2D.h"


class QuadTree
{
private:
	//enums

	enum Type
	{
		LEAF,
		NODE
	};

	enum NodePos
	{
		OVERLAPPING = -1, //if overlapping the boundries for sub nodes
		NW,
		NE,
		SE,
		SW,
		NWNE,
		NWSW

	};

public:
	//functioons
	void destroyQuadTree(); //destroys quad tree, clears entities and destroys sub nodes
	void splitQuadTree(); //attempts to split the quadtree into four partitions/sub nodes
	void addEntity(const Entity& inputEntity); //adds entities to quadtree, edntity will trickle down to a designated leaf node
	int getNodePos(const Entity& inputEntity) const; //returns in what sub node the entitiy belongs, -1 if it doesnt fit
	std::vector<QuadTree>& getEntiesInProximity(const Entity& inputEntity); //returns all entieis that are in proximyu to colide with given entity

	//constructor
	QuadTree(int inputNodeLevel, double XMax, double XMin, double YMax, double YMin);
	//destruyctor
	~QuadTree();

public:
	//members
	const int maxNodeLevel = 8;
	const int maxEntitiesPerNode = 3; //max amount of entities a quadtree can have before it splits into a new quadtree

private:
	//membeers
	int nodeLevel;
	//int type
	int nodePosition;

	double maxX,  //quad tree bounding box of current node
		   minX,
		   maxY,
		   minY;

	std::vector<Entity> entities; //all the entities in the leaf node
	std::vector<QuadTree> nodes; //all the nodes of quadtree the current node has, 4 partitions of the current node layer

};

#endif // ! _QUADTREE_