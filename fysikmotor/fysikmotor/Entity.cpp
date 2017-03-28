#include "Entity.h"



// set functions
void Entity::setPosition(const Vec2D& inputPos) //Sets the pos using a PEVec2D object
{
	if (entityState == 0)
	{

		//prevAABBBR = shape.getBottomRightAABBCorner();
		//prevAABBTL = shape.getTopLeftAABBCorner();
		prevPos = inputPos;
	}
	else
	{
		//prevAABBBR = shape.getBottomRightAABBCorner();
		//prevAABBTL = shape.getTopLeftAABBCorner();
		prevPos = shape.getCenterPos();
	}
	
	shape.setPosition(inputPos);
}
void Entity::setVelocity(const Vec2D& inputVel) //sets velocity using pevec2d object
{
	velocity = inputVel;
}
void Entity::setForces(std::vector<Force>& inputForces) //sets all the acting forces on the current object using a vector of vec2d objects
{
	forces = inputForces;
}
void Entity::setMass(float inputMass) //sets the mass in kg
{
	mass = inputMass;
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
void Entity::setDragCoefficient(float inputDouble)
{
	dragCoefficient = inputDouble;
}
void Entity::setVertexShape(const VertexShape& inputShape)
{
	shape = inputShape;
}
void Entity::addForce(const Force& inputForce) //adds it to acting forces vector
{
	forces.push_back(inputForce);

}
void Entity::setEntityState(const int inputState) //0 for static non movable, 0 for movable
{
	entityState = inputState;
}
void Entity::setEnttityID(const int inputIDNumber)
{
	entityID = inputIDNumber;
}
void Entity::setPreviousVelocity(const Vec2D& inputPrevVel)
{
	prevVel = inputPrevVel;
}
void Entity::setPreviousPosition(const Vec2D inputPrevPos)
{
	prevPos = inputPrevPos;
}
void Entity::setPreviousRotation(const float inputPrevRot)
{
	prevRot = inputPrevRot;
}
void Entity::setPreviousAABBTL(const Vec2D& inputAABBTL)
{
	prevAABBTL = inputAABBTL;
}
void Entity::setPreviousAABBBR(const Vec2D& inputAABBBR)
{
	prevAABBBR = inputAABBBR;
}
void Entity::setResultingForce(const Vec2D& inputResultingForce)
{
	resultingForce = inputResultingForce;
}
void Entity::setFrictionCoefficient(const float inputFrictionCoefficient)
{
	frictionCoefficient = inputFrictionCoefficient;
}
void Entity::setLostTime(const float inputTime)
{
	lostTime = inputTime;
}
void Entity::setTrackEntityData(const bool inputBool)
{
	trackEntityData = inputBool;
}
void Entity::setSillhueteArea(const float inputSillhueteArea)
{
	sillhuetteArea = inputSillhueteArea;
}

//get functions
Vec2D Entity::getPosition() const //gets the pos
{
	return shape.getCenterPos();
}
Vec2D Entity::getVelocity() const //gets the vel, in meters per second
{
	return velocity;
}
std::vector<Force> Entity::getForces() const //gets all the acting forces
{
	return forces;
}
float Entity::getMass() const//gets the mass in kg
{
	return mass;
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
float Entity::getDragCoefficient() const
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
Vec2D Entity::getPreviousVelocity() const
{
	return prevVel;
}
Vec2D Entity::getPreviousPosition() const
{
	return prevPos;
}
float Entity::getPreviousRotation() const
{
	return prevRot;
}
Vec2D Entity::getPreviousAABBTL() const
{
	return prevAABBTL;
}
Vec2D Entity::getPreviousAABBBR() const
{
	return prevAABBBR;
}
Vec2D Entity::getResultingForce() const
{
	return resultingForce;
}
float Entity::getFrictionCoefficient() const
{
	return frictionCoefficient;
}
float Entity::getLostTime() const
{
	return lostTime;
}
bool Entity::getTrackEntityData() const
{
	return trackEntityData;
}
float Entity::getSillhueteArea() const
{
	return sillhuetteArea;
}
//Constructor
Entity::Entity()
	:
	entityID(-1),
	entityState(-1),
	velocity(),
	forces(),
	resultingForce(),
	mass(FLT_MAX),
	shape(),
	isColliding(false),
	frictionCoefficient(FLT_MAX),
	restitutionCoefficient(FLT_MAX),
	dragCoefficient(FLT_MAX),
	sillhuetteArea(FLT_MAX),
	prevPos(FLT_MAX, FLT_MAX),
	prevVel(FLT_MAX, FLT_MAX),
	prevRot(FLT_MAX),
	prevAABBTL(FLT_MAX, FLT_MAX),
	prevAABBBR(FLT_MAX, FLT_MAX),
	lostTime(FLT_MAX),
	trackEntityData(false)
{
}