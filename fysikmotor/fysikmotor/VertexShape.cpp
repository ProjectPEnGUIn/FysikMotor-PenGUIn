#include "VertexShape.h"


//set
void VertexShape::setPosition(const Vec2D& inputPos) //sets the centerpos and all vertices
{

}
void VertexShape::movePosition(const Vec2D& inputMoveAmount) //increments all posistions
{
	//move all positions around with input amount

	trueCenterPosition += inputMoveAmount;
	rotationCenter += inputMoveAmount;

	//moves the vertices pos
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices[i] += inputMoveAmount;
	}
}
void VertexShape::setRotationOffset(const Vec2D& inputRotationOffset) //rotationpoiint is offset by this amound from centerpos
{
	rotationCenter = inputRotationOffset;
}
void VertexShape::incrementRotationDEGREES(double inputRotationIncrementDEGREES) //adds to tyhe current rotation of shaped
{
	rotationAmountDEGREES += inputRotationIncrementDEGREES;

	//convert the radian member to the same value
	rotationAmountRADIANS = (rotationAmountDEGREES * PI) / 180.0;
}
void VertexShape::incrementRotationRADIANS(double inputRotationIncrementRADIANS)
{
	rotationAmountRADIANS += inputRotationIncrementRADIANS;

	//convert the degree thingy so they get the sam e vlaue
	rotationAmountDEGREES = (rotationAmountRADIANS * 180.0) / PI;
}
void VertexShape::setRotationDEGREES(double inputRotationDEGREES)
{
	rotationAmountDEGREES = inputRotationDEGREES;
	rotationAmountRADIANS = (rotationAmountDEGREES * PI) / 180.0;
}
void VertexShape::setRotationRADIANS(double inputRotationRADIANS)
{
	rotationAmountRADIANS = inputRotationRADIANS;
	rotationAmountDEGREES = (rotationAmountRADIANS * 180.0) / PI;
}

void VertexShape::addVertexPoint(const Vec2D& inputWorldCoordinate) //adds a vertex for the shape at the input world coo´rdinate, appends it to vertex vector
{
	vertices.push_back(inputWorldCoordinate);

	//update vertices shape with the new vertex added
	updateCenterPos();
	updateRotationOnVertices();
	updateAABBBox();
}
void VertexShape::removeVertex(int inputVertexIndex) //removes the vertex at the given index, starts at 0
{
	//prevent out of range things
	if (inputVertexIndex < vertices.size())
	{
		vertices.erase(vertices.begin() + inputVertexIndex);
	}
}
void VertexShape::clearVertices() //erases all vertex points
{
	vertices.clear();
}

//get
Vec2D VertexShape::getCenterPos() const
{
	return trueCenterPosition;
}
double VertexShape::getCurrentRotationDEGREES() const
{
	return rotationAmountDEGREES;
}
double VertexShape::getCurrentRotationRADIANS() const
{
	return rotationAmountRADIANS;
}
int VertexShape::getAmountOfVertices() const
{
	return vertices.size();
}
std::vector<Vec2D> VertexShape::getVertices() const //returnsa all vertices
{
	return vertices;
}
Vec2D VertexShape::getTopLeftAABBCorner() const
{
	return aabbMin;
}
Vec2D VertexShape::getBottomRightAABBCorner() const
{
	return aabbMax;
}

//updating
void VertexShape::updateAABBBox() //updates the aabb bounding box
{
	Vec2D maxPos, minPos;

	//searches through all the vertiuces for the max and min values
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].getX() > maxPos.getX())
			maxPos.setX(vertices[i].getX());

		if (vertices[i].getY() > maxPos.getY())
			maxPos.setY(vertices[i].getY());

		if (vertices[i].getX() < minPos.getX())
			minPos.setX(vertices[i].getX());

		if (vertices[i].getY() < minPos.getY())
			minPos.setY(vertices[i].getX());
	}

	aabbMax = maxPos;
	aabbMin = minPos;
}
void VertexShape::updateRotationOnVertices() //updates the vertices points
{
	//TODO
}
void VertexShape::updateCenterPos() //updates the centerpos location of the vertices shape
{
	double centerXTemp, centerYTemp;

	//average values from vertices to get x and y values

	//go through all vertices
	unsigned int i = 0;
	for ( ; i < vertices.size(); i++)
	{
		centerXTemp += vertices[i].getX();
		centerYTemp += vertices[i].getY();
	}

	//averages the x and y values out over the number of vertices
	trueCenterPosition.setX(centerXTemp / i);
	trueCenterPosition.setY(centerYTemp / i);
}


VertexShape::VertexShape()
	:
	rotationAmountDEGREES(0),
	rotationAmountRADIANS(0)
{
}
