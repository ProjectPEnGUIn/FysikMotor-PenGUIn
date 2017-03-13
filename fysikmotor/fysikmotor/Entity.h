//can represent all avalibe entities in the basic physics engine
//entity object, stores all values for an entity, pos, speed, acting forces, mass, density etc

//handle entity logic/rendering outside of this object,

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
	void setForces(std::vector<Force>& inputForces); //sets all the acting forces on the current object using a vector of vec2d objects
	void setMass(float inputMass); //sets the mass in kg
	void setAngleRotationDEGREES(float inputRotationDEGREES); //sets the entity rotation in degrees
	void setAngleRotationRADIANS(float inputRotationRADIANS); //Sets the entity rotation in radians
	void setIsColliding(bool inputBool); //sets isColding
	void setRestitutionCoefficient(float inputDouble); //between 0 and 1
	void setDragCoefficient(float inputDouble);
	void setVertexShape(const VertexShape& inputShape);
	void addForce(const Force& inputForce); //adds it to acting forces vector
	void setEntityState(const int inputState); //0 for static non movable, 1 for movable
	void setEnttityID(const int inputIDNumber); //used to differentiate entiteis from one another
	void setPreviousVelocity(const Vec2D& inputPrevVel);
	void setPreviousPosition(const Vec2D inputPrevPos);
	void setPreviousRotation(const float inputPrevRot);
	void setPreviousAABBTL(const Vec2D& inputAABBTL);
	void setPreviousAABBBR(const Vec2D& inputAABBBR);
	void setResultingForce(const Vec2D& inputResultingForce);
	void setFrictionCoefficient(const float inputFrictionCoefficient);
	void setLostTime(const float inputLostTime);
	void setTrackEntityData(const bool inputBool);

	//get functions
	Vec2D getPosition() const; //gets the pos
	Vec2D getVelocity() const; //gets the vel, in meters per second
	std::vector<Force> getForces() const; //gets all the acting forces
	float getMass() const; //gets the mass in kg
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
	bool getTrackEntityData() const;

	//Constructor
	Entity();

private:
	//members

	int entityID; //the id of the entity, -1 if not set, used to identify entity
	int entityState; //what state it is in, -1 if not set

	//curent entity data:
	Vec2D velocity,
		resultingForce;
	    //position is stored in shape

	std::vector<Force> forces; //all acting forces on entity

	float mass;

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

	bool trackEntityData;
};
#endif // !_ENTITY_