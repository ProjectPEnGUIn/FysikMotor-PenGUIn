//handles everything regarding the entities themselves, collision detection, collisions, updating using timestep, applying forces
//drawing the entiies is not handled here, need to take interpolation in consideration

//split upp entities in different sectors on a quad tree

//Erik Magnusson 5/12 2016

#pragma once
#ifndef _ENTITYHANDLER_
#define _ENTITYHANDLER_

#include <iostream>
#include <string>
#include <vector>

#include "PEVec2D.h"
#include "Entity.h"

class EntityHandler
{
private:

public:
	EntityHandler();
private:
	//members

};

#endif // !_ENTITYHANDLER_