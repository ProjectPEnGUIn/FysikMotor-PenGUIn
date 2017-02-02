#include "GJK.h"
void GJK::negateVector(Vec2D& inputVector)
{
//http://planetside.co.uk/wiki/index.php?title=Negate_Vector
//http://www.math.uiuc.edu/Macaulay2/doc/Macaulay2-1.9/share/doc/Macaulay2/Macaulay2Doc/html/_-_sp__List.html


	inputVector = Vec2D(-1.0f * inputVector.getX(), -1.0f * inputVector.getY());
}
bool GJK::processSimplex(Vec2D& direction)
{
	if (simplex[A].getX() != FLT_MAX && simplex[A].getY() != FLT_MAX && simplex[B].getX() != FLT_MAX && simplex[B].getY() != FLT_MAX && simplex[C].getX() == FLT_MAX && simplex[C].getY() == FLT_MAX)
	{
		//1 simplex

		if (isSameDirection(simplex[A] * -1.0f, simplex[B] - simplex[A]))
		{
			direction = (simplex[B] - simplex[A]).getRightNormal();

			direction.scaleVector((simplex[A] * -1.0f) * direction);

			//simplex = [simplex.a, simplex.b]
			simplex[A] = simplex[A];
			simplex[B] = simplex[B];
			simplex[C] = Vec2D(FLT_MAX, FLT_MAX);
		}
		else
		{
			direction = simplex[A] * -1.0f;

			simplex[A] = simplex[A];
			simplex[B] = Vec2D(FLT_MAX, FLT_MAX);
			simplex[C] = Vec2D(FLT_MAX, FLT_MAX);
		}
	}
	else
	{
		//2 simplex

		Vec2D AB = simplex[B] - simplex[A],
			AC = simplex[C] - simplex[A],
			AO = simplex[A] * -1.0f;

		Vec2D ACB = AB.getRightNormal();
		ACB.scaleVector(ACB * (AC * -1.0f));

		Vec2D ABC = AC.getRightNormal();
		ABC.scaleVector(ABC * (AB * -1.0f));

		if (isSameDirection(ACB, AO))
		{
			if (isSameDirection(AB, AO))
			{
				direction = ACB;

				simplex[A] = simplex[A];
				simplex[B] = simplex[B];
				simplex[C] = Vec2D(FLT_MAX, FLT_MAX);

				return false;
			}
			else
			{
				direction = AO;

				simplex[A] = simplex[A];
				simplex[B] = Vec2D(FLT_MAX, FLT_MAX);
				simplex[C] = Vec2D(FLT_MAX, FLT_MAX);

				return false;
			}
		}
		else if (isSameDirection(ABC, AO))
		{
			if (isSameDirection(AC, AO))
			{
				direction = ABC;

				simplex[A] = simplex[A];
				simplex[B] = Vec2D(FLT_MAX, FLT_MAX);
				simplex[C] = simplex[C];

				return false;
			}
			else
			{
				direction = AO;

				simplex[A] = simplex[A];
				simplex[B] = Vec2D(FLT_MAX, FLT_MAX);
				simplex[C] = Vec2D(FLT_MAX, FLT_MAX);

				return false;
			}

		}
		else
			return true;
	}
}
Vec2D GJK::getFarthestPointInDirection(const VertexShape& inputShape, const Vec2D& inputDirection) const
{
 //http://in2gpu.com/2014/05/12/gjk-algorithm-collision-detection-2d-in-c/

	int index = 0;
	float maxDot = inputShape.getVertices()[index] * inputDirection.getNormalisation();

	

	for (unsigned int i = 1; i < inputShape.getVertices().size(); i++)
	{
		float dot = inputShape.getVertices()[i] * inputDirection.getNormalisation();

		if (dot > maxDot)
		{
			maxDot = dot;
			index = i;
		}
	}

	return inputShape.getVertices()[index];
}
Vec2D GJK::support(const VertexShape& inputShape1, const VertexShape& inputShape2, const Vec2D& inputDirection) const
{
//http://in2gpu.com/2014/05/12/gjk-algorithm-collision-detection-2d-in-c/

	Vec2D p1 = getFarthestPointInDirection(inputShape1, inputDirection);
	Vec2D p2 = getFarthestPointInDirection(inputShape2, inputDirection * -1.0f);

	//Vec2D p3 = Vec2D(p1.getX() - p2.getX(), p1.getY() - p2.getY());
	

	return  p1 - p2;
}
bool GJK::isSameDirection(const Vec2D& inputVector1, const Vec2D& inputVector2) const
{
	return inputVector1*inputVector2;
}
bool GJK::collisionCheck(const VertexShape& inputShape1, const VertexShape& inputShape2)
{
//http://in2gpu.com/2014/05/12/gjk-algorithm-collision-detection-2d-in-c/
//http://entropyinteractive.com/2011/04/gjk-algorithm/


	Vec2D direction = Vec2D(1, 0);

	simplex[A] = Vec2D(FLT_MAX, FLT_MAX);
	simplex[B] = Vec2D(FLT_MAX, FLT_MAX);
	simplex[C] = Vec2D(FLT_MAX, FLT_MAX);


	simplex[A] = support(inputShape1, inputShape2, direction);

	direction = simplex[0] * 1.0f;

	while (true)
	{
		if(simplex[A].getX() != FLT_MAX && simplex[A].getY() != FLT_MAX)
			simplex[A] = support(inputShape1, inputShape2, direction);

		if (simplex[B].getX() != FLT_MAX && simplex[B].getY() != FLT_MAX)
			simplex[B] = support(inputShape1, inputShape2, direction);

		if (simplex[C].getX() != FLT_MAX && simplex[C].getY() != FLT_MAX)
			simplex[C] = support(inputShape1, inputShape2, direction);

		if (!isSameDirection(direction, simplex[A]))
			return false;
		
		
		if (processSimplex(direction))
			return true;
		

	}
}
GJK::GJK()
	:
	contactPoints(),
	minimumTranslationVector()
{
}

