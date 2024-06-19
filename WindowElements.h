#pragma once
#include "StaticObject.h"
#include <iostream>
#include "settings.h"

class WindowElements : public StaticObject
{
private:
	sf::RectangleShape simulationBorder;
	Settings& settings = Settings::getInstance();
public:
	WindowElements();
	~WindowElements() = default;
	void draw(sf::RenderWindow& window) override;
};

