#include "Force.h"
void Force::setForce(const Vec2D& inputForce)
{
	force = inputForce;
}
void Force::setOffset(const Vec2D& inputOffset)
{
	offset = inputOffset;
}
void Force::setName(const std::string& inputName)
{
	name = inputName;
}

Vec2D Force::getForce() const //gets the force
{
	return force;
}
Vec2D Force::getOffset() const //gets force offset from the center
{
	return offset;
}
std::string Force::getName() const //gets the name of the force
{
	return name;
}



Force::Force()
	:
	force(),
	offset(),
	name("_noNameSet")
{
}
Force::Force(const Vec2D& inputForce, const Vec2D& inputOffset, const std::string& inputName)
	:
	force(inputForce),
	offset(inputOffset),
	name(inputName)
{
}
Force::Force(const Vec2D& inputForce, const Vec2D& inputOffset)
	:
	force(inputForce),
	offset(inputOffset),
	name("_noNameSet")
{
}