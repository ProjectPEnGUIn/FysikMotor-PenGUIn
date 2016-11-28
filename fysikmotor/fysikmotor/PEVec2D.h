//PEnGUIn ( Euclidian ) Vector in two dimensions
//has a direction and magnitude, can represent a velocity, force etc...
//we are limiting ourselves to two dimensions in our project, 3Dvec isnt neccesary for our needs as it stands ( 28 / 11 2016 )

//Erik Magnusson 28/11 2016

//object stores x and y component in double, using double for them both, shouldn't be a major difference in performance for us and we get greater precision as in more decimals
//magnitude, direction ( degrees AND radians )
//operator overloading, able to add  C = A + B, where each letter is an PVec2D object
//suports +, -, *, /
//euclidian vector math functions

#pragma once
#ifndef _PEVEC2D_
#define _PEVEC2D_

template <typename T>
class PEVec2D
{
private:
	//functions
	T getX(); //returns x component in double
	T getY(); //returns y component in double
    

    //overloading operators, allows one to use + - * / with PVe

public:
	//functions
	PEVec2D();
	virtual ~PEVec2D();
private:
	//members

	T x;
	T y;

};

using Vec2D = PEVec2D<double>;  //defines what type the vector object

#endif // !_PEVEC2D_
