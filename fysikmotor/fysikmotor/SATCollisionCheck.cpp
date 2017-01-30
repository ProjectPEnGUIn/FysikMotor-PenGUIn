#include "SATCollisionCheck.h"

bool SATCollisionCheck::isConvex(const Entity& inputEntity) const
{
	//TODO LOGIC

	return true;
}
void SATCollisionCheck::SATtest(const Vec2D& inputAxis, const std::vector<Vec2D>& inputPoints, float& inputMinAlong, float& inputMaxAlong)
{
    //http://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection 30/1

	inputMaxAlong = -FLT_MAX;
	inputMinAlong = FLT_MAX;

	for (unsigned int i = 0; i < inputPoints.size(); i++)
	{
		float dotValue = inputAxis * inputPoints[i];

		if (dotValue < inputMinAlong)
			inputMinAlong = dotValue;

		if (dotValue > inputMaxAlong)
			inputMaxAlong = dotValue;
	}
}
std::vector<Vec2D> SATCollisionCheck::getNormals(const std::vector<Vec2D>& inputVertices) const //takes in all vertices and returns all normals
{
	std::vector<Vec2D> returnNormals;

	for (unsigned int i = 0; i < inputVertices.size(); i++)
	{
		Vec2D temp;

		temp = inputVertices[i] - inputVertices[(i + 1)%inputVertices.size()];

		returnNormals.push_back(temp.getRightNormal());
	}

	return returnNormals;
}
bool SATCollisionCheck::overlaps(const float min1, const float max1, const float min2, const float max2) const
{
	return isBetweenOrdered(min2, min1, max1) || isBetweenOrdered(min1, min2, max2);
}
inline bool SATCollisionCheck::isBetweenOrdered(const float val, const float lowerBound, const float upperBound) const
{
	return lowerBound <= val && val <= upperBound;
}
bool SATCollisionCheck::SATCheck(const Entity& inputEntity1, const Entity& inputEntity2)
{
	//mainly use http://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection 30/1
	//aswell as previously mentioned sources

	if (isConvex(inputEntity1) && isConvex(inputEntity2))
	{
		//test normals on shape 1 for overlapping on shape 2 axis
		for ( Vec2D n : getNormals(inputEntity1.getVertexShape().getVertices()))
		{
			float shape1Max = -FLT_MAX, shape1Min = FLT_MAX, shape2Max = -FLT_MAX, shape2Min = FLT_MAX;

			SATtest(n, inputEntity1.getVertexShape().getVertices(), shape1Min, shape1Max);
			SATtest(n, inputEntity2.getVertexShape().getVertices(), shape2Min, shape2Max);

			if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				return false;
			}
		
		}

		//test normals on shape 2 for overlapping on shape 2 axis
		for (Vec2D n : getNormals(inputEntity2.getVertexShape().getVertices()))
		{
			float shape1Max = -FLT_MAX, shape1Min = FLT_MAX, shape2Max = -FLT_MAX, shape2Min = FLT_MAX;

			SATtest(n, inputEntity1.getVertexShape().getVertices(), shape1Min, shape1Max);
			SATtest(n, inputEntity2.getVertexShape().getVertices(), shape2Min, shape2Max);

			if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				return false;
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
	penentrationVector(),
	contactPoint()
{
}
