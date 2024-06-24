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


struct PositionInfo 
{
    sf::Vector2i position;
    float speed;
    Direction direction;
};

class Car : public DynamicObject
{
public:
    Car(sf::Vector2i position, Direction direction, std::shared_ptr<std::vector<std::vector<unsigned int>>> p_roadMap, float speed, std::string carTexturePath);
    void update(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;   
    sf::Sprite &getCarSprite();
    void resetToNewPosition(sf::Vector2i newPosition, Direction newDirection);
    const sf::Vector2i getCarNextPositionPoint();
    const sf::Vector2i getCarCurrentPositionPoint();
    float &getCarCurrentSpeed();
    float &getCarOriginalSpeed();
    

public:
    bool outOfBounds = false;

public:
    static std::vector<PositionInfo> currentPositions;
    static std::vector<PositionInfo> nextPositions;

protected:
    RoadPatterns& roadPatterns = RoadPatterns::getInstance();
    Settings& settings = Settings::getInstance();

protected:
    void carSetSpawnPosition(sf::Vector2i position);
    void carFindNextPositionPoint();
    void carMoveSprite();
    void carTurnSprite();
    const void carPushBackCurrentPosition(sf::Vector2i position, float cspeed, Direction cdir);
    const void carPushBackNextPosition(sf::Vector2i position, float cspeed, Direction cdir);
    void removeOutOfBoundsFromPositions();
    bool carCheckIfBlocked();
    Direction chooseRandomDirection(unsigned int triggerValue);
    Direction carTurnDirection;
    const Direction checkCarTurnDirection(Direction nextDir);

protected:
    std::shared_ptr<std::vector<std::vector<unsigned int>>> p_roadMap;
    sf::Vector2i carCurrentPositionPoint;
    sf::Vector2i carCurrentSpritePosition;
    sf::Vector2i carPreviousPositionPoint;
    Direction carDirection;
    Direction carNextDirection;
    sf::Sprite carSprite;
    sf::Texture carTexture;
    sf::Vector2f carRotation;
    sf::Vector2i nextPositionPoint;
    bool isMoving = false;
    bool isTurning = false;
    bool isWaiting = false;
    int waitCounter = 0;
    float carFrameCount = 0;
    float rotationCount = 0;
    float carSpeed = 0.5f;
    float carOriginalSpeed = 0.5f;
    float carSlowDownSpeed = 0.5f;
    Direction tempDirection = Direction::UP;

protected:
    const std::unordered_set<unsigned int> roadValues = { 1,2,3,4 };
    const std::unordered_set<unsigned int> turnTriggerValues = { 5,6,7,8,9,10,11,12 };
    

};

