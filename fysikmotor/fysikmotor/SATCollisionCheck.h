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

Erik Magnusson NA3 1/12 2017
*/

#ifndef  _SATCOLLISIONCHECK_
#define _SATCOLLISIONCHECK_

#include "Entity.h"
#include "PEVec2D.h"

#pragma once
class SATCollisionCheck
{
private:
	//functions

public:
	//functions

	bool SATCheck(const Entity& inputEntity1, const Entity& inputEntity2) const;
	void clearVariables(); //resets all variables so it can take in new entities and compare
	Vec2D getPenentrationVector() const; //returns
	Vec2D getContactPoint() const; //coords of contact point between

	SATCollisionCheck();

private:
	//members
	
	Vec2D contactPoint; //the point, pos, at which the entities are touching
	Vec2D penentrationVector; //vector containing the penentration distance between two objects that are inside eachother

};
#endif // ! _SATCOLLISIONCHECK_