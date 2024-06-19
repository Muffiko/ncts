#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "DynamicObject.h"
#include "Button.h"
#include "StaticObject.h"
#include "WindowElements.h"
#include "settings.h"
#include "MapHandler.h"
#include "Road.h"
#include "RoadTypes.h"
#include "Car.h"
#pragma warning(push)
#pragma warning(disable: 26495)
#include <SFML/Graphics.hpp>
#pragma warning(pop)

class SimulationRun
{
public:
	sf::RenderWindow window;
	std::vector<std::unique_ptr<DynamicObject>> buttonObjects;
	std::vector<std::unique_ptr<StaticObject>> staticObjects;
	std::vector<std::unique_ptr<DynamicObject>> carObjects;
	bool isRunning = true;

public:
	void runSimulation();

private:
	Settings& settings = Settings::getInstance();
	void initializeWindow();
	void createStaticObjects(std::vector<std::vector<unsigned int>> spriteMap);
	void createDynamicObjects(std::shared_ptr<std::vector<std::vector<unsigned int>>> roadMap);
	void createButtonObjects();

	void drawButtonObjects(sf::RenderWindow &window);
	void updateButtonObjects(sf::RenderWindow &window);
	void drawStaticObjects(sf::RenderWindow& window);
	void drawDynamicObjects(sf::RenderWindow& window);
	void updateDynamicObjects(sf::RenderWindow& window);

	void createMoreCars(MapHandler mapH);


};
