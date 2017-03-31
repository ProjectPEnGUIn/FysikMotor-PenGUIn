#include "VertexShape.h"


//set

void VertexShape::setPosition(const Vec2D& inputPos) //sets the centerpos and all vertices, global coords
{
	//1 check deltaPos //2 apply deltapos to all vertices and the centerpos

	 Vec2D deltaPos = inputPos - centerPosition;

	 centerPosition += deltaPos;

	 //change vertices positions
	 for (Vec2D& p : vertices)
	 {
		 p += deltaPos;
	 }

	 updateAABBBox(); //updates aabbbox with new vertices positions

}
void VertexShape::movePosition(const Vec2D& inputMoveAmount) //increments current position
{
	//move all positions around with input amount

	centerPosition += inputMoveAmount;
	//rotationCenter += inputMoveAmount;

	//moves the vertices pos
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices[i] += inputMoveAmount;
	}

	//update vertices shape with the new vertex added
	
	updateAABBBox(); //updates aabbbox with new vertices positions
}

void VertexShape::incrementRotationDEGREES(float inputRotationIncrementDEGREES) //adds to tyhe current rotation of shaped
{
	rotationOffsetDEGREES += inputRotationIncrementDEGREES;

	//convert the radian member to the same value
	rotationOffsetRADIANS = (rotationOffsetDEGREES * PI) / 180.0f;

	//update vertices shape with the new vertex added
	updateCenterPos();
	updateRotationOnVertices();
	updateAABBBox();
}
void VertexShape::incrementRotationRADIANS(float inputRotationIncrementRADIANS)
{
	rotationOffsetRADIANS += inputRotationIncrementRADIANS;

	//convert the degree thingy so they get the sam e vlaue
	rotationOffsetDEGREES = (rotationOffsetRADIANS * 180.0f) / PI;

	//update vertices shape with the new vertex added
	updateCenterPos();
	updateRotationOnVertices();
	updateAABBBox();
}
void VertexShape::setRotationDEGREES(float inputRotationDEGREES)
{
	float delta = inputRotationDEGREES - rotationOffsetDEGREES;
	rotationOffsetDEGREES = fmod(rotationOffsetDEGREES + delta, 360.0f);
	rotationOffsetRADIANS = fmod((rotationOffsetDEGREES * 0.017453292f), (2 * PI));

	//std::cout << "rot: " << inputRotationDEGREES << " - newrot: " << rotationOffsetDEGREES << std::endl;
	//std::cout << "pres enter yo\n";
	//std::cin.get();

	//update vertices shape with the new vertex added
	updateCenterPos();
	updateRotationOnVertices();
	updateAABBBox();
}
void VertexShape::setRotationRADIANS(float inputRotationRADIANS)
{
	float delta = inputRotationRADIANS - rotationOffsetRADIANS;
	rotationOffsetRADIANS = fmod(rotationOffsetRADIANS + delta, (2 * PI));
	rotationOffsetDEGREES = fmod(rotationOffsetRADIANS / 0.017453292f, 360.0f);

	//update vertices shape with the new vertex added
	updateCenterPos();
	updateRotationOnVertices();
	updateAABBBox();
}

void VertexShape::addVertexPoint(const Vec2D& inputWorldCoordinate)//CLOCKWISE DIRECTION, adds a vertex for the shape at the input world coo´rdinate, appends it to vertex vector
{
	vertices.push_back(inputWorldCoordinate);

	//update vertices shape with the new vertex added
	updateCenterPos();
	updateAABBBox();
}
void VertexShape::removeVertex(int inputVertexIndex) //removes the vertex at the given index, starts at 0
{
	//prevent out of range things
	if ((unsigned) inputVertexIndex < vertices.size())
	{
		vertices.erase(vertices.begin() + inputVertexIndex);
	}
	//update vertices shape with the new vertex added
	updateCenterPos();
	updateRotationOnVertices();
	updateAABBBox();
}
void VertexShape::clearVertices() //erases all vertex points
{
	vertices.clear(); //erases the vector
}

//get
Vec2D VertexShape::getCenterPos() const //returns centerpos of shape
{
	return centerPosition;
}
float VertexShape::getCurrentRotationDEGREES() const //returns current rotation in degrees
{
	return rotationOffsetDEGREES;
}
float VertexShape::getCurrentRotationRADIANS() const //returns current rottation in radians
{
	return rotationOffsetRADIANS;
}
int VertexShape::getAmountOfVertices() const //returns number of vertices as an int
{
	return vertices.size();
}
std::vector<Vec2D> VertexShape::getVertices() const //returns all vertices in a std::vector<>
{
	return vertices;
}
Vec2D VertexShape::getTopLeftAABBCorner() const //return top left corner in world coordinates
{
	return aabbTL;
}
Vec2D VertexShape::getBottomRightAABBCorner() const //returns bottom right corner in  world coordinates
{
	return aabbBR;
}
sf::Transform VertexShape::getCurrentTransformation() const
{
	return rotation;
}

//updating
void VertexShape::updateAABBBox() //updates the aabb bounding box
{
	float maxX = -FLT_MAX, minX = FLT_MAX, maxY = -FLT_MAX, minY = FLT_MAX; //has to be inited to something

	//goes through all vertices and finds the max/min values in x and y direction
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].getX() > maxX)
			maxX = vertices[i].getX();

		if (vertices[i].getY() > maxY)
			maxY = vertices[i].getY();

		if (vertices[i].getX() < minX)
			minX = vertices[i].getX();

		if (vertices[i].getY() < minY)
			minY = vertices[i].getY();
	}

	//sets the new max/min points in each direction
	aabbTL.setXY(minX, maxY);
	aabbBR.setXY(maxX, minY);
}
void VertexShape::updateRotationOnVertices() //updates the vertices points
{
	rotation = sf::Transform{};
	rotation.rotate(rotationOffsetDEGREES, sf::Vector2f(centerPosition.getX() , centerPosition.getY()));//, trueCenterPosition.getX(), trueCenterPosition.getY());

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		sf::Vector2f temp; //use sfml vector as rotatio n object returns it

	    //transforms the vertex point and stores it in temp
		temp = rotation.transformPoint(vertices[i].getX(), vertices[i].getY());
		
		vertices[i].setXY(temp.x, temp.y); //give the vertex the new temppos
	}

}
void VertexShape::updateCenterPos() //updates the centerpos location of the vertices shape
{
	float centerXTemp = 0, centerYTemp = 0;

	//average values from vertices to get x and y values is the centerpos

	//go through all vertices
	unsigned int i = 0;
	for ( ; i < vertices.size(); i++)
	{
		centerXTemp += vertices[i].getX();
		centerYTemp += vertices[i].getY();
	}

	//averages the x and y values out over the number of vertices which then gives the centerpos
	centerPosition.setX(centerXTemp / i);
	centerPosition.setY(centerYTemp / i);
}

VertexShape::VertexShape() //default constructor
	:
	PI(3.14159265f),
	centerPosition(),
	rotationOffsetDEGREES(0),
	rotationOffsetRADIANS(0),
	vertices(),
	rotation(),
	aabbTL(),
	aabbBR()

{
}

//own made copy assignment operator, caused errors without it
VertexShape& VertexShape::operator=(const VertexShape& inputVertexShape)
{
	if (this != &inputVertexShape)
	{
		centerPosition = inputVertexShape.getCenterPos();
		rotationOffsetDEGREES = inputVertexShape.getCurrentRotationDEGREES();
		rotationOffsetRADIANS = inputVertexShape.getCurrentRotationRADIANS();
		vertices = inputVertexShape.getVertices();
		rotation = inputVertexShape.getCurrentTransformation();
		aabbBR = inputVertexShape.getBottomRightAABBCorner();
		aabbTL = inputVertexShape.getTopLeftAABBCorner();
	}
	return *this;
}