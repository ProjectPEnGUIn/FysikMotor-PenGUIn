#include "PE.h"


void PE::init(float inputMaxX, float inputMinX, float inputMaxY, float inputMinY)
{
	drawHandler.init(inputMaxX, inputMinX, inputMaxY, inputMinY);
	entityHandler.init(inputMaxX, inputMinX, inputMaxY, inputMinY);
	//init things
}
void PE::addEntity(const Entity& inputEntity)
{
	entityHandler.addEntity(inputEntity);
}
void PE::draw(sf::RenderWindow& inputRenderwindow)
{
	drawHandler.draw(inputRenderwindow, entityHandler.getAllEntities());
}
void PE::update(const float& deltaTime)
{
	entityHandler.updateEntities(deltaTime);
}
void getEvent(sf::Event& inputEvent)
{
	//dothing
}

PE::PE()
	:
	entityHandler(),
	drawHandler()
{
	
}

