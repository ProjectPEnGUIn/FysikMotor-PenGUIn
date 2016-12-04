//can represent all avalibe entities in the basic physics engine
//entity object, stores all values for an entity, pos, speed, acting forces, mass, density etc
//represents an object within the corteasian plane/ world we will make, get the coords from the plane/world and render it to a "miniwindow" at the PROPER location
//only use defined shapes for now, no vertex shapes, only rectangle and circles in this version

//update entity using timestep, delta time. 
//handle collisions outside of this object

//everything is in metric units

//Erik Magnusson 4/12 - 2016

#pragma once
#ifndef _ENTITY_
#define _ENTITY

#include <vector>
#include <iostream>
#include <string>

#include "PEVec2D.h" //2d vector, x and y componten, has overloading operators to 

class Entity
{
public:
	//enums

	enum ENTITYSHAPE
	{
		RECTANGLE, //rectangleshape, has a width and a height
		CIRCLE     //circleshape, has a radius
	};
	enum ENTITYSTATE
	{
		STATIC, //Static entity, cant be moved, not affected by forces, still affects other entites, example usage; ground?
		MOVABLE //movable entity, is movable, affected by forces etc

	};
private:
	//functions
public:
	//functions

	//set functions
	void setPosition(const Vec2D& inputPos); //Sets the pos using a PEVec2D object
	void setVelocity(const Vec2D& inputVel); //sets velocity using pevec2d object
	void setAcceleration(const Vec2D& inputAcc); //sets the velocity using pevec2d object
	void setActingForces(std::vector<Vec2D> inputActingForces); //sets all the acting forces on the current object using a vector of vec2d objects
	void setMass(double inputMass); //sets the mass in kg
	void setWidth(double inputWidth); //Sets the width in meters
	void setHeight(double inputHeight); //Sets the height in meters
	void setRadius(double inputRadius); //Sets the radius in meters
	void setAngleRotationDEGREES(double inputRotationDEGREES); //sets the entity rotation in degrees
	void setAngleRotationRADIANS(double inputRotationRADIANS); //Sets the entity rotation in radians
	void setIsColiding(bool inputBool); //sets isColding
	void setColidingCenterPos(const Vec2D& inputColidingCenterPos); //sets the overlapping centerposition of where it is colding

	//get functions
	Vec2D getPosition(); //gets the pos
	Vec2D getVelocity(); //gets the vel, in meters per second
	Vec2D getAcceleration(); //gets the acc, in meters per second squared
	std::vector<Vec2D> getActingForces(); //gets all the acting forces
	double getMass(); //gets the mass in kg
	double getWidth(); //gets the width in meters
	double getHeight(); //gets the height in meters
	double getRadius(); //gets the radius in meters
	double getAngleRotationDEGREES(); //gets the rotation of entity in degrees
	double getAngleRotationRADIANS(); //gets the rotation of entity in radians
	bool   getIsColiding();
	Vec2D  getColidingCenterPos();

	//Constructor
	Entity();

private:
	//members

	int entityID; //the id of the entity, -1 if not set
	int entityShape; //what shape it is, -1 if not set
	int entityState; //what state it is in, -1 if not set

	Vec2D position; //pos of entity, is always in the top left
	Vec2D velocity; //velocity of entity, has a magnitude and direction, in meters per second
	Vec2D acceleration; //acceleration, in meters per seconds squared
	std::vector<Vec2D> actingForces; //all of the acting forces on the entity at this moment, in Newtons

	double mass; //mass of entity in kg

	double width; //if rectangle, in meters
	double height; //if rectangle, in meters
	double radius; //if circle, in meters

	double rotationAngleDEGREES; //how much object is rotated in degrees
	double rotationAngleRADIANS; //how much object is rotated in radians

	bool isColiding; //is true if entity is coliding with another entity
	Vec2D colidingCenterPos; //the centerpos of the coliding area, two objects should share the same colidingpos if they are coliding, is -999999 if not true ( no one would make a "world" the size of 100km * 100km, program would surely crash before that
	
};
#endif // !_ENTITY_

