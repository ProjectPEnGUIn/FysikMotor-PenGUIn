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

	const float height = inputVector.getMagnitude() * (viewPixelSize.y / maxY) * inputScale;

	//rotation is clockwise due to sfml t, sfml rotate is 0 at the top basiclly
	float rotation = inputVector.getDirectionDEGREES();

	rotation += 90.0f;
	rotation *= -1.0f;

	if (rotation > 360.0f || rotation < 0)
		rotation = fmod(rotation, 360.0f);

	sf::ConvexShape arrowShape;
	arrowShape.setPointCount(7);

	arrowShape.setPoint(0, sf::Vector2f(-1, 0));
	arrowShape.setPoint(1, sf::Vector2f(-1, height));
	arrowShape.setPoint(2, sf::Vector2f(-3, height * 1.01f));
	arrowShape.setPoint(3, sf::Vector2f(0, height * 1.05f));
	arrowShape.setPoint(4, sf::Vector2f(3, height));
	arrowShape.setPoint(5, sf::Vector2f(1, height * 1.01f));
	arrowShape.setPoint(6, sf::Vector2f(1, 0));

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
	//4 give the rendertexture to sprite
	//5 draw sprite on screen

	rTexture.clear(sf::Color(255, 255, 255)); //clears imga to white
	//draw lines etc onto the rtexture

	if (drawSquareGrid)
	{
		//lines splitting up x axis
		for (float x = 0.0f; x < maxX; x += squareGridSpacing)
		{
			sf::RectangleShape line;
			line.setSize(sf::Vector2f(1, viewPixelSize.y));
			line.setFillColor(sf::Color(30, 30, 30, 90));
			line.setPosition(toPixelCoords(Vec2D(x, maxY)));
			rTexture.draw(line);
		}

		//lines splitting up y axis
		//lines splitting up x axis
		for (float y = 0.0f; y < maxY; y += squareGridSpacing)
		{
			sf::RectangleShape line;
			line.setSize(sf::Vector2f(viewPixelSize.x, 1));
			line.setFillColor(sf::Color(30, 30, 30, 90));
			line.setPosition(toPixelCoords(Vec2D(0, y)));
			rTexture.draw(line);
		}
	}


	//go through each of the entityies and draw its shape onto the texture
	for (const Entity& e : inputEntities)
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

		if (drawCenterOfMass && e.getEntityState() != 0)
		{
			//Draw it as a point, aka small circle
			//maybe error with centering point, no offset? ehh will see if error occurs during runtime

			sf::CircleShape centerOfMass;
			centerOfMass.setFillColor(sf::Color::Red);
			centerOfMass.setOrigin(1, 1);
			centerOfMass.setRadius(2); //make it scale to entitysize sometime
			centerOfMass.setPosition(toPixelCoords(sf::Vector2f(e.getPosition().getX() , e.getPosition().getY())));

			rTexture.draw(centerOfMass);
		}
		if (drawActingForces)
		{
			//go through each of the acting forces and draw it from the cente ofmass of entity
			for (const Force& f : e.getForces())
			{		
				//doesnt draw forces that have both x and y as 0, pointless and draws a horisontal line on screen
				if (!(f.getForce().getX() == 0 && f.getForce().getY() == 0)) 
				{
					rTexture.draw(makeArrowShape(e.getPosition().getX()  + f.getOffset().getX(), e.getPosition().getY() + f.getOffset().getY(), f.getForce(), f.getColour(), 0.25f));

					if (f.getName() != "_noNameSet")
					{
						//draw the force name and value with units

						text.setString(std::string(f.getName() + " " + std::to_string(f.getForce().getMagnitude()) + " N"));
						text.setFillColor(f.getColour() - sf::Color(0, 0, 0, 50));
						text.setPosition(toPixelCoords(e.getPosition() * 1.01f + f.getForce() * 0.25f));
						rTexture.draw(text);
					}
				}
			}
		}

		if (drawID)
		{
			text.setString(std::string("ID: " + std::to_string(e.getEntityID())));
			text.setFillColor(sf::Color(200, 0, 150, 200));
			text.setPosition(toPixelCoords(e.getPosition()));
			rTexture.draw(text);
		}
		if (drawVelocityVector)
		{		
			//vel x
			if (e.getVelocity().getX() != 0.0f)
			{
				rTexture.draw(makeArrowShape(e.getPosition().getX(), e.getPosition().getY(), Vec2D(e.getVelocity().getX(), 0), sf::Color(0, 0, 255), 0.5f));
				text.setString(std::string("Velocity in X " + std::to_string(e.getVelocity().getX())));
				text.setFillColor(sf::Color(0, 0, 255) - sf::Color(0, 0, 0, 50));
				text.setPosition(toPixelCoords(e.getPosition() + Vec2D(e.getVelocity().getX() * 0.5f, 0)));
				rTexture.draw(text);
			}
			//vel y
			if (e.getVelocity().getY() != 0.0f)
			{
				rTexture.draw(makeArrowShape(e.getPosition().getX(), e.getPosition().getY(), Vec2D(0, e.getVelocity().getY()), sf::Color(0, 0, 255), 0.5f));
				text.setString(std::string("Velocity in Y " + std::to_string(e.getVelocity().getX())));
				text.setFillColor(sf::Color(0, 0, 255) - sf::Color(0, 0, 0, 50));
				text.setPosition(toPixelCoords(e.getPosition() + Vec2D(0, e.getVelocity().getY() * 0.5f)));
				rTexture.draw(text);
			}
				
		}

	}


	rTexture.display(); //displays it onto the rtexture
	
	sprite.setTexture(rTexture.getTexture()); //sets the sprite texture to the rtexture
	sprite.setPosition(viewPixelPos);

//	inputRenderWindow.setView(view);
	inputRenderWindow.draw(sprite); //Draws the sprite onto the renderwindow
	inputRenderWindow.setView(inputRenderWindow.getDefaultView());
}
void DrawHandler::setViewPosition(const sf::Vector2f& inputViewPosition) //sets the view pos on the simulation plane
{
	//viewPos = inputViewPosition;
}
void DrawHandler::moveViewPosition(const sf::Vector2f& inputMoveAmount) //moves the view by the input amount
{
	view.move(inputMoveAmount);
}
void DrawHandler::setZoom(const sf::Vector2f& inputZoomFactor) //sets the zoomfactor with sf vec2f
{
	view.setViewport(sf::FloatRect(sf::Vector2f(viewPos.getX(), viewPos.getY()), inputZoomFactor));
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
void DrawHandler::setDrawID(const bool inputBool)
{
	drawID = inputBool;
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
void DrawHandler::test(sf::Vector2f& simPos, sf::Vector2f& simSize)
{
//	view.setCenter(toPixelCoords(simPos));
	view.setSize(sf::Vector2f(500, 500));
	view.zoom(2.f);
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
bool DrawHandler::getDrawID() const
{
	return drawID;
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
	return view;
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

	if(!font.loadFromFile("Fonts/arial.ttf"));
	{
		std::cout << "ERROR LOADING FONT IN ENTITYHANDLER INIT\n";
	}

	text.setFont(font);
	text.setCharacterSize(15);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(0.8f);
}


DrawHandler::DrawHandler()
	:
	maxX(0.0f),
	minX(0.0f),
	maxY(0.0f),
	minY(0.0f),
	view(),
	viewPos(),
	viewPixelPos(),
	viewPixelSize(),
	rTexture(),
	sprite(),
	font(),
	text(),
	squareGridSpacing(1.0f),

	drawActingForces(true),
	drawSquareGrid(true),
	drawVertexPoints(false),
	drawfilledVertexShapes(false),
	drawID(true),
	drawCenterOfMass(true),
	drawVelocityVector(true),
	drawFrictionSurface(false),
	drawAABBCollisionArea(true),
	drawEntityTexture(false),
	drawRotationAngleOfEntity(false),
	drawTrejectory(false)
{

}

