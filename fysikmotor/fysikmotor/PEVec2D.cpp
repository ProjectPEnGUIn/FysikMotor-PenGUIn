#include "PEVec2D.h"



//set functions
template <typename T> void Vec2D::setX(double inputX) //sets x component
{
	this->x = inputX;
}
template <typename T> void Vec2D::setY(double inputY) //sets y component
{
	this->y = inputY;
}
template <typename T> void Vec2D::setXY(double inputX, double inputY) //sets both x and y components
{
	this->x = inputX;
	this->y = inpuyY;
}

template <typename T> void Vec2D::setVectorMagnitude(T inputLength) //sets the length of the vector, keeps the direction
{

}
template <typename T> void Vec2D::setDirectionDEGREES(T inputDirectionInDegrees) //set the direction of vector in degrees
{

}
template <typename T> void Vec2D::setDirectionRADIANS(T inputDirectionInRadians) //set the diredtion of vector in radians
{

}
template <typename T> void Vec2D::scaleVector(T inputScaleAmount) //scales the vector so many times
{

}

//get functions
template <typename T> T Vec2D::getX() //returns x component
{
	return this->x;
}
template <typename T> T Vec2D::getY() //returns y component
{
	return this->y;
}

template <typename T> T Vec2D::getDirectionDEGREES() //gets the direction of vector in degrees
{
	
}
template <typename T> T Vec2D::getDirectionRADIANS() //gets the direction of vector in radians
{

}
template <typename T> T Vec2D::getMagnitude() //returns the magnitude/length
{
	
}

//overloading operators, allows one to use + - * / with PEVec2D<T> objects
template <typename T> Vec2D::operator+(PEVec2D<T> inputVectorToAdd) //allowes usage of vec1 + vec2 = vec3. will return PEVec2D object
{
	//adds their x and y components together
	return PEVec2D<T> returnVec2D(this->x + inputVectorToAdd.getX(), this->y + inputVectorToAdd.getY());
}
template <typename T> Vec2D::operator-(PEVec2D<T> inputVectorToSubtract) //allows usage of vec1 - vec2 = vec3. will return PEVec2D<T> objec
{
	//subtracts their x and y components
	return PEVec2D<T> returnVec2D(this->x - inputVectorToSubtract.getX(), this->y - inputVectorToSubtract.getY());
}
template <typename T> Vec2D:: operator*(PEVec2D<T> inputScalar) //allows usage of vec1 * scalar = vec3. will return PEVec2D<T> object
{
	return PEVec2D<T> returnVec2D(this->x * inputScalar, this->y * inputScalar);
}
template <typename T> Vec2D::operator*(PEVec2D<T> inputVectorToMultiply); //allows usage of vec1 * vec2 = vec3. will return PEVec2D<T> object

														//constructor
template <typename T> Vec2D::PEVec2D() //inits x and y components to 0, give them values at another point
{
	this->x = 0;
	this->y = 0;
}
template <typename T> Vec2D:PEVec2D(T inputX, T inputY) //set both x and y at init
{
	this->x = inputX;
	this->y = inputY;
}

//destructor
template <typename T> Vec2D::~PEVec2D();