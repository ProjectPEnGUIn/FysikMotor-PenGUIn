#include "SATCollisionCheck.h"

bool SATCollisionCheck::isConvex(const Entity& inputEntity) const
{
	//TODO LOGIC

	return true;
}
void SATCollisionCheck::SATtest(const Vec2D& inputAxis, const std::vector<Vec2D>& inputPoints, float& inputMinAlong, float& inputMaxAlong)
{
    //http://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection 30/1
	//http://www.dyn4j.org/2010/01/sat/#sat-mtv 31/1

	//input axis is normalised and right normal of edge

	inputMinAlong = inputAxis * inputPoints[0];
	inputMaxAlong = inputMaxAlong;
	
	
	for (unsigned int i = 1; i < inputPoints.size(); i++)
	{
		float dotValue = inputAxis * inputPoints[i];

		if (dotValue < inputMinAlong)
			inputMinAlong = dotValue;

		 if (dotValue > inputMaxAlong)
			inputMaxAlong = dotValue;
	}
}
std::vector<Vec2D> SATCollisionCheck::getNormalizedNormals(const std::vector<Vec2D>& inputVertices) const //takes in all vertices and returns all normals
{
	std::vector<Vec2D> returnNormals;

	for (unsigned int i = 0; i < inputVertices.size(); i++)
	{
		//ERROR direction of plane is NOT taken in count
		
		Vec2D temp;

		temp = inputVertices[i] - inputVertices[(i + 1)%inputVertices.size()];

	//	std::cout << temp.getDirectionDEGREES() << " ERROR edge degree is not being counted" << std::endl;

		returnNormals.push_back((temp.getRightNormal()).getNormalisation());
	}

	return returnNormals;
}
bool SATCollisionCheck::overlaps(const float min1, const float max1, const float min2, const float max2)
{
	//MTV calc from http://www.dyn4j.org/2010/01/sat/#sat-mtv 31/1

	return isBetweenOrdered(min2, min1, max1) || isBetweenOrdered(min1, min2, max2);

}
inline bool SATCollisionCheck::isBetweenOrdered(const float val, const float lowerBound, const float upperBound) const
{
	return lowerBound <= val && val <= upperBound;
}
float SATCollisionCheck::getOverlapAmount(const float max1, const float min1, const float max2, const float min2) const
{
	if (min2 > min1 && min2 < max1)
		return max1 - min2;

	if (min1 > min2 && min1 < max2)
		return max2 - min1;

	return -FLT_MAX;
}

bool SATCollisionCheck::SATCheck(const Entity& inputEntity1, const Entity& inputEntity2)
{
	//mainly use http://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection 30/1
	//http://www.dyn4j.org/2010/01/sat/#sat-mtv 31/1
	//aswell as previously mentioned sources

	if (isConvex(inputEntity1) && isConvex(inputEntity2))
	{
		//test normals on shape 1 for overlapping on shape 2 axis
		for (const Vec2D& n : getNormalizedNormals(inputEntity1.getVertexShape().getVertices()))
		{
			float shape1Max = -FLT_MAX, shape1Min = FLT_MAX, shape2Max = -FLT_MAX, shape2Min = FLT_MAX;


			SATtest(n, inputEntity1.getVertexShape().getVertices(), shape1Min, shape1Max);
			SATtest(n, inputEntity2.getVertexShape().getVertices(), shape2Min, shape2Max);
			if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				return false;
			}
			else
			{
				float tempOverlap = getOverlapAmount(shape1Max, shape1Min, shape2Max, shape2Min);

				if (tempOverlap < overlap)
				{
					//std::cout << n.getDirectionDEGREES() << std::endl;
					overlap = tempOverlap;
					penentrationVector = n;
					penentrationVector = penentrationVector.getLeftNormal();
					penentrationVector.setVectorMagnitude(overlap);
				
				}

			}
		
		}

		//test normals on shape 2 for overlapping on shape 2 axis
		for (const Vec2D& n : getNormalizedNormals(inputEntity2.getVertexShape().getVertices()))
		{
			float shape1Max = -FLT_MAX, shape1Min = FLT_MAX, shape2Max = -FLT_MAX, shape2Min = FLT_MAX;

			SATtest(n, inputEntity1.getVertexShape().getVertices(), shape1Min, shape1Max);
			SATtest(n, inputEntity2.getVertexShape().getVertices(), shape2Min, shape2Max);

			if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				return false;
			}
			else
			{
				float tempOverlap = getOverlapAmount(shape1Max, shape1Min, shape2Max, shape2Min);

				if (tempOverlap < overlap)
				{
					overlap = tempOverlap;
					penentrationVector = n;
					penentrationVector = penentrationVector.getLeftNormal();
					penentrationVector.setVectorMagnitude(overlap);
					
				}
			}
		}


		return true;
	}
	else
		std::cout << "ERROR tried to do SAT check between two entiteis that arent convex\n";


	return false;
}



void SATCollisionCheck::clearVariables() //resets all variables so it can take in new entities and compare
{
	penentrationVector.setXY(0, 0);
	contactPoint.setXY(FLT_MAX, FLT_MAX);
}
float SATCollisionCheck::getOverlap() const
{
	return overlap;
}
Vec2D SATCollisionCheck::getPenentrationVector() const //returns
{
	return penentrationVector;
}
Vec2D SATCollisionCheck::getContactPoint() const //coords of contact point between
{
	return contactPoint;
}
SATCollisionCheck::SATCollisionCheck()
	:
	overlap(FLT_MAX),
	penentrationVector(),
	contactPoint()
{
}
