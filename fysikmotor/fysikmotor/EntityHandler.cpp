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


//	Vec2D e1Old = e1.getVelocity(), e2Old = e2.getVelocity();

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
//TODO may not be needed	
}
void EntityHandler::updateResultingForce(Entity& e)
{
	Vec2D resultingForce;
//	std::cout << e.getForces().size() << std::endl;
//	std::cin.get();
	for (const Force& f : e.getForces())
	{
		resultingForce += f.getForce();
	}

	e.setResultingForce(resultingForce);
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
	tempElapsedTime += deltaTime;

	//update entities
	for (Entity& e : entities)
	{
	//	if (e.getVelocity().getY() < -20)
	//		std::cin.get();
	//	std::cout << "v: " << e.getVelocity().getX() << " " << e.getVelocity().getY() << std::endl;


		//if it is a movable entity
		if (e.getEntityState() == 1) //only update movable entities
		{

		//	std::cout << "v: " << e.getVelocity().getX() << std::endl;

			clearActingForces(e);
			updateActingForces(e); //also updates resultingforce FYI
			updateVelocity(e, deltaTime);
			//TODO ANGULAR THINGIES
			updatePreviousEntityData(e);
			updatePosition(deltaTime, e);


		//	if (tempElapsedTime > 5)
		//		std::cin.get();

		}
		else if (e.getEntityState() == 0)
			clearActingForces(e); //removes the forces, forces on static objects is only used for drawing to see where they are applied
	}

	//check for collisions //simple O(N^N) check, could easily be optimised
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
							
						float timeFactor = deltaTime / 15.0f,
							elapsedTime = 0;
					
						//prevent an endless loop
						int maxIterations = 16, //needs to be fine tuned
							iteration = 0;

						bool done = false;
						while (elapsedTime < deltaTime && done == false && iteration < maxIterations)
						{
							iteration++;

							if (collisionTest.SATCheck(shape1, shape2))
							{
									//collision detected
									//do logic just as normal

								done = true; //wont iterate another time

								//Find time of impact
								Vec2D normal = collisionTest.getPenentrationVector().getNormalisation(); //lenght = 1
								//	https://en.wikipedia.org/wiki/Vector_projection 1/3 2017
							    //project e velocity onto normal axis
								float e1Proj = (e.getVelocity() * normal),
									e2Proj = (entities[i].getVelocity() * normal);

								float overlapTime = FLT_MAX;
								if (e1Proj + e2Proj == 0 && collisionTest.getOverlap() != 0.0f)
									overlapTime = collisionTest.getOverlap()/2; //NOT SURE IF THIS IS RIGHT BUT IT WORKS ¯\_(´_` )_/¯
								else if (collisionTest.getOverlap() != 0.0f)
									overlapTime = fabs(collisionTest.getOverlap() / (e1Proj + e2Proj)); //the time that they have been overlapping for
								else
									overlapTime = 0;

								//std::cout << "et: " << elapsedTime << std::endl;
								elapsedTime -= overlapTime;
								//std::cout << "et - ot: " << elapsedTime << std::endl;
								//
								//move the entities to when they were not íntersecting using the time calculated
								if (e.getEntityState() != 0)
									e.setPosition(e.getPreviousPosition() + (e.getVelocity() * (elapsedTime)));
								
								if (entities[i].getEntityState() != 0)
									entities[i].setPosition(entities[i].getPreviousPosition() + (entities[i].getVelocity() * (elapsedTime)));
								

								//do the impulse collision for linear movement
								impulseCollision(e, entities[i]);

								//do the impulse?? collision for angular movement
								//TODO


								////add forces acting on both objects
								//Vec2D force = e.getResultingForce(),
								//	totalNormalForce = force.getRotatedVectorDEGREES(collisionTest.getEdge2().getDirectionDEGREES()).getAntiClockWiseNormal().getAntiClockWiseNormal(),
								//	normalForcex = Vec2D(totalNormalForce.getX(), 0).getRotatedVectorDEGREES(collisionTest.getEdge2().getDirectionDEGREES()),
								//	normalForcey = Vec2D(0, totalNormalForce.getY()).getRotatedVectorDEGREES(collisionTest.getEdge2().getDirectionDEGREES());
								//
								//
								//float frictionForceSize = totalNormalForce.getMagnitude() * cos(collisionTest.getEdge2().getDirectionRADIANS()) * ((e.getFrictionCoefficient() + entities[i].getFrictionCoefficient()) / 2);
								//
								////e acts on e[i] with this force
						    	//entities[i].addForce(Force(Vec2D(0, normalForcey.getAntiClockWiseNormal().getAntiClockWiseNormal().getY()), Vec2D(), "Normal Y component", sf::Color::Green));  //rotates it 180 degrees and applies to e[i]
								//
								////only apply friction if the force in the direction is great enoug
								////TODO: SPlit up forces into sepeate forces, will then see the frictionforce acting in the right direction
								//
								//if (frictionForceSize > normalForcex.getMagnitude())
								//	normalForcex.setVectorMagnitude(normalForcex.getMagnitude() - frictionForceSize);
								//else
								//	normalForcex.setVectorMagnitude(0);
								//
								//e.addForce(Force(normalForcex, Vec2D(), "ttt", sf::Color::Cyan));
								//e.addForce(Force(normalForcey, Vec2D(), "ygktrg", sf::Color::Magenta));

								float angle = collisionTest.getEdge2().getDirectionRADIANS(); //change it to difference between force and plane??? IDK

								Vec2D force = e.getResultingForce(), //IS THIS RIGHt??
									edge = collisionTest.getEdge2().getNormalisation(),
									normalAxis = edge.getAntiClockWiseNormal(), //in the direction of collison normal
									parallellAxis = edge.getAntiClockWiseNormal().getAntiClockWiseNormal(), //parallell to the edge and normal to normalaxis
									forceOnNormalAxis1 = normalAxis,
									//forceOnNormalAxis2 = normalAxis,
									forceOnParallellAxis1 = parallellAxis;
								//	forceOnParallellAxis2 = parallellAxis;
							
								//forceOnNormalAxis1.setVectorMagnitude(force.getY() * cos(angle));
								//forceOnNormalAxis2.setVectorMagnitude(force.getX() * cos(angle));
								//forceOnParallellAxis1.setVectorMagnitude(force.getY() * sin(angle));
								//forceOnParallellAxis2.setVectorMagnitude(force.getX() * sin(angle));
								
								
								forceOnNormalAxis1.setVectorMagnitude(force.getMagnitude() * cos(angle));
								forceOnParallellAxis1.setVectorMagnitude(force.getMagnitude() * sin(angle));
							//	std::cout << "angle: " << angle << std::endl;

								e.addForce(Force(forceOnNormalAxis1, Vec2D()));
								e.addForce(Force(forceOnParallellAxis1, Vec2D()));
								entities[i].addForce(Force(forceOnNormalAxis1.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D()));
							//	entities[i].addForce(Force(forceOnParallellAxis1.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D()));
								//std::cout << "FORCE; " << force.getX() << " " << force.getY() << std::endl;
								//std::cout << forceOnNormalAxis1.getMagnitude() << " " << forceOnParallellAxis1.getMagnitude() << std::endl;
								//std::cout << forceOnNormalAxis1.getDirectionDEGREES() << " " << forceOnParallellAxis1.getDirectionDEGREES() << std::endl;
								//std::cin.get();

								//Vec2D fR = forceOnNormalAxis1 + forceOnParallellAxis1 + forceOnNormalAxis2 + forceOnParallellAxis2;
						//		Vec2D fR = forceOnNormalAxis1 + forceOnParallellAxis1;
							
								//fR.setXY(cos(angle)*fR.getX() - sin(angle) * fR.getY(), sin(angle) * fR.getX() + cos(angle) * fR.getY());
							
								//std::cout<<"f: " << fR.getX() << " " << fR.getY() << std::endl;
							//	sstd::cin.get();
								//std::cout << "flipped f: " << fR.getAntiClockWiseNormal().getAntiClockWiseNormal().getX() << " " << fR.getAntiClockWiseNormal().getAntiClockWiseNormal().getY() << std::endl;
							//	std::cin.get();

								//entities[i].addForce(Force(fR, Vec2D(), " ", sf::Color::Cyan));
								//e.addForce(Force(fR.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), " ", sf::Color::Cyan));

		//maybe it works idk

							
								

								float remainingTime = deltaTime - elapsedTime; //the amount of time left in this tick
								if (remainingTime > 0)
								{
									//wrong with ramongin time???

								    //remainingTime = 1;

									std::cout << "time left in tick: "<< remainingTime << std::endl;
									//move time forward for each entity

									//std::cin.get();
									//For e
									//e.addForce(Force(Vec2D(-gravitationalAcceleration.getX() * e.getMass(), -gravitationalAcceleration.getY() * e.getMass()), Vec2D(0, 0), "Gravity"));

									updateResultingForce(e);
									//std::cout << e.getResultingForce().getX() << " " << e.getResultingForce().getY();
									//std::cin.get();

									updateVelocity(e, remainingTime);
									//TODO UPDATE ANGULAR THINGY
									updatePosition(remainingTime, e);

									//For e[i]
									updateResultingForce(entities[i]); //Only updates the resulting forces
									updateVelocity(entities[i], remainingTime);
									//TODO UPDATE ANGULAR THINGY

									updatePosition(remainingTime, entities[i]);

								}
							
							}
							else
							{
								//check at a later interval
					
								//add more time
								if (elapsedTime + timeFactor < deltaTime)
									elapsedTime += timeFactor;
								else
									done = true;
					
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


//void EntityHandler::updateAcceleration(Entity& inputEntity) //updates acceleration on entitis
//{
//	//get resulting force of each entity and use F = ma, a = F/m
//
//	
//	//	inputEntity.setAcceleration(Vec2D(resultingForce.getX() / inputEntity.getMass(), resultingForce.getY() / inputEntity.getMass()));
//}
void EntityHandler::updateVelocity(Entity& inputEntity, const float InputDeltaTime) //updates velócitiyes on entiteis
{
	if (inputEntity.getEntityState() != 0)
	{
		inputEntity.setVelocity(Vec2D(inputEntity.getVelocity().getX() + ((inputEntity.getResultingForce().getX() * InputDeltaTime) / inputEntity.getMass()), inputEntity.getVelocity().getY() + ((inputEntity.getResultingForce().getY() * InputDeltaTime) / inputEntity.getMass())));
	}
}
void EntityHandler::updatePosition(const float deltaTime, Entity& inputEntity)
{	
	if (inputEntity.getEntityState() != 0)
	{
		inputEntity.setPosition(inputEntity.getPosition() + inputEntity.getVelocity().scaleVector(deltaTime));
	}
}
void EntityHandler::updateActingForces(Entity& inputEntity)
{
	//add gravity, air resitance etc..

		//F = mg
	if (inputEntity.getEntityState() != 0)
	{

		Vec2D resultingForce;

		//add gravity force
		inputEntity.addForce(Force(Vec2D(gravitationalAcceleration.getX() * inputEntity.getMass(), gravitationalAcceleration.getY() * inputEntity.getMass()), Vec2D(0, 0), "Gravity"));

		//add air resistance
		//TODO: calc silluhuete area
	//	error: goes to infinity reeeeal quick.
	//	inputEntity.addForce(Force(getAirDragForce(inputEntity.getVelocity(), inputEntity.getDragCoefficient(), 10, inputEntity.getPosition().getY()).getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Air drag"));

		//std::cout << getAirDragForce(inputEntity.getVelocity(), inputEntity.getDragCoefficient(), 10, inputEntity.getPosition().getY()).getX() << " " << getAirDragForce(inputEntity.getVelocity(), inputEntity.getDragCoefficient(), 10, inputEntity.getPosition().getY()).getY() << std::endl;

		for (const Force& f : inputEntity.getForces())
		{
			resultingForce += f.getForce();
		}

		inputEntity.setResultingForce(resultingForce);
	}
	else if (inputEntity.getEntityState() == 0) //STATIC 
		inputEntity.setResultingForce(Vec2D());
}
void EntityHandler::clearActingForces(Entity& inputEntity)
{

	inputEntity.setResultingForce(Vec2D(0, 0));
	inputEntity.setForces(std::vector<Force>{});
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
