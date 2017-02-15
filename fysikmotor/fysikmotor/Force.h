/*
Simple force class to handle forces on objects
has a force vector and an offset vector,
offset is from the center of object
lightweight and will probably come of use when handling torque and such


Erik Magnusson 9/2
*/


#pragma once
#ifndef _FORCE_
#define _FORCE_

#include <string>

#include "PEVec2D.h"

class Force
{
private:
	//functions

public:

	void setForce(const Vec2D& inputForce);
	void setOffset(const Vec2D& inputOffset);
	void setName(const std::string& inputName);

	Vec2D getForce() const; //gets the force
	Vec2D getOffset() const; //gets force offset from the center
	std::string getName() const; //gets the name of the force

	Force();
	Force(const Vec2D& inputForce, const Vec2D& inputOffset, const std::string& inputName);
	Force(const Vec2D& inputForce, const Vec2D& inputOffset);

private:
	//members

	Vec2D force; //the force itself
	Vec2D offset; //the force offset from the center

	std::string name; //name of the force, could be useful

};
#endif // !_FORCE_

