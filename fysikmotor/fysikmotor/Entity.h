//can represent all avalibe entities in the basic physics engine
//entity object, stores all values for an entity, pos, speed, acting forces, mass, density etc
//represents an object within the corteasian plane/ world we will make, get the coords from the plane/world and render it to a "miniwindow" at the PROPER location
//only use defined shapes for now, no vertex shapes, only rectangle and circles in this version

//update entity using timestep, delta time. 
//handle collisions outside of this object,

//everything is in metric units

//Erik Magnusson 4/12 - 2016

//https://en.wikipedia.org/wiki/Coefficient_of_restitution very relevant

#pragma once
#ifndef _ENTITY_
#define _ENTITY

#include <SFML\System.hpp>

#include <vector>
#include <iostream>
#include <string>

#include "PEVec2D.h" //2d vector, x and y componten, has overloading operators to it

class Entity
{
public:
	//enums

	enum class Shape
	{
		RECTANGLE, //rectangleshape, has a width and a height
		CIRCLE     //circleshape, has a radius
	};
	enum class State
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
	void setCenterOfMass(const Vec2D& inputCenterOfMass); //sets the center of mass
	void setWidth(double inputWidth); //Sets the width in meters
	void setHeight(double inputHeight); //Sets the height in meters
	void setRadius(double inputRadius); //Sets the radius in meters
	void setAngleRotationDEGREES(double inputRotationDEGREES); //sets the entity rotation in degrees
	void setAngleRotationRADIANS(double inputRotationRADIANS); //Sets the entity rotation in radians
	void setIsColliding(bool inputBool); //sets isColding
	void setRestitutionCoefficient(double inputDouble); //between 0 and 1
	void setAirDrag(double inputDouble);

	//get functions
	Vec2D getPosition() const; //gets the pos
	Vec2D getVelocity() const; //gets the vel, in meters per second
	Vec2D getAcceleration() const; //gets the acc, in meters per second squared
	std::vector<Vec2D> getActingForces() const; //gets all the acting forces
	double getMass() const; //gets the mass in kg
	Vec2D  getCenterOfmass() const; //returns the Center of mass
	double getWidth() const; //gets the width in meters
	double getHeight() const; //gets the height in meters
	double getRadius() const; //gets the radius in meters
	double getAngleRotationDEGREES() const; //gets the rotation of entity in degrees
	double getAngleRotationRADIANS() const; //gets the rotation of entity in radians
	bool getIsColliding() const;
	double getRestitutionCoefficient() const;
	double getAirDrag() const;

	//update functions
	void updateALL(sf::Time inputDeltaTime, const Vec2D& inputResultingForce); //updates all of the entity properties, speed, acc, forces
	void updateAcceleration(const Vec2D& inputResultingForce); //updates acceleration
	void updateVelocity(); //updates speed
	void updatePosition();

	//Constructor
	Entity();

private:
	//members

	int entityID; //the id of the entity, -1 if not set
	int entityShape; //what shape it is, -1 if not set
	int entityState; //what state it is in, -1 if not set

	Vec2D position; //pos of entity, is in the center
	Vec2D velocity; //velocity of entity, has a magnitude and direction, in meters per second
	Vec2D acceleration; //acceleration, in meters per seconds squared
	std::vector<Vec2D> actingForces; //all of the acting forces on the entity at this moment, in Newtons

	double mass; //mass of entity in kg, -1 if not set
	Vec2D centerOfMass; //pos of center of mass, is in the center of entity by default

	double width; //if rectangle, in meters
	double height; //if rectangle, in meters
	double radius; //if circle, in meters

	double rotationAngleDEGREES; //how much object is rotated in degrees
	double rotationAngleRADIANS; //how much object is rotated in radians

	bool isColliding; //can change the outline to show that it is colliding

	double restitutionCoefficient; //is between 0 and 1, affects how collisions occur and the result
	double dragCoefficient; //air drag of the body

};
#endif // !_ENTITY_