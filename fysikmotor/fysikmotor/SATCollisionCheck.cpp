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
//void SATCollisionCheck::calculateContactPoints(const VertexShape& inputShape1, const VertexShape& inputShape2) //sets the proper contactpoints
//{
//	//roughly based on http://www.dyn4j.org/2011/11/contact-points-using-clipping/  psudeocode9/2
//
//	std::vector<Vec2D> edge1 = { Vec2D(FLT_MAX, FLT_MAX), Vec2D(FLT_MAX, FLT_MAX), Vec2D(FLT_MAX, FLT_MAX) },
//		edge2 = { Vec2D(FLT_MAX, FLT_MAX), Vec2D(FLT_MAX, FLT_MAX), Vec2D(FLT_MAX, FLT_MAX) };
//
//	Vec2D n = penentrationVector.getNormalisation().getAntiClockWiseNormal().getAntiClockWiseNormal();
//
//	edge1 = getNearestEdge(inputShape1.getVertices(), n );
//	edge2 = getNearestEdge(inputShape2.getVertices(), n * -1.0f);
//
//	Vec2D edge1v = edge1[1] - edge1[2],
//		edge2v = edge2[1] - edge2[2];
//	
//	std::cout << "n: " << n.getX() << " " << n.getY() << std::endl;
//	std::cout << "e1 = (" << edge1[1].getX() << ", " << edge1[1].getY() << ") to (" << edge1[2].getX() << " ," << edge1[2].getY() << ") = (" << edge1v.getX() << ", " << edge1v.getY() << ")\n";
//	std::cout << "e2 = (" << edge2[1].getX() << ", " << edge2[1].getY() << ") to (" << edge2[2].getX() << " ," << edge2[2].getY() << ") = (" << edge2v.getX() << ", " << edge2v.getY() << ")\n";
//	std::cout << "e1max: " << edge1[0].getX() << " " << edge1[0].getY() << std::endl;
//	std::cout << "e2max: " << edge2[0].getX() << " " << edge2[0].getY() << std::endl;
//	std::cout << "e1 * n = " << edge1v * n << std::endl;
//	std::cout << "e2 * n = " << edge2v * n << std::endl;
//	std::cout << "press enter\n";
//	std::cin.get();
//
//	std::vector<Vec2D> ref, inc;
//	bool flipped = false;
//
//	if (fabs(edge1v * n) <= fabs(edge2v * n))
//	{
//		ref = edge1;
//		inc = edge2;
//	}
//	else
//	{
//		ref = edge2;
//		inc = edge1;
//		flipped = true;
//
//		std::cout << "-DID THE FLIP-" << std::endl;
//	}
//
//	Vec2D refv = ref[1] - ref[2];
//	refv = refv.getNormalisation();
//	float o1 = refv * ref[2];
//
//	std::cout << "flipped: " << flipped << std::endl;
//	std::cout << "ref normalastion " << refv.getX() << " " << refv.getY() << std::endl;
//	std::cout << "o1 " << o1 << std::endl;
//
//	std::vector<Vec2D> tempClippedPoints = getClippedPoints(inc[1], inc[2], refv, o1);
//	if (tempClippedPoints.size() < 2)
//	{
//		//std::cout << "cancel point calc\n";
//		return;
//	}
//
//	std::cout << "points so far:\n";
//	for (unsigned int i = 0; i < tempClippedPoints.size(); i++)
//	{
//		std::cout << "[" << i << "] " << tempClippedPoints[i].getX() << " " << tempClippedPoints[i].getY() << std::endl;
//	}
//
//	/////////////////////////////////^works so far :S
//
//	float o2 = refv * ref[1];
//	std::cout << "o2: " << o2 << std::endl;
//	tempClippedPoints = getClippedPoints(tempClippedPoints[0], tempClippedPoints[1], refv * -1.0f, -o2);
//	if (tempClippedPoints.size() < 2)
//	{
//		//std::cout << "cancel point calc2jgijfijgfij\n";
//		return;
//	}
//	std::cout << "points so far:\n";
//	for (unsigned int i = 0; i < tempClippedPoints.size(); i++)
//	{
//		std::cout << "[" << i << "] " << tempClippedPoints[i].getX() << " " << tempClippedPoints[i].getY() << std::endl;
//	}
//	////////////////////////////^works so far
//
//	//Vec2D refNorm = refv.getCrossProductWithScalar(-1.0f);
//	Vec2D refNorm = refv.getCrossProductWithScalar(-1.0f);
//
//	std::cout << "refNorm: " << refNorm.getX() << " " << refNorm.getY() << std::endl;
//	std::cout << "flipped status: " << flipped << std::endl;
//
//	//if (flipped)
//	//	refNorm *= -1.0f;
//	//std::cout << "refNorm (if flipped): " << refNorm.getX() << " " << refNorm.getY() << std::endl;
//
//	float max = refNorm * ref[0]; //////////////////////////////////error getting max value
//
//	std::cout << "ref[max]: " << ref[0].getX() << " " << ref[0].getY() << std::endl;
//	std::cout << "ref: " << ref[0].getX() << " " << ref[0].getY() << std::endl;
//	std::cout << "max: " << max << std::endl;
//
//	if (refNorm * tempClippedPoints[0] - max < 0.0f)
//	{
//		tempClippedPoints.erase(tempClippedPoints.begin() + 0);
//			
//		if (refNorm * tempClippedPoints[0] - max < 0.0f)
//			tempClippedPoints.erase(tempClippedPoints.begin() + 0);
//	}
//	else if (refNorm * tempClippedPoints[1] - max < 0.0f)
//		tempClippedPoints.erase(tempClippedPoints.begin() + 1);
//
//
//	contactPoints = tempClippedPoints;
//}
//std::vector<Vec2D> SATCollisionCheck::getNearestEdge(const std::vector<Vec2D>& inputShapeVertices, const Vec2D& inputNormal)
//{
//	//roughly based on this psudeocode http://www.dyn4j.org/2011/11/contact-points-using-clipping/  9/2 2017
//
//	std::vector<Vec2D> edge;
//
//	int index = -1;
//	float max = -FLT_MAX;
//
//	for (unsigned int i = 0; i < inputShapeVertices.size(); i++)
//	{
//		float projection = inputShapeVertices[i] * inputNormal;
//		
//		if (projection > max)
//		{
//			index = i;
//			max = projection;
//		}
//	}
//
//	std::cout << "--getNearestEdge--\n"
//		<< "index: " << index << std::endl
//		<< "maxp: " << max << std::endl;
//
//	Vec2D v = inputShapeVertices[index],
//		vNext = inputShapeVertices[(index + 1) % inputShapeVertices.size()],
//		vPrevious = inputShapeVertices[(index - 1) % inputShapeVertices.size()],
//		left = v - vPrevious, 
//		right = v - vNext; 
//
//	left = left.getNormalisation();
//	right = right.getNormalisation();
//
//	if (right * inputNormal <= left * inputNormal)
//	{
//	//right
//
//		std::cout << "-Right-\n";
//
//		edge.push_back(v);
//		edge.push_back(v);
//		edge.push_back(vNext);
//	}
//	else
//	{
//		std::cout << "-Left-\n";
//
//		//left
//		edge.push_back(v);
//		edge.push_back(vPrevious);
//		edge.push_back(v);
//	}
//
//	std::cout << "-----\n";
//
//	return edge;
//}
//std::vector<Vec2D> SATCollisionCheck::getClippedPoints(const Vec2D& v1, const Vec2D& v2, const Vec2D& n, const float o)
//{
////http://www.dyn4j.org/2011/11/contact-points-using-clipping/ 9/2 2017
//	
//	std::vector<Vec2D> tempClippedPoints;
//
//	float d1 = n * v1 - o,
//		d2 = n * v2 - o;
//
//	if (d1 >= 0.0f)
//		tempClippedPoints.push_back(v1);
//
//	if (d2 >= 0.0f)
//		tempClippedPoints.push_back(v2);
//
//	std::cout << "-------------------------" << std::endl;
//	std::cout << "v1: " << v1.getX() << " " << v1.getY() << std::endl;
//	std::cout << "v2: " << v2.getX() << " " << v2.getY() << std::endl;
//
//	std::cout << "d1 " << d1 << "\nd2 " << d2 << std::endl;
//
//	if (d1 * d2 < 0.0f)
//	{
//		Vec2D e = v2 - v1;
//
//		std::cout << "e: " << e.getX() << " " << e.getY() << std::endl;
//
//		float u = d1 / (d1 - d2);
//
//		e *= u;
//
//		std::cout << "u: " << u << std::endl;
//		std::cout << "e * u: " << e.getX() << " " << e.getY() << std::endl;
//
//		e += v1;
//
//		std::cout << "e + v1: " << e.getX() << " " << e.getY() << std::endl;
//
//		tempClippedPoints.push_back(e);
//
//	}
//
//	std::cout << "-------------------------" << std::endl;
//
//	return tempClippedPoints;
//}
void SATCollisionCheck::calculateContactPoints(const std::vector<Vec2D>& shape1Vertices, const std::vector<Vec2D>& shape2Vertices)
{
	//1 find the edge from each shape

	Vec2D normal = penentrationVector.getNormalisation(); //points to shape1
	std::vector<Vec2D> edge1 = getEdge(shape1Vertices, normal * -1.0f),
		edge2 = getEdge(shape2Vertices, normal);
}
std::vector<Vec2D> SATCollisionCheck::getEdge(const std::vector<Vec2D>& shapeVertices, const Vec2D& collisionNormal) const //returns two points forming an edge
{
	//roughly based on http://www.dyn4j.org/2011/11/contact-points-using-clipping/ 19/2

	//int indexMax = -1, indexNextUpMax = -1;
	//float max = -FLT_MAX, nextUpMax = -FLT_MAX;
	//
	//for (unsigned int i = 0; i < shapeVertices.size(); i++)
	//{
	//	float projection = collisionNormal * shapeVertices[i];
	//
	//	if (projection > max)
	//	{
	//		indexNextUpMax = indexMax;
	//		nextUpMax = max;
	//
	//		max = projection;
	//		indexMax = i;
	//	}
	//	else if (projection > nextUpMax)
	//	{
	//		nextUpMax = projection;
	//		indexNextUpMax = i;
	//	}
	//}
	//
	//
	//Vec2D maxV = shapeVertices[indexMax],
	//	almostMaxV = shapeVertices[indexNextUpMax];

	//std::cout << "maxv: " << maxV.getX() << " " << maxV.getY() << std::endl;
	//std::cout << "almost maxv " << almostMaxV.getX() << " " << almostMaxV.getY() << std::endl;
	//std::cin.get();

	int indexMin = -1, indexNextUpMin = -1;
	float min = FLT_MAX, nextUpMin = FLT_MAX;
	for (unsigned int i = 0; i < shapeVertices.size(); i++)
	{
		float projection = collisionNormal * shapeVertices[i];

		if (projection < min)
		{
			indexNextUpMin = indexMin;
			nextUpMin = min;

			indexMin = i;
			min = projection;
		}
		else if (projection < nextUpMin)
		{
			indexNextUpMin = i;
			min = projection;
		}
	}

	Vec2D vertex1 = shapeVertices[indexMin],
		vertex2 = shapeVertices[indexNextUpMin];

	std::cout << "V1: " << vertex1.getX() << " " << vertex2.getY() <<
		"\nV2: " << vertex2.getX() << " " << vertex2.getY() << std::endl;

	return std::vector<Vec2D>{};
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

	//	if (penentrationVector.getX() < 0.0f && penentrationVector.getX() > -0.0000001)
	//		penentrationVector.setX(0.0f);
	//	if (penentrationVector.getY() < 0.0f && penentrationVector.getY() > -0.0000001)
	//		penentrationVector.setY(0.0f);

		//minimizing rounding errors
		if (penentrationVector.getX() < 0.0f && penentrationVector.getX() > -0.0000001)
			penentrationVector.setX(roundf(penentrationVector.getX() * 100.0f / 100.0f));
		if (penentrationVector.getY() < 0.0f && penentrationVector.getY() > -0.0000001)
			penentrationVector.setY(roundf(penentrationVector.getY() * 100.0f / 100.0f));
	
		//if (penentrationVector.getX() == -0)
		//	penentrationVector.setX(0.0f);
		//if (penentrationVector.getY() == -0)
		//	penentrationVector.setY(0.0f);

		//calc contactpoints
	//	calculateContactPoints(inputVertexShape1.getVertices(), inputVertexShape2.getVertices());

		return true;
	}
	else
		std::cout << "ERROR tried to do SAT check between two entiteis that arent convex\n";


	return false;
}
bool SATCollisionCheck::binarySATCheck(const VertexShape& inputVertexShape1, const VertexShape& inputVertexShape2, const float& deltaTime, const Vec2D& v1, const Vec2D& v2)
{
	//do binary search for collision i ntime between currentpos and pos at next tick

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