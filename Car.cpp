#include "Car.h"

Car::Car(sf::Vector2i position, Direction direction, std::shared_ptr<std::vector<std::vector<unsigned int>>> roadMap, float speed, std::string carTexturePath) : p_roadMap(roadMap)
{
	
	carTexture.loadFromFile(carTexturePath);
	carSprite.setTexture(carTexture);
	carSprite.setOrigin((sf::Vector2f)carTexture.getSize() / 2.0f);
	carSprite.setScale(1, 1);
	carCurrentPositionPoint = position;
	carDirection = direction;
	carNextDirection = direction;
	carTurnDirection = Direction::RIGHT;
	if (carDirection == Direction::UP)
	{
		carSprite.setRotation(0);
		carCurrentSpritePosition = sf::Vector2i(carCurrentPositionPoint.x * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness + carTexture.getSize().x / 2.f, carCurrentPositionPoint.y * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness - 1);
	}
	else if (carDirection == Direction::DOWN)
	{
		carSprite.setRotation(180);
		carCurrentSpritePosition = sf::Vector2i(carCurrentPositionPoint.x * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness + carTexture.getSize().x / 2.f, carCurrentPositionPoint.y * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness + carTexture.getSize().x / 2.0f );
	}
	else if (carDirection == Direction::LEFT)
	{
		carSprite.setRotation(-90);
		carCurrentSpritePosition = sf::Vector2i(carCurrentPositionPoint.x * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness -  carTexture.getSize().y / 2.f, carCurrentPositionPoint.y * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness + carTexture.getSize().x / 2.0f);
	}
	else if (carDirection == Direction::RIGHT)
	{
		carSprite.setRotation(90);
		carCurrentSpritePosition = sf::Vector2i(carCurrentPositionPoint.x * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness + carTexture.getSize().y / 2.f , carCurrentPositionPoint.y * 10 + settings.simulationBorderOffset + settings.simulationBorderThickness + carTexture.getSize().x / 2.0f);
	}
	
	carSprite.setPosition(carCurrentSpritePosition.x, carCurrentSpritePosition.y);
	nextPositionPoint = carCurrentPositionPoint;
	carSpeed = speed;
	isMoving = false;

}

void Car::carFindNextPositionPoint()
{
	sf::Vector2i potentialNextPosition = carCurrentPositionPoint;
	sf::Vector2i potentialNextTurnPosition = carCurrentPositionPoint;
	switch (carDirection)
	{
	case Direction::UP:
		potentialNextPosition.y -= 1;
		potentialNextTurnPosition.y -= 2;
		break;
	case Direction::DOWN:
		potentialNextPosition.y += 1;
		potentialNextTurnPosition.y += 2;
		break;
	case Direction::LEFT:
		potentialNextPosition.x -= 1;
		potentialNextTurnPosition.x -= 2;
		break;
	case Direction::RIGHT:
		potentialNextPosition.x += 1;
		potentialNextTurnPosition.x += 2;
		break;
	}

	if (!(potentialNextTurnPosition.x < 0 || potentialNextTurnPosition.x >= p_roadMap->at(0).size() || potentialNextTurnPosition.y < 0 || potentialNextTurnPosition.y >= p_roadMap->size()))
	{
			
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
	}
	else
	{
		outOfBounds = true;
	}


	if (!(potentialNextPosition.x < 0 || potentialNextPosition.x >= p_roadMap->at(0).size()-1 || potentialNextPosition.y < 0 || potentialNextPosition.y >= p_roadMap->size()))
	{
		unsigned int potentialNextValue = (*p_roadMap)[potentialNextPosition.y][potentialNextPosition.x];
		if (roadValues.find(potentialNextValue) != roadValues.end())
		{
			nextPositionPoint = potentialNextPosition;
		}
		else if (turnTriggerValues.find(potentialNextValue) != turnTriggerValues.end())
		{
			nextPositionPoint = potentialNextPosition;
			carNextDirection = tempDirection;
		}
		else
		{
			nextPositionPoint = carCurrentPositionPoint;
		}
	}
	else
	{
		nextPositionPoint = carCurrentPositionPoint;
		outOfBounds = true;
	}
}

Direction Car::chooseRandomDirection(unsigned int triggerValue)
{

	std::vector<Direction> possibleDirections = roadPatterns.possibleTurnDirections[triggerValue];
	Direction newDirection = possibleDirections[rand() % possibleDirections.size()];
	return newDirection;
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

		// Apply movement based on direction
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

void Car::carAdjustSprite()
{
	int i = 1;
	if (carDirection == Direction::UP)
	{
		carSprite.move(0, -1*(carTexture.getSize().x/2.0f) - 1);
	}
	else if (carDirection == Direction::DOWN)
	{
		carSprite.move(0, 1 * (carTexture.getSize().x / 2.0f) + 1);
	}
	else if (carDirection == Direction::LEFT)
	{
		carSprite.move(1 * (carTexture.getSize().x / 2.0f) + 1, 0);
	}
	else if (carDirection == Direction::RIGHT)
	{
		carSprite.move(-1 * (carTexture.getSize().x / 2.0f) - 1, 0);
	}
	needsAdjusting = false;
	i = i*-1;
	if (carNextDirection == Direction::DOWN && isTurning && carDirection == Direction::RIGHT)
	{
		carSprite.move(0, 1 * (carTexture.getSize().x / 2.0f) + 1);
	}
	else if (carNextDirection == Direction::RIGHT && isTurning)
	{
		//carSprite.move(-1 * (carTexture.getSize().x / 2.0f) + 1, 0);
		carSprite.move(0, 1 * (carTexture.getSize().x / 2.0f) + 1);
	}
	else if (carNextDirection == Direction::DOWN && isTurning && carDirection == Direction::LEFT)
	{
		carSprite.move(-1 * (carTexture.getSize().x / 2.0f) + 1, 0);
	}
	else if (carNextDirection == Direction::RIGHT && isTurning && carDirection == Direction::DOWN)
	{
		carSprite.move(-1 * (carTexture.getSize().x / 2.0f) + 1, 0);
	}
}

Direction Car::checkCarTurnDirection(Direction nextDir)
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




void Car::update(sf::RenderWindow& window)
{
	if(!isMoving) carFindNextPositionPoint();
	if(!outOfBounds)
	{
		carMoveSprite();
		
		if (isTurning)
		{
			carTurnSprite();
			//if (needsAdjusting) carAdjustSprite();		
		}
		carCurrentPositionPoint = nextPositionPoint;
		carDirection = carNextDirection;
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





