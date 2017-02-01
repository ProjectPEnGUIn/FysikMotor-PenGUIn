#include "DrawHandler.h"

bool DrawHandler::isEntityWithinView(const Entity& inputEntity) const
{
	//if view entity is within the view area of the world 
	if (entityAreaAABBCheck(inputEntity, viewPos.getX() + maxX, viewPos.getX(), viewPos.getY(), viewPos.getY() - maxY))
		return true;

	return false;
}
sf::ConvexShape DrawHandler::makeIntoConvexShape(const VertexShape& inputVertexShape) const //turns an own made vertexshapape object into a vertexarray object
{
	//used http://www.sfml-dev.org/documentation/2.4.1/classsf_1_1VertexArray.php#aa38c10707c28a97f4627ae8b2f3ad969 7/1 2017

	sf::ConvexShape returnShape(inputVertexShape.getAmountOfVertices()); //inits the return shape with the amount of vertices
    
	std::vector<Vec2D> shapeVertices = inputVertexShape.getVertices(); //gets all the vertices points from shape

//	std::cout << shapeVertices.size() << " " << inputVertexShape.getAmountOfVertices() << std::endl;

	for (int i = 0; i < inputVertexShape.getAmountOfVertices(); i++)
	{
		//adds vertices onto the returnshaope one after another
		returnShape.setPoint(i, toPixelCoords(shapeVertices[i]));
	}

	returnShape.setOutlineColor(sf::Color::Black);
	returnShape.setOutlineThickness(1);

	return returnShape;
}
void DrawHandler::keepViewWithinBorders() const //keeps the view within the max and min world size
{
	//check if view is outside 
}

sf::ConvexShape DrawHandler::makeArrowShape(const float inputStartX, const float inputStartY, const Vec2D& inputVector, const sf::Color inputColour, const float inputScale) //arrow scales to the input length
{
	//make a square for now to save time

	const float height = inputVector.getMagnitude() * inputScale;

	//rotation is clockwise due to sfml t, sfml rotate is 0 at the top basiclly
	float rotation = inputVector.getDirectionDEGREES();

	rotation += 90.0f;
	rotation *= -1.0f;

	if (rotation > 360.0f || rotation < 0)
		rotation = fmod(rotation, 360.0f);

	sf::ConvexShape arrowShape;
	arrowShape.setPointCount(4);

	arrowShape.setPoint(0, sf::Vector2f(-1, 0));
	arrowShape.setPoint(1, sf::Vector2f(1, 0));
	arrowShape.setPoint(2, sf::Vector2f(1, 0) + toPixelCoords(sf::Vector2f(0, height)));
	arrowShape.setPoint(3, sf::Vector2f(-1, 0) + toPixelCoords(sf::Vector2f(0, height)));

	arrowShape.setPosition(toPixelCoords(sf::Vector2f(inputStartX, inputStartY)));

	arrowShape.setRotation(rotation);

	arrowShape.setFillColor(inputColour);
	
	return arrowShape;
}
sf::Vector2f DrawHandler::toPixelCoords(const Vec2D& inputWorldCoordinates) const
{
	return sf::Vector2f(inputWorldCoordinates.getX() * (viewPixelSize.x / maxX), (maxY - inputWorldCoordinates.getY()) * (viewPixelSize.y / maxY));
}
sf::Vector2f DrawHandler::toPixelCoords(const sf::Vector2f& inputWorldCoordinates) const
{
	return sf::Vector2f(inputWorldCoordinates.x * (viewPixelSize.x / maxX), (maxY - inputWorldCoordinates.y) * (viewPixelSize.y / maxY));
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

	rTexture.clear(sf::Color(255, 255, 255)); //clears imga to white

	//draw lines etc onto the rtexture

	if (drawSquareGrid)
	{
		for (float yLines = maxY / squareGridSpacing; yLines > 0; yLines--)
		{
			//for(int xLines = 
		}
	}

	//go through each of the entityies and draw its shape onto the texture
	for (Entity e : inputEntities)
	{
		if (drawAABBCollisionArea)
		{
			sf::RectangleShape rShape; 
			rShape.setSize(toPixelCoords(Vec2D(e.getAABBMBottomRight().getX(), e.getAABBTopLeft().getY())) - toPixelCoords(Vec2D(e.getAABBMBottomRight().getX(), e.getAABBTopLeft().getY())));
			rShape.setOutlineColor(sf::Color(255, 0, 0));
			rShape.setPosition(toPixelCoords(Vec2D(e.getAABBTopLeft().getX(), e.getAABBTopLeft().getY())));
			rShape.setOutlineThickness(1);
			rTexture.draw(rShape); 
		}
		if (drawVertexIDs)
		{

		}
		if (drawVelocityVector)
		{
			//rTexture.draw(makeArrowShape(e.getPosition().getX() + e.getCenterOfmassOffset().getX(), e.getPosition().getY() + e.getCenterOfmassOffset().getY(), e.getVelocity(), sf::Color::Magenta));
		}
		if (drawFrictionSurface)
		{
			//ehhh todo
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

		rTexture.draw(makeIntoConvexShape(e.getVertexShape()));

		if (drawCenterOfMass)
		{
			//Draw it as a point, aka small circle
			//maybe error with centering point, no offset? ehh will see if error occurs during runtime

			sf::CircleShape centerOfMass;
			centerOfMass.setFillColor(sf::Color::Red);
			centerOfMass.setOrigin(1, 1);
			centerOfMass.setRadius(2); //make it scale to entitysize sometime
			centerOfMass.setPosition(toPixelCoords(sf::Vector2f(e.getPosition().getX() + e.getCenterOfmassOffset().getX(), e.getPosition().getY() + e.getCenterOfmassOffset().getY())));

			rTexture.draw(centerOfMass);
		}
		if (drawActingForces)
		{
			//go through each of the acting forces and draw it from the cente ofmass of entity
			for (const Vec2D& f : e.getActingForces())
			{		
				//doesnt draw forces that have both x and y as 0, pointless and draws a horisontal line on screen
				if (!(f.getX() == 0 && f.getY() == 0)) 
				{
					rTexture.draw(makeArrowShape(e.getPosition().getX() + e.getCenterOfmassOffset().getX(), e.getPosition().getY() + e.getCenterOfmassOffset().getY(), f, sf::Color::Blue, 0.1f));
				}
			}
		}

	}
	rTexture.display(); //displays it onto the rtexture
	
	sprite.setTexture(rTexture.getTexture()); //sets the sprite texture to the rtexture

	sprite.setPosition(viewPixelPos);

	inputRenderWindow.draw(sprite); //Draws the sprite onto the renderwindow
}
void DrawHandler::setViewPosition(const sf::Vector2f& inputViewPosition) //sets the view pos on the simulation plane
{
	//viewPos = inputViewPosition;
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
void DrawHandler::setDrawTrejectory(const bool inputBool)
{
	drawTrejectory = inputBool;
}
void DrawHandler::setSquareGridSpacing(const float inputSpacing)
{
	squareGridSpacing = inputSpacing;
}
void DrawHandler::setSimulationBounds(const float inputMaxX, const float inputMinX, const float inputMaxY, const float inputMinY)
{
	maxX = inputMaxX;
	minX = inputMinX;
	maxY = inputMaxY;
	minY = inputMinY;

}
void DrawHandler::setViewPixelPos(const sf::Vector2f& inputViewPixelPos)
{
	viewPixelPos = inputViewPixelPos;
}
//get functions
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
bool DrawHandler::getDrawTrejectory() const
{
	return drawTrejectory;
}
sf::View DrawHandler::getView() const
{
	return simulationView;
}
float DrawHandler::getSquareGridSpacing() const
{
	return squareGridSpacing;
}

void DrawHandler::init(const float inputSimulationWidth, const float inputSimulationHeight, const float imageWidth, const float imageHeight)
{
	maxX = inputSimulationWidth;
	minX = 0.0f;
	maxY = inputSimulationHeight;
	minY = 0;


	viewPixelSize.x = imageWidth;
	viewPixelSize.y = imageHeight;

	rTexture.create(imageWidth, imageHeight);
}

DrawHandler::DrawHandler()
	:
	maxX(0.0f),
	minX(0.0f),
	maxY(0.0f),
	minY(0.0f),
	simulationView(),
	viewPos(),
	viewPixelPos(),
	viewPixelSize(),
	rTexture(),
	sprite(),
	squareGridSpacing(1.0f),

	drawActingForces(true),
	drawSquareGrid(false),
	drawVertexPoints(false),
	drawfilledVertexShapes(false),
	drawVertexIDs(false),
	drawCenterOfMass(true),
	drawVelocityVector(false),
	drawFrictionSurface(false),
	drawAABBCollisionArea(true),
	drawEntityTexture(false),
	drawRotationAngleOfEntity(false),
	drawTrejectory(false)
{

}

