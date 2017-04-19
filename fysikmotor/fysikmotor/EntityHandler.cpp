#include "EntityHandler.h"

void EntityHandler::logEntityData(const Entity& e, const float currentDeltaTime, const float totalElapsedTime) //logs entity data onto storedentitydata
{
	std::string data;

	//adds it into one long line of data

	//GLOBALTIME, DELTATIME, ID, STATE, POSx, POSy, VELx, VELy, FRx, FRy, MASS, ROT(DEGREES), FRICTIONCOEFFICIENT, RESTITUTIONFOCEFFIENCT, DRAGCOEFFICIENT
	data =  std::to_string(totalElapsedTime) + ", "
		+ std::to_string(currentDeltaTime) + ", "
		+ std::to_string(e.getEntityID()) + ", "
		+ std::to_string(e.getEntityState()) + ", "
		+ std::to_string(e.getPosition().getX()) + ", "
		+ std::to_string(e.getPosition().getY()) + ", "
		+ std::to_string(e.getVelocity().getX()) + ", "
		+ std::to_string(e.getVelocity().getY()) + ", "
		+ std::to_string(e.getResultingForce().getX()) + ", "
		+ std::to_string(e.getResultingForce().getY()) + ", "
		+ std::to_string(e.getMass()) + ", "
		+ std::to_string(e.getVertexShape().getCurrentRotationDEGREES()) + ", "
		+ std::to_string(e.getFrictionCoefficient()) + ", "
		+ std::to_string(e.getRestitutionCoefficient()) + ", "
		+ std::to_string(e.getDragCoefficient()) + ", "
		+ std::to_string(airResistanceEnabled) + ", "
		+ "\n"; //end of line

	storedEntityData.addData(data); 
}
void EntityHandler::handleCollision(Entity& e1, Entity& e2) //resolves collision
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
	
	//3: apply values to entiteis if they are NOT static
	if (e1.getEntityState() != 0)
	{
		e1.setVelocity(e1Vf);
	}
	
	if (e2.getEntityState() != 0)
	{
		e2.setVelocity(e2Vf);
	}

	//std::cout << e1Vf.getX() << "  " << e1Vf.getY() << std::endl;
	//std::cout << e2Vf.getX() << " " << e2Vf.getY() << std::endl;
	//std::cin.get();

	//float tCor = (e1.getRestitutionCoefficient() + e2.getRestitutionCoefficient()) / 2, //rough estimade 
	//	fx = tCor * (e1.getVelocity().getX() - e2.getVelocity().getX()),
	//	fy = tCor * (e1.getVelocity().getY() - e2.getVelocity().getY()),
	//	gx = e1.getMass() * e1.getVelocity().getX() + e2.getMass() * e2.getVelocity().getX(),
	//	gy = e1.getMass() * e1.getVelocity().getY() + e2.getMass() * e2.getVelocity().getY(),
	//	vA2x = (gx - fx * e2.getMass()) / (e1.getMass() + e2.getMass()),
	//	vA2y = (gy - fy * e2.getMass()) / (e1.getMass() + e2.getMass()),
	//	vB2x = fx - vA2x,
	//	vB2y = fy - vA2y;
	//
	//if (e1.getEntityState() != 0)
	//	e1.setVelocity(Vec2D(vA2x, vA2y));
	//if (e2.getEntityState() != 0)
	//	e2.setVelocity(Vec2D(vB2x, vB2y));

}

void EntityHandler::updateResultingForce(Entity& e)
{
	Vec2D resultingForce;

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
	const float d = getAirDensity(inputHeight) * inputDragCoefficient * inputSillhouetteArea * 0.5;

	float fx = d * inputVelocity.getX() * inputVelocity.getX(),
		fy = d * inputVelocity.getY() * inputVelocity.getY();

		return Vec2D(fx, fy);
}


void EntityHandler::setLogData(const bool inputBool)
{
	logData = inputBool;
}
void EntityHandler::setDataLoggerIntervall(const float intervall)
{
	dataLoggerIntervall = intervall;
}

void EntityHandler::initDataLogger(const std::string& inputFilename, const bool inputOverwriteStatus)
{
	storedEntityData = DataLogger(inputFilename, inputOverwriteStatus);

	std::string dataInfo = "GLOBALTIME, DELTATIME, ID, STATE, POS_x, POS_y, VEL_x, VEL_y, FR_x, FR_y, MASS, ROTATION(DEGREES), FRICTIONCOEF.., RESTITUTIONCOEF.., AIR DRAG COEF..,  use air resistance\n";
	storedEntityData.addData(dataInfo); //adds some data to show what each columm stands for
}
void EntityHandler::setGravitationalAcceleration(const Vec2D& inputGravitationalAcceleration)
{
	gravitationalAcceleration = inputGravitationalAcceleration;
}
void EntityHandler::setUseAirRessitance(const bool inputBool)
{
	airResistanceEnabled = inputBool;
}

void EntityHandler::updateEntities(const float deltaTime) //updates all entities, checks for collisions, handles collisioons
{
	////using physics update order from this
	////http://buildnewgames.com/gamephysics/ 8/3 2017
	//
	////1: Add forces
	////1.1 gravity
	////1.2 air drag
	////1.3 forces that other objects are excerting
	////2. Calc velocity
	////3. calc position
	////4. go back to 1
	//
	//elapsedTime += deltaTime;
	//timeCounter += deltaTime;
	//
	//if (timeCounter > dataLoggerIntervall)
	//{
	//	timeCounter -= dataLoggerIntervall;
	//	logData = true;
	//}
	//
    ////	//add gravity and air drag
    //	for (Entity& e : entities)
    //	{
    //		clearActingForces(e);
    //		updateActingForces(e);
    //	}
    //
    //	//1.3 use collisioncheck to check what forces to excert on other objects
  	//
    //	for (Entity& e : entities)
    //	{
    //		for (Entity& e2 : entities)
    //		{
    //
    //			if (e.getEntityID() != -1 && e2.getEntityID() != -1 //both entities are defined
    //				&& e.getEntityID() != e2.getEntityID() //entite wonth check collision with itself
    //				&& e.getEntityState() != 0) //e is not a static entity 
    //			{
    //				//do a supersamplig/binary search SAT check to find collision
    //
    //			
    //				//broad phase check
    //			//	if(minskowskiDifferenceAABBCollisionCheck(e, e2) == true || sweptMinskowskiDifferenceAABBCollisionCheck(e, e2, deltaTime) == true)
    //			//	{
    //
    //					//accurate narrowphase check between one entity and another
    //					SATCollisionCheck collisionCheck;
    //
	//					//Stores a copy of the entities positiion
    //				   VertexShape shape1 = e.getVertexShape(),
    //						shape2 = e2.getVertexShape();
    //
    //					//try to elapse time and move the shapes forward in this tick in small steps
    //					bool done = false;
    //
    //					float et = 0.0f,
    //						maxTime = deltaTime, //max time interval to check collisions at
    //						timeIncrementAmount = deltaTime / 20; //TODO: finetune this value
    //
    //					//prevents an endless loop
    //					int iteration = 0,
    //						maxIteration = 21;
    //
    //					while (!done && et  < maxTime && iteration < maxIteration)
    //					{
    //						iteration++;
    //
    //						if (collisionCheck.SATCheck(shape1, shape2))
    //						{
    //							done = true;
    //
    //							//they are colliding
    //
    //							//1: for how long have they been overlapping? use this to minimize overall timeloss, take this in count when calculating logic in next section
    //							//the entities could have been travling inside one another for a certain amount of time before the collision check was done
    //							//will need to take this into count when updating logic furtheron
    //
    //							//chooses an axis on which to project their velocitrties on
    //							Vec2D projectionAxis = collisionCheck.getPenentrationVector().getNormalisation(); //the axis of least penentration
    //						
    //							float e1VelocityProjection = projectionAxis * e.getVelocity(), //projects the velocities on the axis
    //								e2VelocityProjection = projectionAxis * e2.getVelocity();
    //						
    //							float overlapTime = FLT_MAX,
    //								overlap = collisionCheck.getOverlap(); //the distance they are overlaping ín the overlapping axis
    //						
    //							//use distance = velocity * time, time = distane/velocity
    //							
    //							if (e1VelocityProjection + e2VelocityProjection == 0 && overlap != 0.0f)
    //								overlapTime = fabs(overlap / (e1VelocityProjection * 2.0f)); //e1proj + e2proj = 0, they are traveling towards eachother with the same velocity
    //							else if (overlap != 0.0f)
    //								overlapTime = fabs(overlap / (e1VelocityProjection + e2VelocityProjection)); //the time that they have been overlapping for
    //							else
    //								overlapTime = 0;
   	//
	//							//moves entities back to where they are just not touching
	//							if(e.getEntityState() != 0.0f)
	//								e.setPosition(e.getPosition() + e.getVelocity()* (et- overlapTime));
	//							if (e2.getEntityState() != 0.0f)
	//								e2.setPosition(e.getPosition() + e2.getVelocity()* (et-overlapTime));
    //
	//							e.setLostTime(et);
	//							e2.setLostTime(et);
    //
    //							//2: collision logic
    //							handleCollision(e, e2); 
    //
    //							//3: Apply forces on both entities
    //							Vec2D force = e.getResultingForce(), //the force that e excerts on e2
    //							//TAKE e2 IN COUNT OR NOT?
    //								collisionSurfaceEdge = collisionCheck.getEdge2().getNormalisation(),
    //								AxisNormalToCollisionSurface = collisionSurfaceEdge.getAntiClockWiseNormal(),
    //								AxisParallellToCollisionSurface = collisionSurfaceEdge.getAntiClockWiseNormal().getAntiClockWiseNormal(), //flipped 180 degrees
    //								forceOnNormalAxis = AxisNormalToCollisionSurface, //sets the axis on which the force acts on
    //								forceOnParallellAxis = AxisParallellToCollisionSurface, //sets axis
    //								frictionForceOnParallellAxis = AxisParallellToCollisionSurface.getAntiClockWiseNormal().getAntiClockWiseNormal(); //sets axis 180 degrees flipped, frictionforce is in oposite direction
    //
    //							float angle = collisionCheck.getEdge2().getDirectionRADIANS(), //the angle of the plane
    //								normalForce = cos(angle) * force.getMagnitude(),
    //								parallellForce = sin(angle) * force.getMagnitude(),
    //								frictionForce = ((e.getFrictionCoefficient() + e2.getFrictionCoefficient()) / 2) * normalForce;
    //
    //							//Set the correspondign forces that act on each of these axis
    //							forceOnNormalAxis.setVectorMagnitude(normalForce);
    //							
    //							//if parallellforce is greater than frictionforce, set them both to their corresponding values, if parallellforce is less than frictionforce, set frictionforce to parallellforce
    //							(parallellForce > frictionForce) ? forceOnParallellAxis.setVectorMagnitude(parallellForce), frictionForceOnParallellAxis.setVectorMagnitude(frictionForce) : forceOnParallellAxis.setVectorMagnitude(parallellForce), frictionForceOnParallellAxis.setVectorMagnitude(parallellForce);
    //							
    //							//apply the forces on both entities
    //							e.addForce(Force(forceOnNormalAxis, Vec2D(), "Normal Force", sf::Color::Green));
	//							if (parallellForce != 0)
	//								e.addForce(Force(forceOnParallellAxis, Vec2D(), "Parallell Force", sf::Color::Magenta));
    //							if(frictionForce != 0)
	//								e.addForce(Force(frictionForceOnParallellAxis, Vec2D(), "Friction Force", sf::Color::Cyan + sf::Color(100, 0, 0)));
    //
    //							//flipps the forces in the oposite direction
    //							e2.addForce(Force(forceOnNormalAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Normal Force", sf::Color::Green));
    //							if(parallellForce != 0)
	//								e2.addForce(Force(forceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Parallell Force", sf::Color::Magenta));
    //							if(frictionForce != 0)
	//								e2.addForce(Force(frictionForceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Friction Force", sf::Color::Cyan + sf::Color(100, 0, 0)));
    //						}
    //						else
    //						{
    //							//collision was not found
    //
    //							if (et + timeIncrementAmount >= deltaTime)
    //								done = true;
    //							
    //							else
	//								et += timeIncrementAmount; //adds more time
    //
    //							//set the shapes' position at the next elapsedTimeInterval
    //
    //							shape1.setPosition(e.getPosition() + e.getVelocity() * et);
    //							shape2.setPosition(e2.getPosition() + e2.getVelocity() * et);
    //
    //							//goes back into the loop and does a collisioncheck with theses values, if false it goes back here where time the gets incremented
    //						}
    //					}
    //
    //				//}
    //
    //			}
    //
    //		}
    //	}
    //
    ////update logic
	//for (Entity& e : entities)
	//{
	//	if (e.getEntityState() != 0)
	//	{
	//		float additionalTime = e.getLostTime();
	//		if (additionalTime == FLT_MAX || additionalTime < 0.0f)
	//			additionalTime = 0;
	//		e.setLostTime(FLT_MAX);
	//
	//		//update enttiy
	//		updateResultingForce(e);
	//		updateVelocity(e, deltaTime + additionalTime);
	//		updatePreviousEntityData(e);
	//		updatePosition(e, deltaTime + additionalTime);
	//
	//		//only logs data if it is time and that entity is set to be tracked
	//		if (logData == true && e.getTrackEntityData() == true)
	//			logEntityData(e, deltaTime, elapsedTime);
	//	}
	//
	//}
	//
	//logData = false;


//=======================================================================================================================================================================================================================================

	elapsedTime += deltaTime;
	timeCounter += deltaTime;
	
	if (timeCounter > dataLoggerIntervall)
	{
		timeCounter -= dataLoggerIntervall;
		logData = true;
	}

     //1: try to elapse this current tick, add gravity/air resistance and elapse time with deltatime
	for (Entity& e : entities)
	{
		//error checking
		if (e.getEntityState() == -1)
		{
			std::cout << "ERROR: Tried to update an entity that has NOT been given a state! SKIPPED THIS ENTITY IN UPDATE\n";
			
			//skips this iteration and moves on to next entity
			continue;
		}
		//don't need to update static entities
		if (e.getEntityState() != 0)
		{
			//do update of entity here
			clearActingForces(e);
			updateActingForces(e); //Adds gravity and air resistancce if it is enabled
			updateVelocity(e, deltaTime); //updates velocity using the resulting force
			updatePreviousEntityData(e); //saves this tick entitydata in designated variables to know where it previously was
			updatePosition(e, deltaTime); //updates pos with vel and dtime

			e.setIsColliding(false);
		}
		else if (e.getEntityState() == 0)
		{
			e.setIsColliding(false);
			e.setForces(std::vector<Force>{});
		}

	}

	//2: check if there has been a collison this tick, from the start of this tick to the end of this tick,
	//if there has been a collision, move entities back to point of collision, update forces which they act on eachother
	//simple bruteforce collisoioncheck, O(N^2 - 1)
	for (Entity& e : entities)
	{
		for (Entity& e2 : entities)
		{
		
			if (e.getEntityState() != -1 && e2.getEntityState() != -1 //both of the entity states are set
				&& e.getEntityID() != -1 && e2.getEntityID() != -1 //both of the entities has been given an ID
				&& e.getEntityID() != e2.getEntityID() //collision is not being checked between one entity and itself
				&& e.getIsColliding() == false 
				&& e.getEntityState() != 0
				)
			{
				//simple broadphase AABB check using minskowski difference, one of them checking for intersection forward in time
				//used to easy determine if the entites have collided or not OR if they entities will collide during  this tick or not

				if (minskowskiDifferenceAABBCollisionCheck(e, e2) == true || sweptMinskowskiDifferenceAABBCollisionCheck(e, e2, deltaTime))
				{
					//broadphase collisoncheck found a plauseble collision

					//now try do do a narrowphase multisampling collision check
					//use Seperating Axis Theorem to accuratly check for collisions between convex polygons
					//multisampling: check for collisons in small intervals and then move the entities forward a tiny bit and repeat

					//stores penentration depth/penentraion normal, used to check
					SATCollisionCheck collisionCheck;
					
					//store a copy of the body of each entity not directly affect the entity if not needed
					VertexShape shape1 = e.getVertexShape(),
						shape2 = e2.getVertexShape();
				
					float checkedTime = 0,
						timeIncrement = deltaTime / 15; 

					//multisampling loop
					bool done = false;
					while (!done && checkedTime + timeIncrement < deltaTime)
					{
						if (collisionCheck.SATCheck(shape1, shape2) == true)
						{
							//a collison betweeen the entities have been found using the accurate collision check method
							//the entities are/will definitly be colliding this tick

							done = true;

							//1: find out how long they have been colliding ( intersecting) 
							//2: move the entities to point of collision in time
							//3: save the time that the entites lost while traveling inside eachother in this tick
							//4: handle collision logic
							//5: apply acting forces on e1

							//TODO: APPLY FORCES IN ONLY ONE WAY??? SINCE THE ENTITES WIKLL BE CGEHCJKED FOR COLLISIOON AGAIN ANYWAY??

							//1: find out how long they have been colliding ( intersecting) 
							//the axis on which to project the velocities
							Vec2D prAxis = collisionCheck.getPenentrationVector().getNormalisation(); 

							//projects both entities velocities onto one common axis
							float e1VelPr = e.getVelocity() * prAxis,
								e2Velpr = e2.getVelocity() * prAxis,
								overlap = collisionCheck.getOverlap(), //the distance on the projection axis they are overlaping
								overlapTime = FLT_MAX;


							if (e1VelPr + e2Velpr == 0.0f && overlap != 0.0f)
								overlapTime = fabs(overlap / (e1VelPr * 2));
							else if (overlap != 0.0f)
								overlapTime = fabs(overlap / (e1VelPr + e2Velpr));
							else
								overlapTime = 0;

							//2: move the entities to point of collision in time'
							if(e.getEntityState() != 0)
								e.setPosition(e.getPreviousPosition() + e.getVelocity() * (checkedTime - overlapTime));
							if (e2.getEntityState() != 0)
								e2.setPosition(e2.getPreviousPosition() + e2.getVelocity() * (checkedTime - overlapTime));

							float leftoverTime = deltaTime - checkedTime + overlapTime;

							//3: save the time that the entites lost while traveling inside eachother in this tick
							if (leftoverTime < e.getLostTime() && e.getLostTime() != FLT_MAX && e.getEntityState() != 0)
							{
								e.setIsColliding(false);
								e.setLostTime(leftoverTime);
							}
							else if (e.getLostTime() == FLT_MAX && e.getEntityState() != 0)
							{
								e.setLostTime(leftoverTime);
							}

							if (leftoverTime < e2.getLostTime() && e2.getLostTime() != FLT_MAX && e2.getEntityState() != 0)
							{
								e2.setIsColliding(false);
								e2.setLostTime(leftoverTime);
							}
							else if (e2.getLostTime() == FLT_MAX && e2.getEntityState() != 0)
							{
								e2.setLostTime(leftoverTime);
							}
						

							//skip collison logic if it is not the collison at the smallest time point
							if (e.getIsColliding() == true)
								continue; 

							e.setIsColliding(true);
							e2.setIsColliding(true);

							//4: handle collision lgic
							handleCollision(e, e2);
							

							//5: apply acting forces on e1
							Vec2D force = e.getResultingForce(), //the force that e excerts on e2
								collisionSurface = collisionCheck.getEdge2().getNormalisation(), //the surface on e2 that is in contact with e1
								axisNormalToSurface = collisionSurface.getAntiClockWiseNormal(), //the normal to the collision surface, pointing away from the surface
								axisParallellToSurface = collisionSurface.getAntiClockWiseNormal().getAntiClockWiseNormal(),
								forceOnNormalAxis = axisNormalToSurface, //sets the axis on which to excert the normalforce on
								forceOnParallellAxis = axisParallellToSurface, //sets the axis on which to excert the parallellforce on
								frictionForceOnParallellAxis = axisParallellToSurface.getAntiClockWiseNormal().getAntiClockWiseNormal(); //sets the axis on which to excert the frictionforce on

							//the forces that will applied on each axis
							float angle = collisionCheck.getEdge2().getDirectionRADIANS(),
								normalForce = cos(angle) * force.getMagnitude(),
								parallellforce = sin(angle) * force.getMagnitude(),
								frictionForce = ((e.getFrictionCoefficient() + e2.getFrictionCoefficient()) / 2) * normalForce;

							//set the forces on corresponding axis
							forceOnNormalAxis.setVectorMagnitude(normalForce);
							forceOnParallellAxis.setVectorMagnitude(parallellforce);

							if (frictionForce >= parallellforce)
								frictionForceOnParallellAxis.setVectorMagnitude(frictionForce);
							else
								frictionForceOnParallellAxis.setVectorMagnitude(parallellforce);

							//apply forces on each entity
							e.addForce(Force(forceOnNormalAxis, Vec2D(), "Normal Force", sf::Color::Green));
							if (parallellforce != 0.0f)
								e.addForce(Force(forceOnParallellAxis, Vec2D(), "Parallell Force", sf::Color::Magenta));
							if (frictionForce != 0.0f)
								e.addForce(Force(frictionForceOnParallellAxis, Vec2D(), "Friction Force", sf::Color::Cyan));

							//apply flipped forces on e2
							//apply forces on each entity
							e2.addForce(Force(forceOnNormalAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Normal Force", sf::Color::Green));
							if (parallellforce != 0.0f)
								e2.addForce(Force(forceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Parallell Force", sf::Color::Magenta));
							if (frictionForce != 0.0f)
								e2.addForce(Force(frictionForceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Friction Force", sf::Color::Cyan));
						}
						else
						{
							//a collision at this time was NOT found
							//try to move the shapes forward and a tiny bit using the timeincrement and entities velocity

							if (checkedTime + timeIncrement >= deltaTime)
								done = true;
							else
								checkedTime += timeIncrement;

							//move shapes forward
							shape1.setPosition(e.getPreviousPosition() + e.getVelocity() * checkedTime);
							shape2.setPosition(e2.getPreviousPosition() + e2.getVelocity() * checkedTime);

							//now try to check for collision at this point in time
						}
					}


				}

			}
		}
	}

	//3: If there is additiontime for each entity, move them with it
	for (Entity& e : entities)
	{
		//error checking
		if (e.getEntityState() == -1)
		{
			std::cout << "ERROR: Tried to update an entity that has NOT been given a state! SKIPPED THIS ENTITY IN UPDATE\n";
			//skips this iteration
			continue;
		}
		//don't need to update static entities
		if (e.getEntityState() != 0)
		{
			float remainingTime = e.getLostTime();
			e.setLostTime(FLT_MAX); //resets it
			//no remaining time has been set for this entity, no point in trying to update it
			if (remainingTime == FLT_MAX)
			{
				remainingTime = 0;
				//skips this iteration and moves on to next entity
				continue;
			}

			//do update of entity here
			updateResultingForce(e);
			updateVelocity(e, remainingTime); //updates velocity using the resulting force
			updatePreviousEntityData(e); //saves this tick entitydata in designated variables to know where it previously was
			updatePosition(e, remainingTime); //updates pos with vel and dtime

		}


	}

	//logs entity data
	for (Entity& e : entities)
	{
		if (e.getEntityState() != 0)
		{
		
			if (logData == true && e.getTrackEntityData() == true)
				logEntityData(e, deltaTime, elapsedTime);

		}
	}

	logData = false;
}

void EntityHandler::updateVelocity(Entity& inputEntity, const float InputDeltaTime) //updates velócitiyes on entiteis
{
	if (inputEntity.getEntityState() != 0)
	{
		inputEntity.setVelocity(Vec2D(inputEntity.getVelocity().getX() + ((inputEntity.getResultingForce().getX() * InputDeltaTime) / inputEntity.getMass()), inputEntity.getVelocity().getY() + ((inputEntity.getResultingForce().getY() * InputDeltaTime) / inputEntity.getMass())));
	}
}
void EntityHandler::updatePosition(Entity& inputEntity,const float deltaTime)
{	
	inputEntity.setPosition(inputEntity.getPosition() + (inputEntity.getVelocity() * deltaTime));
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
		if (airResistanceEnabled == true)
		{
			Vec2D airDrag = getAirDragForce(inputEntity.getVelocity(), inputEntity.getDragCoefficient(), inputEntity.getSillhueteArea(), inputEntity.getPosition().getY()),
				direction = inputEntity.getVelocity().getNormalisation().getAntiClockWiseNormal().getAntiClockWiseNormal();
			direction.setVectorMagnitude(airDrag.getMagnitude());
			
			inputEntity.addForce(Force(direction, Vec2D(), "Air Drag", sf::Color::Cyan));
		}

		for (const Force& f : inputEntity.getForces())
		{
			resultingForce += f.getForce();
		}
		
		inputEntity.setResultingForce(resultingForce);
	}
	else if (inputEntity.getEntityState() == 0) //STATIC 
		inputEntity.setResultingForce(Vec2D());
}
void EntityHandler::clearActingForces(Entity& inputEntity) //removes all forces acting on entity and sets resultingforce to 0
{
	inputEntity.setResultingForce(Vec2D(0, 0));
	inputEntity.setForces(std::vector<Force>{});
}
void EntityHandler::updatePreviousEntityData(Entity& inputEntity)
{
	inputEntity.setPreviousPosition(inputEntity.getPosition());
	inputEntity.setPreviousVelocity(inputEntity.getVelocity());
	inputEntity.setPreviousAABBTL(inputEntity.getAABBTopLeft());
	inputEntity.setPreviousAABBBR(inputEntity.getAABBMBottomRight());
}
					   //add entites
void EntityHandler::addEntity(Entity inputEntity) //adds the entity to the list of entities
{
	
		entities.push_back(inputEntity);
}
void EntityHandler::removeAllEntities()
{
	entities.clear();
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
	elapsedTime(0),
	timeCounter(0),
	logData(false),
	dataLoggerIntervall(1),
	storedEntityData(),
	airResistanceEnabled(true)
	
{
	
}

EntityHandler::~EntityHandler() //default destructor
{
	storedEntityData.saveCurrentData();
}