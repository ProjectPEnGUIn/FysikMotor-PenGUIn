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
std::vector<Vec2D> SATCollisionCheck::getEdges(const std::vector<Vec2D>& inputVerticies) //returns all edges
{
	std::vector<Vec2D> edges;
	
	for (unsigned int i = 0; i <inputVerticies.size(); i++)
	{
		Vec2D temp;
		temp = inputVerticies[i] - inputVerticies[(i + 1)% inputVerticies.size()];
		edges.push_back(temp);
	}
	
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
void SATCollisionCheck::findEdgesInCollision(const std::vector<Vec2D>& shape1Vertices, const std::vector<Vec2D>& shape2Vertices, const Vec2D& normal)
{
	//use what ive learnt from trying to impleemente sat before in this
	//tried to follow a guide a some time ago but did not get anywhere using it, trying again from memory. http://www.dyn4j.org/2011/11/contact-points-using-clipping/ gets credit 2/3 2017


	//normal points from shape 1 to shape 2
	//NOTE: normal has to be size 1

	//find vertice furthest along the oposite? <- not sure / direction the normal is pointing

	//shape1, fidn the vertice closest to shape2

	
	Vec2D nNormal1 = (normal.getDirectionDEGREES() >= 180.0f) ? normal : normal.getClockWiseNormal().getClockWiseNormal();
	
	int index1 = 0; 
	float maxp1 = nNormal1 * shape1Vertices[0];
	for (unsigned int i = 0; i < shape1Vertices.size(); i++)
	{
		float newp = nNormal1 * shape1Vertices[i];
		
		if (newp > maxp1)
		{
			maxp1 = newp;
			index1 = i;
		}
	}

	//shape 2: find the vertice closests to shape1, invert normal
	
	
	Vec2D nNormal2 = (normal.getDirectionDEGREES() >= 180.0f) ? normal.getClockWiseNormal().getClockWiseNormal() : normal;
	
	int index2 = 0;
	float maxp2 = nNormal2 * shape2Vertices[0];
	for (unsigned int i = 0; i < shape2Vertices.size(); i++)
	{
		float newp = nNormal2 * shape2Vertices[i];

		if (newp > maxp2)
		{
			maxp2 = newp;
			index2 = i;
		}
	}

	//closest points
	Vec2D s1cP1 = shape1Vertices[index1],
		s1cP2,
		s2cP1 = shape2Vertices[index2],
		s2cP2;


	//^WORKS SO FAR.


	//find the points next the found points, check with the two verticies connecting to closest vertex to see which one is closest, same logic as when calculating the frist point

	Vec2D p1Next = shape1Vertices[(index1 + 1) % shape1Vertices.size()],	//use mod operator to avoid out of range errors with the vectors
		p1Previous = shape1Vertices[(index1 - 1) % shape1Vertices.size()],
		p2Next = shape2Vertices[(index2 + 1) % shape2Vertices.size()],
		p2Previous = shape2Vertices[(index2 - 1) % shape2Vertices.size()],
	
		//used the psudeo code from tutoro
		s1L = (p1Previous - s1cP1).getNormalisation(),
		s1R = (p1Next - s1cP1).getNormalisation(),
		s2L = (p2Previous - s2cP1).getNormalisation(),
		s2R = (p2Next - s2cP1).getNormalisation();

	//error vertices building edges must be in right order

	if (s1R * nNormal1 <= s1L * nNormal1)
	{
		s1cP2 = p1Previous;

		edge1 = s1cP1 - s1cP2;
	}
	else
	{
		s1cP2 = p1Next;

		edge1 = s1cP2 - s1cP1;
	}

	if (s2R * nNormal2 <= s2L * nNormal2)
	{
		s2cP2 = p2Previous;

		edge2 = s2cP1 - s2cP2;
	}
	else
	{
		s2cP2 = p2Next;

		edge2 = s2cP2 - s2cP1;
	}

	//edges are in anticlockwise direction, but it works so im leaving it here, if it needs adjusting i'll do it later

	

	//std::cout << "edge 1: " << edge1.getX() << " " << edge1.getY() << " angle: " << edge1.getDirectionDEGREES() << std::endl;
	//std::cout << "edge 2: " << edge2.getX() << " " << edge2.getY() << " angle: " << edge2.getDirectionDEGREES() << std::endl;
	////std::cin.get();
	//std::cout << "points on shape1: p1: " << s1cP1.getX() << " " << s1cP1.getY() << " p2: " << s1cP2.getX() << " " << s1cP2.getY()
	//	<< "\nPoints on shape2: p1: " << s2cP1.getX() << " " << s2cP1.getY() << " p2: " << s2cP2.getX() << " " << s2cP2.getY() << std::endl;
	//
	//std::cout << "Normal dir: " << normal.getDirectionDEGREES() << std::endl << " n1N: " << nNormal1.getDirectionDEGREES() << " n2N: " << nNormal2.getDirectionDEGREES() << std::endl;
	//
	//std::cout << "Paused: Press Enter\n";
	//std::cin.get();
	

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

		//makes it so the vector points from e1 to e2
		Vec2D d = inputVertexShape2.getCenterPos() - inputVertexShape1.getCenterPos();
		if (d * penentrationVector.getNormalisation() > 0.0f)
			penentrationVector = penentrationVector * -1.0f;

		//minimizing rounding errors
		if (penentrationVector.getX() < 0.0f && penentrationVector.getX() > -0.0000001)
			penentrationVector.setX(roundf(penentrationVector.getX() * 100.0f / 100.0f));
		if (penentrationVector.getY() < 0.0f && penentrationVector.getY() > -0.0000001)
			penentrationVector.setY(roundf(penentrationVector.getY() * 100.0f / 100.0f));

		//calc contactpoints
		//1: find closest edges
		findEdgesInCollision(inputVertexShape1.getVertices(), inputVertexShape2.getVertices(), penentrationVector.getNormalisation());

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

Vec2D SATCollisionCheck::getEdge1() const //the edge on the first shape that is involved in the collision
{
	return edge1;
}
Vec2D SATCollisionCheck::getEdge2() const //the edge on the second shape that is involved in the collision
{
	return edge2;
}
SATCollisionCheck::SATCollisionCheck()
	:
	edge1(FLT_MAX, FLT_MAX),
	edge2(FLT_MAX, FLT_MAX),
	overlap(FLT_MAX),
	contactPoints(),
	penentrationVector()
	
{
}