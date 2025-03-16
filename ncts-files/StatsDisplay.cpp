#include "StatsDisplay.h"

StatsDisplay::StatsDisplay()
{
    statNumberOfCarsLabel.setString("Cars: ");
    statScaleLabel.setString("Scale: ");
    statAvgSpeedLabel.setString("Avg speed: ");


    statNumberOfCarsLabel.setFont(*Settings::getInstance().font);
    statNumberOfCarsLabel.setFillColor(sf::Color::Black);
    statNumberOfCarsLabel.setCharacterSize(15);
    statNumberOfCarsLabel.setPosition(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 3.5 * settings.buttonSize.x);

    statScaleLabel.setFont(*Settings::getInstance().font);
    statScaleLabel.setFillColor(sf::Color::Black);
    statScaleLabel.setCharacterSize(15);
    statScaleLabel.setPosition(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 3.7 * settings.buttonSize.x);

    statAvgSpeedLabel.setFont(*Settings::getInstance().font);
    statAvgSpeedLabel.setFillColor(sf::Color::Black);
    statAvgSpeedLabel.setCharacterSize(15);
    statAvgSpeedLabel.setPosition(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 3.9 * settings.buttonSize.x);


    statNumberOfCarsValue.setFont(*Settings::getInstance().font);
    statNumberOfCarsValue.setFillColor(sf::Color::Red);
    statNumberOfCarsValue.setCharacterSize(15);
    statNumberOfCarsValue.setPosition(statNumberOfCarsLabel.getGlobalBounds().width + statNumberOfCarsLabel.getPosition().x, statNumberOfCarsLabel.getPosition().y);

    statScaleValue.setFont(*Settings::getInstance().font);
    statScaleValue.setFillColor(sf::Color::Red);
    statScaleValue.setCharacterSize(15);
    statScaleValue.setPosition(statScaleLabel.getGlobalBounds().width + statScaleLabel.getPosition().x, statScaleLabel.getPosition().y);

    statAvgSpeedValue.setFont(*Settings::getInstance().font);
    statAvgSpeedValue.setFillColor(sf::Color::Red);
    statAvgSpeedValue.setCharacterSize(15);
    statAvgSpeedValue.setPosition(statAvgSpeedLabel.getGlobalBounds().width + statAvgSpeedLabel.getPosition().x, statAvgSpeedLabel.getPosition().y);

}

void StatsDisplay::draw(sf::RenderWindow& window)
{
    window.draw(statNumberOfCarsLabel);
    window.draw(statNumberOfCarsValue);
    window.draw(statScaleLabel);
    window.draw(statScaleValue);
    window.draw(statAvgSpeedLabel);
    window.draw(statAvgSpeedValue);
}

void StatsDisplay::update(sf::RenderWindow& window)
{
    std::stringstream ssNumberOfCars, ssScale, ssAvgSpeed;

    ssNumberOfCars << numberOfCars;
    statNumberOfCarsValue.setString(ssNumberOfCars.str());

    ssScale << std::fixed << std::setprecision(2) << scaleOfCars;
    statScaleValue.setString(ssScale.str());

    ssAvgSpeed << std::fixed << std::setprecision(2) << avgSpeedOfCars;
    statAvgSpeedValue.setString(ssAvgSpeed.str());
}

void StatsDisplay::updateStats(int numOfCars, float scale, float avgSpeed)
{
    numberOfCars = numOfCars;
    scaleOfCars = scale;
    avgSpeedOfCars = avgSpeed;
}
