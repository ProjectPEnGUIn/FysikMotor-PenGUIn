
/*

functions to handle aabb check since it is used at multiple points in program
AABB check is simple and not very resource intensive since it is just comparing one number with another all the time 


basic premis

//entity plane has a positive y up, negative y down
//positvie x right, negative x left

//top right aabb coords are the top right, min x, max y
//bottom left aabb coords are bottom eft, max x, min y

//for a simple aabb collision to be true:

//left edge of e1 has to be inside of e2 x boundries, e2.x || e2.x + width
//OR
//right edge of e1 has to be inside of e2 x boundries e2.x || e2.x + width

//AND

//top edge of e1 has to be inside of e2 y boundries e2.y || e2.x + height
//OR
//bottom edge has to inside of e2 y boundries e2.y || e2.y + height

handle:
entity - entity
entity - square area
square area - square area
entity - dot
square area - dot
area fully contain entity

Erik Magnusson 7/1 2017
*/

#pragma once
#ifndef _AABBFUNCTIONS_
#define _AABBFUNCTIONS_


#include <iostream>
#include <math.h>
#include <cmath>

#include "Entity.h"
#include "PEVec2D.h"


bool minskowskiDifferenceAABBCollisionCheck(const Entity& inputEntity1, const Entity& inputEntity2);

bool sweptMinskowskiDifferenceAABBCollisionCheck(const Entity& inputEntity1, const Entity& inputEntity2, const float inputDeltaTime);
//helper functions to this function;
float getRayIntersectionFractionOfFirstRay(const Vec2D& inputVec1Origin, const Vec2D& inputVec1End, const Vec2D& inputVec2Origin, const Vec2D& inputVec2End);
float getRayIntersectionFraction(const Vec2D& inputVectorOrigin, const Vec2D& inputDirectionVector, const Vec2D& inputTL, const Vec2D& inputBR);

bool entityAreaAABBCheck(const Entity& inputEntity, const float& maxX, const float& minX, const float& maxY, const float& minY);
bool entityEntityAABBCheck(const Entity& inputEntity1, const Entity inputEntity2);
bool entityAreaAABBCheck(const Entity& inputEntity, const float& maxX, const float& minX, const float& maxY, const float& minY);
bool entityFullyWithinAreaAABBCheck(const Entity& inputEntity, const float& maxX, const float& minX, const float& maxY, const float& minY);
bool areaAreaAABBCheck(const float& maxX1, const float& minX1, const float& maxY1, const float& minY1, const float& maxX2, const float& minX2, const float& maxY2, const float& minY2);
bool entityPartiallyContainedWithinArea(const Entity& inputEntity, const float& maxX, const float& minX, const float& maxY, const float& minY); //WARNING: call can fully contained functions first to avoid errors


#endif _AABBFUNCTIONS_
