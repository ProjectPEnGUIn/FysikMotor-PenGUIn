#include "AABBCheck.h"

bool minskowskiDifferenceAABBCollisionCheck(const Entity& inputEntity1, const Entity& inputEntity2)
{
	//https://hamaluik.com/posts/simple-aabb-collision-using-minkowski-difference/
	//covert python code into c++, the y axis in the python code was flipped, caused alot of errors 

	//use differnt values in mdtopleft since the rest of the code uses flipped y axis
	Vec2D mdTopLeft = Vec2D(inputEntity1.getAABBTopLeft().getX(), inputEntity1.getAABBTopLeft().getY()) - Vec2D(inputEntity2.getAABBMBottomRight().getX(), inputEntity2.getAABBMBottomRight().getY());
	Vec2D mdFullSize = Vec2D(inputEntity1.getAABBMBottomRight().getX() - inputEntity1.getAABBTopLeft().getX(), inputEntity1.getAABBTopLeft().getY() - inputEntity1.getAABBMBottomRight().getY()) + Vec2D(inputEntity2.getAABBMBottomRight().getX() - inputEntity2.getAABBTopLeft().getX(), inputEntity2.getAABBTopLeft().getY() - inputEntity2.getAABBMBottomRight().getY());

	if ((mdTopLeft.getX() <= 0)
		&& (mdTopLeft.getX() + mdFullSize.getX() >= 0)
	    && (mdTopLeft.getY() - mdFullSize.getY() <= 0)
		&& (mdTopLeft.getY() >= 0))
	{
		return true;
	}
	
	return false;
}

bool sweptMinskowskiDifferenceAABBCollisionCheck(const Entity& inputEntity1, const Entity& inputEntity2, const float inputDeltaTime)
{
	//https://hamaluik.com/posts/simple-aabb-collision-using-minkowski-difference/
    //https://hamaluik.com/posts/swept-aabb-collision-using-minkowski-difference/ 24/1
	//convert python code into c++, the y axis in the python code was flipped, caused alot of errors 

	//check for nornmal mdaabb check first and then use this function
	//use entitity data from before the entities were moved to see if a collision between them could have occured between frames

	//use previous aabb position before the entities got new positions to see if a collision could have occoured between the movement from one pos to the next

	//use differnt values in mdtopleft since the rest of the code uses flipped y axis
	Vec2D mdTopLeft = Vec2D(inputEntity1.getPreviousAABBTL().getX(), inputEntity1.getPreviousAABBTL().getY()) - Vec2D(inputEntity2.getPreviousAABBBR().getX(), inputEntity2.getPreviousAABBBR().getY());
	Vec2D mdFullSize = Vec2D(inputEntity1.getPreviousAABBBR().getX() - inputEntity1.getPreviousAABBTL().getX(), inputEntity1.getPreviousAABBTL().getY() - inputEntity1.getPreviousAABBBR().getY()) + Vec2D(inputEntity2.getAABBMBottomRight().getX() - inputEntity2.getPreviousAABBTL().getX(), inputEntity2.getPreviousAABBTL().getY() - inputEntity2.getPreviousAABBBR().getY());

	if ((mdTopLeft.getX() <= 0)
		&& (mdTopLeft.getX() + mdFullSize.getX() >= 0)
		&& (mdTopLeft.getY() - mdFullSize.getY() <= 0)
		&& (mdTopLeft.getY() >= 0))
	{
		//this will already have been checked
		//return true;
	}
	else
	{
		Vec2D relativeMotion = (Vec2D(inputEntity1.getVelocity().getX(), -inputEntity1.getVelocity().getY()) - Vec2D(inputEntity2.getVelocity().getX(), -inputEntity2.getVelocity().getY())).scaleVector(inputDeltaTime); //how much they have moved relative to eachother
        
		float h = getRayIntersectionFraction(Vec2D(0, 0), relativeMotion, Vec2D(mdTopLeft.getX(), mdTopLeft.getY()), Vec2D(mdTopLeft.getX() + mdFullSize.getX(), mdTopLeft.getY() - mdFullSize.getY()));

		if (h < FLT_MAX)
		{
			//will be a collision this frame
			
			return true;
		}
	}

	return false;
}
float getRayIntersectionFractionOfFirstRay(const Vec2D& inputVec1Origin, const Vec2D& inputVec1End, const Vec2D& inputVec2Origin, const Vec2D& inputVec2End)
{
	//based on https://hamaluik.com/posts/swept-aabb-collision-using-minkowski-difference/ python code, 24/1
	//converted from python to c++

	Vec2D r = inputVec1End - inputVec1Origin;
	Vec2D s = inputVec2End - inputVec2Origin;

	float numerator = (inputVec2Origin - inputVec1Origin) * r;
	float denomenator = r * s;

	if (numerator == 0 && denomenator == 0)
	{
		//lines are colinear
		return FLT_MAX;
	}
	if (denomenator == 0)
	{
		//lines are parallell
		return FLT_MAX;
	}

	float u = numerator / denomenator;
	float t = ((inputVec2Origin - inputVec1Origin) * s) / denomenator;

	if ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1))
	{
		return t;
	}

	return FLT_MAX;
}
float getRayIntersectionFraction(const Vec2D& inputVectorOrigin, const Vec2D& inputDirectionVector, const Vec2D& inputTL, const Vec2D& inputBR)
{
	//based on https://hamaluik.com/posts/swept-aabb-collision-using-minkowski-difference/ 24/1
	//y axis is flipped - may fix it later

	Vec2D end = inputVectorOrigin + inputDirectionVector;

	float minT = getRayIntersectionFractionOfFirstRay(inputVectorOrigin, end, Vec2D(inputTL.getX(), inputTL.getY()), Vec2D(inputTL.getX(), inputBR.getY()));
	
	float x = getRayIntersectionFractionOfFirstRay(inputVectorOrigin, end, Vec2D(inputTL.getX(), inputBR.getY()), Vec2D(inputBR.getX(), inputBR.getY()));
	if (x < minT)
		minT = x;

	
	x = getRayIntersectionFractionOfFirstRay(inputVectorOrigin, end, Vec2D(inputBR.getX(), inputBR.getY()), Vec2D(inputBR.getX(), inputBR.getY()));
	if (x < minT)
		minT = x;

	//x = getRayIntersectionFractionOfFirstRay(origin, end, new Vector(max.x, min.y), new Vector(min.x, min.y));
	x = getRayIntersectionFractionOfFirstRay(inputVectorOrigin, end, Vec2D(inputBR.getX(), inputTL.getY()), Vec2D(inputTL.getX(), inputTL.getY()));
	if (x < minT)
		minT = x;


	return minT;
}
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