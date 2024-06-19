#pragma once
#include <SFML/Graphics.hpp>

class Settings
{
public:
    static Settings& getInstance()
    {
        static Settings instance;
        return instance;
    }

    Settings(Settings const&) = delete; 
    void operator=(Settings const&) = delete;

    sf::Vector2f simulationBorderSize = sf::Vector2f(1360.f, 800.f);
    float simulationBorderThickness = 3.f;
    float simulationBorderOffset = 50.f;
	sf::Vector2f spriteMapTileSize = sf::Vector2f(80.f, 80.f);
    sf::Vector2i roadMapTileSize = sf::Vector2i(80/10, 80/10);
    sf::Vector2f simulationBorderPosition = sf::Vector2f(simulationBorderOffset - 2.f * simulationBorderThickness, simulationBorderOffset - 2.f * simulationBorderThickness);
    sf::Vector2i windowSize = sf::Vector2i(1600, 900);

	sf::Vector2f buttonSize = sf::Vector2f(80.f, 30.f);
	sf::Vector2f StartButtonPosition = sf::Vector2f(windowSize.x-((windowSize.x-simulationBorderSize.x)/2.f)-(buttonSize.x/4.f), simulationBorderOffset);
    sf::Vector2f StopButtonPosition = sf::Vector2f(StartButtonPosition.x, StartButtonPosition.y + buttonSize.y + 10);
private:
    Settings() {} // Private constructor
};