#include "Car.h"

std::vector<PositionInfo> Car::currentPositions = {};
std::vector<PositionInfo> Car::nextPositions = {};

Car::Car(sf::Vector2i position, Direction direction, std::shared_ptr<std::vector<std::vector<unsigned int>>> roadMap, float speed, std::string carTexturePath) : p_roadMap(roadMap)
{
	
	carTexture.loadFromFile(carTexturePath);
	carSprite.setTexture(carTexture);
	carSprite.setOrigin((sf::Vector2f)carTexture.getSize() / 2.0f);
	
	carDirection = direction;
	carNextDirection = direction;
	carTurnDirection = Direction::RIGHT;
	carSetSpawnPosition(position);
	nextPositionPoint = carCurrentPositionPoint;
	carSpeed = speed;
	isMoving = false;
	carOriginalSpeed = speed;
	carPreviousPositionPoint = carCurrentPositionPoint;
	carSprite.setScale(0.8, 0.8);
}

void Car::carSetSpawnPosition(sf::Vector2i position)
{
	carSprite.setOrigin((sf::Vector2f)carTexture.getSize() / 2.0f);
	carCurrentPositionPoint = position;
	float rotation = 0;
	sf::Vector2f offsetAdjustment(0.f, 0.f);

	switch (carDirection) 
	{
	case Direction::UP:
            rotation = 0;
			offsetAdjustment = sf::Vector2f(carTexture.getSize().x / 2.f - 2, -3);
            break;
	case Direction::DOWN:
            rotation = 180;
			offsetAdjustment = sf::Vector2f(carTexture.getSize().x / 2.f - 2, carTexture.getSize().y / 2.0f + 3);
            break;
	case Direction::LEFT:
            rotation = -90;
			offsetAdjustment = sf::Vector2f(carTexture.getSize().y / 2.f -3, carTexture.getSize().x / 2.0f);
            break;
	case Direction::RIGHT:
            rotation = 90;
			offsetAdjustment = sf::Vector2f(carTexture.getSize().y / 2.f + 3, carTexture.getSize().x / 2.0f - 2);
            break;
    }

	
	carSprite.setRotation(rotation);
	sf::Vector2i basePosition = sf::Vector2i(carCurrentPositionPoint.x * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness, carCurrentPositionPoint.y * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness);
	carCurrentSpritePosition = basePosition + sf::Vector2i(offsetAdjustment);

	if ((carDirection == Direction::UP || carDirection == Direction::DOWN) && carCurrentPositionPoint.x % 2 == 0)
	{
		carCurrentSpritePosition.x += 3;
	}
	else if ((carDirection == Direction::LEFT || carDirection == Direction::RIGHT) && carCurrentPositionPoint.y % 2 == 0)
	{
		carCurrentSpritePosition.y += 3;
	}
	else
	{
		if (carDirection == Direction::UP || carDirection == Direction::DOWN)
		{
			carCurrentSpritePosition.x -= 2;
		}
		else
		{
			carCurrentSpritePosition.y -= 2;
		}
	}

	carSprite.setPosition(carCurrentSpritePosition.x, carCurrentSpritePosition.y);
}

void Car::resetToNewPosition(sf::Vector2i newPosition, Direction newDirection)
{
	removeOutOfBoundsFromPositions();
	outOfBounds = false;
	carDirection = newDirection;
	carNextDirection = newDirection;
	carTurnDirection = Direction::RIGHT;
	carSpeed = carOriginalSpeed;
	isMoving = false;
	isTurning = false;
	isWaiting = false;
	waitCounter = 0;
	carFrameCount = 0;
	rotationCount = 0;
	carSetSpawnPosition(newPosition);
	
}

const sf::Vector2i Car::getCarNextPositionPoint()
{
	return nextPositionPoint;
}

const sf::Vector2i Car::getCarCurrentPositionPoint()
{
	return carCurrentPositionPoint;
}

void Car::carFindNextPositionPoint()
{

	int crashDetectionRange = (int)carSpeed;

	sf::Vector2i potentialNextPosition = carCurrentPositionPoint;
	sf::Vector2i potentialNextTurnPosition = carCurrentPositionPoint;
	sf::Vector2i potentialCrashPosition = carCurrentPositionPoint;
	switch (carDirection)
	{
	case Direction::UP:
		potentialNextPosition.y -= 1;
		potentialNextTurnPosition.y -= 2;
		potentialCrashPosition.y -= crashDetectionRange;
		break;
	case Direction::DOWN:
		potentialNextPosition.y += 1;
		potentialNextTurnPosition.y += 2;
		potentialCrashPosition.y += crashDetectionRange;
		break;
	case Direction::LEFT:
		potentialNextPosition.x -= 1;
		potentialNextTurnPosition.x -= 2;
		potentialCrashPosition.x -= crashDetectionRange;
		break;
	case Direction::RIGHT:
		potentialNextPosition.x += 1;
		potentialNextTurnPosition.x += 2;
		potentialCrashPosition.x += crashDetectionRange;
		break;
	}

	auto isPositionBlocked = [&](const sf::Vector2i& pos, Direction dir) {
		for (const auto& info : nextPositions) {
			if (info.position == pos && info.direction == dir) {
				return true;
			}
		}
		for (const auto& info : currentPositions) {
			if (info.position == pos) {
				return true;
			}
		}
		return false;
		};

	sf::Vector2i blockageDetectedAt = sf::Vector2i(0,0); 
	bool isBlocked = false;

	if (isPositionBlocked(potentialNextPosition, carDirection))
	{
		blockageDetectedAt = potentialNextPosition;
		isBlocked = true;
	}
	else if (isPositionBlocked(potentialNextTurnPosition, carDirection))
	{
		blockageDetectedAt = potentialNextTurnPosition;
		isBlocked = true;
	}
	else if (isPositionBlocked(potentialCrashPosition, carDirection)) 
	{
		blockageDetectedAt = potentialCrashPosition;
		isBlocked = true;
	}

	if (!(potentialNextTurnPosition.x < 0 || potentialNextTurnPosition.x >= p_roadMap->at(0).size() || potentialNextTurnPosition.y < 0 || potentialNextTurnPosition.y >= p_roadMap->size()))
	{
		if (!(potentialNextPosition.x < 0 || potentialNextPosition.x >= p_roadMap->at(0).size() - 1 || potentialNextPosition.y < 0 || potentialNextPosition.y >= p_roadMap->size()))
		{

			if (!isBlocked)
			{
				removeOutOfBoundsFromPositions();
				unsigned int potentialNextTurnValue = (*p_roadMap)[potentialNextTurnPosition.y][potentialNextTurnPosition.x];
				if (turnTriggerValues.find(potentialNextTurnValue) != turnTriggerValues.end())
				{
					tempDirection = chooseRandomDirection(potentialNextTurnValue);
					if (carDirection != tempDirection)
					{
						carTurnDirection = checkCarTurnDirection(tempDirection);
						isTurning = true;
					}
				}

				unsigned int potentialNextValue = (*p_roadMap)[potentialNextPosition.y][potentialNextPosition.x];
				if (roadValues.find(potentialNextValue) != roadValues.end())
				{
					nextPositionPoint = potentialNextPosition;
					carPushBackNextPosition(nextPositionPoint, carSpeed, carDirection);
					isWaiting = false;
				}
				else if (turnTriggerValues.find(potentialNextValue) != turnTriggerValues.end())
				{
					nextPositionPoint = potentialNextPosition;
					carNextDirection = tempDirection;
					carPushBackNextPosition(nextPositionPoint, carSpeed, carDirection);
					isWaiting = false;
				}
				else
				{
					outOfBounds = true;
				}
			}
			else
			{
				isWaiting = true;
				auto slowDownSpeed = [&](const sf::Vector2i& pos) {
					for (const auto& info : currentPositions)
					{
						if (info.position == pos)
						{
							return info.speed;
						}
					}
					};

				if(slowDownSpeed(blockageDetectedAt) > 0.1) carSpeed = slowDownSpeed(blockageDetectedAt);
			}
		}
		else
		{
			removeOutOfBoundsFromPositions();
			outOfBounds = true;
		}
	}
	else
	{
		removeOutOfBoundsFromPositions();
		outOfBounds = true;
		
	}
}

Direction Car::chooseRandomDirection(unsigned int triggerValue)
{

	std::vector<Direction> possibleDirections = roadPatterns.possibleTurnDirections[triggerValue];
	Direction newDirection = possibleDirections[rand() % possibleDirections.size()];
	return newDirection;
}

const void Car::carPushBackCurrentPosition(sf::Vector2i position, float cspeed, Direction cdir)
{
	PositionInfo positionInfo; 
	positionInfo.position = carCurrentPositionPoint;
	positionInfo.speed = cspeed;
	positionInfo.direction = cdir;
	auto it = std::find_if(currentPositions.begin(), currentPositions.end(), [&](const PositionInfo& info) {
		return info.position == positionInfo.position;
		});
	if (it == currentPositions.end())
	{
		currentPositions.push_back(positionInfo);
	}
}

const void Car::carPushBackNextPosition(sf::Vector2i position, float cspeed, Direction cdir)
{
	PositionInfo positionInfo; 
	positionInfo.position = nextPositionPoint;
	positionInfo.speed = cspeed;
	positionInfo.direction = cdir;
	auto it = std::find_if(nextPositions.begin(), nextPositions.end(), [&](const PositionInfo& info) {
		return info.position == positionInfo.position;
		});
	if (it == nextPositions.end())
	{
		nextPositions.push_back(positionInfo);
	}
}

void Car::carMoveSprite()
{

	static float moveAccumulator = 0.0f; 
	

	if (carFrameCount < 10 && !outOfBounds)
	{
		isMoving = true;

		float moveStep = carSpeed + moveAccumulator;
		int movePixels = static_cast<int>(moveStep); 
		moveAccumulator = moveStep - movePixels; 

		if (carDirection == Direction::UP)
		{
			carSprite.move(0, -movePixels);
		}
		else if (carDirection == Direction::DOWN)
		{
			carSprite.move(0, movePixels);
		}
		else if (carDirection == Direction::LEFT)
		{
			carSprite.move(-movePixels, 0);
		}
		else if (carDirection == Direction::RIGHT)
		{
			carSprite.move(movePixels, 0);
		}
		carFrameCount += movePixels;

		const float leftBound = settings.simulationBorderOffset + settings.simulationBorderThickness;
		const float topBound = settings.simulationBorderOffset + settings.simulationBorderThickness;
		const float rightBound = settings.simulationBorderOffset + settings.simulationBorderSize.x - settings.simulationBorderThickness;
		const float bottomBound = settings.simulationBorderOffset + settings.simulationBorderSize.y - settings.simulationBorderThickness;

		sf::Vector2f pos = carSprite.getPosition();
		if (pos.x < leftBound || pos.x > rightBound || pos.y < topBound || pos.y > bottomBound)
		{
			removeOutOfBoundsFromPositions();
			outOfBounds = true;
		}

		if (carFrameCount > 10)
		{
			int excess = carFrameCount - 10;
			if (carDirection == Direction::UP) carSprite.move(0, excess);
			else if (carDirection == Direction::DOWN) carSprite.move(0, -excess);
			else if (carDirection == Direction::LEFT) carSprite.move(excess, 0);
			else if (carDirection == Direction::RIGHT) carSprite.move(-excess, 0);
			carFrameCount = 10;
		}
	}
	else
	{
		carFrameCount = 0;
		isMoving = false;
	}

	
}

void Car::carTurnSprite()
{
	static float rotateAccumulator = 0.0f;

	if (isTurning && rotationCount < 90)
	{
		float rotateStep = (45.f / (10.f / carSpeed)) + rotateAccumulator;
		int rotateDegrees = static_cast<int>(rotateStep);
		rotateAccumulator = rotateStep - rotateDegrees;

		if (carTurnDirection == Direction::RIGHT)
		{
			carSprite.rotate(rotateDegrees);
		}
		else if (carTurnDirection == Direction::LEFT)
		{
			carSprite.rotate(-rotateDegrees);
		}
		rotationCount += rotateDegrees;
		
		
		if (rotationCount > 90)
		{
			int excess = rotationCount - 90;
			if (carTurnDirection == Direction::LEFT) carSprite.rotate(excess);
			else if (carTurnDirection == Direction::RIGHT) carSprite.rotate(-excess);
			rotationCount = 90;
		}
	}
	else if (rotationCount == 90)
	{
		isTurning = false;
		rotationCount = 0;
	}
}



const Direction Car::checkCarTurnDirection(Direction nextDir)
{

	if (carDirection == Direction::UP) return nextDir;

	int currentDirection = static_cast<int>(carDirection);
	int nextDirection = static_cast<int>(nextDir);

	if (carDirection == Direction::DOWN) 
	{
		if (nextDir == Direction::LEFT) return Direction::RIGHT;
		if (nextDir == Direction::RIGHT) return Direction::LEFT;
	}
	else 
	{
		int delta = (nextDirection - currentDirection + 4) % 4;
		if (delta == 1) return Direction::RIGHT; 
		if (delta == 3) return Direction::LEFT; 
	}

	return carDirection;
}

void Car::removeOutOfBoundsFromPositions()
{
	nextPositions.erase(std::remove_if(nextPositions.begin(), nextPositions.end(), [&](const PositionInfo& info)
		{ return info.position == nextPositionPoint; }), nextPositions.end());

	currentPositions.erase(std::remove_if(currentPositions.begin(), currentPositions.end(), [&](const PositionInfo& info) 
		{ return info.position == carCurrentPositionPoint; }), currentPositions.end());
}


void Car::update(sf::RenderWindow& window)
{

	if (!isMoving && !outOfBounds)
	{
		carFindNextPositionPoint();
		carPushBackCurrentPosition(carPreviousPositionPoint, carSpeed, carDirection);
		if (!isWaiting) waitCounter++;
		if (waitCounter > 10)
		{
			carSpeed = carOriginalSpeed;
			waitCounter = 0;
		}
	}
	if(!outOfBounds)
	{
		if (!isWaiting) carMoveSprite();
		if (isTurning && !isWaiting) carTurnSprite();
		carDirection = carNextDirection;
	}
	if (!isMoving)
	{
		currentPositions.erase(std::remove_if(currentPositions.begin(), currentPositions.end(), [&](const PositionInfo& info)
			{ return info.position == carCurrentPositionPoint; }), currentPositions.end());
		carCurrentPositionPoint = nextPositionPoint;
	}
}

void Car::draw(sf::RenderWindow& window)
{
	window.draw(carSprite);
}

sf::Sprite &Car::getCarSprite()
{
	return carSprite;
}

float &Car::getCarCurrentSpeed()
{
	return carSpeed;
}

float &Car::getCarOriginalSpeed()
{
	return carOriginalSpeed;
}






