#include "WindowElements.h"


WindowElements::WindowElements()
{
    Settings& settings = Settings::getInstance();
    simulationBorder.setSize(settings.simulationBorderSize);
    simulationBorder.setFillColor(sf::Color::Transparent);
    simulationBorder.setOutlineColor(sf::Color::Black);
    simulationBorder.setOutlineThickness(settings.simulationBorderThickness);
    simulationBorder.setPosition(50 + 1 * settings.simulationBorderThickness, 50 + 1 * settings.simulationBorderThickness);
}

void WindowElements::draw(sf::RenderWindow& window)
{
	window.draw(simulationBorder);
}