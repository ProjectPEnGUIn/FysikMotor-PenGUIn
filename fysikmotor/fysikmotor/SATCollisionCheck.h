/*
Seperating axis theorem
a very accurate and precise way of checking for collision between convex shapes
concave shapes need to be split up into convex shapes for them to be usable - will handle that

checks each axis for overlapping, will cancel out if one of them doesnt fully overlapp and return false
IF they are colliding a penentration vector can be retrived, how far inside of eachother the shapes are
that penentrationvector along with both shapes' speed can be used to determine the exact moment when the objects collided
and collisionhandling can be more precise

//http://www.metanetsoftware.com/technique/tutorialA.html#section3 12/1 2017, an article describing SAT
in detail made by an indie game making company. Should be reliable enough of a source
has visual interactive examples of SAT

//http://www.dyn4j.org/2010/01/sat/ 15/12 2016
also describes SAT collision

https://www.youtube.com/watch?v=Ap5eBYKlGDo#t=0.661912 a quick simple guide, not in detail in any shape of form
but shows SAT in a simple way and easy to understand or to get a grip of the general idea

//https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169 12/1 2017
also indepth

use this object and a function that takes in two entities, returns true if colliding. 
then if true it can retrive the penentrationvector

Erik Magnusson NA3 12/1 2017


//new attempt 30/1 2017
http://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection


//4/2
https://www.codeproject.com/Articles/15573/D-Polygon-Collision-Detection
http://elancev.name/oliver/2D%20polygon.htm#tut6
http://www.sevenson.com.au/actionscript/sat/

http://elancev.name/oliver/2D%20polygon.htm#tut6 6/2 2017

http://www.dyn4j.org/2011/11/contact-points-using-clipping/ 9/2 2017
*/

#ifndef  _SATCOLLISIONCHECK_
#define _SATCOLLISIONCHECK_

#include <cmath>
#include <math.h>

#include "VertexShape.h"
#include "PEVec2D.h"

#pragma once
class SATCollisionCheck
{
private:
	//functions

	bool isConvex(const VertexShape& inputEntity) const;
	void SATtest(const Vec2D& inputAxis, const std::vector<Vec2D>& inputPoints, float& minAlong, float& maxAlong);
//	std::vector<Vec2D> getNormalizedNormals(const std::vector<Vec2D>& inputVertices) const; //takes in all vertices and returns all normals
	std::vector<Vec2D> getEdges(const std::vector<Vec2D>& inputVerticies); //returns all edges
	bool overlaps(const float min1, const float max1, const float min2, const float max2);
	inline bool isBetweenOrdered(const float val, const float lowerBound, const float upperBound) const;
	
//	void calculateContactPoints(const VertexShape& inputShape1, const VertexShape& inputShape2) ; //sets the proper contactpoints
//	std::vector<Vec2D> getNearestEdge(const std::vector<Vec2D>& inputShapeVertices, const Vec2D& inputNormal);
//	std::vector<Vec2D> getClippedPoints(const Vec2D& v1, const Vec2D& v2, const Vec2D& n, const float o);

	void calculateContactPoints(const std::vector<Vec2D>& shape1Vertices, const std::vector<Vec2D>& shape2Vertices); //returns the two points forming an edge
	std::vector<Vec2D> getEdge(const std::vector<Vec2D>& shapeVertices, const Vec2D& collisionNormal) const;

public:
	//functions

	bool SATCheck(const VertexShape& inputVertexShape1, const VertexShape& inputVertexShape2);
	void clearVariables(); //resets all variables so it can take in new entities and compare
	float getOverlap() const;
	Vec2D getPenentrationVector() const; //returns
	std::vector<Vec2D> getContactPoints() const; //coords of contact point between

	SATCollisionCheck();

private:
	//members
	
	float overlap;
	std::vector<Vec2D> contactPoints; //global world coordinates where collision occoured
	Vec2D penentrationVector; //vector containing the penentration distance between two objects that are inside eachother //is facing 90 degrees out from contact edge

};
#endif // ! _SATCOLLISIONCHECK_
