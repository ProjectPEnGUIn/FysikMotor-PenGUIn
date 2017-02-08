#include "SATCollisionCheck.h"

bool SATCollisionCheck::isConvex(const VertexShape& inputEntity) const
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
	inputMaxAlong = inputMinAlong;
	
	
	for (unsigned int i = 0; i < inputPoints.size(); i++)
	{
		float dotValue = inputAxis * inputPoints[i];

		if (dotValue < inputMinAlong)
			inputMinAlong = dotValue;

		else
			if (dotValue > inputMaxAlong)
				inputMaxAlong = dotValue;
		
	}
}
//std::vector<Vec2D> SATCollisionCheck::getNormalizedNormals(const std::vector<Vec2D>& inputVertices) const //takes in all vertices and returns all normals
//{
//	std::vector<Vec2D> returnNormals;
//
//	for (unsigned int i = 0; i < inputVertices.size(); i++)
//	{
//		//ERROR direction of plane is NOT taken in count
//		
//		Vec2D temp;
//
//		temp = inputVertices[i] - inputVertices[(i + 1)%inputVertices.size()];
//
//	//	std::cout << temp.getDirectionDEGREES() << " ERROR edge degree is not being counted" << std::endl;
//
//		returnNormals.push_back((temp.getRightNormal()).getNormalisation());
//	}
//
//	return returnNormals;
//}
std::vector<Vec2D> SATCollisionCheck::getEdges(const std::vector<Vec2D>& inputVerticies) //returns all edges
{
	std::vector<Vec2D> edges;
	
	for (unsigned int i = 0; i <inputVerticies.size(); i++)
	{
		Vec2D temp;
		temp = inputVerticies[i] - inputVerticies[(i + 1)% inputVerticies.size()];
		edges.push_back(temp);
	}
	
	//std::cout << "---PRINtiNG EDGE COORDS\n";
	//for (unsigned int i = 0; i < edges.size(); i++)
	//{
	//	std::cout << "x:" << edges[i].getX() << " y:" << edges[i].getY() << std::endl;
	//}
	//std::cout << "press enter\n";
	//std::cin.get();
	
	return edges;
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
bool SATCollisionCheck::SATCheck(const VertexShape& inputVertexShape1, const VertexShape& inputVertexShape2)
{
	//mainly use http://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection 30/1
	//http://www.dyn4j.org/2010/01/sat/#sat-mtv 31/1
	//aswell as previously mentioned sources

	Vec2D overlapAxis;


	if (isConvex(inputVertexShape1) && isConvex(inputVertexShape2))
	{
	

		//test normals on shape 1 for overlapping on shape 2 axis
		for (const Vec2D& n : getEdges(inputVertexShape1.getVertices()))
		{
			float shape1Max = -FLT_MAX, shape1Min = FLT_MAX, shape2Max = -FLT_MAX, shape2Min = FLT_MAX;

			SATtest(n.getClockWiseNormal().getNormalisation(), inputVertexShape1.getVertices(), shape1Min, shape1Max);
			SATtest(n.getClockWiseNormal().getNormalisation(), inputVertexShape2.getVertices(), shape2Min, shape2Max);
			if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				return false;
			}
			else
			{
					float d0 = shape1Max - shape2Min,
					d1 = shape2Max - shape1Min,
					tempOverlap = (d0 < d1) ? d0 : d1;

					if (tempOverlap < overlap)
					{
						overlap = tempOverlap;
						overlapAxis = n.getClockWiseNormal().getNormalisation();
					}
			}
		}

	
		//test normals on shape 2 for overlapping on shape 2 axis
		for (const Vec2D& n : getEdges(inputVertexShape2.getVertices()))
		{
			float shape1Max = -FLT_MAX, shape1Min = FLT_MAX, shape2Max = -FLT_MAX, shape2Min = FLT_MAX;

			SATtest(n.getClockWiseNormal().getNormalisation(), inputVertexShape1.getVertices(), shape1Min, shape1Max);
			SATtest(n.getClockWiseNormal().getNormalisation(), inputVertexShape2.getVertices(), shape2Min, shape2Max);
			if (!overlaps(shape1Min, shape1Max, shape2Min, shape2Max))
			{
				return false;
			}
			else
			{

				float d0 = shape1Max - shape2Min,
					d1 = shape2Max - shape1Min,
					tempOverlap = (d0 < d1) ? d0 : d1;

				if (tempOverlap < overlap)
				{
					overlap = tempOverlap;
					overlapAxis = n.getClockWiseNormal().getNormalisation();
				}
			}
		}

		
		overlapAxis.setVectorMagnitude(overlap);
		penentrationVector = overlapAxis;

	//	if (overlap < 0.000001)
	//		return false;

	//	//having to implement this due to float rounding errors, 0 becomes -0.000000001 which messes with returning vector diredction
	//	if (penentrationVector.getX() < 0.0f && penentrationVector.getX() > -0.0001f)
	//		penentrationVector.setX(0.0f);
	//	if (penentrationVector.getY() < 0.0f && penentrationVector.getY() > -0.0001f)
	//		penentrationVector.setY(0.0f);
	
		return true;
	}
	else
		std::cout << "ERROR tried to do SAT check between two entiteis that arent convex\n";


	return false;
}

void SATCollisionCheck::clearVariables() //resets all variables so it can take in new entities and compare
{

	overlap = FLT_MAX;
	contactPoints.clear();
	penentrationVector.setXY(0, 0);
	
}
float SATCollisionCheck::getOverlap() const
{
	return overlap;
}
Vec2D SATCollisionCheck::getPenentrationVector() const //returns
{
	return penentrationVector;
}
std::vector<Vec2D> SATCollisionCheck::getContactPoints() const //coords of contact point between
{
	return contactPoints;
}
SATCollisionCheck::SATCollisionCheck()
	:
	overlap(FLT_MAX),
	contactPoints(),
	penentrationVector()
{
}