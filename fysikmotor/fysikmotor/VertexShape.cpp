#include "VertexShape.h"


//set
void VertexShape::setPosition(const Vec2D& inputPos) //sets the centerpos and all vertices
{

}
void VertexShape::movePosition(const Vec2D& inputMoveAmount) //increments all posistions
{
	//move all positions around with input amount

	trueCenterPosition += inputMoveAmount;
	//rotationCenter += inputMoveAmount;

	//moves the vertices pos
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices[i] += inputMoveAmount;
	}
}
void VertexShape::setRotationCenterOffset(const Vec2D& inputRotationOffset) //rotationpoiint is offset by this amound from centerpos
{
	rotationCenterOffset = inputRotationOffset;
}
void VertexShape::incrementRotationDEGREES(float inputRotationIncrementDEGREES) //adds to tyhe current rotation of shaped
{
	rotationOffsetDEGREES += inputRotationIncrementDEGREES;

	//convert the radian member to the same value
	rotationOffsetRADIANS = (rotationOffsetDEGREES * PI) / 180.0f;

	updateRotationOnVertices();
}
void VertexShape::incrementRotationRADIANS(float inputRotationIncrementRADIANS)
{
	rotationOffsetRADIANS += inputRotationIncrementRADIANS;

	//convert the degree thingy so they get the sam e vlaue
	rotationOffsetDEGREES = (rotationOffsetRADIANS * 180.0f) / PI;

	updateRotationOnVertices();
}
void VertexShape::setRotationDEGREES(float inputRotationDEGREES)
{
	float delta = rotationOffsetDEGREES - inputRotationDEGREES;
	rotationOffsetDEGREES = inputRotationDEGREES + delta;
	rotationOffsetRADIANS = (rotationOffsetDEGREES * PI) / 180.0f;

	updateRotationOnVertices();
}
void VertexShape::setRotationRADIANS(float inputRotationRADIANS)
{
	float delta = rotationOffsetRADIANS - inputRotationRADIANS;
	rotationOffsetRADIANS = inputRotationRADIANS + delta;

	rotationOffsetDEGREES = (rotationOffsetRADIANS * 180.0f) / PI;

	updateRotationOnVertices();
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
	if ((unsigned) inputVertexIndex < vertices.size())
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
Vec2D VertexShape::getRotationCenterOffset() const
{
	return rotationCenterOffset;
}
float VertexShape::getCurrentRotationDEGREES() const
{
	return rotationOffsetDEGREES;
}
float VertexShape::getCurrentRotationRADIANS() const
{
	return rotationOffsetRADIANS;
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

	rotation.rotate(rotationOffsetDEGREES, trueCenterPosition.getX(), trueCenterPosition.getY());
	
	sf::Vector2f temp; //use sfml vector

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
	    //transforms the vertex point and stores it in temp
		temp = rotation.transformPoint(vertices[i].getX() + rotationCenterOffset.getX(), vertices[i].getY() + rotationCenterOffset.getY());
		vertices[i].setXY(temp.x, temp.y); //give the vertex the new temppos
	}
}
void VertexShape::updateCenterPos() //updates the centerpos location of the vertices shape
{
	float centerXTemp = 0, centerYTemp = 0;

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
	trueCenterPosition(),
	rotationCenterOffset(),
	rotationOffsetDEGREES(0),
	rotationOffsetRADIANS(0),
	vertices(),
	rotation(),
	aabbMin(),
	aabbMax()

{
	//log creating? maybe
}

VertexShape& VertexShape::operator=(const VertexShape& inputVertexShape)
{
	if (this != &inputVertexShape)
	{
		
	}
	return *this;
}