#include "EntityHandler.h"

//collision checks
bool EntityHandler::aabbCheck(const Entity& entity1, const Entity& entity2) //does a quick aabb check to see if its posible for the two entites to colide, axis alinged bounding box, not resource intensive
{
	//does a simple axis alined bounding box check, check if entityys rough outline boxes are touching
	//returns true if they are witin eachother

	//if both entities have a set entity id and that the objects is not checking collision status with itself
	if (entity1.getEntityID() != -1 && entity2.getEntityID() != -1
		&& entity1.getEntityID() != entity2.getEntityID())
	{
		//entity plane has a positive y up, negative y down
		//positvie x right, negative x left

		//top right aabb coords are the top right, min x, max y
		//bottom left aabb coords are bottom eft, max x, min y

		//for a simple aabb collision to be true:

		//left edge of e1 has to be inside of e2 x boundries, e2.x || e2.x + width
		//OR
		//right edge of e1 has to be inside of e2 x boundries e2.x || e2.x + width

		//AND

		//top edge of e1 has to be inside of e2 y boundries e2.y || e2.x + height
		//OR
		//bottom edge has to inside of e2 y boundries e2.y || e2.y + height
		
		//checks if entity1 is ínside entity 2
		//if a statement is false it will quit checking at the next &&, avoid unnecessary checks
		if (((entity1.getAABBTopLeft().getX() >= entity2.getAABBTopLeft().getX() && entity1.getAABBTopLeft().getX() <= entity2.getAABBMBottomRight().getX())
			|| //or
			(entity1.getAABBMBottomRight().getX() >= entity2.getAABBTopLeft().getX() && entity1.getAABBMBottomRight().getX() <= entity2.getAABBMBottomRight().getX()))
			&& //and
			((entity1.getAABBTopLeft().getY() >= entity2.getAABBMBottomRight().getY() && entity1.getAABBTopLeft().getY() <= entity2.getAABBTopLeft().getY())
			|| //or
			(entity1.getAABBMBottomRight().getY() >= entity2.getAABBMBottomRight().getY() && entity1.getAABBMBottomRight().getY() <= entity2.getAABBTopLeft().getY())))
		{
			//aabb check is true
			return true;
		}
	}

	//aabb check is false
	return false;
}
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
