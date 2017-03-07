#include "PE.h"

void PE::loadSimulation(const std::string& filename) //loads simulation scenario
{
	//filenames is the end of 

	std::string path = "/Saves/" + filename; // the full path to the savefile text document

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
	drawHandler.test(sf::Vector2f(5, 5), sf::Vector2f(20, 20));
}

