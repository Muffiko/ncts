#pragma once
#include "GraphicObject.h"
class StaticObject : public GraphicObject
{
public:
	StaticObject() = default;
	~StaticObject() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
};

