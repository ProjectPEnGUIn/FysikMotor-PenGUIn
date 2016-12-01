//PEnGUIn ( Euclidian ) Vector in two dimensions
//has a direction and magnitude, can represent a velocity, force etc... is used in a cortesian plane or euclidan plane, cordinatesystem, whatever you want to call it
//we are limiting ourselves to two dimensions in our project, 3Dvec isnt neccesary for our needs as it stands ( 28 / 11 2016 )

//Erik Magnusson 28/11 2016

//object stores x and y component
//magnitude, direction ( degrees AND radians )
//operator overloading, able to add  C = A + B, where each letter is an PVec2D object
//suports +, -, *, /
//euclidian vector math functions

//material used for formulas and such:
//https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces/vectors/v/vector-introduction-linear-algebra
//http://www.euclideanspace.com/maths/algebra/vectors/
//https://en.wikipedia.org/wiki/Euclidean_vector
//https://www.youtube.com/watch?v=PgGhEovFhd0&t=1s

#pragma once
#ifndef _PEVEC2D_
#define _PEVEC2D_

#include <iostream>
#include <cmath>
#include <math.h>

const double PI = 3.14159265; //should be fine enough

template <typename T> //the PEVec2D uses whatever typename is set at initialisation, ex: double, float, int
class PEVec2D
{
private:
	//functions
  

public:
	//functions

    //set functions
	void setX(T inputX); //sets x component
	void setY(T inputY); //sets y component
	void setXY(T inputX, T inputY); //sets both x and y components

	void setVectorMagnitude(T inputLength); //sets the length of the vector, keeps the direction
	void setDirectionDEGREES(T inputDirectionInDegrees); //set the direction of vector in degrees
	void setDirectionRADIANS(T inputDirectionInRadians); //set the diredtion of vector in radians
	void scaleVector(T inputScaleAmount); //scales the vector so many times
    
	//get functions
	T getX(); //returns x component
	T getY(); //returns y component

	double getDirectionDEGREES(); //gets the direction of vector in degrees
	double getDirectionRADIANS(); //gets the direction of vector in radians
	double getMagnitude(); //returns the magnitude/length

	//overloading operators, allows one to use + - * / = with PEVec2D<T> objects
	PEVec2D<T> operator+(PEVec2D<T> inputVectorToAdd); //allowes usage of vec1 + vec2 = vec3. will return PEVec2D object
	PEVec2D<T> operator-(PEVec2D<T> inputVectorToSubtract); //allows usage of vec1 - vec2 = vec3. will return PEVec2D<T> object
	PEVec2D<T> operator*(T inputScalar); //allows usage of vec1 * scalar = vec3. will return PEVec2D<T> object
	void operator=(PEVec2D<T> setVectorAs); //allowes usage of vec1 = vec2, vec1 gets value of vec2. will return PEVec2D<T> object
	void operator+=(PEVec2D<T> addToVector);
	void operator-=(PEVec2D<T> subtractFromVector);
	void operator*=(T multiplyVectorWithScalar);


	//constructor
	PEVec2D(); //inits x and y components to 0, give them values at another point
	PEVec2D(T inputX, T inputY); //set both x and y at init

	
private:
	//members

	T x{}; //{} inits it no matter what type it is
	T y{};

};






//implementation of functions in header file to using templates

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
	T angle = getDirectionRADIANS(); //gets the direction to temp store it

	//gives x and y new values, but keeps the direction
	x = cos(angle) * inputLength;
	y = sin(angle) * inputLength;
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
	if (x == 0 && y == 0) //stops erroirs
		return 0;

	return (atan(y / x) * 180) / PI; //atan returns in radians, must convert
}
template <typename T> double PEVec2D<T>::getDirectionRADIANS() //gets the direction of vector in radians
{
	if (x == 0 && y == 0) //stops errors
		return 0;

	return atan(y / x);
}
template <typename T> double PEVec2D<T>::getMagnitude() //returns the magnitude/length
{
	if (x == 0 && y == 0) //stops errors
		return 0;

	return sqrt((x * x) + (y * y));
}

//overloading operators, allows one to use + - * / = with PEVec2D<T> objects
template <typename T> PEVec2D<T> PEVec2D<T>::operator+(PEVec2D<T> inputVectorToAdd) //allowes usage of vec1 + vec2 = vec3. will return PEVec2D object
{
	//adds their x and y components together

	PEVec2D<T> returnVec2D(x + inputVectorToAdd.getX(), y + inputVectorToAdd.getY());

	return returnVec2D;
}
template <typename T> PEVec2D<T> PEVec2D<T>::operator-(PEVec2D<T> inputVectorToSubtract) //allows usage of vec1 - vec2 = vec3. will return PEVec2D<T> objec
{
	//subtracts their x and y components

	PEVec2D<T> returnVec2D(x - inputVectorToSubtract.getX(), y - inputVectorToSubtract.getY());

	return returnVec2D;
}
template <typename T> PEVec2D<T> PEVec2D<T>::operator*(T inputScalar) //allows usage of vec1 * scalar = vec3. will return PEVec2D<T> object
{
	PEVec2D<T> returnVec2D(x * inputScalar, y * inputScalar);

	return  returnVec2D;
}
template <typename T> void PEVec2D<T>::operator=(PEVec2D<T> setVectorAs) //allowes usage of vec1 = vec2, vec1 gets value of vec2
{
	x = setVectorAs.getX();
	y = setVectorAs.getY();
}
template <typename T> void PEVec2D<T>::operator+=(PEVec2D<T> addToVector)
{
	x = x + addToVector.getX();
	y = y + addToVector.getY();
}
template <typename T> void PEVec2D<T>::operator-=(PEVec2D<T> subtractFromVector)
{
	x = x - subtractFromVector.getX();
	y = y - subtractFromVector.getY();
}
template <typename T> void PEVec2D<T>::operator*=(T multiplyVectorWithScalar)
{
	x = x * multiplyVectorWithScalar;
	y = y * multiplyVectorWithScalar;
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


using Vec2D = PEVec2D<double>;

#endif // !_PEVEC2D_
