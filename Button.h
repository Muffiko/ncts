#pragma once
#include "DynamicObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "SimulationRun.h"

class SimulationRun;

class Button : public DynamicObject
{
protected:
	SimulationRun* simRun = nullptr;

public:

	Button(std::string text, std::string fontPath, sf::Vector2f position, SimulationRun* simRun);
	void update(sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	virtual void onClick() {}

	void setFontSize(unsigned int size);
	void setButtonFont(const sf::Font& font);
	void setButtonText(const sf::Text& text);
	void setButtonPosition(const sf::Vector2f& position);
	void setButtonSize(const sf::Vector2f& size);
	void setButtonBackground(const sf::RectangleShape& background);
	void setButtonTextColor(const sf::Color& color);
	void setButtonBackgroundColor(const sf::Color& color);
	void setButtonOutlineColor(const sf::Color& color);
	void setButtonBackgroundColorPressed(const sf::Color& color);
	void setButtonBackgroundColorHovered(const sf::Color& color);
	void setButtonTextColorPressed(const sf::Color& color);
	void setButtonTextColorHovered(const sf::Color& color);
	void setButtonOutlineThickness(float thickness);

protected:
	Settings& settings = Settings::getInstance();
	unsigned int fontSize = 12;
	sf::Font buttonFont;
	sf::Text buttonText;
	sf::Vector2f buttonPosition;
	sf::Vector2f buttonSize = settings.buttonSize;
	sf::RectangleShape buttonBackground;
	sf::Color buttonTextColor = sf::Color::Black;
	sf::Color buttonBackgroundColor = sf::Color::White;
	sf::Color buttonOutlineColor = sf::Color::Black;
	sf::Color buttonBackgroundColorPressed = sf::Color::Green;
	sf::Color buttonBackgroundColorHovered = sf::Color::Black;
	sf::Color buttonTextColorPressed = sf::Color::Black;
	sf::Color buttonTextColorHovered = sf::Color::White;
	float buttonOutlineThickness = 1.0f;
	bool prevHovered = false;
	bool isHovered = false;
	bool prevPressed = false;
	bool isPressed = false;

};

class StopButton : public Button
{
public:
	using Button::Button;
	void onClick() override;
};

class StartButton : public Button
{
public:
	using Button::Button;
	void onClick() override;
};

class ScaleButton : public Button
{
public:
	using Button::Button;
	void onClick() override;
};