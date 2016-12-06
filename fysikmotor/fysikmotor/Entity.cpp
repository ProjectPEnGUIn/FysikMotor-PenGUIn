#include "Entity.h"



// set functions
void Entity::setPosition(const Vec2D& inputPos) //Sets the pos using a PEVec2D object
{
	position = inputPos;
}
void Entity::setVelocity(const Vec2D& inputVel) //sets velocity using pevec2d object
{
	velocity = inputVel;
}
void Entity::setAcceleration(const Vec2D& inputAcc) //sets the velocity using pevec2d object
{
	acceleration = inputAcc;
}
void Entity::setActingForces(std::vector<Vec2D> inputActingForces) //sets all the acting forces on the current object using a vector of vec2d objects
{

}
void Entity::setMass(double inputMass) //sets the mass in kg
{
	mass = inputMass;
}
void Entity::setCenterOfMass(const Vec2D& inputCenterOfMass) //sets the center of mass
{
	centerOfMass = inputCenterOfMass;
}
void Entity::setWidth(double inputWidth) //Sets the width in meters
{
	width = inputWidth;
}
void Entity::setHeight(double inputHeight) //Sets the height in meters
{
	height = inputHeight;
}
void Entity::setRadius(double inputRadius) //Sets the radius in meters
{
	radius = inputRadius;
}
void Entity::setAngleRotationDEGREES(double inputRotationDEGREES) //sets the entity rotation in degrees
{
	rotationAngleDEGREES = inputRotationDEGREES;
}
void Entity::setAngleRotationRADIANS(double inputRotationRADIANS) //Sets the entity rotation in radians
{
	rotationAngleRADIANS = inputRotationRADIANS;
}
void Entity::setIsColliding(bool inputBool)
{
	isColliding = inputBool;
}
void Entity::setRestitutionCoefficient(double inputDouble) //between 0 and 1
{
	restitutionCoefficient = inputDouble;
}
void Entity::setAirDrag(double inputDouble)
{
	dragCoefficient = inputDouble;
}

//get functions
Vec2D Entity::getPosition() const //gets the pos
{
	return position;
}
Vec2D Entity::getVelocity() const //gets the vel, in meters per second
{
	return velocity;
}
Vec2D Entity::getAcceleration() const //gets the acc, in meters per second squared
{
	return acceleration;
}
std::vector<Vec2D> Entity::getActingForces() const //gets all the acting forces
{
	return actingForces;
}
double Entity::getMass() const//gets the mass in kg
{
	return mass;
}
Vec2D  Entity::getCenterOfmass() const //returns the Center of mass
{
	return centerOfMass;
}
double Entity::getWidth() const //gets the width in meters
{
	return width;
}
double Entity::getHeight() const //gets the height in meters
{
	return height;
}
double Entity::getRadius() const //gets the radius in meters
{
	return radius;
}
double Entity::getAngleRotationDEGREES() const //gets the rotation of entity in degrees
{
	return rotationAngleDEGREES;
}
double Entity::getAngleRotationRADIANS() const //gets the rotation of entity in radians
{
	return rotationAngleRADIANS;
}
bool Entity::getIsColliding() const
{
	return isColliding;
}
double Entity::getRestitutionCoefficient() const
{
	return restitutionCoefficient;
}
double Entity::getAirDrag() const
{
	return dragCoefficient;
}

//update functions
void Entity::updateALL(sf::Time inputDeltaTime, const Vec2D& inputResultingForce) //updates all of the entity properties, speed, acc, forces
{

}
void Entity::updateAcceleration(const Vec2D& inputResultingForce) //updates acceleration
{
	//using F = ma, a = F/m
}
void Entity::updateVelocity() //updates speed
{
	velocity += acceleration;
}
void Entity::updatePosition()
{
	//adds velocity to position
	position += velocity;
}

//Constructor
Entity::Entity()
	:
	entityID(-1),
	entityShape(-1),
	entityState(-1),
	position(),
	velocity(),
	acceleration(),
	mass(-1),
	centerOfMass(),
	width(-1),
	height(-1),
	radius(-1),
	rotationAngleDEGREES(0),
	rotationAngleRADIANS(0),
	isColliding(false)
{


}
