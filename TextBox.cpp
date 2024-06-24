#include "TextBox.h"

TextBox::TextBox(std::string text, std::string fontPath, sf::Vector2f position, SimulationRun* simRun) : simRun(simRun)
{
    textBoxText.setString(text);
    textBoxText.setFont(*Settings::getInstance().font);
    textBoxText.setCharacterSize(fontSize);
    textBoxText.setFillColor(textBoxTextColor);
    sf::Vector2f pos = sf::Vector2f(position.x / 2, position.y);
    textBoxText.setPosition(position);
    textBoxPosition = position;
    textBoxBackground.setPosition(position);
    textBoxBackground.setSize(textBoxSize);
    textBoxBackground.setOutlineThickness(textBoxOutlineThickness);
    textBoxBackground.setOutlineColor(sf::Color::Black);
    sf::FloatRect textBounds = textBoxText.getLocalBounds();
    textBoxText.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    textBoxText.setPosition(textBoxBackground.getPosition().x + textBoxBackground.getSize().x / 2.0f,
        textBoxBackground.getPosition().y + textBoxBackground.getSize().y / 2.0f);
}

void TextBox::draw(sf::RenderWindow& window)
{
    window.draw(textBoxBackground);
    window.draw(textBoxText);
}

void TextBox::update(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    setSelected(textBoxBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)));
}


void TextBox::handleEvent(sf::Event event)
{
    if (isSelected)
    {
        if (event.type == sf::Event::TextEntered)
        {
            handleTextEntered(event.text.unicode);
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            isKeyPressed = true;
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            isKeyPressed = false;
        }
    }
}

void TextBox::handleTextEntered(sf::Uint32 unicode)
{
    if (isKeyPressed)
    {
        return;
    }

    if (unicode == '\b') 
    {
        std::string txt = textBoxText.getString();
        if (!txt.empty())
        {
            txt.pop_back();
            textBoxText.setString(txt);
        }
    }
    else if (unicode < 128) 
    {
        textBoxText.setString(textBoxText.getString() + static_cast<char>(unicode));
        sf::FloatRect textBounds = textBoxText.getLocalBounds();
        textBoxText.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        textBoxText.setPosition(textBoxBackground.getPosition().x + textBoxBackground.getSize().x / 2.0f,
            textBoxBackground.getPosition().y + textBoxBackground.getSize().y / 2.0f);
    }

 
    if (validateFilePath(textBoxText.getString()))
    {
        textBoxBackground.setOutlineColor(validOutlineColor);
    }
    else
    {
        textBoxBackground.setOutlineColor(invalidOutlineColor);
    }
}

std::string TextBox::getText()
{
    return textBoxText.getString();
}

bool TextBox::isPathValid()
{
    return validateFilePath(textBoxText.getString());
}

void TextBox::setText(const std::string text)
{
    textBoxText.setString(text);
	sf::FloatRect textBounds = textBoxText.getLocalBounds();
	textBoxText.setOrigin(textBounds.left + textBounds.width / 2.0f,
        		textBounds.top + textBounds.height / 2.0f);
	textBoxText.setPosition(textBoxBackground.getPosition().x + textBoxBackground.getSize().x / 2.0f,
        		textBoxBackground.getPosition().y + textBoxBackground.getSize().y / 2.0f);
}

void TextBox::setSelected(bool selected)
{
    isSelected = selected;
    if (isSelected)
    {
        textBoxBackground.setFillColor(sf::Color(211,211,211,200));
    }
    else
    {
        textBoxBackground.setFillColor(textBoxBackgroundColor);
    }
}

bool TextBox::getSelected() const
{
    return isSelected;
}

bool TextBox::validateFilePath(const std::string& text)
{
    std::regex pathPattern("^[a-zA-Z0-9_./-]+\\.txt$");
    return std::regex_match(text, pathPattern);
}