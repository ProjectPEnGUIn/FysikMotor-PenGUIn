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
#include "Force.h"

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
	void setForces(std::vector<Force>& inputForces); //sets all the acting forces on the current object using a vector of vec2d objects
	void setMass(float inputMass); //sets the mass in kg
	void setCenterOfMass(const Vec2D& inputCenterOfMass); //sets the center of mass
	void setAngleRotationDEGREES(float inputRotationDEGREES); //sets the entity rotation in degrees
	void setAngleRotationRADIANS(float inputRotationRADIANS); //Sets the entity rotation in radians
	void setIsColliding(bool inputBool); //sets isColding
	void setRestitutionCoefficient(float inputDouble); //between 0 and 1
	void setDragCoefficient(float inputDouble);
	void setVertexShape(const VertexShape& inputShape);
	void addForce(const Force& inputForce); //adds it to acting forces vector
	void setEntityState(const int inputState); //0 for static non movable, 0 for movable
	void setEnttityID(const int inputIDNumber);
	void setPreviousVelocity(const Vec2D& inputPrevVel);
	void setPreviousPosition(const Vec2D inputPrevPos);
	void setPreviousRotation(const float inputPrevRot);
	void setPreviousAABBTL(const Vec2D& inputAABBTL);
	void setPreviousAABBBR(const Vec2D& inputAABBBR);
	void setResultingForce(const Vec2D& inputResultingForce);
	void setFrictionCoefficient(const float inputFrictionCoefficient);
	void setLostTime(const float inputLostTime);

	//get functions
	Vec2D getPosition() const; //gets the pos
	Vec2D getVelocity() const; //gets the vel, in meters per second
	Vec2D getAcceleration() const; //gets the acc, in meters per second squared
	std::vector<Force> getForces() const; //gets all the acting forces
	float getMass() const; //gets the mass in kg
	Vec2D  getCenterOfmassOffset() const; //returns the Center of mass
	float getAngleRotationDEGREES() const; //gets the rotation of entity in degrees
	float getAngleRotationRADIANS() const; //gets the rotation of entity in radians
	bool getIsColliding() const;
	float getRestitutionCoefficient() const;
	float getDragCoefficient() const;
	Vec2D getAABBTopLeft() const; //returns aabb shape top left coords
	Vec2D getAABBMBottomRight() const; //returns shape aabb bottom left coords
	int getEntityID() const; //returns entity id, is an int
	int getEntityState() const;
	VertexShape getVertexShape() const;
	Vec2D getPreviousVelocity() const;
	Vec2D getPreviousPosition() const;
	float getPreviousRotation() const;
	Vec2D getPreviousAABBTL() const;
	Vec2D getPreviousAABBBR() const;
	Vec2D getResultingForce() const;
	float getFrictionCoefficient() const;
	float getLostTime() const;

	//update functions
	void updateALL(sf::Time inputDeltaTime, const Vec2D& inputResultingForce); //updates all of the entity properties, speed, acc, forces


	//void move(const Vec2D& inputMoveAmount);

	//Constructor
	Entity();

	//other
	//Entity& operator=(const Entity& inputEntity) = default; //own copy assignment operator made? due to getting error C2280, //http://en.cppreference.com/w/cpp/language/rule_of_three#Rule_of_five, //WAS ERROR WITH SHAPE COPYTHING, NOT INITING VARIABLES IN CONSTR

private:
	//members

	int entityID; //the id of the entity, -1 if not set
	int entityState; //what state it is in, -1 if not set

	//curent entity data:
	Vec2D velocity,
		acceleration,
		resultingForce;
	    //position is stored in vertexshape

	std::vector<Force> forces; //all acting forces on entity

	float mass;
	Vec2D centerOfMassOffset;

	//coefficients for entity
	float frictionCoefficient,
		restitutionCoefficient,
		dragCoefficient;

	VertexShape shape; //entity shape

	//prev tick entity data:
	Vec2D prevPos,
		prevVel,
		prevAABBTL, 
		prevAABBBR;
	float prevRot;

	float lostTime; 
	bool isColliding;
};
#endif // !_ENTITY_