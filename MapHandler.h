#pragma once
#include "StaticObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <sstream>
#include "RoadPatterns.h"
#include "RoadTypes.h"
#include "settings.h"
#include <unordered_map> 


class MapHandler
{ //17x10
public:
	Settings& settings = Settings::getInstance();

	MapHandler(std::string fileName);
	void loadMapFromFile(std::string fileName);
	void setMapFileName(std::string fileName);
	std::vector<std::vector<unsigned int>> convertSpriteMapToRoadMap();
	std::vector<std::vector<unsigned int>> getSpriteMap();
	std::vector<std::vector<unsigned int>> getRoadMap();
	void convertSpriteMap();
	void findCarSpawnPoints();
	std::vector<sf::Vector2i> getCarSpawnPoints();
	RoadTypes getSpriteMapRoadType(sf::Vector2i currentPos);
	void displayRoadMap();
	void displayRoadMapGrid(sf::RenderWindow& window, const std::string fontPath);

private:
	std::string mapFileName;
	std::vector<std::vector<unsigned int>> spriteMap;
	std::vector<sf::Vector2i> carSpawnPoints;
	std::vector<std::vector<unsigned int>> roadMap;
};

