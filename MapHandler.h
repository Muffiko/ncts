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
#include <filesystem>

class MapHandler
{ //17x10
public:
	
	Settings& settings = Settings::getInstance();
	MapHandler() {}
	MapHandler(std::string fileName);
	void loadMapFromFile(const std::string& fileName);
	void setMapFileName(std::string fileName);
	std::vector<std::vector<unsigned int>> convertSpriteMapToRoadMap();
	std::vector<std::vector<unsigned int>> getSpriteMap();
	std::vector<std::vector<unsigned int>> getRoadMap();
	void convertSpriteMap(bool fix);
	void findCarSpawnPoints();
	std::vector<sf::Vector2i> getCarSpawnPoints();
	RoadTypes getSpriteMapRoadType(sf::Vector2i currentPos);
	void displayRoadMap();
	void displayRoadMapGrid(sf::RenderWindow& window, const std::string fontPath);
	void mapClear();
	void saveSpriteMapToFile(const std::string& fileName);
	std::vector<std::vector<unsigned int>> spriteMap;

private:
	std::string mapFileName;
	std::vector<sf::Vector2i> carSpawnPoints;
	std::vector<std::vector<unsigned int>> roadMap;
};

