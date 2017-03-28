/*
Physics Eng
-only intendeine Simulation Draw
d for PEnGUIn physics simulation as for now, will need rework if be able to use PEnGUIn just like box2D or something

draws everything in physics simulation
translates simulation world coordinates into pixel coordinates

-view feature, ability to view only a portion of sim world at a time -move/zoom window feature

-draw world lines/boxes. ex 1m x 1m

-set a background image/colour for the heck of it

-takes in a vector of entities, makes them into sfml vertexarrays and draws them to the image >>IF<< they are wthin viewwindow range,

-image size
-returns a sfml image thing that can be drawn anywhere on the program window

Erik Magnusson 23/12 2016

//http://www.sfml-dev.org/documentation/2.4.1/classsf_1_1RenderTexture.php 1/1 2017

-use sfml view for the "window" that will move around?? rather than creating basicly the same thing from scratch
//http://www.sfml-dev.org/tutorials/2.4/graphics-view.php

*/

#ifndef _DRAWHANDLER_
#define _DRAWHANDLER_

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include <vector>
#include <math.h>
#include <cmath> 
#include <string>

#include "Entity.h"
#include "AABBCheck.h"

#pragma once
class DrawHandler
{
private:
	//functions
	bool isEntityWithinView(const Entity& inputEntity) const;
	sf::ConvexShape makeIntoConvexShape(const VertexShape& inputVertexShape) const; //turns an own made vertexshapape object into a vertexarray object
	void keepViewWithinBorders() const; //keeps the view within the max and min world size
	sf::ConvexShape makeArrowShape(const float inputStartX, const float inputStartY, const Vec2D& inputVector, const sf::Color inputColour, const float inputScale); //arrow scales to the input lengt
	sf::Vector2f toPixelCoords(const Vec2D& inputWorldCoordinates) const;
	sf::Vector2f toPixelCoords(const sf::Vector2f& inputWorldCoordinates) const;

	void updateView() const;

public:
	//functions

	//main functions for draw handler
	void draw(sf::RenderWindow& inputRenderWindow, const std::vector<Entity>& inputEntities); //draws everytyhing to the screen
	void setViewPosition(const sf::Vector2f& inputViewPosition); //sets the view pos on the simulation plane
	void moveViewPosition(const sf::Vector2f& inputMoveAmount); //moves the view by the input amount
	void setZoom(const sf::Vector2f& inputZoomFactor); //sets the zoomfactor with sf vec2f
	//void showEntireSimulation() const; //changes variables to show entire sim window at once, easy preset thingy

	//set functions
	void setDrawActingForces(const bool inputBool);
	void setDrawSquareGrid(const bool inputBool);
	void setDrawFilledVertexShape(const bool inputBool);
	void setDrawID(const bool inputBool);
	void setDrawCenterOfMass(const bool inputBool);
	void setDrawVelocityVector(const bool inputBool);
	void setDrawAABBCollisionArea(const bool inputBool);
	void setDrawEntityTexture(const bool inputBool);
	void setDrawRotationAngle(const bool inputBool);
	void setDrawTrejectory(const bool inputBool);
	void setSquareGridSpacing(const float inputSpacing);

	void setSimulationBounds(const float inputMaxX, const float inputMinX, const float inputMaxY, const float inputMinY);
	void setViewPixelPos(const sf::Vector2f& inputViewPixelPos);
	void setViewSimulationPos(const Vec2D& inputSimulationPos);
	void test(sf::Vector2f& simPos, sf::Vector2f& simSize);


	//get functions
	bool getDrawActingForces() const;
	bool getDrawSquareGrid() const;
	bool getDrawFilledVertexShape() const;
	bool getDrawID() const;
	bool getDrawCenterOfMass() const;
	bool getDrawVelocityVector() const;
	bool getDrawAABBCollisionArea() const;
	bool getDrawEntityTexture() const;
	bool getDrawRotationAngle()const;
	bool getDrawTrejectory() const;
	sf::View getView() const;
	float getSquareGridSpacing() const;

	void init(const float inputSimulationWidth, const float inputSimulationHeight, const float imageWidth, const float imageHeight);
	DrawHandler();
	
private:
	//members

	//world size
	float maxX,
		minX,
		maxY,
		minY;
	
	sf::View view; //its pos is in its center
	Vec2D viewPos; //top right corner in the plane

	sf::Vector2f viewPixelPos;
	sf::Vector2f viewPixelSize; //widt and height in pixels onscreen

	sf::RenderTexture rTexture; //the texture entities will be drawn onto
	sf::Sprite sprite; //the sprite that will be drawn onto the sf renderwindow
	sf::Font font;
	sf::Text text;

	float squareGridSpacing; //in meters

	//bools regarding the rendering
	bool drawActingForces,
		drawSquareGrid,
		drawfilledVertexShapes,
		drawID,
		drawCenterOfMass,
		drawVelocityVector,
		drawAABBCollisionArea,
		drawEntityTexture,
		drawRotationAngleOfEntity,
		drawTrejectory;

};
#endif // !_DRAWHANDLER_