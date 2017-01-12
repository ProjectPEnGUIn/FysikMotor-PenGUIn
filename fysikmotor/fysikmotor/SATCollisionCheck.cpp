#include "SATCollisionCheck.h"


bool SATCollisionCheck::SATCheck(const Entity& inputEntity1, const Entity& inputEntity2) const
{

	return false;
}
void SATCollisionCheck::clearVariables() //resets all variables so it can take in new entities and compare
{
	penentrationVector.setXY(0, 0);
}
Vec2D SATCollisionCheck::getPenentrationVector() const //returns
{
	return penentrationVector;
}

SATCollisionCheck::SATCollisionCheck()
	:
	penentrationVector()
{
}
