//#include "GJK.h"
//bool GJK::isShapeConvex(const VertexShape& inputVertexShape) const
//{
//	//TODO
//
//	return true;
//}
//Vec2D GJK::support(const VertexShape& inputVertexShape1, const VertexShape& inputVertexShape2, const Vec2D& inputDirection) //returns a point in the minskowski differance
//{
//	//https://www.youtube.com/watch?v=XIavUJ848Mk 2/2
//
//	Vec2D p1 = getFarthestPointInDirection(inputVertexShape1.getVertices(), inputDirection),
//		p2 = getFarthestPointInDirection(inputVertexShape2.getVertices(), Vec2D(-inputDirection.getX(), -inputDirection.getY()));
//
//	Vec2D p3 = Vec2D((p1 - p2).getX(), (p1 - p2).getY());
//	return p3;
//}
//Vec2D GJK::getFarthestPointInDirection(const std::vector<Vec2D>& inputPoints, const Vec2D& inputDirection)
//{
//	//http://in2gpu.com/2014/05/12/gjk-algorithm-collision-detection-2d-in-c/ 1/2
//
//	int index = 0;
//	float maxDot = inputPoints[index] * inputDirection;
//
//	for (unsigned int i = 1; i < inputPoints.size(); i++)
//	{
//		float dot = inputPoints[i] * inputDirection;
//
//		if (dot > maxDot)
//		{
//			maxDot = dot;
//			index = i;
//		}
//	}
//
//	return inputPoints[index];
//}
//bool GJK::doSimplex(std::vector<Vec2D>& inputSimplex, Vec2D& inputDirection) //modifies theo input values
//{
//	//https://www.youtube.com/watch?v=XIavUJ848Mk 2/2
////http://in2gpu.com/2014/05/12/gjk-algorithm-collision-detection-2d-in-c/ 1/2
//
//	
//	if (inputSimplex.size() == 3)
//	{
//		//triangle
//	
//	   Vec2D AB = inputSimplex[inputSimplex.size() - 2] - inputSimplex[inputSimplex.size() - 1], //AB = B-A
//	   AC = inputSimplex[inputSimplex.size() - 3] - inputSimplex[inputSimplex.size() - 1], //AC = C - A
//	   AO = inputSimplex[inputSimplex.size() - 1] * -1.0f;
//
//	   inputDirection = Vec2D(-1.0f * AB.getY(), AB.getX());//away from C
//
//	   if (inputDirection * inputSimplex[inputSimplex.size() - 3] > 0)
//		   inputDirection = inputDirection * -1.0f;
//
//	   if (inputDirection * AO > 0) //same direction
//	   {
//	
//		   //removes C
//		   inputSimplex.erase(inputSimplex.begin() + 0);
//
//		   return false;
//	   }
//
//	   inputDirection = AC.getRightNormal();
//
//	   if (inputDirection * inputSimplex[inputSimplex.size() - 2] > 0)
//	   {
//		   inputDirection *= -1.0f;
//	   }
//
//	   if (inputDirection * AO > 0)
//	   {
//		   //remove b
//		   inputSimplex.erase(inputSimplex.begin() + 1);
//
//		   return false;
//	   }
//
//	   return true;
//
//	}
//	else 
//	{
//		//line segment
//
//		Vec2D A = inputSimplex[inputSimplex.size() - 1],
//			B = inputSimplex[inputSimplex.size() - 2],
//			AB = B - A,
//			AO = A * -1.0f;
//
//		inputDirection = AB.getRightNormal();
//
//		if (inputDirection * AO < 0)
//		{
//			inputDirection *= -1.0f;
//		}
//	}
//
//	
//	return false;
//}
//Vec2D GJK::getMTV() const //returns the minimum translation vector
//{
//	return minimumTranslationVector;
//}
//std::vector<Vec2D> GJK::getContactPoints() const //returns all the contact points in gl
//{
//	return contactPoints;
//}
//bool GJK::collisionCheck(const VertexShape& inputShape1, const VertexShape& inputShape2)
//{
//
//	//https://www.youtube.com/watch?v=XIavUJ848Mk 2/2
//	//http://programyourfaceoff.blogspot.se/2012/01/gjk-algorithm.html
//
//	if (isShapeConvex(inputShape1) && isShapeConvex(inputShape2))
//	{
//		int maxIterations = 100;
//
//		std::vector<Vec2D> simplex;
//		Vec2D direction(1, -1);
//
//		Vec2D s = support(inputShape1, inputShape2, direction);
//		
//		simplex.push_back(s);
//
//		direction = s * -1.0f;
//
//		while (maxIterations > 0)
//		{
//
//			
//			simplex.push_back(support(inputShape1, inputShape2, direction));
//
//			if (simplex[simplex.size() -1] * direction <= 0)
//				return false;
//			
//		//	simplex.push_back(a);
//
//		
//
//			if (doSimplex(simplex, direction))
//			{
//				
//				return true;
//			}
//
//			maxIterations--;
//		}
//
//		std::cout << "Reached max iterations; collision probably is true\n";
//		return true;
//	}
//	else
//	{
//		std::cout << "ERROR GJK; shapes needs to be convex\n";
//		return false;
//	}
//
//	return false;
//}
//GJK::GJK()
//	:
//	contactPoints(),
//	minimumTranslationVector()
//{
//}

