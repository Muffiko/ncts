#include "Button.h"


Button::Button(std::string text, std::string fontPath, sf::Vector2f position, SimulationRun* simRun) : simRun(simRun)
{
	buttonText.setString(text);
	buttonFont.loadFromFile(fontPath);
	buttonText.setFont(buttonFont);
	buttonText.setCharacterSize(fontSize);
	buttonText.setFillColor(buttonTextColor);
	buttonText.setPosition(position);
	buttonPosition = position;
	buttonBackground.setPosition(position);
	buttonBackground.setSize(buttonSize);
	buttonText.setPosition(position);
	buttonBackground.setOutlineThickness(buttonOutlineThickness);
	buttonBackground.setOutlineColor(buttonOutlineColor);
	sf::FloatRect textBounds = buttonText.getLocalBounds();
	buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	buttonText.setPosition(buttonBackground.getPosition().x + buttonBackground.getSize().x / 2.0f,
		buttonBackground.getPosition().y + buttonBackground.getSize().y / 2.0f);
}

void Button::draw(sf::RenderWindow& window) 
{
	window.draw(buttonBackground);
	window.draw(buttonText);
}

void Button::update(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	bool newHovered = buttonBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
	bool newPressed = newHovered && sf::Mouse::isButtonPressed(sf::Mouse::Left);

	prevHovered = isHovered;
	prevPressed = isPressed;

	isHovered = newHovered;
	isPressed = newPressed;

	bool stateChanged = (isPressed != prevPressed) || (isHovered != prevHovered);
	if (stateChanged)
	{
		if (isPressed && !prevPressed)
		{
			buttonBackground.setFillColor(buttonBackgroundColorPressed);
			buttonText.setFillColor(buttonTextColorPressed);
			onClick();
		}
		else if (isHovered)
		{
			buttonBackground.setFillColor(buttonBackgroundColorHovered);
			buttonText.setFillColor(buttonTextColorHovered);
		}
		else
		{
			buttonBackground.setFillColor(buttonBackgroundColor);
			buttonText.setFillColor(buttonTextColor);
		}
	}
}



void Button::setFontSize(unsigned int size)
{
	fontSize = size;
}

void Button::setButtonFont(const sf::Font& font) 
{
	buttonFont = font;
}

void Button::setButtonText(const sf::Text& text) 
{
	buttonText = text;
}

void Button::setButtonPosition(const sf::Vector2f& position) 
{
	buttonPosition = position;
}

void Button::setButtonSize(const sf::Vector2f& size) 
{
	buttonSize = size;
}

void Button::setButtonBackground(const sf::RectangleShape& background) 
{
	buttonBackground = background;
}

void Button::setButtonTextColor(const sf::Color& color) 
{
	buttonTextColor = color;
}

void Button::setButtonBackgroundColor(const sf::Color& color) 
{
	buttonBackgroundColor = color;
}

void Button::setButtonOutlineColor(const sf::Color& color) 
{
	buttonOutlineColor = color;
}

void Button::setButtonBackgroundColorPressed(const sf::Color& color) 
{
	buttonBackgroundColorPressed = color;
}

void Button::setButtonBackgroundColorHovered(const sf::Color& color) 
{
	buttonBackgroundColorHovered = color;
}

void Button::setButtonTextColorPressed(const sf::Color& color) 
{
	buttonTextColorPressed = color;
}

void Button::setButtonTextColorHovered(const sf::Color& color) 
{
	buttonTextColorHovered = color;
}

void Button::setButtonOutlineThickness(float thickness) 
{
	buttonOutlineThickness = thickness;
}

void StopButton::onClick()
{
	if (simRun) 
	{ 
		std::cout << "Stop Button Clicked" << std::endl;
		simRun->isRunning = false; 
	}
}

void StartButton::onClick()
{
	if (simRun)
	{
		std::cout << "Start Button Clicked" << std::endl;
		simRun->isRunning = true;
	}
}

void ScaleButton::onClick()
{
	if (simRun)
	{
		std::vector<std::unique_ptr<DynamicObject>>::iterator it = simRun->carObjects.begin();
		while (it != simRun -> carObjects.end())
		{
			Car* car = dynamic_cast<Car*>(it->get());
			if (car != nullptr)
			{
				if (car->getCarSprite().getScale().x < 4)
				{
					car->getCarSprite().setScale(car->getCarSprite().getScale().x + 0.5, car->getCarSprite().getScale().y + 0.5);
				}
				else
				{
					car->getCarSprite().setScale(0.5, 0.5);
				}
			}
		++it;
		}
	}
}