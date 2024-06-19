#pragma once
#include "DynamicObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <sstream>
#include "RoadPatterns.h"
#include "RoadTypes.h"
#include "settings.h"
#include <unordered_set>



class Car : public DynamicObject
{
public:
    RoadPatterns& roadPatterns = RoadPatterns::getInstance();
    Settings& settings = Settings::getInstance();
    Car(sf::Vector2i position, Direction direction, std::shared_ptr<std::vector<std::vector<unsigned int>>> p_roadMap, float speed, std::string carTexturePath);
    void update(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    bool outOfBounds = false;
    sf::Sprite &getCarSprite();
protected:
    void carFindNextPositionPoint();
    void carMoveSprite();
    void carTurnSprite();
    void carAdjustSprite();
    std::shared_ptr<std::vector<std::vector<unsigned int>>> p_roadMap;
    sf::Vector2i carCurrentPositionPoint;
    sf::Vector2i carCurrentSpritePosition;
    float carSpeed = 0.5f;
    Direction carDirection;
    Direction carNextDirection;
    sf::Sprite carSprite;
    sf::Texture carTexture;
    sf::Vector2f carRotation;
    sf::Vector2i nextPositionPoint;
    bool isMoving = false;
    bool isTurning = false;
    bool needsAdjusting = false;
    float carFrameCount = 0;
    float rotationCount = 0;
    std::unordered_set<unsigned int> roadValues = { 1,2,3,4 };
    std::unordered_set<unsigned int> turnTriggerValues = { 5,6,7,8,9,10,11,12 };
    Direction chooseRandomDirection(unsigned int triggerValue);
    Direction carTurnDirection;
    Direction checkCarTurnDirection(Direction nextDir);
    Direction tempDirection = Direction::UP;

};

