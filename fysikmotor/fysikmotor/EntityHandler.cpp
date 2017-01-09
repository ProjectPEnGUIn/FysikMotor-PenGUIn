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
void EntityHandler::entityCollision(Entity& entity1, Entity& entity2) //handles collision between entities
{

}

EntityHandler::EntityHandler()
	:
	worldMaxX(0),
	worldMinX(0),
	worldMaxY(0),
	worldMinY(0)
{
}
