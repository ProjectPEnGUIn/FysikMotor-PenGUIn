/*

object which takes and handles input accordingly.

make use of sfml event and inputevents for inputs

mainly use mouse for input for now, ex mouse pressed, released...
take in a view to get proper mouse pos
take in renderwindow to get relative pos to window

//http://www.sfml-dev.org/tutorials/2.4/window-inputs.php
//http://www.sfml-dev.org/tutorials/2.4/window-events.php

Erik Magnusson 12/1 2017

*/


#pragma once
#ifndef  _INPUTHANDLER_
#define _INPUTHANDLER_

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "PEVec2D.h"

class InputHandler
{
private:
	//functions

	sf::Vector2f vec2DToVector2f(const Vec2D& inputVec2D);
	Vec2D vector2fToVec2D(const sf::Vector2f& inputVector2f);

public:
	//functions

	void handleEvent(const sf::Event& inputEvent);


	InputHandler();
	~InputHandler();

private:
	//members

	sf::Mouse mouse; //mouse object, real time acces to mouse status without using events, pos and buttons down
	sf::Keyboard keyboard;


	//members regarding mouse movent
	//store current and last pos relative to the screen as a vec2d, change then after each click
	Vec2D currentPressedPos,
		lastPressedPos;

};
#endif // ! _INPUTHANDLER_
