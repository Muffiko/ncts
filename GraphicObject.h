#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "settings.h"
class GraphicObject
{
public:
	
	GraphicObject() = default;
	~GraphicObject() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	bool isActive = true;
};

