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

template <typename T> //the PEVec2D uses whatever typename is set at initialisation, ex: double, float, int
class PEVec2D
{
private:
	//functions
  

public:
	//functions

    //set functions
	void setX(double inputX); //sets x component
	void setY(double inputY); //sets y component
	void setXY(double inputX, double inputY); //sets both x and y components

	void setVectorMagnitude(T inputLength); //sets the length of the vector, keeps the direction
	void setDirectionDEGREES(T inputDirectionInDegrees); //set the direction of vector in degrees
	void setDirectionRADIANS(T inputDirectionInRadians); //set the diredtion of vector in radians
	void scaleVector(T inputScaleAmount); //scales the vector so many times
    
	//get functions
	T getX(); //returns x component
	T getY(); //returns y component

	T getDirectionDEGREES(); //gets the direction of vector in degrees
	T getDirectionRADIANS(); //gets the direction of vector in radians
	T getMagnitude(); //returns the magnitude/length

	//overloading operators, allows one to use + - *  with PEVec2D<T> objects
	PEVec2D<T> operator+(PEVec2D<T> inputVectorToAdd); //allowes usage of vec1 + vec2 = vec3. will return PEVec2D object
	PEVec2D<T> operator-(PEVec2D<T> inputVectorToSubtract); //allows usage of vec1 - vec2 = vec3. will return PEVec2D<T> object
	PEVec2D<T> operator*(PEVec2D<T> inputScalar); //allows usage of vec1 * scalar = vec3. will return PEVec2D<T> object
	

	//constructor
	PEVec2D(); //inits x and y components to 0, give them values at another point
	PEVec2D(T inputX, T inputY); //set both x and y at init

	//destructor
    ~PEVec2D();
private:
	//members

	T x;
	T y;

};

using Vec2D = PEVec2D<double>;  

#endif // !_PEVEC2D_
