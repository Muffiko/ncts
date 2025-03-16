#include "EmergencyCar.h"

void EmergencyCar::carFindNextPositionPoint()
{
	int crashDetectionRange = 4;

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

	sf::Vector2i blockageDetectedAt = sf::Vector2i(0, 0);
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
				removeOutOfBoundsFromPositions();
				sf::Vector2i potentialTurnPosition = carCurrentPositionPoint;
				if (carDirection == Direction::UP)
				{
					potentialTurnPosition.x += 1;
					if (!isPositionBlocked(potentialTurnPosition, Direction::RIGHT) && potentialTurnPosition.x != 0)
					{
						nextPositionPoint = potentialTurnPosition;
						carTurnDirection = Direction::RIGHT;
						tempDirection = Direction::LEFT;
					}
					else
					{
						potentialTurnPosition.x -= 1;
						if (!isPositionBlocked(potentialTurnPosition, Direction::LEFT) && potentialTurnPosition.x != 0)
						{
							nextPositionPoint = potentialTurnPosition;
							carTurnDirection = Direction::LEFT;
							tempDirection = Direction::RIGHT;
						}
					}
				}
				else if (carDirection == Direction::DOWN)
				{
					potentialTurnPosition.x += 1;
					if (!isPositionBlocked(potentialTurnPosition, Direction::RIGHT) && potentialTurnPosition.x != 0)
					{
						nextPositionPoint = potentialTurnPosition;
						carTurnDirection = Direction::LEFT;
						tempDirection = Direction::RIGHT;
					}
					else
					{
						potentialTurnPosition.x -= 1;
						if (!isPositionBlocked(potentialTurnPosition, Direction::LEFT) && potentialTurnPosition.x != 0)
						{
							nextPositionPoint = potentialTurnPosition;
							carTurnDirection = Direction::RIGHT;
							tempDirection = Direction::LEFT;
						}
					}
				}
				else if (carDirection == Direction::LEFT)
				{
					potentialTurnPosition.y += 1;
					if (!isPositionBlocked(potentialTurnPosition, Direction::DOWN) && potentialTurnPosition.x != 0)
					{
						nextPositionPoint = potentialTurnPosition;
						carTurnDirection = Direction::LEFT;
						tempDirection = Direction::RIGHT;
					}
					else
					{
						potentialTurnPosition.y -= 1;
						if (!isPositionBlocked(potentialTurnPosition, Direction::UP) && potentialTurnPosition.x != 0)
						{
							nextPositionPoint = potentialTurnPosition;
							carTurnDirection = Direction::RIGHT;
							tempDirection = Direction::LEFT;
						}
					}
				}
				else if (carDirection == Direction::RIGHT)
				{
					potentialTurnPosition.y += 1;
					if (!isPositionBlocked(potentialTurnPosition, Direction::DOWN) && potentialTurnPosition.x != 0)
					{
						nextPositionPoint = potentialTurnPosition;
						carTurnDirection = Direction::RIGHT;
						tempDirection = Direction::LEFT;
					}
					else
					{
						potentialTurnPosition.y -= 1;
						if (!isPositionBlocked(potentialTurnPosition, Direction::UP) && potentialTurnPosition.x != 0)
						{
							nextPositionPoint = potentialTurnPosition;
							carTurnDirection = Direction::LEFT;
							tempDirection = Direction::RIGHT;
						}
					}
					isOvertaking = true;
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

					if (slowDownSpeed(blockageDetectedAt) > 0.1) carSpeed = slowDownSpeed(blockageDetectedAt);
				}
			
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

void EmergencyCar::update(sf::RenderWindow& window)
{
	if (isOvertaking)
	{
		if (carDirection == Direction::UP)
		{
			carSprite.move(0, 1);
		}
		else if (carDirection == Direction::DOWN)
		{
			carSprite.move(0, -1);
		}
		else if (carDirection == Direction::LEFT)
		{
			carSprite.move(1, 0);
		}
		else if (carDirection == Direction::RIGHT)
		{
			carSprite.move(-1, 0);
		}
		overtakingCounter++;
		if (carTurnDirection == Direction::RIGHT)
		{
			
			carSprite.rotate(carRotateBy);
			if (carDirection == Direction::UP)
			{
				carSprite.move(-1.2, 0);
			}
			else if (carDirection == Direction::DOWN)
			{
				carSprite.move(1.2, 0);
			}
			else if (carDirection == Direction::LEFT)
			{
				carSprite.move(0, -1.2);
			}
			else if (carDirection == Direction::RIGHT)
			{
				carSprite.move(0, 1.2);
			}

		}
		else if (carTurnDirection == Direction::LEFT)
		{
			carSprite.rotate(carRotateBy);
			if (carDirection == Direction::UP)
			{
				carSprite.move(1.2, 0);
			}
			else if (carDirection == Direction::DOWN)
			{
				carSprite.move(-1.2, 0);
			}
			else if (carDirection == Direction::LEFT)
			{
				carSprite.move(0, 1.2);
			}
			else if (carDirection == Direction::RIGHT)
			{
				carSprite.move(0, -1.2);
			}
		}
		if (overtakingCounter == 5)
		{
			carRotateBy *= -1;
		}
		if (overtakingCounter == 10)
		{
			overtakingCounter = 0;
			carTurnDirection = tempDirection;
			carCurrentPositionPoint = nextPositionPoint;
			isOvertaking = false;
			skipMove = true;
		}
	}
	else
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
		if (!outOfBounds)
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
}

