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
#include "VertexShape.h" //define entity shapes using vertices

class Entity
{
public:
	//enums

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
	void setMass(float inputMass); //sets the mass in kg
	void setCenterOfMass(const Vec2D& inputCenterOfMass); //sets the center of mass
	void setAngleRotationDEGREES(float inputRotationDEGREES); //sets the entity rotation in degrees
	void setAngleRotationRADIANS(float inputRotationRADIANS); //Sets the entity rotation in radians
	void setIsColliding(bool inputBool); //sets isColding
	void setRestitutionCoefficient(float inputDouble); //between 0 and 1
	void setAirDrag(float inputDouble);

	//get functions
	Vec2D getPosition() const; //gets the pos
	Vec2D getVelocity() const; //gets the vel, in meters per second
	Vec2D getAcceleration() const; //gets the acc, in meters per second squared
	std::vector<Vec2D> getActingForces() const; //gets all the acting forces
	float getMass() const; //gets the mass in kg
	Vec2D  getCenterOfmassOffset() const; //returns the Center of mass
	float getAngleRotationDEGREES() const; //gets the rotation of entity in degrees
	float getAngleRotationRADIANS() const; //gets the rotation of entity in radians
	bool getIsColliding() const;
	float getRestitutionCoefficient() const;
	float getAirDrag() const;
	Vec2D getAABBTopLeft() const; //returns aabb shape top left coords
	Vec2D getAABBMBottomRight() const; //returns shape aabb bottom left coords
	int getEntityID() const; //returns entity id, is an int
	int getEntityState() const;
	VertexShape getVertexShape() const;

	//update functions
	void updateALL(sf::Time inputDeltaTime, const Vec2D& inputResultingForce); //updates all of the entity properties, speed, acc, forces
	void updateAcceleration(const Vec2D& inputResultingForce); //updates acceleration
	void updateVelocity(); //updates speed
	void updatePosition();

	//Constructor
	Entity();

	//other
	//Entity& operator=(const Entity& inputEntity) = default; //own copy assignment operator made? due to getting error C2280, //http://en.cppreference.com/w/cpp/language/rule_of_three#Rule_of_five, //WAS ERROR WITH SHAPE COPYTHING, NOT INITING VARIABLES IN CONSTR

private:
	//members

	int entityID; //the id of the entity, -1 if not set
	int entityState; //what state it is in, -1 if not set

	Vec2D position; //pos of entity, is in the center
	Vec2D velocity; //velocity of entity, has a magnitude and direction, in meters per second
	Vec2D acceleration; //acceleration, in meters per seconds squared
	std::vector<Vec2D> actingForces; //all of the acting forces on the entity at this moment, in Newtons

	float mass; //mass of entity in kg, -1 if not set
	Vec2D centerOfMassOffset; //pos of center of mass, is in the center of entity by default

	VertexShape shape; //the shape of entity, define it with verticies, has rotation, centerpos / pos in middle

	bool isColliding; //can change the outline to show that it is colliding

	float restitutionCoefficient; //is between 0 and 1, affects how collisions occur and the result
	float dragCoefficient; //air drag of the body

};
#endif // !_ENTITY_