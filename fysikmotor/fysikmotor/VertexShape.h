//entity shape defined by vertices, define shapes using vertex points
//setup a basic AABB to get approxiamty boundig box coords, easy comparison with other entiteis


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

#include "PEVec2D.h"

class VertexShape
{
private:

public:
	//functions

	//set
	void setPos(const Vec2D& inputPos); //sets the pos for shape origin point
	void movePos(const Vec2D& inputMoveAmount); //increments the pos by how much u input

	//get
	Vec2D getMinAABBPoint() const; //returns the min aabb point
	Vec2D getMaxAABBPoint() const; //returns the max aabb point

	//updating
	void updateAABBBox(); //updates the aabb bounding box
	void updateRotationOnVertices(); //updates the vertices points

	//constructor
	VertexShape();
	
private:
	//members

	Vec2D originPosition; //the pos on which speed gets added onto
	std::vector<Vec2D> vertices; //vertices that define the shape, each vertex point gets added to the originpos to make the defining vertexpoint
	sf::Transform rotation; //rotation of

	Vec2D rotationCenterX, //the center of which the shape rotates around in x and y
		  rotationCenterY;

	Vec2D aabbMin, aabbMax; //the aabb boundingbox min and max coords, easy collison checks


};
#endif // ! _VERTEXSHAPE_