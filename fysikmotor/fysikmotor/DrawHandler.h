
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
#include <math.h> //for making arrowshape
#include <cmath> //for making arrowshape

#include "EntityHandler.h"
#include "AABBCheck.h"

#pragma once
class DrawHandler
{
private:
	//functions
	bool isEntityWithinView(const Entity& inputEntity) const;
	sf::VertexArray makeIntoVertexArray(const VertexShape& inputVertexShape) const; //turns an own made vertexshapape object into a vertexarray object
	void keepViewWithinBorders() const; //keeps the view within the max and min world size
	sf::Vector2f translateWorldCoordinateIntoImageCoordinate(const sf::Vector2f& inputWorldCoordinate) const;
	sf::Vector2f translateWorldCoordinateIntoImageCoordinate(const Vec2D& inputWorldCoordinate) const;
	sf::Vector2f translateScreenCoordinateIntoWorldCoordinate(const sf::View& inputview);
	sf::VertexArray makeArrowShape(const float startX, const float startY, const float inputLength, const float sizeFactor, const float inputRotationDEGREES, const sf::Color inputColour); //arrow scales to the input length


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
	void setDrawAxis(const bool inputBool);
	void setDrawActingForces(const bool inputBool);
	void setDrawSquareGrid(const bool inputBool);
	void setDrawVertexPoints(const bool inputBool);
	void setDrawFilledVertexShape(const bool inputBool);
	void setDrawVertexIDs(const bool inputBool);
	void setDrawCenterOfMass(const bool inputBool);
	void setDrawVelocityVector(const bool inputBool);
	void setDrawFrictionSurface(const bool inputBool);
	void setDrawAABBCollisionArea(const bool inputBool);
	void setDrawEntityTexture(const bool inputBool);
	void setDrawRotationAngle(const bool inputBool);
	void setSimulationBounds(const float inputMaxX, const float inputMinX, const float inputMaxY, const float inputMinY);
	void setViewPixelPos(const sf::Vector2f& inputViewPixelPos);
	void setViewSimulationPos(const Vec2D& inputSimulationPos);

	//get functions
	bool getDrawAxis() const;
	bool getDrawActingForces() const;
	bool getDrawSquareGrid() const;
	bool getDrawVertexPoints() const;
	bool getDrawFilledVertexShape() const;
	bool getDrawVertexIDs() const;
	bool getDrawCenterOfMass() const;
	bool getDrawVelocityVector() const;
	bool getDrawFrictionSurface() const;
	bool getDrawAABBCollisionArea() const;
	bool getDrawEntityTexture() const;
	bool getDrawRotationAngle()const;
	sf::View getView() const;

	DrawHandler();
	
private:
	//members

	//world size
	float maxX,
		minX,
		maxY,
		minY;
	
	sf::View simulationView; //its pos is in its center
	Vec2D viewPos; //top right corner in the plane
	Vec2D viewSize; //width, height in meters on the cortesian plane thingy

	sf::Vector2f viewPixelPos;
	sf::Vector2f viewPixelSize; //widt and height in pixels onscreen

	sf::RenderTexture rTexture; //the texture entities will be drawn onto
	sf::Sprite sprite; //the sprite that will be drawn onto the sf renderwindow

	//bools regarding the rendering
	bool drawAxis,
		drawActingForces,
		drawSquareGrid,
		drawVertexPoints,
		drawfilledVertexShapes,
		drawVertexIDs,
		drawCenterOfMass,
		drawVelocityVector,
		drawFrictionSurface,
		drawAABBCollisionArea,
		drawEntityTexture,
		drawRotationAngleOfEntity;

};
#endif // !_DRAWHANDLER_
