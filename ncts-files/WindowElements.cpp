#include "WindowElements.h"


WindowElements::WindowElements()
{
    Settings& settings = Settings::getInstance();
    simulationBorder.setSize(settings.simulationBorderSize);
    simulationBorder.setFillColor(sf::Color::Transparent);
    simulationBorder.setOutlineColor(sf::Color::Black);
    simulationBorder.setOutlineThickness(settings.simulationBorderThickness);
    simulationBorder.setPosition(50 + 1 * settings.simulationBorderThickness, 50 + 1 * settings.simulationBorderThickness);

    
    scaleText.setString("Scale");
    scaleText.setFont(*Settings::getInstance().font);
    scaleText.setFillColor(sf::Color::Black);
    scaleText.setCharacterSize(11);
    scaleText.setPosition(settings.StopButtonPosition.x + settings.buttonSize.x/3, settings.StopButtonPosition.y + settings.buttonSize.x/2 + 35);

    numberOfCarsText.setString("Number of cars");
    numberOfCarsText.setFont(*Settings::getInstance().font);
    numberOfCarsText.setFillColor(sf::Color::Black);
    numberOfCarsText.setCharacterSize(11);
    numberOfCarsText.setPosition(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 2*settings.buttonSize.x + settings.buttonSize.y);
}

void WindowElements::draw(sf::RenderWindow& window)
{
	window.draw(simulationBorder);
    window.draw(scaleText);
    window.draw(numberOfCarsText);
}