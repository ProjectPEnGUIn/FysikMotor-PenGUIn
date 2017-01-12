#include "EntityHandler.h"

//collision checks

bool EntityHandler::SATCheck(const Entity& entity1, const Entity& entity2) //does a thurough check using SAT, seperating axis theorem, very resource intensive, lots of math functions, ex sqrt, cosine, sine. very accurate
{
	//seperating axis theorem check, 20/12 2016
	//very thurough collision check, downside: very resource intensive, lots of math functions need to be called with sqrt, sine, cosine, tan
	//pros: one type of collision check between all possible shapes of entities
	//handle both convec shapes and non convex shape by splitting up non convex shapes into convex sub parts
	//mainly use http://www.dyn4j.org/2010/01/sat/ for this


	
	//SAT check if false
	return false;
}
//collision countermeasures
void EntityHandler::entityCollision(Entity& InputEntity1, Entity& inputEntity2, const Vec2D& penentrationVector) //handles collision between entities
{
	//asumes the entities are colliding, they are inside of eachother which means there is a penentrationvector 

	//used https://en.wikipedia.org/wiki/Coefficient_of_restitution 12/1 2017
	//and Fysik 1, Impuls Written by Lars Frankel, Daniel Gottfridsson and  Ulf Jonasson and published by GLEERUPS in 2011
	//Used pages 167, 168, 169 and the chapter summerisation

	//use penentrationvector to accuratly handle collisions, exact time.
	//use it to move entities around as if they never traveled useless distance while inside of eachother

	//store inital velocities of both entities
	Vec2D  entity1V0 = InputEntity1.getVelocity(), entity2V0 = inputEntity2.getVelocity();

	//average resutution coefficient, not sure how to handle different entities with different restutuions yet
	float restitution = (InputEntity1.getRestitutionCoefficient() + inputEntity2.getRestitutionCoefficient()) / 2.0f;

	//set both new speeds and position on entity
	Vec2D entity1Vf, entity2Vf; //final velocities

	//along x axis
	entity1Vf = (  InputEntity1.getMass() * entity1V0.getX()


}

EntityHandler::EntityHandler()
	:
	worldMaxX(0),
	worldMinX(0),
	worldMaxY(0),
	worldMinY(0)
{
}
