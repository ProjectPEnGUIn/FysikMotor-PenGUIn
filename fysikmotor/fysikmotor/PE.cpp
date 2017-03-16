#include "PE.h"

bool PE::fileExists(const std::string& filename) const //checks weather file already exists or not
{
	//http://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing 12/3 2017

	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
		return true;

	return false;
}
bool PE::containsLetters(const std::string& inputString)
{
	return !std::all_of(inputString.begin(), inputString.end(), ::isdigit);
}
float PE::getFloat(const std::string& inputString)
{
	if (containsLetters(inputString))
		return FLT_MAX;
	else
		return std::stof(inputString);
}
bool PE::getBool(const std::string& inputString)
{
	if (containsLetters(inputString))
		return false;
	else
		return std::stoi(inputString);
}
void PE::loadSimulation(const std::string& filename) //loads simulation scenario
{
	//filenames is the end of 

	std::string path = "/SavedScenarios/" + filename + ".txt"; // the full path to the savefile text document

	std::ifstream inputFromFile;

	if (fileExists(path))
	{
		//there is a save with path name

		//tries to open that filename
		inputFromFile.open(path);
		if (!inputFromFile.is_open())
		{
			std::cout << "ERROR: PE did not open filename<" << path << "> properly\n";
			return;
		}
		
		std::vector<std::string> data; //stores all data from the file in a vector of strings
		std::string line; //tempstring

		//reads the textfile line by line
		while (std::getline(inputFromFile, line))
		{
			data.push_back(line);
		}

		entityHandler.removeAllEntities(); //removes current entitties

		//data has been loaded, now process it
		//go through line by line and look for keywords

		//temp variables
		float pes_width = FLT_MAX,
			pes_height = FLT_MAX,
			pes_Pwidth = FLT_MAX,
			pes_Pheight = FLT_MAX,
			pes_sPosX = FLT_MAX,
			pes_sPosY = FLT_MAX,
			dhs_gSpace = FLT_MAX,
			ehs_gAcY = FLT_MAX,
			ehs_gAcX = FLT_MAX,
			ehs_loggIntervall = FLT_MAX;

		bool dhs_force = false,
			dhs_grid = false,
			dhs_vertices = false,
			dhs_filled = false,
			dhs_ID = false,
			dhs_mass = false,
			dhs_vel = false,
			dhs_fric = false,
			dhs_aabb = false,
			dhs_texture = false,
			dhs_angle = false,
			dhs_trejectory = false;

		for (unsigned int i = data.size() - 1; i >= 0; i++)
		{
			std::string temp = data[i];
			//input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
			temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end()); //removes all spaces from the string, removes some user error

			//there is somethign to be read from on that line, ### keyword
			if (temp.find("###"))
			{
				//WARNING MAY CAUSE ERRORS IF PROPER VALUES ARE NOT SET IN FILE
				//NOT OPTIMISED BUT IT WORKS

				//finds the line containing the wanted data and makes a substr ofwhat is written after the : , then transforms it into desired type
				//DOES ERROR CHECKING IN GETFLOATFUCNTIONS

				if (temp.find("###_pe_settings_width_meters:"))
					pes_width = getFloat(temp.substr(temp.find(":") + 1, temp.length()));
				
				if (temp.find("###pe_settings_height_meters:"))
					pes_height = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###pe_settings_pixel_width:"))
					pes_Pwidth = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###pe_settings_pixel_height::"))
					pes_Pheight = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###pe_settings_onscreen_pos_x:"))
					pes_sPosX = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###pe_settings_onscreen_pos_y:"))
					pes_sPosY = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_grid_spacing_meters:"))
					dhs_gSpace = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###eh_settings_gravitational_acceleration_x:"))
					ehs_gAcX = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###eh_settings_gravitational_acceleration_y:"))
					ehs_gAcY = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###eh_settings_datalogger_interval_seconds:"))
					ehs_loggIntervall = getFloat(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_forces:"))
					dhs_force = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_grid:"))
					dhs_grid = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_filled_shape:"))
					dhs_filled = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_ID:"))
					dhs_ID = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_mass_center:"))
					dhs_mass = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_velocity:"))
					dhs_vel = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_aabb_area:"))
					dhs_aabb = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_rotation_angle:"))
					dhs_angle = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###dh_settings_draw_entity_trejectory:"))
					dhs_trejectory = getBool(temp.substr(temp.find(":") + 1, temp.length()));

				if (temp.find("###entity"))
				{
					//entity data
					Entity tempEntity;




					
					entityHandler.addEntity(tempEntity);
				}

			}
		}

		//set values


	}
	else
		std::cout << "ERROR: PE Tried to load from a savefile that does NOT exist\n";

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
	entityHandler.initDataLogger("enttiysavetest", true);
	entityHandler.setDataLoggerIntervall(0.01f);
}

