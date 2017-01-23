#include "EntityHandler.h"

//collision checks

bool EntityHandler::SATCheck(const Entity& entity1, const Entity& entity2) //does a thurough check using SAT, seperating axis theorem, very resource intensive, lots of math functions, ex sqrt, cosine, sine. very accurate
{
	//seperating axis theorem check, 20/12 2016
	//very thurough collision check, downside: very resource intensive, lots of math functions need to be called with sqrt, sine, cosine, tan
	//pros: one type of collision check between all possible shapes of entities
	//handle both convec shapes and non convex shape by splitting up non convex shapes into convex sub parts
	//mainly use http://www.dyn4j.org/2010/01/sat/ for this


	
	//SAT check if false
	return false;
}
//collision countermeasures
void EntityHandler::entityCollision(Entity& inputEntity1, Entity& inputEntity2, const Vec2D& penentrationVector, const Vec2D& contactPoint) //handles collision between entities
{
	//asumes the entities are colliding, they are inside of eachother which means there is a penentrationvector 

	//used https://en.wikipedia.org/wiki/Coefficient_of_restitution 12/1 2017
	//and Fysik 1, Impuls Written by Lars Frankel, Daniel Gottfridsson and  Ulf Jonasson and published by GLEERUPS in 2011
	//Used pages 167, 168, 169 and the chapter summerisation


	//use penentrationvector to accuratly handle collisions, exact time.
	//use it to move entities around as if they never traveled useless distance while inside of eachother

	//store inital velocities of both entities
	Vec2D  entity1V0 = inputEntity1.getVelocity(), entity2V0 = inputEntity2.getVelocity();

	//average resutution coefficient, not sure how to handle different entities with different restutuions yet
	float restitution = (inputEntity1.getRestitutionCoefficient() + inputEntity2.getRestitutionCoefficient()) / 2.0f;

	//set both new speeds and position on entity
	Vec2D entity1Vf, entity2Vf; //final velocities

	//set new speeds in x axis
	entity1Vf.setX(((entity1V0.getX() * inputEntity1.getMass()) + (entity2V0.getX() *  inputEntity2.getMass()) + ((entity2V0.getX() - entity1V0.getX()) * inputEntity2.getMass() * restitution)) / (inputEntity1.getMass() + inputEntity2.getMass()));
	entity2Vf.setX(((entity1V0.getX() * inputEntity1.getMass()) + (entity2V0.getX() *  inputEntity2.getMass()) + ((entity2V0.getX() - entity1V0.getX()) * inputEntity1.getMass() * restitution)) / (inputEntity1.getMass() + inputEntity2.getMass()));

	//set new speeds in y axis
	entity1Vf.setY(((entity1V0.getY() * inputEntity1.getMass()) + (entity2V0.getY() *  inputEntity2.getMass()) + ((entity2V0.getY() - entity1V0.getY()) * inputEntity2.getMass() * restitution)) / (inputEntity1.getMass() + inputEntity2.getMass()));
	entity2Vf.setY(((entity1V0.getY() * inputEntity1.getMass()) + (entity2V0.getY() *  inputEntity2.getMass()) + ((entity2V0.getY() - entity1V0.getY()) * inputEntity1.getMass() * restitution)) / (inputEntity1.getMass() + inputEntity2.getMass()));

	//calculate how long the entities have been inside of eachother using both v0 and the penentration vector(distance traveled)
	//the penentrationvector magnitude is the distance
	//use distancce = velocity * time

	//in seconds
	float overlapTime = penentrationVector.getMagnitude() / (inputEntity1.getVelocity().getMagnitude() + inputEntity2.getVelocity().getMagnitude());

	//corrects their position to when they were just touching, proceed to set new speed to them at that time and then move time forwoard said overlappping time
	//will be just as if they didnt overlapp and collision occoured at the moment they tocuh and time moved forward
	//correction: use the contactpoint between the entity shapes to apply physics to said shapes ( take in count what type both of entities are; static/movable)
	//THEN move time forward

	//moves them back to contact point with original speed
	inputEntity1.setPosition(inputEntity1.getPosition() + Vec2D(entity1V0.getX() * -overlapTime, entity1V0.getY() * -overlapTime));
	inputEntity2.setPosition(inputEntity2.getPosition() + Vec2D(entity2V0.getX() * -overlapTime, entity2V0.getY() * -overlapTime));



	//HANDLE PHYSICS YO, torque etc, take use of contactpoint


	//move time forward, time = overlaptime, with new speed
	inputEntity1.setPosition(inputEntity1.getPosition() + Vec2D(entity1Vf.getX() * overlapTime, entity1Vf.getY() * overlapTime));
	inputEntity2.setPosition(inputEntity2.getPosition() + Vec2D(entity2Vf.getX() * overlapTime, entity2Vf.getY() * overlapTime));

}

void EntityHandler::updateEntities(float deltaTime) //updates all entities, checks for collisions, handles collisioons
{
	//update forces - force - acc - vel - pos - reset forces ( let forces accumulate from now unti next logictick)
	//then check for collision between entities after they have been moved

	//go through and update each of the entiteis one by one
	for (Entity& e : entities)
	{
		//if it is a movable entity

			updateActingForces(e);
			updateAcceleration(e);
			updateVelocity(e);
			updatePreviousEntityData(e);
			updatePosition(deltaTime, e);
			clearActingForces(e);
	
			if(e.getEntityID() == 1)
		    	e.setPosition(e.getPosition() + Vec2D(0 ,0.08 ));
	}

	//check for collisions
	for (Entity& e : entities)
	{
		//retrive entity from quadtree
		//
		//
		//


		//temp bruteforce check fornow
		for (unsigned int i = 0; i < entities.size(); i++)
		{
		
			//checks so the entiteis are defined and that collisions are not being checked with one entity and itself
			if ((e.getEntityID() != -1) 
				&& (entities[i].getEntityID() != -1)
				&& (e.getEntityID() != entities[i].getEntityID()))
			{
				if (minskowskiDifferenceAABBCollisionCheck(e, entities[i]) == true)
				{
					//entiteis are possibly colliding

					std::cout << "\ntouch" << std::endl;
					std::cin.get();

					////continue and try SAT collision method to be sure
					//if (satCheck.SATCheck(e, entities[i]))
					//{
					//	//entities are definity inside of eachother
					//
					//	//handle collison logic
					//	entityCollision(e, entities[i], satCheck.getPenentrationVector(), satCheck.getContactPoint());
					//}
				}
			}
		 }
		}

	}


void EntityHandler::updateAcceleration(Entity& inputEntity) //updates acceleration on entitis
{
	//get resulting force of each entity and use F = ma, a = F/m

		Vec2D resultingForce;

		for (Vec2D& f : inputEntity.getActingForces())
		{
			resultingForce += f;
		}

		inputEntity.setAcceleration(Vec2D(resultingForce.getX() / inputEntity.getMass(), resultingForce.getY() / inputEntity.getMass()));
}
void EntityHandler::updateVelocity(Entity& inputEntity) //updates velócitiyes on entiteis
{
	
	    inputEntity.setVelocity(Vec2D(inputEntity.getVelocity().getX() + inputEntity.getAcceleration().getX(), inputEntity.getVelocity().getY() + inputEntity.getAcceleration().getY()));
	//	std::cout << inputEntity.getVelocity().getY() << std::endl; std::cin.get();
}
void EntityHandler::updatePosition(const float deltaTime, Entity& inputEntity)
{
	
	    inputEntity.setPosition(inputEntity.getPosition() + inputEntity.getVelocity().scaleVector(deltaTime));
		
		//std::cout << "x:" << e.getPosition().getX() + e.getAcceleration().getX() << " y:" << e.getPosition().getY() + e.getAcceleration().getY() << std::endl;
		//std::cin.get();
	
}
void EntityHandler::updateActingForces(Entity& inputEntity)
{
	//add gravity, air resitance etc..

		//F = mg
	    inputEntity.addForce(Vec2D(gravitationalAcceleration.getX() * inputEntity.getMass(), gravitationalAcceleration.getY() * inputEntity.getMass()));

}
void EntityHandler::clearActingForces(Entity& inputEntity)
{
	std::vector<Vec2D> a; //has no values

	inputEntity.setActingForces(a);
}
void EntityHandler::updatePreviousEntityData(Entity& inputEntity)
{
	inputEntity.setPreviousPosition(inputEntity.getPosition());
	
	inputEntity.setPreviousVelocity(inputEntity.getVelocity());
	//inputEntity.setPreviousRotation(inputEntity.getVertexShape().get)
}
					   //add entites
void EntityHandler::addEntity(Entity inputEntity) //adds the entity to the list of entities
{
	entities.push_back(inputEntity);
}
									//get functions
float EntityHandler::getWorldMaxX()
{
	return worldMaxX;
}
float EntityHandler::getworldMinX()
{
	return worldMinX;
}
float EntityHandler::getWorldMaxY()
{
	return worldMaxY;
}
float EntityHandler::getWorldMinY()
{
	return worldMinY;
}
void EntityHandler::init(const float inputMaxX, const float inputMinX, const float inputMaxY, const float inputMinY)
{
	worldMaxX = inputMaxX;
	worldMinX = inputMinX;
	worldMaxY = inputMaxY;
	worldMinY = inputMinY;
}


std::vector<Entity> EntityHandler::getAllEntities() //retirives all entiteis in pe 
{
	return entities;
}

EntityHandler::EntityHandler()
	:
	worldMaxX(0),
	worldMinX(0),
	worldMaxY(0),
	worldMinY(0),

	gravitationalAcceleration(0.0f, 0.0f)
{
}
