#include "PEVec2D.h"



//set functions
template <typename T> void PEVec2D<T>::setX(T inputX) //sets x component
{
	x = inputX;
}
template <typename T> void PEVec2D<T>::setY(T inputY) //sets y component
{
	y = inputY;
}
template <typename T> void PEVec2D<T>::setXY(T inputX, T inputY) //sets both x and y components
{
	x = inputX;
	y = inputY;
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
	return x;
}
template <typename T> T PEVec2D<T>::getY() //returns y component
{
	return y;
}

template <typename T> double PEVec2D<T>::getDirectionDEGREES() //gets the direction of vector in degrees
{
	
}
template <typename T> double PEVec2D<T>::getDirectionRADIANS() //gets the direction of vector in radians
{
	
}
template <typename T> double PEVec2D<T>::getMagnitude() //returns the magnitude/length
{
	
}

//overloading operators, allows one to use + - * / = with PEVec2D<T> objects
template <typename T> PEVec2D<T> PEVec2D<T>::operator+(PEVec2D<T> inputVectorToAdd) //allowes usage of vec1 + vec2 = vec3. will return PEVec2D object
{
	//adds their x and y components together
	
	return PEVec2D<T> returnVec2D(x + inputVectorToAdd.getX(), y + inputVectorToAdd.getY());
}
template <typename T> PEVec2D<T> PEVec2D<T>::operator-(PEVec2D<T> inputVectorToSubtract) //allows usage of vec1 - vec2 = vec3. will return PEVec2D<T> objec
{
	//subtracts their x and y components
	
	return PEVec2D<T> returnVec2D(x - inputVectorToSubtract.getX(), y - inputVectorToSubtract.getY());
}
template <typename T> PEVec2D<T> PEVec2D<T>::operator*(T inputScalar) //allows usage of vec1 * scalar = vec3. will return PEVec2D<T> object
{
	return PEVec2D<T> returnVec2D(x * inputScalar, y * inputScalar);
}
template <typename T> PEVec2D<T> PEVec2D<T>::operator=(PEVec2D<T> setVectorAs) //allowes usage of vec1 = vec2, vec1 gets value of vec2
{

}
														//constructor
template <typename T> PEVec2D<T>::PEVec2D() //inits x and y components to 0, give them values at another point
{

}
template <typename T> PEVec2D<T>::PEVec2D(T inputX, T inputY) //set both x and y at init
	:
	x(inputX),
	y(inputY)
{
	
}

//destructor
template <typename T> PEVec2D<T>::~PEVec2D()
{

}