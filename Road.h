#pragma once
#include "StaticObject.h"
#include "RoadTypes.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

class Road : public StaticObject
{
private:
    sf::Sprite roadSprite;
    sf::Vector2f position;
    RoadTypes roadType;
    sf::Texture roadTexture; 

    void setRoadSprite();

public:
    Road(sf::Vector2f position, RoadTypes roadType);
    void draw(sf::RenderWindow& window) override;
};
