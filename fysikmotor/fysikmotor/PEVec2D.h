//Physics engine vector in two dimensions
//has a direction and magnitude, can represent a velocity, force etc... is used in a euclidian space
//we are limiting ourselves to two dimensions in our project, 3Dvec isnt neccesary for our needs as it stands ( 28 / 11 2016 )

//Erik Magnusson 28/11 2016

//object stores x and y component
//magnitude, direction ( degrees AND radians )
//operator overloading, able to add  C = A + B
//suports +, -, * =
//euclidian vector math functions

//material used for formulas and such:
//https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces/vectors/v/vector-introduction-linear-algebra
//http://www.euclideanspace.com/maths/algebra/vectors/
//https://en.wikipedia.org/wiki/Euclidean_vector
//https://www.youtube.com/watch?v=PgGhEovFhd0&t=1s

//http://www.metanetsoftware.com/technique/tutorialA.html#section3 12/1 2017

#pragma once
#ifndef _PEVEC2D_
#define _PEVEC2D_

#include <iostream>
#include <cmath>
#include <math.h>
#include <cassert>


template <typename T> //the PEVec2D uses whatever typename is set at initialisation, ex: double, float, int
class PEVec2D
{
public:
	//functions

    //set functions
	void setX(T inputX); //sets x component
	void setY(T inputY); //sets y component
	void setXY(T inputX, T inputY); //sets both x and y components at the same time

	void setVectorMagnitude(T inputLength); //sets the length of the vector, keeps the direction, avoid calling if neccesary due to performancy hit with sine/cosine/tan usage
	void setDirectionDEGREES(T inputDirectionInDegrees); //set the direction of vector in degrees, avoid calling if neccesary due to performancy hit with sine/cosine/tan usage
	void setDirectionRADIANS(T inputDirectionInRadians); //set the diredtion of vector in radians, avoid calling if neccesary due to performancy hit with sine/cosine/tan usage
	PEVec2D scaleVector(T inputScaleAmount); //scales the vector components

	//get functions
	T getX() const; //returns x component
	T getY() const; //returns y component

	float getDirectionDEGREES() const; //gets the direction of vector in degrees
	float getDirectionRADIANS() const; //gets the direction of vector in radians
	T getMagnitude() const; //returns the magnitude/length of the vector

	PEVec2D getNormalisation() const; //returns this vector with a length of 1
	PEVec2D getClockWiseNormal() const; //90 degree normal to current vector in clockwise direcion
	PEVec2D getAntiClockWiseNormal() const; //90 degree normal to current vector in anticlockwise direction
	PEVec2D getCrossProductWithScalar(const T& inputScalar) const; //gets the vector CROSS product
	PEVec2D getRotatedVectorDEGREES(const T& inputDEGREES) const; //returns the vector rotated in a direction
	PEVec2D getRotatedVectorRADIANS(const T& inputRADIANS) const; // returns the vector rotate in a dircetion

	//overloading operators, allows use of c++ operators on own made objects. Very useful
	PEVec2D operator+(const PEVec2D& inputVectorToAdd) const; //allowes usage of vec1 + vec2 = vec3. will return PEVec2D object
	PEVec2D operator-(const PEVec2D& inputVectorToSubtract) const; //allows usage of vec1 - vec2 = vec3. will return PEVec2D<T> object
	PEVec2D operator*(const T inputScalar) const; //allows usage of vec1 * scalar = vec3. will return PEVec2D<T> object
	PEVec2D& operator+=(const PEVec2D& addToVector); //adds a vector to this vector
	PEVec2D& operator-=(const PEVec2D& subtractFromVector); //removes a vector from this vector
	PEVec2D& operator*=(const T multiplyVectorWithScalar); //multiplies this vector by a scalar
	T operator*=(const PEVec2D& inputVectorToDotProduct) const; //2d vector dot product
	T operator*(const PEVec2D& inputVectorToDotProduct) const; //2d vector dot product
	
	//constructor
	PEVec2D(); //inits x and y components, give them values at another point
	PEVec2D(T inputX, T inputY); //set both x and y at init

private:
	//members

	T x{}; //{} inits it no matter what type it is
	T y{};

	float PI = 3.14159265f;
};

//--------------

//implementation of functions in header file due to using templates
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
	float angle = getDirectionRADIANS(); //gets the direction to temp store it, cos/sin uses rad

	//gives x and y new values, but keeps the original direction
	x = cos(angle) * inputLength;
	y = sin(angle) * inputLength;
}
template <typename T> void PEVec2D<T>::setDirectionDEGREES(T inputDirectionInDegrees) //set the direction of vector in degrees
{
	//https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/2drota.htm 7/2
	//x' = x cos f - y sin f
    //y' = y cos f + x sin f
	
	T oldX = x,
		oldY = y;
	float cosAngle = cos(inputDirectionInDegrees * 0.0174532925f),
		sinAngle = sin(inputDirectionInDegrees * 0.0174532925f);

	x = oldX *cosAngle - oldY * sinAngle;
	y = oldY * cosAngle + oldX * sinAngle;

}
template <typename T> void PEVec2D<T>::setDirectionRADIANS(T inputDirectionInRadians) //set the diredtion of vector in radians
{
	//easy énough and it works
	setDirectionDEGREES(57.2957795f * inputDirectionInRadians);
}


template <typename T> PEVec2D<T> PEVec2D<T>::scaleVector(T inputScaleAmount) //scales wtih scalar
{
	return Vec2D(x * inputScaleAmount, y * inputScaleAmount);
}
template <typename T> T PEVec2D<T>::getX() const //returns x component
{
	return x;
}
template <typename T> T PEVec2D<T>::getY() const //returns y component
{
	return y;
}

template <typename T> float PEVec2D<T>::getDirectionDEGREES() const //gets the direction of vector in degrees
{
	if (x == 0 && y == 0) //stops errors
	{
		return 0;
	}

	float angle = atan2(y, x) * 180.0f / PI; //gets radian angle and then converts to degrees

	//makes it so the angle is 0 <= a <= 360
	if (angle < 0)
		return angle + 360.0f;
	else
		return angle;
}
template <typename T> float PEVec2D<T>::getDirectionRADIANS() const //gets the direction of vector in radians
{
	if (x == 0 && y == 0) //stops errors
	{
		return 0;
	}

	float angle = atan2(y, x);

	//makes it so the angle is returned in 0 <= a <= 2*PI
	if (angle < 0)
		return angle + 2 * PI;
	else
		return atan2(y , x);
}

template <typename T> PEVec2D<T> PEVec2D<T>::getNormalisation() const //returns this vector with a length of 1
{
	//prevetns errors
	if (x == 0 && y == 0)
		return PEVec2D<T>(0, 0);

	const float currentLength = sqrt((x*x) + (y*y));

	return PEVec2D<T>(x / currentLength, y / currentLength);
}
template <typename T> PEVec2D<T> PEVec2D<T>::getClockWiseNormal() const //90 degree normal to current vector in clockwisedirection
{
	return PEVec2D<T>(y, -x);
}
template <typename T> PEVec2D<T> PEVec2D<T>::getAntiClockWiseNormal() const //90 degree normal to current vector in anticlockwise direction
{
	return PEVec2D<T>(-y, x);
}
template <typename T> T PEVec2D<T>::getMagnitude() const //returns the magnitude/length of this vector
{
	if (x == 0 && y == 0) //stops errors
		return 0;

	return sqrt((x * x) + (y * y));
}
template <typename T> PEVec2D<T> PEVec2D<T>::getCrossProductWithScalar(const T& inputScalar) const //gets the vector CROSS product
{
	//http://www.dyn4j.org/2011/11/contact-points-using-clipping/ 9/2 2017

	return PEVec2D<T>(y * inputScalar, -x *inputScalar);
}
template <typename T> PEVec2D<T> PEVec2D<T>::getRotatedVectorDEGREES(const T& inputDEGREES) const //returns the vector rotated in a direction
{
	//EASY, convert degrees to radians
	return getRotatedVectorRADIANS(inputDEGREES * 0.0174532925f);
}
template <typename T> PEVec2D<T> PEVec2D<T>::getRotatedVectorRADIANS(const T& inputRADIANS) const // returns the vector rotate in a dircetion
{

	T oldX = x,
		oldY = y,
	   cosAngle = cos(inputRADIANS),
		sinAngle = sin(inputRADIANS);

	return PEVec2D<T>(oldX *cosAngle - oldY * sinAngle, oldY * cosAngle + oldX * sinAngle);
}
template <typename T> PEVec2D<T> PEVec2D<T>::operator+(const PEVec2D<T>& inputVectorToAdd) const //allowes usage of vec1 + vec2 = vec3. will return PEVec2D object
{
	//adds their x and y components together

	PEVec2D<T> returnVec2D(x + inputVectorToAdd.getX(), y + inputVectorToAdd.getY());

	return returnVec2D;
}
template <typename T> PEVec2D<T> PEVec2D<T>::operator-(const PEVec2D<T>& inputVectorToSubtract) const //allows usage of vec1 - vec2 = vec3. will return PEVec2D<T> objec
{
	//subtracts their x and y components

	PEVec2D<T> returnVec2D(x - inputVectorToSubtract.getX(), y - inputVectorToSubtract.getY());

	return returnVec2D;
}
template <typename T> PEVec2D<T> PEVec2D<T>::operator*(T inputScalar) const //allows usage of vec1 * scalar = vec3. will return PEVec2D<T> object
{
	PEVec2D<T> returnVec2D(x * inputScalar, y * inputScalar);

	return  returnVec2D;
}

template <typename T> PEVec2D<T>& PEVec2D<T>::operator+=(const PEVec2D<T>& addToVector)
{
	x = x + addToVector.getX();
	y = y + addToVector.getY();
	return *this;
}
template <typename T> PEVec2D<T>& PEVec2D<T>::operator-=(const PEVec2D<T>& subtractFromVector)
{
	x = x - subtractFromVector.getX();
	y = y - subtractFromVector.getY();
	return *this;
}
template <typename T> PEVec2D<T>& PEVec2D<T>::operator*=(const T multiplyVectorWithScalar)
{
	x = x * multiplyVectorWithScalar;
	y = y * multiplyVectorWithScalar;
	
	return *this;
}
template <typename T> T PEVec2D<T>::operator*=(const PEVec2D& inputVectorToDotProduct) const //2d vector dot product
{	
	return x * inputVectorToCrossProduct.getY() + y * inputVectorToDotProduct.getX();
}
template <typename T> T PEVec2D<T>::operator*(const PEVec2D& inputVectorToDotProduct) const//2d vector dot product
{
	//return x * inputVectorToCrossProduct.getY() + y * inputVectorToCrossProduct.getX();

	//according to http://mines.lumpylumpy.com/Electronics/Computers/Software/Cpp/Graphics/Vector/DotProduct.php#.WJsdoG_hCM8 8/2
	return x * inputVectorToDotProduct.getX() + y * inputVectorToDotProduct.getY();
}

template <typename T> PEVec2D<T>::PEVec2D() //inits x and y components, give them values at another point
{
}
template <typename T> PEVec2D<T>::PEVec2D(T inputX, T inputY) //set both x and y at init
	:
	x(inputX),
	y(inputY)
{
}

//using Metres = float; 
using Vec2D = PEVec2D<float>; //allows one to use Vec2D in the program instead of typing PEVec2D<float>

#endif // !_PEVEC2D_
