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
void Force::setColour(sf::Color& inputColour)
{
	colour = inputColour;
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
sf::Color Force::getColour() const
{
	return colour;
}



Force::Force()
	:
	force(),
	offset(),
	name("_noNameSet"),
	colour(sf::Color::Red)
{
}
Force::Force(const Vec2D& inputForce, const Vec2D& inputOffset, const std::string& inputName)
	:
	force(inputForce),
	offset(inputOffset),
	name(inputName),
	colour(sf::Color::Red)
{
}
Force::Force(const Vec2D& inputForce, const Vec2D& inputOffset)
	:
	force(inputForce),
	offset(inputOffset),
	name("_noNameSet"),
	colour(sf::Color::Red)
{
}
Force::Force(const Vec2D& inputForce, const Vec2D& inputOffset, const std::string& inputName, sf::Color inputColour)
	:
	force(inputForce),
	offset(inputOffset),
	name(inputName),
	colour(inputColour)
{
}
Force::Force(const Vec2D& inputForce)
	:
	force(inputForce),
	offset(),
	name("_noNameSet"),
	colour(sf::Color::Red)

{

}