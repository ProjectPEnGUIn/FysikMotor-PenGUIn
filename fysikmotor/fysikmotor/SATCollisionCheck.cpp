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
float SATCollisionCheck::getOverlapAmount(const float min1, const float max1, const float min2, const float max2) const
{

//	//https://www.codeproject.com/Articles/15573/D-Polygon-Collision-Detection 4/2	
//	//proper overlap amounts
//
//	if (min1 < min2)
//		return min2 - max1;
//
//	else
//		return min1 - max2;


	return -FLT_MAX;
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

			SATtest(n.getAntiClockWiseNormal().getNormalisation(), inputVertexShape1.getVertices(), shape1Min, shape1Max);
			SATtest(n.getAntiClockWiseNormal().getNormalisation(), inputVertexShape2.getVertices(), shape2Min, shape2Max);
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
						overlapAxis = n.getAntiClockWiseNormal().getNormalisation();
					}
			}
		}

	
		//test normals on shape 2 for overlapping on shape 2 axis
		for (const Vec2D& n : getEdges(inputVertexShape2.getVertices()))
		{
			float shape1Max = -FLT_MAX, shape1Min = FLT_MAX, shape2Max = -FLT_MAX, shape2Min = FLT_MAX;

			SATtest(n.getAntiClockWiseNormal().getNormalisation(), inputVertexShape1.getVertices(), shape1Min, shape1Max);
			SATtest(n.getAntiClockWiseNormal().getNormalisation(), inputVertexShape2.getVertices(), shape2Min, shape2Max);
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
					overlapAxis = n.getAntiClockWiseNormal().getNormalisation();
				}
			}
		}

		
		overlapAxis.setVectorMagnitude(overlap);
		penentrationVector = overlapAxis;

		//having to implement this due to float rounding errors, 0 becomes -0.000000001 which messes with returning vector diredction
		if (penentrationVector.getX() < 0.0f && penentrationVector.getX() > -0.000001f)
			penentrationVector.setX(0.0f);
		if (penentrationVector.getY() < 0.0f && penentrationVector.getY() > -0.000001f)
			penentrationVector.setY(0.0f);
	
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



//std::vector<Vec2D> SATCollisionCheck::getEdges(const std::vector<Vec2D> inputVerticies)
//{
//	std::vector<Vec2D> edges;
//	
//		for (unsigned int i = 0; i <inputVerticies.size(); i++)
//		{
//			Vec2D temp;
//	
//			temp = inputVerticies[i] - inputVerticies[(i + 1)% inputVerticies.size()];
//
//			edges.push_back(temp);
//		}
//	
//		return edges;
//}
//void SATCollisionCheck::calculateIntervall(const Vec2D& inputAxis, const std::vector<Vec2D>& inputEdges, float& inputMin, float& inputMax)
//{
//	//http://elancev.name/oliver/2D%20polygon.htm#tut6
//
//	float d = inputAxis * inputEdges[0];
//
//	inputMin = d;
//	inputMax = d;
//
//	for (unsigned int i = 0; i < inputEdges.size(); i++)
//	{
//		d = inputEdges[i] * inputAxis;
//
//		if (d < inputMin)
//			inputMin = d;
//
//		if (d > inputMax)
//			inputMax = d;
//	}
//
//}
//bool SATCollisionCheck::axisSeparatePolygons(Vec2D& inputAxis, const std::vector<Vec2D>& inputShape1Edges, const std::vector<Vec2D>& inputShape2Edges)
//{
////http://elancev.name/oliver/2D%20polygon.htm#tut6
//
//	float min1, max1,
//		min2, max2;
//
//	calculateIntervall(inputAxis, inputShape1Edges, min1, max1);
//	calculateIntervall(inputAxis, inputShape2Edges, min2, max2);
//
//	std::cout << "min1:" << min1 << " max1:" << max1 << " min2:" << min2 << " max2:" << max2 << std::endl;
//	std::cin.get();
//
//
//	if (min1 > max2 || min2 > max1)
//		return true;
//
//	//find interval overlap
//	float d0 = max1 - min2;
//	float d1 = max2 - min1;
//	float depth = (d0 < d1) ? d0 : d1;
//
//	float axisLengthSquared = inputAxis * inputAxis;
//
//	inputAxis *= (depth / axisLengthSquared);
//
//	return false;
//
//}
//bool SATCollisionCheck::collisioncheck(const VertexShape& inputShape1, const VertexShape& inputShape2) //returns true if overlaping
//{
//
//	//http://elancev.name/oliver/2D%20polygon.htm#tut6
//
//	std::vector<Vec2D> potentialPushVectors;
//
//
//	for (Vec2D& n : getEdges(inputShape1.getVertices()))
//	{
//		if (axisSeparatePolygons(n, inputShape1.getVertices(), inputShape2.getVertices()))
//		{
//			std::cout << "exited at frist looop"<< std::endl;
//			return false;
//		}
//	}
//
//
//	for (Vec2D& n : getEdges(inputShape2.getVertices()))
//	{
//		if (axisSeparatePolygons(n, inputShape1.getVertices(), inputShape2.getVertices()))
//		{
//			std::cout << "e3sxited at 2nd loop" << std::endl;
//			return false;
//		}
//	}
//
//	std::cout << "exited at bottom" << std::endl;
//	return true;
//}