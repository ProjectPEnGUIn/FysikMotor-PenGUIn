#include "EntityHandler.h"

////collision countermeasures

void EntityHandler::impulseCollision(Entity& e1, Entity& e2) //resolves collision
{
	// https://en.wikipedia.org/wiki/Coefficient_of_restitution 26/2 2017


	//1: change linear velocities
	Vec2D e1Vf, e2Vf; //final velocities

	//approximating CoR
	float cor = (e1.getRestitutionCoefficient() + e2.getRestitutionCoefficient()) / 2.0f; //coeficcient of restitution

	e1Vf.setX((e1.getMass() * e1.getVelocity().getX() + e2.getMass() * e2.getVelocity().getX() + e2.getMass() * cor * (e2.getVelocity().getX() - e1.getVelocity().getX())) / (e1.getMass() + e2.getMass()));
	e1Vf.setY((e1.getMass() * e1.getVelocity().getY() + e2.getMass() * e2.getVelocity().getY() + e2.getMass() * cor * (e2.getVelocity().getY() - e1.getVelocity().getY())) / (e1.getMass() + e2.getMass()));

	e2Vf.setX((e1.getMass() * e1.getVelocity().getX() + e2.getMass() * e2.getVelocity().getX() + e1.getMass() * cor * (e1.getVelocity().getX() - e2.getVelocity().getX())) / (e1.getMass() + e2.getMass()));
	e2Vf.setY((e1.getMass() * e1.getVelocity().getY() + e2.getMass() * e2.getVelocity().getY() + e1.getMass() * cor * (e1.getVelocity().getY() - e2.getVelocity().getY())) / (e1.getMass() + e2.getMass()));

	//2: change rotational velocityies etc


	//3: apply values to entiteis if they are NOT static


	Vec2D e1Old = e1.getVelocity(), e2Old = e2.getVelocity();

	//std::cout << "----\nE1 old: " << e1Old.getX() << " " << e1Old.getY() <<
	//	"\nE1 new: " << e1Vf.getX() << " " << e1Vf.getY() <<
	//	"\nE2 old: " << e2Old.getX() << " " << e2Old.getY() <<
	//	"\nE2 new: " << e2Vf.getX() << " " << e2Vf.getY() << "\nCoR: " << cor << "\n---------";
//	std::cin.get();


	if (e1.getEntityState() != 0)
	{
		e1.setVelocity(e1Vf);
	}

	if (e2.getEntityState() != 0)
	{
		e2.setVelocity(e2Vf);
	}


}
void EntityHandler::elapseTime(Entity& inputEntity, const float deltaTime) //elapses time for the entitiy
{
	
}
float EntityHandler::getAirDensity(const float inputHeight) const
{

	//asume air density 1.225 for now https://en.wikipedia.org/wiki/Density_of_air 28/1

	return float(1.25f);
}
Vec2D EntityHandler::getAirDragForce(const Vec2D& inputVelocity, const float inputDragCoefficient, const float inputSillhouetteArea, const float inputHeight) const //returns the air resistance force vector
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

		if (e.getIsColliding() == 1)
		{
			std::cout << "press enter\n" << std::endl;
			std::cin.get();
			e.setIsColliding(false);
			
		}

		//if it is a movable entity
		if (e.getEntityState() == 1)
		{
		
			updateAcceleration(e);
			updateVelocity(e, deltaTime);
			updatePreviousEntityData(e);
			updatePosition(deltaTime, e);
			clearActingForces(e);
			updateActingForces(e);
			
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
					//various collision checks

					SATCollisionCheck collisionTest;

						if ( minskowskiDifferenceAABBCollisionCheck(e, entities[i]) == true || sweptMinskowskiDifferenceAABBCollisionCheck(e, entities[i], deltaTime) == true)
					{
						
					
						//do a binary SAT search / multisapling, check for collison at different intervals during this tick, may result in errors with fast movign objects						
					   //increase elapsedTime up until it reaches deltaTime, if no collision has been found  they probably did not collide during this tick
					
						//copies their bodies
						VertexShape shape1 = e.getVertexShape(),
							shape2 = entities[i].getVertexShape();
					
						//places the bodies at where they were at the start of the tick
						shape1.setPosition(e.getPreviousPosition());
						shape2.setPosition(entities[i].getPreviousPosition());
	
	
					//	//TODO; make timefactor the right interval
					//	float s1halfsize = (shape1.getBottomRightAABBCorner() - shape1.getTopLeftAABBCorner()).getMagnitude() / 2,
					//		s2halfsize = (shape2.getBottomRightAABBCorner() - shape2.getTopLeftAABBCorner()).getMagnitude() / 2,
					//		minSize = s1halfsize <= s2halfsize ? s1halfsize : s2halfsize; //min "radius" from center, checks should be at an interval lesser than this, s = vt, use this to decide proper timefactor, t = s/v(greatest)
					//	//	maxVelocity = (e.getVelocity().getMagnitude() > entities[i].getVelocity().getMagnitude()) ? e.getVelocity().getMagnitude() : entities[i].getVelocity().getMagnitude(),
							
						float timeFactor = deltaTime / 10.0f,
							elapsedTime = 0;
					
						//prevent an endless loop
						int maxIterations = 15, //needs to be fine tuned
							iteration = 0;

						bool done = false;
						while (elapsedTime < deltaTime && done == false && iteration < maxIterations)
						{
							iteration++;

						//	std::cout << "welp fug\n";
					
							//if (elapsedTime + timeFactor > deltaTime)
							//	done = true; //no point in trying to check for collision in next tick during next iteration

							if (collisionTest.SATCheck(shape1, shape2))
							{

								//	std::cout << "HIT\n" << std::endl;

									//collision detected
									//do logic just as normal

								done = true; //wont iterate another time


								//HANDLE LOGIC
								Vec2D normal = collisionTest.getPenentrationVector().getNormalisation(); //lenght = 1
								//	https://en.wikipedia.org/wiki/Vector_projection 1/3 2017
								//project e velocity onto normal axis
								float e1Proj = (e.getVelocity() * normal),
									e2Proj = (entities[i].getVelocity() * normal);

								float overlapTime = FLT_MAX;
								if (e1Proj + e2Proj == 0)
									overlapTime = collisionTest.getOverlap(); //NOT SURE IF THIS IS RIGHT BUT IT WORKS ¯\_(´_` )_/¯
								else
									overlapTime = fabs(collisionTest.getOverlap() / (e1Proj + e2Proj)); //the time that they have been overlapping for

								elapsedTime -= overlapTime;

							//	std::cout << "-----------\n";
							//	std::cout << "normal: " << collisionTest.getPenentrationVector().getX() << " " << collisionTest.getPenentrationVector().getY() << " angle: " << collisionTest.getPenentrationVector().getDirectionDEGREES() << std::endl;
							//	std::cout << "collided this tick: " << collisionTest.getCollisionBetweenTicks() << std::endl;
							//	std::cout << "time: " << collisionTest.getCollisionTime() << std::endl;
							//	std::cout << "-----------\n" << std::endl;
							//	std::cout << "gloabltimestep: " << deltaTime << std::endl;
							//
							//	std::cout << "e v: " << e.getVelocity().getX() << " " << e.getVelocity().getY() << " e[i] v: " << entities[i].getVelocity().getX() << " " << entities[i].getVelocity().getY() << std::endl;
							//	std::cout << "vproj: eproj: " << e1Proj << " e[i]proj: " << e2Proj << std::endl;
							//	std::cout << "proj sum: " << fabs(e1Proj + e2Proj) <<
							//		"\nOverlaptime: " << overlapTime << std::endl;
							//	std::cout << "penentration depth: " << collisionTest.getOverlap() << std::endl;
							//	std::cout << "v1 * t + v2 * t: " << e1Proj * overlapTime + e2Proj*overlapTime << " <- must take the absolute value, fabs" << std::endl;
							//	std::cout << "elapsed: " << elapsedTime << std::endl;

								//move the entities back to when they were not íntersecting using the time calculated
								if (e.getEntityState() != 0)
									e.setPosition(e.getPreviousPosition() + (e.getVelocity() * elapsedTime));

								if (entities[i].getEntityState() != 0)
									entities[i].setPosition(entities[i].getPreviousPosition() + (entities[i].getVelocity() * elapsedTime));

								//do the impulse collision for linear movement
								impulseCollision(e, entities[i]);

								//do the impulse?? collision for angular movement
								//TODO


								//add force and corresponding antiforce to each entity, calc friction

								Vec2D e1Fr = e.getResultingForce(),
									e2Fr = entities[i].getResultingForce();

								//e acts on e[i] with its Fr
								entities[i].addForce(Force(e1Fr, Vec2D(0, 0))); 
								//e[i] excerts a force (back?) on e, split it up in two seperate forces
								e.addForce(Force(e1Fr * sin(collisionTest.getEdge2().getDirectionRADIANS()), Vec2D(0, 0))); //x part of that force
								e.addForce(Force(e1Fr * cos(collisionTest.getEdge2().getDirectionRADIANS()), Vec2D(0, 0))); //y part of that force


								//std::cout << "rad: " << collisionTest.getEdge2().getDirectionDEGREES() << std::endl;
								//
								//std::cout << e.getForces().size() << std::endl;
								//for (unsigned int i = 0; i < e.getForces().size(); i++)
								//{
								//	std::cout << e.getForces()[i].getForce().getX() << " " << e.getForces()[i].getForce().getY() << std::endl;
								//}
								//std::cin.get();

								float remainingTime = deltaTime - elapsedTime; //the amount of time left in this tick
								if (remainingTime > 0)
								{
									//move time forward for each entity

									//update linear / angular movement
								}
							}
							else
							{
								//check at a later interval
					
								//add more time
							//	if(elapsedTime + timeFactor < deltaTime)
							//    	elapsedTime += timeFactor;
					
								//pos = pos + distance, distance = velocity * time
								shape1.setPosition(shape1.getCenterPos() + (e.getVelocity() * timeFactor));
								shape2.setPosition(shape2.getCenterPos() + (entities[i].getVelocity() * timeFactor));
							}
						}
					
					}
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
	worldMaxX(FLT_MAX),
	worldMinX(-FLT_MAX),
	worldMaxY(FLT_MAX),
	worldMinY(-FLT_MAX),

	gravitationalAcceleration(0.0f, -9.82f),

	temp(false),
	tempElapsedTime(0.0f)
{
}
