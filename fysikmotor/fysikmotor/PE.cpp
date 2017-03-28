#include "PE.h"


void PE::loadSimulation(const std::string& settingsFilename, const std::string&  entitylistFilename) //loads simulation scenario
{
	//loads said textfiles upon initialisng, stores the lines in a dynamic vector
	ReadFile settings("SavedScenarios/" + settingsFilename + ".txt"),
		simulation("SavedScenarios/" + entitylistFilename + ".txt");

	//set PE/Entityhandler/drawhandler settings

	//gets all the settings from the loaded settings textfile
	float simulation_width = settings.getFloat("###pe_settings_width_meters:"),
		simulation_height = settings.getFloat("###pe_settings_height_meters:"),
		screen_width = settings.getFloat("###pe_settings_pixel_width:"),
		screen_height = settings.getFloat("###pe_settings_pixel_height:"),
		screen_pos_x = settings.getFloat("###pe_settings_onscreen_pos_x:"),
		screen_pos_y = settings.getFloat("###pe_settings_onscreen_pos_y:"),
		dh_grid_spacing = settings.getFloat("###dh_settings_grid_spacing_meters:"),
		eh_gravity_x = settings.getFloat("###eh_settings_gravitational_acceleration_x:"),
		eh_gravity_y = settings.getFloat("###eh_settings_gravitational_acceleration_y:"),
		eh_datalogg_intervall = settings.getFloat("###eh_settings_datalogger_interval_seconds:");

	bool draw_forces = settings.getBool("###dh_settings_draw_forces:"),
		draw_grid = settings.getBool("###dh_settings_draw_grid:"),
		draw_filled_shape = settings.getBool("###dh_settings_draw_filled_shape:"),
		draw_id = settings.getBool("###dh_settings_draw_id:"),
		draw_mass = settings.getBool("###dh_settings_draw_mass_center:"),
		draw_velocity = settings.getBool("###dh_settings_draw_velocity:"),
		draw_aabb = settings.getBool("###dh_settings_draw_aabb_area:"),
		draw_rotation = settings.getBool("###dh_settings_draw_rotation_angle"),
		draw_trejectory = settings.getBool("###dh_settings_draw_entity_trejectory:"),
		eh_use_airresistance = settings.getBool("###eh_settings_use_airresistance:"),
		eh_overwrite_data = settings.getBool("###eh_settings_overwrite_prev_data:");
	
	std::string eh_filename = settings.getString("###eh_settings_datalogger_filename:");

	//checks all float values to make sure thye have been properly set before setting the values on each componment

	if (simulation_width != FLT_MAX && simulation_height != FLT_MAX && screen_width != FLT_MAX && screen_height != FLT_MAX)
		drawHandler.init(simulation_width, simulation_height, screen_width, screen_height);
	
	if (screen_pos_x != FLT_MAX && screen_pos_y != FLT_MAX)
		drawHandler.setViewPixelPos(sf::Vector2f(screen_pos_x, screen_pos_y));
	
	if (dh_grid_spacing != FLT_MAX)
		drawHandler.setSquareGridSpacing(dh_grid_spacing);

	if (simulation_width != FLT_MAX && simulation_height != FLT_MAX)
		entityHandler.init(simulation_width, 0.0f, simulation_height, 0.0f);

	if (eh_gravity_x != FLT_MAX && eh_gravity_y != FLT_MAX)
		entityHandler.setGravitationalAcceleration(Vec2D(eh_gravity_x, eh_gravity_y));

	if (eh_datalogg_intervall != FLT_MAX)
		entityHandler.setDataLoggerIntervall(eh_datalogg_intervall);

	if (eh_filename != "")
	{
		entityHandler.initDataLogger(eh_filename, eh_overwrite_data);
	}
		

	//bool values does not have to be checked, either they are true or not, if not loaded succesfully they are set to false

	entityHandler.setUseAirRessitance(eh_use_airresistance);
	drawHandler.setDrawActingForces(draw_forces);
	drawHandler.setDrawSquareGrid(draw_grid);
	drawHandler.setDrawFilledVertexShape(draw_filled_shape);
	drawHandler.setDrawID(draw_id);
	drawHandler.setDrawCenterOfMass(draw_mass);
	drawHandler.setDrawVelocityVector(draw_velocity);
	drawHandler.setDrawAABBCollisionArea(draw_aabb);
	drawHandler.setDrawRotationAngle(draw_rotation);
	drawHandler.setDrawTrejectory(draw_trejectory);


	//load in entities
	entityHandler.removeAllEntities(); //remove previous entities

	std::vector<std::string> data = simulation.getAllData();

	Entity tEntity;
	VertexShape tShape;
	float rot = 0,
		s_pos_x = FLT_MAX,
		s_pos_y = FLT_MAX,
		pos_x = FLT_MAX,
		pos_y = FLT_MAX;

	bool foundEntity = false;
	for (unsigned int i = 0; i < data.size(); i++)
	{
		std::string tempString = data[i];

		if (tempString.find("###entity") != std::string::npos && foundEntity == false)
			foundEntity = true;

		if (tempString.find("]") != std::string::npos && foundEntity == true)
		{
		//	std::cout << "testerino\n";
		//
		//	std::cout << "E:\n" << "pos: " << tEntity.getPosition().getX() << " " << tEntity.getPosition().getY() << std::endl;
		//	std::cout << "vel: " << tEntity.getVelocity().getX() << " " << tEntity.getVelocity().getY() << std::endl;
		//	std::cout << "fr: " << tEntity.getResultingForce().getX() << " " << tEntity.getResultingForce().getY() << std::endl;
		//	std::cout << "mass: " << tEntity.getMass() << std::endl;
		//	std::cout << "fric: " << tEntity.getFrictionCoefficient() << std::endl;
		//	std::cout << "rest: " << tEntity.getRestitutionCoefficient() << std::endl;
		//	std::cout << "drag: " << tEntity.getDragCoefficient() << std::endl;
		//	std::cout << "s area: " << tEntity.getSillhueteArea() << std::endl;
		//	std::cout << "track e: " << tEntity.getTrackEntityData() << std::endl;
		//	std::cout << "rot: " << tEntity.getAngleRotationDEGREES() << std::endl;
		//	std::cout << "amount of vertices: " << tShape.getAmountOfVertices() << std::endl;

			foundEntity = false;
			tEntity.setVertexShape(tShape);
			tEntity.setAngleRotationDEGREES(rot);
			tEntity.setPosition(Vec2D(pos_x, pos_y));

			entityHandler.addEntity(tEntity);
			
			tShape = VertexShape();
			tEntity = Entity(); //clears tEntity
			rot = 0.0f;
			pos_x = FLT_MAX;
			pos_y = FLT_MAX;
		}

		if (foundEntity)
		{
			if (tempString.find("###id:") != std::string::npos)
			{
				float id = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
			
				tEntity.setEnttityID(id);
			}
			if (tempString.find("###state:") != std::string::npos)
			{
				float state = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
			
				tEntity.setEntityState((int) state);
			}
			if (tempString.find("###pos_x:") != std::string::npos && pos_x == FLT_MAX)
			{
				pos_x = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
			}
			if (tempString.find("###pos_y:") != std::string::npos && pos_y == FLT_MAX)
			{
				pos_y = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
			}
			if (tempString.find("###vel_x:") != std::string::npos)
			{
				float vel_x = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				
				tEntity.setVelocity(Vec2D(vel_x, tEntity.getVelocity().getY()));
			}
			if (tempString.find("###vel_y:") != std::string::npos)
			{
				float vel_y = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setVelocity(Vec2D(tEntity.getVelocity().getX(), vel_y));
			}
			if (tempString.find("###r_force_x:") != std::string::npos)
			{
				float r_force_x = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setResultingForce(Vec2D(r_force_x, tEntity.getResultingForce().getY()));
			}
			if (tempString.find("###r_force_y:") != std::string::npos)
			{
				float r_force_y = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setResultingForce(Vec2D(tEntity.getResultingForce().getX(), r_force_y));
			}
			if (tempString.find("###mass:") != std::string::npos)
			{
				float mass= std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setMass(mass);
			}
			if (tempString.find("###friction_coef:") != std::string::npos)
			{
				float fric = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setFrictionCoefficient(fric);
			}
			if (tempString.find("###restitution_coef:") != std::string::npos)
			{
				float rest = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setRestitutionCoefficient(rest);
			}
			if (tempString.find("###drag_coef:") != std::string::npos)
			{
				float drag = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setDragCoefficient(drag);
			}
			if (tempString.find("###sillhuete_area:") != std::string::npos)
			{
				float s_area = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setSillhueteArea(s_area);
			}
			if (tempString.find("###track_entity:") != std::string::npos)
			{
				bool track = std::stoi(tempString.substr(tempString.find(":") + 1, tempString.length()));
				tEntity.setTrackEntityData(track);
			}
			if (tempString.find("###rot_degrees:") != std::string::npos)
			{
				rot = std::stoi(tempString.substr(tempString.find(":") + 1, tempString.length()));
			}
			if (tempString.find("###shape_p_x:") != std::string::npos && s_pos_x == FLT_MAX)
				s_pos_x = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));
			if (tempString.find("###shape_p_y:") != std::string::npos && s_pos_y == FLT_MAX)
				s_pos_y = std::stof(tempString.substr(tempString.find(":") + 1, tempString.length()));

			if (s_pos_x != FLT_MAX && s_pos_y != FLT_MAX)
			{
				tShape.addVertexPoint(Vec2D(s_pos_x, s_pos_y));
				s_pos_x = FLT_MAX;
				s_pos_y = FLT_MAX;
			}

		}

	}

}
void PE::init(const float inputSimulationWidth, const float inputSimulationHeight, const int imageWidth, const int imageHeight, const float imageSCreenXPos, const float imageScreenYPos)
{
	//tissue
	drawHandler.init(inputSimulationWidth, inputSimulationHeight, imageWidth, imageHeight);
	entityHandler.init(inputSimulationWidth, 0.0f, inputSimulationHeight, 0.0f);

	//set image pos on renderwindow

	drawHandler.setViewPixelPos(sf::Vector2f(imageSCreenXPos, imageScreenYPos));
}
void PE::addEntity(const Entity& inputEntity)
{	
	entityHandler.addEntity(inputEntity);
}
void PE::clearEntities()
{
	//entityHandler.clerEntities();
}
void PE::draw(sf::RenderWindow& inputRenderwindow)
{
	drawHandler.draw(inputRenderwindow, entityHandler.getAllEntities());
}
void PE::update(const float& deltaTime)
{
	entityHandler.updateEntities(deltaTime);
}
void inputEvent(sf::Event& inputEvent)
{
	//dothing
}

PE::PE()
	:
	entityHandler(),
	drawHandler()
{	
}

