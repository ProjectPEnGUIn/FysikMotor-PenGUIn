#include "PEVec2D.h"



//set functions
template <typename T> void PEVec2D<T>::setX(double inputX) //sets x component
{
	this->x = inputX;
}
template <typename T> void PEVec2D<T>::setY(double inputY) //sets y component
{
	this->y = inputY;
}
template <typename T> void PEVec2D<T>::setXY(double inputX, double inputY) //sets both x and y components
{
	this->x = inputX;
	this->y = inputY;
}

template <typename T> void PEVec2D<T>::setVectorMagnitude(T inputLength) //sets the length of the vector, keeps the direction
{

}
template <typename T> void PEVec2D<T>::setDirectionDEGREES(T inputDirectionInDegrees) //set the direction of vector in degrees
{

}
template <typename T> void PEVec2D<T>::setDirectionRADIANS(T inputDirectionInRadians) //set the diredtion of vector in radians
{

}
template <typename T> void PEVec2D<T>::scaleVector(T inputScaleAmount) //scales the vector so many times
{

}

//get functions
template <typename T> T PEVec2D<T>::getX() //returns x component
{
	return this->x;
}
template <typename T> T PEVec2D<T>::getY() //returns y component
{
	return this->y;
}

template <typename T> T PEVec2D<T>::getDirectionDEGREES() //gets the direction of vector in degrees
{
	
}
template <typename T> T PEVec2D<T>::getDirectionRADIANS() //gets the direction of vector in radians
{

}
template <typename T> T PEVec2D<T>::getMagnitude() //returns the magnitude/length
{
	
}

//overloading operators, allows one to use + - * / with PEVec2D<T> objects
template <typename T> PEVec2D<T>::operator+(PEVec2D<T> inputVectorToAdd) //allowes usage of vec1 + vec2 = vec3. will return PEVec2D object
{
	//adds their x and y components together
	PEVec2D<T> returnVec2D(this->x + inputVectorToAdd.getX(), this->y + inputVectorToAdd.getY());
	return returnVec2D;
}
template <typename T> PEVec2D<T>::operator-(PEVec2D<T> inputVectorToSubtract) //allows usage of vec1 - vec2 = vec3. will return PEVec2D<T> objec
{
	//subtracts their x and y components
	PEVec2D<T> returnVec2D(this->x - inputVectorToSubtract.getX(), this->y - inputVectorToSubtract.getY());
	return returnVec2D;
}
template <typename T> PEVec2D<T>:: operator*(PEVec2D<T> inputScalar) //allows usage of vec1 * scalar = vec3. will return PEVec2D<T> object
{
	return PEVec2D<T> returnVec2D(this->x * inputScalar, this->y * inputScalar);
}

														//constructor
template <typename T> PEVec2D<T>::PEVec2D() //inits x and y components to 0, give them values at another point
{
	this->x = 0;
	this->y = 0;
}
template <typename T> PEVec2D<T>::PEVec2D(T inputX, T inputY) //set both x and y at init
{
	this->x = inputX;
	this->y = inputY;
}

//destructor
template <typename T> PEVec2D<T>::~PEVec2D()
{

}