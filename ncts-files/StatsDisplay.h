#pragma once
#include "DynamicObject.h"
#include <iomanip>
#include <sstream>

class StatsDisplay : public DynamicObject
{
public:
    StatsDisplay();
    ~StatsDisplay() = default;
    void draw(sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window) override;
    void updateStats(int numOfCars, float scale, float avgSpeed);
private:
    Settings& settings = Settings::getInstance();
    sf::Text statNumberOfCarsLabel;
    sf::Text statNumberOfCarsValue;
    sf::Text statScaleLabel;
    sf::Text statScaleValue;
    sf::Text statAvgSpeedLabel;
    sf::Text statAvgSpeedValue;
    int numberOfCars = 0;
    float scaleOfCars = 0;
    float avgSpeedOfCars = 0;
};

