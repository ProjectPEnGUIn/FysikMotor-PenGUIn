#include "QuadTree.h"

void Quadtree::splitQuadtree()
{
	//tries to split the quadtree region into four sub regions, aka new quadtrees 
	//tries to move entities down into the new sub quadtrees

	//if it needs to be split or if it CAN be split even deeper
	if (subQuadtrees.size() == 0 && currentQuadtreeDepth < maxQuadtreeDepth)
	{
		//create four sub quadtrees at a depth higher than current one
		Quadtree topLeft(currentQuadtreeDepth + 1, (minX + maxX) / 2, minX, maxY, (minY + maxY) / 2), //2nd quadrant
			topRight(currentQuadtreeDepth + 1, maxX, (minX + maxX) / 2, maxY, (minY + maxY) / 2), //1st quadrant
			bottomLeft(currentQuadtreeDepth + 1, (minX + maxX) / 2, minX, (maxY + minY) / 2, minY), //3rd quadrant
			bottomRight(currentQuadtreeDepth + 1, maxX, (minX + maxX) / 2, (maxY + minY) / 2, minY); //4th quadrant

		//input the quadtrees into quadtree holder, order is important, corresponds with subtree enum scheme
		subQuadtrees.push_back(topLeft);
		subQuadtrees.push_back(topRight);
		subQuadtrees.push_back(bottomLeft);
		subQuadtrees.push_back(bottomRight);

		//try to input entieis that exists in current quadtree into sub quadtrees, if they dont fit they will stay in current quadtree entity holder

		//goes through each entity, goes backwards through the vector, can delete elements while passing through and ti will not screw up order for next coming entities
		for (unsigned int i = entitiesStored.size(); i >= 0; i--)
		{
			int entityBelonging = getEntityBelonging(entitiesStored[i]);

			//checks so entitybelonging is within 0 and 3, aka in one of the subqaudtrees, if enttitybelonging is 4 it cannot be fully cotnaied so it wont try to insert it
			//if entity cannot be fully contained, aka entitybelonging == 4 it will skip the line of code and it will stay in current pos
			if (entityBelonging >= 0 && entityBelonging <= 3 && entityBelonging != 4 && entityBelonging != -1)
			{
				subQuadtrees[entityBelonging].addEntity(entitiesStored[i]); //ERROR C2280

				entitiesStored.erase(entitiesStored.begin() + i); //removes the curren entity from this quadtree entity holder,
			}
		}
	}
	else
		std::cout << "ERROR: tried to split quadtree that doesnt need splitting?";

}
int Quadtree::getEntityBelonging(const Entity& inputEntity) const //returns a belonging enum from subtree enum
{
	//returns if it belongs in a subquadtree/quadrant or if it cannot be fully contained, corrspends with subtree enum scheme

	if (canFullyContainEntity(inputEntity, (minX + maxX) / 2, minX, maxY, (minY + maxY) / 2) == true)
		return TOPLEFT;
	else if (canFullyContainEntity(inputEntity, maxX, (minX + maxX) / 2, maxY, (minY + maxY) / 2) == true)
		return TOPRIGHT;
	else if (canFullyContainEntity(inputEntity, (minX + maxX) / 2, minX, (maxY + minY) / 2, minY) == true)
		return BOTTOMLEFT;
	else if (canFullyContainEntity(inputEntity, maxX, (minX + maxX) / 2, (maxY + minY) / 2, minY) == true)
		return BOTTOMRIGHT;
	//checks if entrity can be contaiend in current quadtree depth
	else if (canPartiallyContainEntity(inputEntity, maxX, minX, maxY, minY) == true)
		return CANNOTBEFULLYCONTAINED;

		return -1;

}
bool Quadtree::canFullyContainEntity(const Entity& inputEntity, const float& inputMaxX, const float& inputMinX, const float& inputMaxY, const float& inputMinY) const
{
	//check to see if entity can be fully contained within the given area

	if (inputEntity.getAABBTopLeft().getX() >= minX && inputEntity.getAABBMBottomRight().getX() <= maxX
		&& inputEntity.getAABBTopLeft().getY() <= maxY && inputEntity.getAABBMBottomRight().getY() >= minY)
		return true;

	return false;
}
bool Quadtree::canPartiallyContainEntity(const Entity& inputEntity, const float& inputMaxX, const float& inputMinX, const float& inputMaxY, const float& inputMinY) const
{
	//potential problem, should also return true if it is fully within the given area, just as CanFullContainEntity function
	//canFullyContainEntity should be called and handled with first to avoid errors

	//checks if the given area can contain atleast a part of a given entity, simple aabb check
	if (((inputEntity.getAABBTopLeft().getX() >= minX && inputEntity.getAABBTopLeft().getX() <= maxX) 
		|| (inputEntity.getAABBMBottomRight().getX() >= minX && inputEntity.getAABBMBottomRight().getX() <= maxX))
		&& 
		((inputEntity.getAABBTopLeft().getY() >= minY && inputEntity.getAABBTopLeft().getY() <= maxY)
		|| (inputEntity.getAABBMBottomRight().getY() >= minY && inputEntity.getAABBMBottomRight().getY() <= maxY)))
		return true;

	return false;
}
void Quadtree::addEntity(const Entity& inputEntity)
{
	//checks if current quadtree need to split
	if (entitiesStored.size() > entityThreshold && subQuadtrees.size() == 0)
		splitQuadtree();

	if (subQuadtrees.size() == 4) //checks to see if there are sub quadtrees
	{
		//tries to add the entitie to a sub quadtree, if it doesnt fit it will add to current quadtree entity holder

		int entityBelonging = getEntityBelonging(inputEntity);
		
		if (entityBelonging >= 0 && entityBelonging < 4 && entityBelonging != 4 && entityBelonging != -1)
			subQuadtrees[entityBelonging].addEntity(inputEntity); //adds it to désignated sub quadtree
		else
			entitiesStored.push_back(inputEntity); //adds it to current quadtree entity holder
	}
	else 
		entitiesStored.push_back(inputEntity); //if there are no sub quadtrees it will add entties ontyo current quadtree entiy hodler
}
void Quadtree::clearEntities()
{
	//first clears sub quadtrees, then deletes them and then deletes current entity list, is recursive

	if (subQuadtrees.size() == 4) //if there are any sub quadtrees
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			subQuadtrees[i].clearEntities();
		}
		subQuadtrees.clear();
	}

	entitiesStored.clear();
}
std::vector<Entity> Quadtree::getNearbyEntities(const Entity& inputEntity)
{
	//tries to get entities from subquadtrees before returning a vector of entities
	//add the entittyies from sub quadtrees onto this vectopr of returning entities

	//if an entity cannot be fully contained within a subquadtree it will return entites from the subqaudtrees it overlaps with

	std::vector<Entity> returnVector;

	//copies over the elements to the returnvector from current quadtree entityies
	returnVector.insert(returnVector.end(), entitiesStored.begin(), entitiesStored.end()); //adds the two vectors together

	if (subQuadtrees.size() == 4) //if there are any sub quadtrees, retrive needed entieis from them
	{
		std::vector<Entity> tempVector;
		//check if enties need to be retrived from each sub quadtree/quantrant

		//checks where entity belongs, in what quadrant it should try to get nearby entties from
		int entityBelonging = getEntityBelonging(inputEntity);
	    if(entityBelonging >= 0 && entityBelonging < 4 && entityBelonging != 4 && entityBelonging != -1)
		{
			tempVector = subQuadtrees[entityBelonging].getNearbyEntities(inputEntity);
			
			returnVector.insert(returnVector.begin(), tempVector.begin(), tempVector.end());
			tempVector.clear();
		}
		else if (entityBelonging == CANNOTBEFULLYCONTAINED)
		{
			//try to get entites from each sub quadtree induvidually, if current entity boundries overlaps with given sub quadsstree it will try to retrive entites from there

			if (canPartiallyContainEntity(inputEntity, (minX + maxX) / 2, minX, maxY, (minY + maxY) / 2)) //TOPLEFT
			{
				tempVector = subQuadtrees[TOPLEFT].getNearbyEntities(inputEntity);
			
				returnVector.insert(returnVector.begin(), tempVector.begin(), tempVector.end());
				tempVector.clear();
			}
			
			if (canFullyContainEntity(inputEntity, maxX, (minX + maxX) / 2, maxY, (minY + maxY) / 2)) //TOPRIGHT
			{
				tempVector = subQuadtrees[TOPRIGHT].getNearbyEntities(inputEntity);
			
				returnVector.insert(returnVector.begin(), tempVector.begin(), tempVector.end());
				tempVector.clear();
			}
			
			if (canFullyContainEntity(inputEntity, (minX + maxX) / 2, minX, (maxY + minY) / 2, minY)) //BOTTOMLEFT
			{
				tempVector = subQuadtrees[BOTTOMLEFT].getNearbyEntities(inputEntity);
			
				returnVector.insert(returnVector.begin(), tempVector.begin(), tempVector.end());
				tempVector.clear();
			}
			
			if (canFullyContainEntity(inputEntity, maxX, (minX + maxX) / 2, (maxY + minY) / 2, minY)) //BOTTOMRIGHT
			{
				tempVector = subQuadtrees[BOTTOMRIGHT].getNearbyEntities(inputEntity);
			
				returnVector.insert(returnVector.begin(), tempVector.begin(), tempVector.end());
				tempVector.clear();
			}
		}
			
	}

	return returnVector;
}

Quadtree::Quadtree(int inputCurrentQuadtreeDepth, float maxX, float minX, float maxY, float minY)
	:
	maxX(maxX),
	minX(minX),
	maxY(maxY),
	minY(minY),
	currentQuadtreeDepth(inputCurrentQuadtreeDepth),
	entityThreshold(4),
	maxQuadtreeDepth(5)

{

}

