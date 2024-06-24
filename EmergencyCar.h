#pragma once
#include "Car.h"
class EmergencyCar : public Car
{
	using Car::Car;
	void carFindNextPositionPoint() override;
	void update(sf::RenderWindow& window) override;
	bool isOvertaking = false;
	int overtakingCounter = 0;
	int carRotateBy = 9;
	bool skipMove = false;
	int skipCounter = 0;
};

