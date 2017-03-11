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
void EntityHandler::elapseEntityTime(Entity& inputEntity, const float time) //elapses time for entity
{
	//NOTE: used in update function soley, uses previous velocity which is needed in that case
	if(inputEntity.getEntityState() != 0)
	  inputEntity.setPosition(inputEntity.getPosition() + (inputEntity.getPreviousVelocity() * time));
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

//	//using physics update order from this
//	//http://buildnewgames.com/gamephysics/ 8/3 2017
//
//	//1: Add forces
//	//1.1 gravity
//	//1.2 air drag
//	//1.3 forces that other objects are excerting
//	//2. Calc velocity
//	//3. calc position
//	//4. go back to 1
//
//    //	//add gravity and air drag
//    	for (Entity& e : entities)
//    	{
//    
//    		if (e.getIsColliding())
//    		{ }
//    		//	std::cin.get();
//    
//    		clearActingForces(e);
//    		updateActingForces(e);
//    	}
//    
//    	//1.3 use collisioncheck to check what forces to excert on other objects
//    	//TODO: HOW TO HANDLE TIMELOSS?? 
//    
//    	for (Entity& e : entities)
//    	{
//    		for (Entity& e2 : entities)
//    		{
//    
//    			if (e.getEntityID() != -1 && e2.getEntityID() != -1 //both entities are defined
//    				&& e.getEntityID() != e2.getEntityID() //entite wonth check collision with itself
//    				&& e.getEntityState() != 0) //e is not a static entity 
//    			{
//    				//do a supersamplig/binary search SAT check to find collision
//    
//    			
//    				//broad phase check
//    				if(minskowskiDifferenceAABBCollisionCheck(e, e2) == true || sweptMinskowskiDifferenceAABBCollisionCheck(e, e2, deltaTime) == true)
//    				{
//    
//    					//accurate narrowphase check between one entity and another
//    					// TODO: //use this algorithm in a supersampling/binary collison check search to get a very close correct time of collision
//    					SATCollisionCheck collisionCheck;
//    
//    					VertexShape shape1 = e.getVertexShape(),
//    						shape2 = e2.getVertexShape();
//    
//    					//try to elapse time and move the shapes forward in this tick in small steps
//    					//use prev vel, <-- errors????
//    
//    					bool done = false;
//    
//    					float elapsedTime = 0.0f,
//    						maxTime = deltaTime, //max time interval to check collisions at
//    						timeIncrementAmount = deltaTime / 20; //TODO: finetune this value
//    
//    					//prevents an endless loop
//    					int iteration = 0,
//    						maxIteration = 20;
//    
//    					while (!done && elapsedTime < maxTime && iteration < maxIteration)
//    					{
//    						iteration++;
//    
//    						if (collisionCheck.SATCheck(shape1, shape2))
//    						{
//    							done = true;
//    
//    							//they are colliding
//    
//    							//1: for how long have they been overlapping? use this to minimize overall timeloss, take this in count when calculating logic in next section
//    							//¯\_(´_`)_ / ¯
//    							//the entities could have been travling inside one another for a certain amount of time before the collision check was done
//    							//will need to take this into count when updating logic furtheron
//    
//    						//	//chooses an axis on which to project their velocitrties on
//    						//	Vec2D projectionAxis = collisionCheck.getPenentrationVector().getNormalisation(); //the axis of least penentration
//    						//
//    						//	float e1VelocityProjection = projectionAxis * e.getVelocity(), //projects the velocities on the axis
//    						//		e2VelocityProjection = projectionAxis * e2.getVelocity();
//    						//
//    						//	float overlapTime = FLT_MAX,
//    						//		overlap = collisionCheck.getOverlap(); //the distance they are overlaping ín the overlapping axis
//    						//
//    						//	//use distance = velocity * time, time = distane/velocity
//    						//	
//    						//	if (e1VelocityProjection + e2VelocityProjection == 0 && overlap != 0.0f)
//    						//		overlapTime = fabs(overlap / (e1VelocityProjection * 2.0f)); //e1proj + e2proj = 0, they are traveling towards eachother with the same velocity
//    						//	else if (overlap != 0.0f)
//    						//		overlapTime = fabs(overlap / (e1VelocityProjection + e2VelocityProjection)); //the time that they have been overlapping for
//    						//	else
//    						//		overlapTime = 0;
//    
//    						//	overlap is wrong
//    
//    							//std::cout << "overlap: " << overlap << std::endl;
//    							//std::cout << "overlaptime: " << overlapTime << std::endl;
//    							//std::cin.get();
//    
//    						//	elapseEntityTime(e, elapsedTime); //moves the entity position back to the time of collision
//    						
//								e.setLostTime(elapsedTime);
//    
//    							//2: Impulsecollision logic
//    							impulseCollision(e, e2); 
//    
//    							//3: Apply forces on both entities
//    						
//    							Vec2D force = e.getResultingForce(), //the force that e excerts on e2
//    							//TAKE e2 IN COUNT OR NOT?
//    								collisionSurfaceEdge = collisionCheck.getEdge2().getNormalisation(),
//    								AxisNormalToCollisionSurface = collisionSurfaceEdge.getAntiClockWiseNormal(),
//    								AxisParallellToCollisionSurface = collisionSurfaceEdge.getAntiClockWiseNormal().getAntiClockWiseNormal(), //flipped 180 degrees
//    								forceOnNormalAxis = AxisNormalToCollisionSurface, //sets the axis on which the force acts on
//    								forceOnParallellAxis = AxisParallellToCollisionSurface, //sets axis
//    								frictionForceOnParallellAxis = AxisParallellToCollisionSurface.getAntiClockWiseNormal().getAntiClockWiseNormal(); //sets axis 180 degrees flipped, frictionforce is in oposite direction
//    
//    							float angle = collisionCheck.getEdge2().getDirectionRADIANS(), //the angle of the plane
//    								normalForce = cos(angle) * force.getMagnitude(),
//    								parallellForce = sin(angle) * force.getMagnitude(),
//    								frictionForce = ((e.getFrictionCoefficient() + e2.getFrictionCoefficient()) / 2) * normalForce;
//    
//    							//Set the correspondign forces that act on each of these axis
//    							forceOnNormalAxis.setVectorMagnitude(normalForce);
//    							
//    							//if parallellforce is greater than frictionforce, set them both to their corresponding values, if parallellforce is less than frictionforce, set frictionforce to parallellforce
//    							(parallellForce > frictionForce) ? forceOnParallellAxis.setVectorMagnitude(parallellForce), frictionForceOnParallellAxis.setVectorMagnitude(frictionForce) : forceOnParallellAxis.setVectorMagnitude(parallellForce), frictionForceOnParallellAxis.setVectorMagnitude(parallellForce);
//    							
//    							//apply the forces on both entities
//    							e.addForce(Force(forceOnNormalAxis, Vec2D(), "Normal Force", sf::Color::Green));
//								if (parallellForce != 0)
//									e.addForce(Force(forceOnParallellAxis, Vec2D(), "Parallell Force", sf::Color::Magenta));
//    							if(frictionForce != 0)
//									e.addForce(Force(frictionForceOnParallellAxis, Vec2D(), "Friction Force", sf::Color::Cyan));
//    
//    							//flipps the forces in the oposite direction
//    							e2.addForce(Force(forceOnNormalAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Normal Force", sf::Color::Green));
//    							if(parallellForce != 0)
//									e2.addForce(Force(forceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Parallell Force", sf::Color::Magenta));
//    							if(frictionForce != 0)
//									e2.addForce(Force(frictionForceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Friction Force", sf::Color::Cyan));
//    
//    
//    						}
//    						else
//    						{
//    							//collision was not found
//    
//    							if (elapsedTime + timeIncrementAmount >= deltaTime)
//    								done = true;
//    							
//    							else
//    								elapsedTime += timeIncrementAmount; //adds more time
//    
//    							//set the shapes' position at the elapsedTimeInterval
//    
//    							//USING VELOCITY FROM OLD TICK; may cause errors?
//    							shape1.setPosition(e.getPosition() + e.getVelocity() * elapsedTime);
//    							shape2.setPosition(e2.getPosition() + e2.getVelocity() * elapsedTime);
//    
//    							//goes back into the while loop and does a collisioncheck with theses values, if false it goes back here where time the gets incrementet
//    						}
//    					}
//    
//    				}
//    
//    			}
//    
//    		}
//    	}
//    
//    //update logic
//	for (Entity& e : entities)
//	{
//		if (e.getEntityState() != 0)
//		{
//			float additionalTime = e.getLostTime();
//			if (additionalTime == FLT_MAX)
//				additionalTime = 0;
//			e.setLostTime(FLT_MAX);
//	
//		//	//update entity to the time of collision
//		//	updateResultingForce(e);
//		//	updateVelocity(e, additionalTime);
//		//	updatePosition(e, additionalTime);
//		
//			//update enttiy
//			updateResultingForce(e);
//			updateVelocity(e, deltaTime);
//			updatePreviousEntityData(e);
//			updatePosition(e, deltaTime);
//			
//			//std::cout << e.getForces().size() << std::endl;
//			std::cout << "dt: " << deltaTime << std::endl;
//			std::cout << e.getResultingForce().getX() << " "<< e.getResultingForce().getY() << std::endl;
//			std::cout << e.getVelocity().getX() << " " << e.getVelocity().getY() << std::endl;
//		}
//	
//	}
//	
//	





	tempElapsedTime += deltaTime;

	//update entities
	for (Entity& e : entities)
	{
	//if it is a movable entity
		if (e.getEntityState() == 1) //only update movable entities
		{
			
			//std::cout << tempVec.getX() << " " << tempVec.getY() << " angle: " << tempVec.getDirectionDEGREES() << std::endl;
			//std::cout << "v: " << e.getVelocity().getX() << " " << e.getVelocity().getY() << std::endl;
			//std::cout << "f: " << e.getResultingForce().getX() << " " << e.getResultingForce().getY() << std::endl;
			//if (e.getVelocity().getX() > 0)
				//std::cin.get();

			clearActingForces(e);
			updateActingForces(e); //also updates resultingforce FYI
			updateVelocity(e, deltaTime);
			updatePreviousEntityData(e);
			updatePosition(e, deltaTime);
		}
		else if (e.getEntityState() == 0)
			clearActingForces(e); //removes the forces, forces on static objects is only used for drawing to see where they are applied, remove them at the start of tick
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

					SATCollisionCheck collisionCheck;

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
							
						float timeFactor = deltaTime / 5.0f,
							elapsedTime = 0;
					
						//prevent an endless loop
						int maxIterations = 15, //needs to be fine tuned
							iteration = 0;

						bool done = false;
						while (elapsedTime < deltaTime && done == false && iteration < maxIterations)
						{
							iteration++;

							if (collisionCheck.SATCheck(shape1, shape2))
							{

								//tempVec = collisionCheck.getPenentrationVector();
								//collision detected
								done = true; //wont iterate another time

								//Find time of impact
								//Vec2D normal = collisionCheck.getPenentrationVector().getNormalisation(); //lenght = 1, this is in the direction of least overlap
								////	https://en.wikipedia.org/wiki/Vector_projection 1/3 2017
							   	//
								////project e velocity onto normal axis
								//Vec2D projectionAxis = collisionCheck.getPenentrationVector().getNormalisation();
								//float e1VelocityProjection= (e.getVelocity() * projectionAxis),
								//	e2VelocityProjection = (entities[i].getVelocity() * projectionAxis);
								//
								//float overlapTime = FLT_MAX,
								//	overlap = collisionCheck.getOverlap();
								//if (e1VelocityProjection + e2VelocityProjection == 0 && overlap != 0.0f)
								//	overlapTime = fabs(overlap /(e1VelocityProjection) * 2); //ADD EXPLANATION
								//else if (overlap != 0.0f)
								//	overlapTime = fabs(overlap / (e1VelocityProjection + e2VelocityProjection)); //the time that they have been overlapping for
								//else
								//	overlapTime = 0;
								//
							
								//elapsedTime -= overlapTime;

								//save overlaptime and apply
						
								//elapsedTime *= 0.95;

								//move the entities to when they were not íntersecting using the time calculated
								if (e.getEntityState() != 0)
									e.setPosition(e.getPreviousPosition() + (e.getVelocity() * elapsedTime));
								
								if (entities[i].getEntityState() != 0)
									entities[i].setPosition(entities[i].getPreviousPosition() + (entities[i].getVelocity() * elapsedTime));
								

								//do the impulse collision for linear movement
							//	impulseCollision(e, entities[i]);   //CAUSES ERROR????

								//add forces that are being excerted on objects
							
								//change it to difference between force and plane??? IDK
							//	Vec2D force = Vec2D(e.getMass() * gravitationalAcceleration.getX(), e.getMass() * gravitationalAcceleration.getY()), //the force that e excerts on e2
							Vec2D force = e.getResultingForce(),
							//TAKE e2 IN COUNT OR NOT?
									//collisionSurfaceEdge = collisionCheck.getEdge2().getNormalisation(),
									collisionSurfaceEdge = tempVec,//TEMMMMPPPPPPPPPPPP-------------------------------------------------------------------------------------------------------
    								AxisNormalToCollisionSurface = collisionSurfaceEdge.getAntiClockWiseNormal(),
    								AxisParallellToCollisionSurface = collisionSurfaceEdge.getAntiClockWiseNormal().getAntiClockWiseNormal(), //flipped 180 degrees
    								forceOnNormalAxis = AxisNormalToCollisionSurface, //sets the axis on which the force acts on
    								forceOnParallellAxis = AxisParallellToCollisionSurface, //sets axis
    								frictionForceOnParallellAxis = AxisParallellToCollisionSurface.getAntiClockWiseNormal().getAntiClockWiseNormal(); //sets axis 180 degrees flipped, frictionforce is in oposite direction
    					
								float angle = tempVec.getDirectionRADIANS(),
    							//float angle = collisionCheck.getEdge2().getDirectionRADIANS(), //the angle of the plane ---------------------------------
    								normalForce = cos(angle) * force.getMagnitude(),
    								parallellForce = sin(angle) * force.getMagnitude(),
    								frictionForce = ((e.getFrictionCoefficient() + entities[i].getFrictionCoefficient()) / 2) * normalForce;
    					
    							//Set the correspondign forces that act on each of these axis
    							forceOnNormalAxis.setVectorMagnitude(normalForce);
    						
    							//if parallellforce is greater than frictionforce, set them both to their corresponding values, if parallellforce is less than frictionforce, set frictionforce to parallellforce
    							(parallellForce > frictionForce) ? forceOnParallellAxis.setVectorMagnitude(parallellForce), frictionForceOnParallellAxis.setVectorMagnitude(frictionForce) : forceOnParallellAxis.setVectorMagnitude(parallellForce), frictionForceOnParallellAxis.setVectorMagnitude(parallellForce);
						
						
    							//apply the forces on both entities
								if (normalForce != 0.0f)
    								e.addForce(Force(forceOnNormalAxis, Vec2D(), "Normal Force", sf::Color::Green));
								if(parallellForce != 0.0f)
								    e.addForce(Force(forceOnParallellAxis, Vec2D(), "Parallell Force", sf::Color::Magenta));
    							if(frictionForce != 0.0f)
									e.addForce(Force(frictionForceOnParallellAxis, Vec2D(), "Friction Force", sf::Color::Cyan));
    					
    							//flipps the forces in the oposite direction
								if (normalForce != 0.0f)
									entities[i].addForce(Force(forceOnNormalAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Normal Force", sf::Color::Green));
								if (parallellForce != 0.0f)
									entities[i].addForce(Force(forceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Parallell Force", sf::Color::Magenta));
								if (frictionForce != 0.0f)
									entities[i].addForce(Force(frictionForceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Friction Force", sf::Color::Cyan));
    					
								float remainingTime = deltaTime - elapsedTime; //the amount of time left in this tick
							//    if (remainingTime > e.getLostTime() || e.getLostTime() == FLT_MAX) 
							//		 e.setLostTime(remainingTime);
							//

								

								if (e.getEntityState() != 0)
								{

									updateResultingForce(e);

									updateVelocity(e, remainingTime);
									updatePosition(e, remainingTime);
								}
								if (entities[i].getEntityState() != 0)
								{
									updateResultingForce(entities[i]);
									updateVelocity(entities[i], remainingTime);
									updatePosition(entities[i], remainingTime);
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



	
	////update logic
	//for (Entity& e : entities)
	//{
	//	if (e.getEntityState() != 0)
	//	{
	//		float additionalTime = e.getLostTime();
	//		std::cout << "time: " << additionalTime << std::endl;
	//
	//		if (additionalTime == FLT_MAX)
	//			additionalTime = 0;
	//	
	//		e.setLostTime(FLT_MAX);
	//	
	//	//	updateResultingForce(e);
	//	//	updateVelocity(e, additionalTime);
	//		updatePosition(e, additionalTime);
	//		
	//		//::cout << e.getForces().size() << std::endl;
	//	//	std::cout << e.getResultingForce().getX() << " "<< e.getResultingForce().getY() << std::endl;
	////		std::cout << e.getVelocity().getX() << " " << e.getVelocity().getY() << std::endl;
	//	}
	//
	//}
	
	

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
	//	std::cout << "velbefore: " << inputEntity.getVelocity().getX() << " " << inputEntity.getVelocity().getY() << std::endl;
		inputEntity.setVelocity(Vec2D(inputEntity.getVelocity().getX() + ((inputEntity.getResultingForce().getX() * InputDeltaTime) / inputEntity.getMass()), inputEntity.getVelocity().getY() + ((inputEntity.getResultingForce().getY() * InputDeltaTime) / inputEntity.getMass())));
		//std::cout << "velaftr: " << inputEntity.getVelocity().getX() << " " << inputEntity.getVelocity().getY() << std::endl;
	}
}
void EntityHandler::updatePosition(Entity& inputEntity,const float deltaTime)
{	
	if (inputEntity.getEntityState() != 0)
	{
		inputEntity.setPosition(inputEntity.getPosition() + (inputEntity.getVelocity() * deltaTime));
	}
}
void EntityHandler::updateActingForces(Entity& inputEntity)
{
	//add gravity, air resitance etc..

	if (inputEntity.getEntityState() != 0)
	{

		Vec2D resultingForce;

		//add gravity force
		inputEntity.addForce(Force(Vec2D(gravitationalAcceleration.getX() * inputEntity.getMass(), gravitationalAcceleration.getY() * inputEntity.getMass()), Vec2D(0, 0), "Gravity"));

		//add air resistance
		//TODO: calc silluhuete area
	//	error: goes to infinity reeeeal quick.
	//	inputEntity.addForce(Force(getAirDragForce(inputEntity.getVelocity(), inputEntity.getDragCoefficient(), 10, inputEntity.getPosition().getY()).getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Air drag"));

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
	tempElapsedTime(0.0f),
	tempVec(1,0)
{
	tempVec.setDirectionDEGREES(30);
	//tempVec = tempVec.getAntiClockWiseNormal();
	//tempVec = tempVec.getClockWiseNormal();
}
