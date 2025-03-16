#pragma once
#include "DynamicObject.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "SimulationRun.h"
#include <regex>

class SimulationRun;

class TextBox : public DynamicObject
{
protected:
    SimulationRun* simRun = nullptr;

public:
    Settings& settings = Settings::getInstance();
    TextBox(std::string text, std::string fontPath, sf::Vector2f position, SimulationRun* simRun);
    void update(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(sf::Event event);
    void setSelected(bool selected);
    bool getSelected() const;
    void handleTextEntered(sf::Uint32 unicode);
    std::string getText();
    bool isPathValid();
    void setText(const std::string text);

protected:
    bool isSelected = false;
    bool isKeyPressed = false;
    unsigned int fontSize = 12;
    sf::Font textBoxFont;
    sf::Text textBoxText;
    sf::Vector2f textBoxPosition;
    sf::Vector2f textBoxSize = settings.buttonSize; 
    sf::RectangleShape textBoxBackground;
    sf::Color textBoxTextColor = sf::Color::Black;
    sf::Color textBoxBackgroundColor = sf::Color::White;
    float textBoxOutlineThickness = 1.0f;
    const sf::Color validOutlineColor = sf::Color::Green;
    const sf::Color invalidOutlineColor = sf::Color::Red;
   bool validateFilePath(const std::string& text);
   

};

class TextBoxSave : public TextBox
{
    using TextBox::TextBox;
};

class TextBoxLoad : public TextBox
{
    using TextBox::TextBox;
};