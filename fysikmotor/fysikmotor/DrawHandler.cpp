#include "DrawHandler.h"

bool DrawHandler::isEntityWithinView(const Entity& inputEntity) const
{
	//if view entity is within the view area of the world 
	if (entityAreaAABBCheck(inputEntity, viewPos.getX() + viewSize.getX(), viewPos.getX(), viewPos.getY(), viewPos.getY() - viewSize.getY()))
		return true;

	return false;
}
sf::VertexArray DrawHandler::makeIntoVertexArray(const VertexShape& inputVertexShape) const //turns an own made vertexshapape object into a vertexarray object
{
	//used http://www.sfml-dev.org/documentation/2.4.1/classsf_1_1VertexArray.php#aa38c10707c28a97f4627ae8b2f3ad969 7/1 2017

	sf::VertexArray returnShape(sf::LinesStrip, inputVertexShape.getAmountOfVertices()); //inits the return shape with the amount of vertices
    
	std::vector<Vec2D> shapeVertices = inputVertexShape.getVertices(); //gets all the vertices points from shape

	for (unsigned int i = 0; i < inputVertexShape.getAmountOfVertices(); i++)
	{
		//adds vertices onto the returnshaope
		returnShape[i].position = sf::Vector2f(shapeVertices[i].getX(), shapeVertices[i].getY());
	}

	//do settings for vertexshape etc, fillcolour...
	


	return returnShape;
}
void DrawHandler::keepViewWithinBorders() const //keeps the view within the max and min world size
{
	//check if view is outside of world plane boundries
	//handle result accordingly
}
sf::Vector2f DrawHandler::translateWorldCoordinateIntoImageCoordinate(const sf::Vector2f& inputWorldCoordinate) const
{

}
sf::Vector2f DrawHandler::translateWorldCoordinateIntoImageCoordinate(const Vec2D& inputWorldCoordinate) const
{

}
sf::Vector2f DrawHandler::translateScreenCoordinateIntoWorldCoordinate(const sf::View& inputview) 
{

}

void DrawHandler::updateView() const
{

}

//main functions for draw handler
void DrawHandler::draw(sf::RenderWindow& inputRenderWindow, const std::vector<Entity>& inputEntities) const //draws everytyhing to the screen
{

}
void DrawHandler::setViewPosition(const sf::Vector2f& inputViewPosition) //sets the view pos on the simulation plane
{

}
void DrawHandler::moveViewPosition(const sf::Vector2f& inputMoveAmount) //moves the view by the input amount
{

}
void DrawHandler::setZoom(const sf::Vector2f& inputZoomFactor) //sets the zoomfactor with sf vec2f
{

}
												   //void showEntireSimulation() const; //changes variables to show entire sim window at once, easy preset thingy

												   //set functions
void DrawHandler::setDrawAxis(const bool inputBool)
{

}
void DrawHandler::setDrawActingForces(const bool inputBool)
{

}
void DrawHandler::setDrawSquareGrid(const bool inputBool)
{

}
void DrawHandler::setDrawVertexPoints(const bool inputBool)
{

}
void DrawHandler::setDrawFilledVertexShape(const bool inputBool)
{

}
void DrawHandler::setDrawVertexIDs(const bool inputBool)
{

}
void DrawHandler::setDrawCenterOfMass(const bool inputBool)
{

}
void DrawHandler::setDrawVelocityVector(const bool inputBool)
{

}
void DrawHandler::setDrawFrictionSurface(const bool inputBool)
{

}
void DrawHandler::setDrawAABBCollisionArea(const bool inputBool)
{

}
void DrawHandler::setDrawEntityTexture(const bool inputBool)
{

}
void DrawHandler::setDrawRotationAngle(const bool inputBool)
{

}

//get functions
bool DrawHandler::getDrawAxis() const
{

}
bool DrawHandler::getDrawActingForces() const
{

}
bool DrawHandler::getDrawSquareGrid() const
{

}
bool DrawHandler::getDrawVertexPoints() const
{

}
bool DrawHandler::getDrawFilledVertexShape() const
{

}
bool DrawHandler::getDrawVertexIDs() const
{

}
bool DrawHandler::getDrawCenterOfMass() const
{

}
bool DrawHandler::getDrawVelocityVector() const
{

}
bool DrawHandler::getDrawFrictionSurface() const
{

}
bool DrawHandler::getDrawAABBCollisionArea() const
{

}
bool DrawHandler::getDrawEntityTexture() const
{

}
bool DrawHandler::getDrawRotationAngle()const
{

}
sf::View DrawHandler::getView() const
{

}

DrawHandler::DrawHandler()
	:
	maxX(0.0f),
	minX(0.0f),
	maxY(0.0f),
	minY(0.0f),
	simulationView(),
	viewPos(),
	viewSize(),
	viewPixelPos(),
	viewPixelSize(),
	drawTexture(),
	drawSprite(),

	drawAxis(false),
	drawActingForces(false),
	drawSquareGrid(false),
	drawVertexPoints(false),
	drawfilledVertexShapes(false),
	drawVertexIDs(false),
	drawCenterOfMass(false),
	drawVelocityVector(false),
	drawFrictionSurface(false),
	drawAABBCollisionArea(false),
	drawEntityTexture(false),
	drawRotationAngleOfEntity(false)
{
}

