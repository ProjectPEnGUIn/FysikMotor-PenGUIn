#include "EntityHandler.h"

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
float EntityHandler::getAirDensity(const float inputHeight) const
{

	//asume air density 1.225 for now https://en.wikipedia.org/wiki/Density_of_air 28/1

	return float(1.25f);
}
Vec2D EntityHandler::getAirResistance(const Vec2D& inputVelocity, const float inputDragCoefficient, const float inputSillhouetteArea, const float inputHeight) const //returns the air resistance force vector
{
	//F = C * ( (A * airDensity * V^2)/2
	//ifrån utdelat häfte, inte säker ännu om det är hastighet nu eller hastighet nu+1tick som används

	return Vec2D(inputDragCoefficient * ((inputSillhouetteArea * getAirDensity(inputHeight) * inputVelocity.getX() * inputVelocity.getX()) / 2.0f), inputDragCoefficient * ((inputSillhouetteArea * getAirDensity(inputHeight) * inputVelocity.getY() * inputVelocity.getY()) / 2.0f));
}
void EntityHandler::updateEntities(const float deltaTime) //updates all entities, checks for collisions, handles collisioons
{
	//update forces - force - acc - vel - pos - reset forces ( let forces accumulate from now unti next logictick)
	//then check for collision between entities after they have been moved

	//go through and update each of the entiteis one by one

	tempElapsedTime += deltaTime;

	for (Entity& e : entities)
	{

		if (e.getIsColliding() == true)
		{

			std::cout << "paused; press enter\n";

			std::cin.get();

			e.setIsColliding(false);
		}

		if (e.getIsColliding() == 1)
		{
			//std::cout << "press enter\n" << std::endl;
			//std::cin.get();
			e.setIsColliding(false);
		}

		//if it is a movable entity
		if (e.getEntityState() == 1)
		{
			clearActingForces(e);
			updateActingForces(e);
			updateAcceleration(e);
			updateVelocity(e, deltaTime);
			updatePreviousEntityData(e);
			updatePosition(deltaTime, e);
			
		}

		//std::cout << e.getEntityID() << " " << e.getVertexShape().getVertices().size() << std::endl;
	}

	//check for collisions
	for (Entity& e : entities)
	{
		if (e.getEntityState() == 1)
		{
			//temp bruteforce check for now
			for (unsigned int i = 0; i < entities.size(); i++)
			{
				//checks so the entiteis are defined and that collisions are not being checked with one entity and itself
				if ((e.getEntityID() != -1)
					&& (entities[i].getEntityID() != -1)
					&& (e.getEntityID() != entities[i].getEntityID()))
				{

					SATCollisionCheck satCheck;
					
					if (satCheck.SATCheck(e.getVertexShape(), entities[i].getVertexShape()) == true)
					{
						std::cout << "SAT collision has occoured\n";

					//	std::cout << satCheck.getPenentrationVector().getX() << " " << satCheck.getPenentrationVector().getY() << " magnitutde:" << satCheck.getPenentrationVector().getMagnitude() << " overlap:" << satCheck.getOverlap() << " rotation:"<< satCheck.getPenentrationVector().getDirectionDEGREES() <<  std::endl;
					//	std::cin.get();

						std::cout << "Penentration depth:" << satCheck.getPenentrationVector().getMagnitude() << " angle: " << satCheck.getPenentrationVector().getDirectionDEGREES()<< " x:" << satCheck.getPenentrationVector().getX() << " y:" << satCheck.getPenentrationVector().getY() << std::endl;
						std::cout << "Amount of contactpoints:" << satCheck.getContactPoints().size() << std::endl;
						for (unsigned int i = 0; i < satCheck.getContactPoints().size(); i++)
						{
							std::cout << "point" << i << " x:" << satCheck.getContactPoints()[i].getX() << " y:" << satCheck.getContactPoints()[i].getY() << std::endl;
						}
					//	e.setPosition(e.getPosition() + satCheck.getPenentrationVector());

						e.setIsColliding(true);
					}
					
				//	std::cin.get();
				//	for (const Vec2D& v :  e.getVertexShape().getVertices())
				//	{
				//		std::cout << "x:" << v.getX() << " y:" << v.getY() << std::endl;
				//	}
				//	std::cout << std::endl;
				//	for (const Vec2D& v : entities[i].getVertexShape().getVertices())
				//	{
				//		std::cout << "x:" << v.getX() << " y:" << v.getY() << std::endl;
				//	}
				//	std::cin.get();


					//if (minskowskiDifferenceAABBCollisionCheck(e, entities[i]) == true)
					//{
					//	//entiteis are directly coliding
					//
					//	std::cout << "Entities have directly collided " << e.getPosition().getY() << " lastPos" << e.getPreviousPosition().getY() << " vy " << e.getVelocity().getY() << " time:" << tempElapsedTime << std::endl;
					//	e.setIsColliding(true);
					////	std::cin.get();
					//
					//}
					//else if (sweptMinskowskiDifferenceAABBCollisionCheck(e, entities[i], deltaTime) == true)
					//{
					//	//entiteis have colided this tick
					//	std::cout << "Entities collided this tick nut passed through eachother " << "currentPos " << e.getPosition().getY() << " lastPos" << e.getPreviousPosition().getY() << " vy " << e.getVelocity().getY() <<  " time:" << tempElapsedTime << std::endl;
					//	e.setIsColliding(true);
					//	//	std::cin.get();
					//
					//}
				}
			}
		}
	}

}


void EntityHandler::updateAcceleration(Entity& inputEntity) //updates acceleration on entitis
{
	//get resulting force of each entity and use F = ma, a = F/m

	
	//	inputEntity.setAcceleration(Vec2D(resultingForce.getX() / inputEntity.getMass(), resultingForce.getY() / inputEntity.getMass()));
}
void EntityHandler::updateVelocity(Entity& inputEntity, const float InputDeltaTime) //updates velócitiyes on entiteis
{
	
	    inputEntity.setVelocity(Vec2D(inputEntity.getVelocity().getX() + ((inputEntity.getResultingForce().getX() * InputDeltaTime) / inputEntity.getMass()), inputEntity.getVelocity().getY() + ((inputEntity.getResultingForce().getY() * InputDeltaTime) / inputEntity.getMass())));
	
		
		//	std::cout << inputEntity.getVelocity().getY() << std::endl; std::cin.get();
}
void EntityHandler::updatePosition(const float deltaTime, Entity& inputEntity)
{
	
	    inputEntity.setPosition(inputEntity.getPosition() + inputEntity.getVelocity().scaleVector(deltaTime));
	
}
void EntityHandler::updateActingForces(Entity& inputEntity)
{
	//add gravity, air resitance etc..

		//F = mg
	

		Vec2D resultingForce;

		//add gravity force
		inputEntity.addForce(Force(Vec2D(gravitationalAcceleration.getX() * inputEntity.getMass(), gravitationalAcceleration.getY() * inputEntity.getMass()), Vec2D(0, 0)));
		
		//add air resistance
		//inputEntity.addForce(getAirResistance(inputEntity.getVelocity(), inputEntity.getDragCoefficient(), 12.56f, inputEntity.getPosition().getY()));

		for (const Force& f : inputEntity.getForces())
		{
			resultingForce += f.getForce();
		}

		inputEntity.setResultingForce(resultingForce);
}
void EntityHandler::clearActingForces(Entity& inputEntity)
{
	std::vector<Force> a; //has no values

	inputEntity.setResultingForce(Vec2D(0, 0));
	inputEntity.setForces(a);
}
void EntityHandler::updatePreviousEntityData(Entity& inputEntity)
{
	inputEntity.setPreviousPosition(inputEntity.getPosition());
	
	inputEntity.setPreviousVelocity(inputEntity.getVelocity());
	//inputEntity.setPreviousRotation(inputEntity.getVertexShape().get)

	//Saves the aabb boundries pos before position is updated with new velocity
	inputEntity.setPreviousAABBTL(inputEntity.getAABBTopLeft());
	inputEntity.setPreviousAABBBR(inputEntity.getAABBMBottomRight());


	//std::cout << "width " << inputEntity.getPreviousAABBBR().getX() - inputEntity.getPreviousAABBTL().getX() << " height " << inputEntity.getPreviousAABBTL().getY() - inputEntity.getPreviousAABBBR().getY() << std::endl;
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

	gravitationalAcceleration(0.0f, 0.0f),

	temp(false),
	tempElapsedTime(0.0f)
{
}
