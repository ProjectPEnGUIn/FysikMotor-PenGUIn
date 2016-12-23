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
void Entity::setMass(float inputMass) //sets the mass in kg
{
	mass = inputMass;
}
void Entity::setCenterOfMass(const Vec2D& inputCenterOfMass) //sets the center of mass
{
	shape.setRotationCenterOffset(inputCenterOfMass);
}
void Entity::setAngleRotationDEGREES(float inputRotationDEGREES) //sets the entity rotation in degrees
{
	shape.setRotationDEGREES(inputRotationDEGREES);
}
void Entity::setAngleRotationRADIANS(float inputRotationRADIANS) //Sets the entity rotation in radians
{
	shape.setRotationRADIANS(inputRotationRADIANS);
}
void Entity::setIsColliding(bool inputBool)
{
	isColliding = inputBool;
}
void Entity::setRestitutionCoefficient(float inputDouble) //between 0 and 1
{
	restitutionCoefficient = inputDouble;
}
void Entity::setAirDrag(float inputDouble)
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
float Entity::getMass() const//gets the mass in kg
{
	return mass;
}
Vec2D  Entity::getCenterOfmassOffset() const //returns the Center of mass
{
	return shape.getRotationCenterOffset();
}
float Entity::getAngleRotationDEGREES() const //gets the rotation of entity in degrees
{
	return shape.getCurrentRotationDEGREES();
}
float Entity::getAngleRotationRADIANS() const //gets the rotation of entity in radians
{
	return shape.getCurrentRotationRADIANS();
}
bool Entity::getIsColliding() const
{
	return isColliding;
}
float Entity::getRestitutionCoefficient() const
{
	return restitutionCoefficient;
}
float Entity::getAirDrag() const
{
	return dragCoefficient;
}
Vec2D Entity::getAABBTopLeft() const
{
	return shape.getTopLeftAABBCorner();
}
Vec2D Entity::getAABBMBottomRight() const
{
	return shape.getBottomRightAABBCorner();
}
int Entity::getEntityID() const //returns entity id, is an int
{
	return entityID;
}
int Entity::getEntityState() const
{
	return entityState;
}
VertexShape Entity::getVertexShape() const
{
	return shape;
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
	entityState(-1),

	position(),
	velocity(),
	acceleration(),
	actingForces(),

	mass(-1),
	centerOfMassOffset(),

	shape(),

	isColliding(false),

	restitutionCoefficient(0),
	dragCoefficient(0)
	
{


}



//Entity& Entity::operator=(const Entity& inputEntity)
//{
//	if (this != &inputEntity)
//	{
//		entityID = inputEntity.getEntityID();
//		entityState = inputEntity.getEntityState();
//		position = inputEntity.getPosition();
//		velocity = inputEntity.getPosition();
//		acceleration = inputEntity.getAcceleration();
//		actingForces = inputEntity.getActingForces();
//		mass = inputEntity.getMass();
//		centerOfMassOffset = inputEntity.getCenterOfmassOffset();
//		shape = inputEntity.getVertexShape();
//		isColliding = inputEntity.getIsColliding();
//		restitutionCoefficient = inputEntity.getRestitutionCoefficient();
//		dragCoefficient = inputEntity.getAirDrag();
//	}
//
//	return *this;
//}