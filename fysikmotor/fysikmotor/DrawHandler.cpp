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
		//adds vertices onto the returnshaope one after another
		returnShape[i].position = sf::Vector2f(shapeVertices[i].getX(), shapeVertices[i].getY());
	}

	//change colour etc...

	if (drawfilledVertexShapes)
	{

	}
	if (drawVertexPoints)
	{

	}

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
sf::VertexArray makeArrowShape(const float startX, const float startY, const float inputLength, const float sizeFactor, const float inputRotationDEGREES, const sf::Color inputColour) //arrow scales to the input length, warning uses alot of math and cmath cos/sin functions
{

	float pointyness = 45; //in degrees
	float arrowheadHeight = inputLength / 8;

	sf::VertexArray arrowShape(sf::LinesStrip, 2); //arrowshaft and arrowtip

	arrowShape[0] = sf::Vector2f(startX, startY); //arrow startpoint
	arrowShape[1] = sf::Vector2f(cos(inputRotationDEGREES) * inputLength, sin(inputRotationDEGREES) * inputLength); //arrow tippoint
		
	arrowShape[2] = sf::Vector2f(cos(inputRotationDEGREES) * inputLength - cos(pointyness) * arrowheadHeight, sin(inputRotationDEGREES) * inputLength + sin(pointyness) * arrowheadHeight);
	arrowShape[3] = sf::Vector2f(cos(inputRotationDEGREES) * inputLength + cos(pointyness) * arrowheadHeight, sin(inputRotationDEGREES) * inputLength - sin(pointyness) * arrowheadHeight);
	
	//change the colour of the vertices
	arrowShape[0].color = inputColour;
	arrowShape[1].color = inputColour;
	arrowShape[2].color = inputColour;
	arrowShape[3].color = inputColour;

	return arrowShape;
}
void DrawHandler::updateView() const
{

}
//main functions for draw handler
void DrawHandler::draw(sf::RenderWindow& inputRenderWindow, const std::vector<Entity>& inputEntities) //draws everytyhing to the screen
{
	//got alot of help from Dennis since he has focused mainly on graphics
	//also used sfml dev org

	//1 draw background
	//2 draw other things on background such as lines etc...
	//3 draw entities


	//Create texture to draw things to
	rTexture.create(viewSize.getX(), viewSize.getY());
	rTexture.clear(sf::Color(255, 255, 255));

	//draw lines etc onto the rtexture

	if (drawAxis)
	{
		sf::VertexArray xAxis(sf::LinesStrip, 2), yAxis(sf::LinesStrip, 2);
		
		xAxis[0] = sf::Vector2f(minX, 0);
		xAxis[1] = sf::Vector2f(maxX, 0);
		yAxis[0] = sf::Vector2f(0, minY);
		yAxis[0] = sf::Vector2f(0, maxY);

		rTexture.draw(xAxis);
		rTexture.draw(yAxis);
	}

	if (drawSquareGrid)
	{
		//TODO, need to decide spacing etc

		std::cout << "ERROR: TRIED TO DRW SQAUReQRID EVEN THO ITS NOT DONE DUMBASS/n";
	}
   
	//go through each of the entityies and draw its shape onto the texture
	for (Entity e : inputEntities)
	{
		rTexture.draw(makeIntoVertexArray(e.getVertexShape()));

		if (drawActingForces)
		{
			//go through each of the acting forces and draw it from the cente ofmass of entity
			for (Vec2D f : e.getActingForces())
			{
				rTexture.draw(makeArrowShape(e.getPosition().getX() + e.getCenterOfmassOffset().getX(), e.getPosition().getY() + e.getCenterOfmassOffset().getY(), f.getMagnitude(), 1, f.getDirectionDEGREES(), sf::Color::Red));
			}
		}
		if (drawVertexIDs)
		{

		}
		if (drawCenterOfMass)
		{
			//Draw it as a point, aka small circle
			//maybe error with centering point, no offset? ehh will see if error occurs during runtime

			sf::CircleShape c;
			c.setPosition(e.getPosition().getX() + e.getCenterOfmassOffset().getX(), e.getPosition().getY() + e.getCenterOfmassOffset().getY());
			c.setFillColor(sf::Color::Magenta);
			c.setRadius(1);
			rTexture.draw(c);
		}
		if (drawVelocityVector)
		{
			rTexture.draw(makeArrowShape(e.getPosition().getX() + e.getCenterOfmassOffset().getX(), e.getPosition().getY() + e.getCenterOfmassOffset().getY(), e.getVelocity().getMagnitude(), 1, e.getVelocity().getDirectionDEGREES(), sf::Color::Blue));
		}
		if (drawFrictionSurface)
		{
			//ehhh todo
		}
		if (drawAABBCollisionArea)
		{
			//draw a 2d box around entity

			//creates a rectanglehape
			sf::RectangleShape rShape;
			rShape.setSize(sf::Vector2f(e.getAABBMBottomRight().getX() - e.getAABBTopLeft().getX(), e.getAABBTopLeft().getY() - e.getAABBMBottomRight().getY()));
			rShape.setOutlineColor(sf::Color(255, 0, 0));
			rShape.setPosition(e.getAABBTopLeft().getX(), e.getAABBTopLeft().getY());
			rShape.setOutlineThickness(2);
			rTexture.draw(rShape); //Draws the square shape onto the rTexture
		}
		if (drawEntityTexture)
		{
			//get help from Dennis yo
		}
		if (drawRotationAngleOfEntity)
		{
			//draw line aligned with x axis
			//draw a vertexarray with triangle shapes used, make a halfcircle spanning from the previous mentioned line and then draw text
		}
	}
	rTexture.display(); //displays it onto the rtexture   

	sprite.setTexture(rTexture.getTexture()); //sets the sprite texture to the rtexture
	


	sprite.setPosition(viewPixelPos);

	inputRenderWindow.draw(sprite); //Draws the sprite onto the renderwindow
}
void DrawHandler::setViewPosition(const sf::Vector2f& inputViewPosition) //sets the view pos on the simulation plane
{
	simulationView.setCenter(inputViewPosition);
}
void DrawHandler::moveViewPosition(const sf::Vector2f& inputMoveAmount) //moves the view by the input amount
{
	simulationView.move(inputMoveAmount);
}
void DrawHandler::setZoom(const sf::Vector2f& inputZoomFactor) //sets the zoomfactor with sf vec2f
{
	simulationView.setViewport(sf::FloatRect(sf::Vector2f(viewPos.getX(), viewPos.getY()), inputZoomFactor));
}
//void showEntireSimulation() const; //changes variables to show entire sim window at once, easy preset thingy

//set functions
void DrawHandler::setDrawAxis(const bool inputBool)
{
	drawAxis = inputBool;
}
void DrawHandler::setDrawActingForces(const bool inputBool)
{
	drawActingForces = inputBool;
}
void DrawHandler::setDrawSquareGrid(const bool inputBool)
{
	drawSquareGrid = inputBool;
}
void DrawHandler::setDrawVertexPoints(const bool inputBool)
{
	drawVertexPoints = inputBool;
}
void DrawHandler::setDrawFilledVertexShape(const bool inputBool)
{
	drawfilledVertexShapes = inputBool;
}
void DrawHandler::setDrawVertexIDs(const bool inputBool)
{
	drawVertexIDs = inputBool;
}
void DrawHandler::setDrawCenterOfMass(const bool inputBool)
{
	drawCenterOfMass = inputBool;
}
void DrawHandler::setDrawVelocityVector(const bool inputBool)
{
	drawVelocityVector = inputBool;
}
void DrawHandler::setDrawFrictionSurface(const bool inputBool)
{
	drawFrictionSurface = inputBool;
}
void DrawHandler::setDrawAABBCollisionArea(const bool inputBool)
{
	drawAABBCollisionArea = inputBool;
}
void DrawHandler::setDrawEntityTexture(const bool inputBool)
{
	drawEntityTexture = inputBool;
}
void DrawHandler::setDrawRotationAngle(const bool inputBool)
{
	drawRotationAngleOfEntity = inputBool;
}
void DrawHandler::setSimulationBounds(const float inputMaxX, const float inputMinX, const float inputMaxY, const float inputMinY)
{
	maxX = inputMaxX;
	minX = inputMinX;
	maxY = inputMaxY;
	minY = inputMinY;
}

//get functions
bool DrawHandler::getDrawAxis() const
{
	return drawAxis;
}
bool DrawHandler::getDrawActingForces() const
{
	return drawActingForces;
}
bool DrawHandler::getDrawSquareGrid() const
{
	return drawSquareGrid;
}
bool DrawHandler::getDrawVertexPoints() const
{
	return drawVertexPoints;
}
bool DrawHandler::getDrawFilledVertexShape() const
{
	return drawfilledVertexShapes;
}
bool DrawHandler::getDrawVertexIDs() const
{
	return drawVertexIDs;
}
bool DrawHandler::getDrawCenterOfMass() const
{
	return drawCenterOfMass;
}
bool DrawHandler::getDrawVelocityVector() const
{
	return drawVelocityVector;
}
bool DrawHandler::getDrawFrictionSurface() const
{
	return drawFrictionSurface;
}
bool DrawHandler::getDrawAABBCollisionArea() const
{
	return drawAABBCollisionArea;
}
bool DrawHandler::getDrawEntityTexture() const
{
	return drawEntityTexture;
}
bool DrawHandler::getDrawRotationAngle()const
{
	return drawRotationAngleOfEntity;
}
sf::View DrawHandler::getView() const
{
	return simulationView;
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
	rTexture(),
	sprite(),

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

