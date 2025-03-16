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
#include "StatsDisplay.h"
#include "TextBox.h"
#include "EmergencyCar.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 4244)
#pragma warning(pop)

class SimulationRun
{
public:
	sf::RenderWindow window;
	std::mutex mutex;
	std::unique_ptr<std::thread> mapEditorThread;
	std::vector<std::unique_ptr<DynamicObject>> buttonObjects;
	std::vector<std::unique_ptr<StaticObject>> staticObjects;
	std::vector<std::unique_ptr<DynamicObject>> carObjects;
	std::vector<std::vector<unsigned int>> fakeSpriteMap = std::vector<std::vector<unsigned int>>(10, std::vector<unsigned int>(17, 0));
	bool isRunning = true;
	bool isPaused = false;
	int numberOfCars = 10;
	float carAvgSpeed = 0;
	bool reloadSimulation = true;
	bool openMapEditor = false;
	bool mapEditorReload = false;
	bool mapEditorLoad = false;
	std::string mapEditorFileNameSave = "mapsave.txt";
	std::string mapEditorFileNameLoad = "map.txt";
	std::vector<std::unique_ptr<DynamicObject>> mapEditorButtons;

public:
	void runSimulation();
	void initializeSimulation();
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
	void updateDynamicObjects(sf::RenderWindow& window, MapHandler& mapH);
	

	void createMoreCars(MapHandler& mapH);
	std::pair<sf::Vector2i, Direction> getNewSpawnPointAndDirection(MapHandler& mapH);
	MapHandler mapHandler;

	//MapEditor
	void runMapEditor();
	void reloadMapEditor();
	void loadMapEditor();
	void mapEditorCreateButtons();
	void mapEditorUpdateButtons(sf::RenderWindow& window);
	void mapEditorCreateStaticObjects();
	void mapEditorCreateRoads(std::vector<std::vector<unsigned int>> spriteMap);
	std::vector<std::unique_ptr<StaticObject>> mapEditorStaticObjects;

	
};
