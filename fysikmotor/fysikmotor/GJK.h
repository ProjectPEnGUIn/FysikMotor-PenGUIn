
/*

convex n shape collision detection algorithm using GJK, uses minskows differenaces
GJK - Gilbert Johnsson Keerthi
Could not get SAT to function properly so im giving this a shot

sources taken 1/2 2017
http://www.cs.sjsu.edu/faculty/pollett/masters/Semesters/Spring12/josh/GJK.html
http://www.cs.sjsu.edu/faculty/pollett/masters/Semesters/Spring12/josh/gjk_example_code.txt
https://www.youtube.com/watch?v=Qupqu1xe7Io
http://stackoverflow.com/questions/3076204/collision-points-in-gjk
http://realtimecollisiondetection.net/pubs/SIGGRAPH04_Ericson_GJK_notes.pdf
http://www.dyn4j.org/2010/05/epa-expanding-polytope-algorithm/#epa-start

http://www.dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/
http://in2gpu.com/2014/05/12/gjk-algorithm-collision-detection-2d-in-c/
http://entropyinteractive.com/2011/04/gjk-algorithm/

goals: detect n shaped convex polygon overlapping, get penentration vector/MTV/overlap, get collision coordinates

Erik Magnusson 1/2 2017

*/

#pragma once
#ifndef  _GJK_
#define _GJK_

#include <iostream>
#include <vector>

#include "PEVec2D.h"
#include "Entity.h"

class GJK
{
private:
	//functions
	
	enum simplexCorner{A, B, C};

	bool isShapeConvex(const Entity& inputEntity) const;

	void negateVector(Vec2D& inputVector);
	bool processSimplex(Vec2D& direction);
	Vec2D getFarthestPointInDirection(const VertexShape& inputShape, const Vec2D& inputDirection) const;
	Vec2D support(const VertexShape& inputShape1, const VertexShape& inputShape2, const Vec2D& inputDirection) const;
	bool isSameDirection(const Vec2D& inputVector1, const Vec2D& inputVector2) const;

public:
	//functions

	Vec2D getMTV() const; //returns the minimum translation vector
	std::vector<Vec2D> getContactPoints() const; //returns all the contact points in global coordinates
	bool collisionCheck(const VertexShape& inputShape1, const VertexShape& inputShape2);
	void reset() const; //resets all object variables

	GJK();

private:
	//members

	Vec2D simplex[3] = { Vec2D(FLT_MAX, FLT_MAX), Vec2D(FLT_MAX, FLT_MAX), Vec2D(FLT_MAX, FLT_MAX) };


	std::vector<Vec2D> contactPoints;
	Vec2D minimumTranslationVector;

};
#endif // ! _GJK_
