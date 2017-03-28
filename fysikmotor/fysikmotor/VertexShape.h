//entity shape defined by vertices, define shapes using vertex points
//Defined in clockwise order

//there needs to be atleast 3 vertices added for there to be a shape, else it is just a point or line

//Erik Magnusson

//15ish december 2016
//http://www.sfml-dev.org/documentation/2.4.1/classsf_1_1VertexArray.php
//http://stackoverflow.com/questions/524755/finding-center-of-2d-triangle
//http://stackoverflow.com/questions/28869441/how-to-rotate-points-about-a-specific-origin
//https://www.mathsisfun.com/geometry/vertices-faces-edges.html

#pragma once
#ifndef _VERTEXSHAPE_
#define _VERTEXSHAPE_

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath> //fabs, fmod
#include <math.h> //fabs, fmod

#include "PEVec2D.h"

class VertexShape
{
private:
	//functions

	//updating
	void updateAABBBox(); //updates the aabb bounding box, AABBTL, AABBR,
	void updateRotationOnVertices(); //updates the vertices points
	void updateCenterPos(); //updates the centerpos of shape

public:
	//functions

	//set
	void setPosition(const Vec2D& inputPos); //sets the centerpos and all vertices, global coords
	void movePosition(const Vec2D& inputMoveAmount); //increments current position
	void incrementRotationDEGREES(float inputRotationIncrementDEGREES); //adds to tyhe current rotation of shape
	void incrementRotationRADIANS(float inputRotationIncrementRADIANS);
	void setRotationDEGREES(float inputRotationDEGREES);
	void setRotationRADIANS(float inputRotationRADIANS);

	void addVertexPoint(const Vec2D& inputWorldCoordinate); //CLOCKWISE DIRECTION, adds a vertex for the shape at the input world coo´rdinate, appends it to vertex vector
	void removeVertex(int inputVertexIndex); //removes the vertex at the given index, starts at 0
	void clearVertices(); //erases all vertex points

	//get
	Vec2D getCenterPos() const; //returns centerpos of shape
	float getCurrentRotationDEGREES() const; //returns current rotation in degrees
	float getCurrentRotationRADIANS() const; //returns current rottation in radians
	int getAmountOfVertices() const; //returns number of vertices as an int
	std::vector<Vec2D> getVertices() const; //returns all vertices in a std::vector<>
	Vec2D getTopLeftAABBCorner() const; //return top left corner in world coordinates
	Vec2D getBottomRightAABBCorner() const; //returns bottom right corner in  world coordinates
	sf::Transform getCurrentTransformation() const;

	//constructor
	VertexShape();

	//own made copy assingment operator
    VertexShape& operator=(const VertexShape& inputVertexShape); 
	
public:
	//members
	
private:

	//members
	Vec2D centerPosition; //the real center of vertices shape
	float rotationOffsetDEGREES, //rotation offset from 0
		   rotationOffsetRADIANS;
	std::vector<Vec2D> vertices; //vertices that define the shape, each vertex point x and y ´point
	sf::Transform rotation; //sf::rotation used for rotation of shape
	Vec2D aabbTL, aabbBR; //the aabb boundingbox min and max coords, easy collison checks

	const float PI;
};
#endif // ! _VERTEXSHAPE_