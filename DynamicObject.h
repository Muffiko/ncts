#pragma once
#include "GraphicObject.h"
class DynamicObject : public GraphicObject
{
public:
	virtual void update(sf::RenderWindow& window) = 0;
};

