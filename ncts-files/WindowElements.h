#pragma once
#include "StaticObject.h"
#include <iostream>
#include "settings.h"

class WindowElements : public StaticObject
{
private:
	Settings& settings = Settings::getInstance();
	sf::RectangleShape simulationBorder;
	sf::Text scaleText;
	sf::Text numberOfCarsText;
	sf::Font font;
public:
	WindowElements();
	~WindowElements() = default;
	void draw(sf::RenderWindow& window) override;
};

