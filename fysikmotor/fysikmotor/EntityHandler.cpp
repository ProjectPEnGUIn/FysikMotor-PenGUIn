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
		+ "\n"; //end of line

	storedEntityData.addData(data); 
}
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

	//3: apply values to entiteis if they are NOT static
	if (e1.getEntityState() != 0)
	{
		e1.setVelocity(e1Vf);
	}

	if (e2.getEntityState() != 0)
	{
		e2.setVelocity(e2Vf);
	}
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

	return Vec2D(inputDragCoefficient * ((inputSillhouetteArea * getAirDensity(inputHeight) * inputVelocity.getX() * inputVelocity.getX()) / 2.0f), inputDragCoefficient * ((inputSillhouetteArea * getAirDensity(inputHeight) * inputVelocity.getY() * inputVelocity.getY()) / 2.0f));
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

	std::string dataInfo = "GLOBALTIME, DELTATIME, ID, STATE, POS_x, POS_y, VEL_x, VEL_y, FR_x, FR_y, MASS, ROTATION(DEGREES), FRICTIONCOEF.., RESTITUTIONCOEF.., AIR DRAG COEF..\n";
	storedEntityData.addData(dataInfo); //adds some data to show what each columm stands for
}

void EntityHandler::updateEntities(const float deltaTime) //updates all entities, checks for collisions, handles collisioons
{

	//using physics update order from this
	//http://buildnewgames.com/gamephysics/ 8/3 2017

	//1: Add forces
	//1.1 gravity
	//1.2 air drag
	//1.3 forces that other objects are excerting
	//2. Calc velocity
	//3. calc position
	//4. go back to 1

	elapsedTime += deltaTime;
	timeCounter += deltaTime;

	if (timeCounter > dataLoggerIntervall)
	{
		timeCounter -= dataLoggerIntervall;
		logData = true;
	}

    //	//add gravity and air drag
    	for (Entity& e : entities)
    	{
    		clearActingForces(e);
    		updateActingForces(e);
    	}
    
    	//1.3 use collisioncheck to check what forces to excert on other objects
    	//TODO: HOW TO HANDLE TIMELOSS?? 
    
    	for (Entity& e : entities)
    	{
    		for (Entity& e2 : entities)
    		{
    
    			if (e.getEntityID() != -1 && e2.getEntityID() != -1 //both entities are defined
    				&& e.getEntityID() != e2.getEntityID() //entite wonth check collision with itself
    				&& e.getEntityState() != 0) //e is not a static entity 
    			{
    				//do a supersamplig/binary search SAT check to find collision
    
    			
    				//broad phase check
    				if(minskowskiDifferenceAABBCollisionCheck(e, e2) == true || sweptMinskowskiDifferenceAABBCollisionCheck(e, e2, deltaTime) == true)
    				{
    
    					//accurate narrowphase check between one entity and another
    					// TODO: //use this algorithm in a supersampling/binary collison check search to get a very close correct time of collision
    					SATCollisionCheck collisionCheck;
    
    					VertexShape shape1 = e.getVertexShape(),
    						shape2 = e2.getVertexShape();
    
    					//try to elapse time and move the shapes forward in this tick in small steps
    					//use prev vel, <-- errors????
    
    					bool done = false;
    
    					float elapsedTime = 0.0f,
    						maxTime = deltaTime, //max time interval to check collisions at
    						timeIncrementAmount = deltaTime / 20; //TODO: finetune this value
    
    					//prevents an endless loop
    					int iteration = 0,
    						maxIteration = 20;
    
    					while (!done && elapsedTime < maxTime && iteration < maxIteration)
    					{
    						iteration++;
    
    						if (collisionCheck.SATCheck(shape1, shape2))
    						{
    							done = true;
    
    							//they are colliding
    
    							//1: for how long have they been overlapping? use this to minimize overall timeloss, take this in count when calculating logic in next section
    							//¯\_(´_`)_ / ¯
    							//the entities could have been travling inside one another for a certain amount of time before the collision check was done
    							//will need to take this into count when updating logic furtheron
    
    						//	//chooses an axis on which to project their velocitrties on
    						//	Vec2D projectionAxis = collisionCheck.getPenentrationVector().getNormalisation(); //the axis of least penentration
    						//
    						//	float e1VelocityProjection = projectionAxis * e.getVelocity(), //projects the velocities on the axis
    						//		e2VelocityProjection = projectionAxis * e2.getVelocity();
    						//
    						//	float overlapTime = FLT_MAX,
    						//		overlap = collisionCheck.getOverlap(); //the distance they are overlaping ín the overlapping axis
    						//
    						//	//use distance = velocity * time, time = distane/velocity
    						//	
    						//	if (e1VelocityProjection + e2VelocityProjection == 0 && overlap != 0.0f)
    						//		overlapTime = fabs(overlap / (e1VelocityProjection * 2.0f)); //e1proj + e2proj = 0, they are traveling towards eachother with the same velocity
    						//	else if (overlap != 0.0f)
    						//		overlapTime = fabs(overlap / (e1VelocityProjection + e2VelocityProjection)); //the time that they have been overlapping for
    						//	else
    						//		overlapTime = 0;
    
    						//	overlap is wrong
    
    							//std::cout << "overlap: " << overlap << std::endl;
    							//std::cout << "overlaptime: " << overlapTime << std::endl;
    							//std::cin.get();
    
    						//	elapseEntityTime(e, elapsedTime); //moves the entity position back to the time of collision
    						
							//	e.setLostTime(elapsedTime);
    
    							//2: Impulsecollision logic
    							impulseCollision(e, e2); 
    
    							//3: Apply forces on both entities
    						
    							Vec2D force = e.getResultingForce(), //the force that e excerts on e2
    							//TAKE e2 IN COUNT OR NOT?
    								collisionSurfaceEdge = collisionCheck.getEdge2().getNormalisation(),
    								AxisNormalToCollisionSurface = collisionSurfaceEdge.getAntiClockWiseNormal(),
    								AxisParallellToCollisionSurface = collisionSurfaceEdge.getAntiClockWiseNormal().getAntiClockWiseNormal(), //flipped 180 degrees
    								forceOnNormalAxis = AxisNormalToCollisionSurface, //sets the axis on which the force acts on
    								forceOnParallellAxis = AxisParallellToCollisionSurface, //sets axis
    								frictionForceOnParallellAxis = AxisParallellToCollisionSurface.getAntiClockWiseNormal().getAntiClockWiseNormal(); //sets axis 180 degrees flipped, frictionforce is in oposite direction
    
    							float angle = collisionCheck.getEdge2().getDirectionRADIANS(), //the angle of the plane
    								normalForce = cos(angle) * force.getMagnitude(),
    								parallellForce = sin(angle) * force.getMagnitude(),
    								frictionForce = ((e.getFrictionCoefficient() + e2.getFrictionCoefficient()) / 2) * normalForce;
    
    							//Set the correspondign forces that act on each of these axis
    							forceOnNormalAxis.setVectorMagnitude(normalForce);
    							
    							//if parallellforce is greater than frictionforce, set them both to their corresponding values, if parallellforce is less than frictionforce, set frictionforce to parallellforce
    							(parallellForce > frictionForce) ? forceOnParallellAxis.setVectorMagnitude(parallellForce), frictionForceOnParallellAxis.setVectorMagnitude(frictionForce) : forceOnParallellAxis.setVectorMagnitude(parallellForce), frictionForceOnParallellAxis.setVectorMagnitude(parallellForce);
    							
    							//apply the forces on both entities
    							e.addForce(Force(forceOnNormalAxis, Vec2D(), "Normal Force", sf::Color::Green));
								if (parallellForce != 0)
									e.addForce(Force(forceOnParallellAxis, Vec2D(), "Parallell Force", sf::Color::Magenta));
    							if(frictionForce != 0)
									e.addForce(Force(frictionForceOnParallellAxis, Vec2D(), "Friction Force", sf::Color::Cyan));
    
    							//flipps the forces in the oposite direction
    							e2.addForce(Force(forceOnNormalAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Normal Force", sf::Color::Green));
    							if(parallellForce != 0)
									e2.addForce(Force(forceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Parallell Force", sf::Color::Magenta));
    							if(frictionForce != 0)
									e2.addForce(Force(frictionForceOnParallellAxis.getAntiClockWiseNormal().getAntiClockWiseNormal(), Vec2D(), "Anti Friction Force", sf::Color::Cyan));
    
    
    						}
    						else
    						{
    							//collision was not found
    
    							if (elapsedTime + timeIncrementAmount >= deltaTime)
    								done = true;
    							
    							else
    								elapsedTime += timeIncrementAmount; //adds more time
    
    							//set the shapes' position at the elapsedTimeInterval
    
    							//USING VELOCITY FROM OLD TICK; may cause errors?
    							shape1.setPosition(e.getPosition() + e.getVelocity() * elapsedTime);
    							shape2.setPosition(e2.getPosition() + e2.getVelocity() * elapsedTime);
    
    							//goes back into the while loop and does a collisioncheck with theses values, if false it goes back here where time the gets incrementet
    						}
    					}
    
    				}
    
    			}
    
    		}
    	}
    
    //update logic
	for (Entity& e : entities)
	{
		if (e.getEntityState() != 0)
		{
			//only logs data if it is time and that entity is set to be tracked
			if (logData == true && e.getTrackEntityData() == true) 
				logEntityData(e, deltaTime, elapsedTime);


			float additionalTime = e.getLostTime();
			if (additionalTime == FLT_MAX)
				additionalTime = 0;
			e.setLostTime(FLT_MAX);
	
			//update enttiy
			updateResultingForce(e);
			updateVelocity(e, deltaTime + additionalTime);
			updatePreviousEntityData(e);
			updatePosition(e, deltaTime + additionalTime);
	
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
	storedEntityData()
	
{
	
}

EntityHandler::~EntityHandler() //default destructor
{
	storedEntityData.saveCurrentData();
}