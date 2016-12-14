//entity shape defined by vertices, define shapes using vertex points
//setup a basic AABB to get approxiamty boundig box coords, easy comparison with other entiteis

//there needs to be atleast 3 vertices added for there to be a shape, else it is just a point or line

//Erik Magnusson

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

#include "PEVec2D.h"

const double PI = 3.14159265;

class VertexShape
{
public:
	//functions

	//set
	void setPosition(const Vec2D& inputPos); //sets the centerpos and all vertices
	void movePosition(const Vec2D& inputMoveAmount); //increments all posistions
	void setRotationOffset(const Vec2D& inputRotationOffset); //rotationpoiint is offset by this amound from centerpos
	void incrementRotationDEGREES(double inputRotationIncrementDEGREES); //adds to tyhe current rotation of shape
	void incrementRotationRADIANS(double inputRotationIncrementRADIANS);
	void setRotationDEGREES(double inputRotationDEGREES);
	void setRotationRADIANS(double inputRotationRADIANS);

	void addVertexPoint(const Vec2D& inputWorldCoordinate); //adds a vertex for the shape at the input world coo´rdinate, appends it to vertex vector
	void removeVertex(int inputVertexIndex); //removes the vertex at the given index, starts at 0
	void clearVertices(); //erases all vertex points

	//get
	Vec2D getCenterPos() const;
	double getCurrentRotationDEGREES() const;
	double getCurrentRotationRADIANS() const;
	int getAmountOfVertices() const; 
	std::vector<Vec2D> getVertices() const; //returnsa all vertices
	Vec2D getTopLeftAABBCorner() const;
	Vec2D getBottomRightAABBCorner() const;

	//updating
	void updateAABBBox(); //updates the aabb bounding box
	void updateRotationOnVertices(); //updates the vertices points
	void updateCenterPos(); //updates the centerpos location of the vertices shape

	//constructor
	VertexShape();
	
private:
	//members

	Vec2D trueCenterPosition; //the real center of vertices shape
	Vec2D rotationCenter; //the center of which shape rotates around
	double rotationAmountDEGREES,
		   rotationAmountRADIANS;
	std::vector<Vec2D> vertices; //vertices that define the shape, each vertex point x and y ´point
	sf::Transform rotation; //rotation of shape
	Vec2D aabbMin, aabbMax; //the aabb boundingbox min and max coords, easy collison checks


};
#endif // ! _VERTEXSHAPE_