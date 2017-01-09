#include "AABBCheck.h"


bool entityEntityAABBCheck(const Entity& inputEntity1, const Entity inputEntity2)
{
	//does a simple axis alined bounding box check, check if entityys rough outline boxes are touching
	//returns true if they are witin eachother

	//if both entities have a set entity id and that the objects is not checking collision status with itself
	if (inputEntity1.getEntityID() != -1 && inputEntity2.getEntityID() != -1
		&& inputEntity1.getEntityID() != inputEntity2.getEntityID())
	{

		//checks if entity1 is ínside entity 2
		//if a statement is false it will quit checking at the next &&, avoid unnecessary checks
		if (((inputEntity1.getAABBTopLeft().getX() >= inputEntity2.getAABBTopLeft().getX() && inputEntity1.getAABBTopLeft().getX() <= inputEntity2.getAABBMBottomRight().getX())
			|| (inputEntity1.getAABBMBottomRight().getX() >= inputEntity2.getAABBTopLeft().getX() && inputEntity1.getAABBMBottomRight().getX() <= inputEntity2.getAABBMBottomRight().getX()))
			&& //and
			((inputEntity1.getAABBTopLeft().getY() >= inputEntity2.getAABBMBottomRight().getY() && inputEntity1.getAABBTopLeft().getY() <= inputEntity2.getAABBTopLeft().getY())
			|| (inputEntity2.getAABBMBottomRight().getY() >= inputEntity2.getAABBMBottomRight().getY() && inputEntity1.getAABBMBottomRight().getY() <= inputEntity2.getAABBTopLeft().getY())))
		{
			//aabb check is true
			return true;
		}
	}

	//aabb check is false
	return false;
}
bool entityAreaAABBCheck(const Entity& inputEntity, const float& maxX, const float& minX, const float& maxY, const float& minY)
{
	if (((inputEntity.getAABBTopLeft().getX() >= minX && inputEntity.getAABBTopLeft().getX() <= maxX)
		|| (inputEntity.getAABBMBottomRight().getX() >= minX && inputEntity.getAABBMBottomRight().getX() <= maxX))
		&& //and
		((inputEntity.getAABBTopLeft().getY() >= minY && inputEntity.getAABBTopLeft().getY() <=maxY)
	    || (inputEntity.getAABBMBottomRight().getY() >= minY && inputEntity.getAABBMBottomRight().getY() <= maxY)))
	{
		//aabb check is true
		return true;
	}


    //aabb check is false
    return false;
}
bool entityFullyWithinAreaAABBCheck(const Entity& inputEntity, const float& maxX, const float& minX, const float& maxY, const float& minY)
{
	//check to see if entity can be fully contained within the given area

	if (inputEntity.getAABBTopLeft().getX() >= minX && inputEntity.getAABBMBottomRight().getX() <= maxX
		&& inputEntity.getAABBTopLeft().getY() <= maxY && inputEntity.getAABBMBottomRight().getY() >= minY)
		return true;

	return false;
}
bool areaAreaAABBCheck(const float& maxX1, const float& minX1, const float& maxY1, const float& minY1, const float& maxX2, const float& minX2, const float& maxY2, const float& minY2)
{

	std::cout << "ERROR NOT DONE WITH ENTITYAREAAABB FUNCTION\n";

	return false;
}
bool entityPartiallyContainedWithinArea(const Entity& inputEntity, const float& maxX, const float& minX, const float& maxY, const float& minY)
{

	//potential problem, should also return true if it is fully within the given area, just as CanFullContainEntity function
	//canFullyContainEntity should be called and handled with first to avoid errors

	//checks if the given area can contain atleast a part of a given entity, simple aabb check
	if (((inputEntity.getAABBTopLeft().getX() >= minX && inputEntity.getAABBTopLeft().getX() <= maxX)
		|| (inputEntity.getAABBMBottomRight().getX() >= minX && inputEntity.getAABBMBottomRight().getX() <= maxX))
		&&
		((inputEntity.getAABBTopLeft().getY() >= minY && inputEntity.getAABBTopLeft().getY() <= maxY)
		|| (inputEntity.getAABBMBottomRight().getY() >= minY && inputEntity.getAABBMBottomRight().getY() <= maxY)))
	{
		return true;
	}

	return false;
}