#include "Button.h"
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 4244)
#pragma warning(pop)

Button::Button(std::string text, std::string fontPath, sf::Vector2f position, SimulationRun* simRun) : simRun(simRun)
{
	buttonText.setString(text);
	buttonText.setFont(*Settings::getInstance().font);
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
	buttonBackground.setSize(size);
	sf::FloatRect textBounds = buttonText.getLocalBounds();
	buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	buttonText.setPosition(buttonBackground.getPosition().x + buttonBackground.getSize().x / 2.0f,
		buttonBackground.getPosition().y + buttonBackground.getSize().y / 2.0f);
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
	buttonBackground.setFillColor(color);
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
					car->getCarSprite().setScale(car->getCarSprite().getScale().x + 0.1, car->getCarSprite().getScale().y + 0.1);
				}
				else
				{
					car->getCarSprite().setScale(0.8, 0.8);
				}
			}
		++it;
		}
	}
}

void ScaleButtonMinus::onClick()
{
	if (simRun)
	{
		std::vector<std::unique_ptr<DynamicObject>>::iterator it = simRun->carObjects.begin();
		while (it != simRun->carObjects.end())
		{
			Car* car = dynamic_cast<Car*>(it->get());
			if (car != nullptr)
			{
				if (car->getCarSprite().getScale().x > 0.9)
				{
					car->getCarSprite().setScale(car->getCarSprite().getScale().x - 0.1, car->getCarSprite().getScale().y - 0.1);
				}
				else
				{
					car->getCarSprite().setScale(0.8, 0.8);
				}
			}
			++it;
		}
	}
}

void SpeedButtonPlus::onClick()
{
	if (simRun)
	{
		std::vector<std::unique_ptr<DynamicObject>>::iterator it = simRun->carObjects.begin();
		while (it != simRun->carObjects.end())
		{
			Car* car = dynamic_cast<Car*>(it->get());
			if (car != nullptr)
			{
				if (car->getCarCurrentSpeed() > 0.2f && car->getCarCurrentSpeed() < 10.0f)
				{
					car->getCarCurrentSpeed() += 0.5f;
					car->getCarOriginalSpeed() += 0.5f;
				}
			}
			++it;
		}
	}
}

void SpeedButtonMinus::onClick()
{
	if (simRun)
	{
		std::vector<std::unique_ptr<DynamicObject>>::iterator it = simRun->carObjects.begin();
		while (it != simRun->carObjects.end())
		{
			Car* car = dynamic_cast<Car*>(it->get());
			if (car != nullptr)
			{
				if (car->getCarCurrentSpeed() > 1.5f)
				{
					car->getCarCurrentSpeed() -= 0.5f;
					car->getCarOriginalSpeed() -= 0.5f;
				}
			}
			++it;
		}
	}
}

void SpeedButtonRandom::onClick()
{
	if (simRun)
	{
		std::vector<std::unique_ptr<DynamicObject>>::iterator it = simRun->carObjects.begin();
		while (it != simRun->carObjects.end())
		{
			Car* car = dynamic_cast<Car*>(it->get());
			if (car != nullptr)
			{
				float randomSpeed = (rand() % 21) / 4.0f + 2.0f;
				car->getCarCurrentSpeed() = randomSpeed;
				car->getCarOriginalSpeed() = randomSpeed;
			}
			++it;
		}
	}

}

void NumberOfCarsButtonPlus::onClick()
{
	if (simRun)
	{
		if (simRun->numberOfCars < 30)
		{
			simRun->numberOfCars++;
		}
	}
}

void NumberOfCarsButtonMinus::onClick()
{
	if (simRun)
	{
		if (simRun->numberOfCars > 1)
		{
			simRun->numberOfCars--;
		}
	}
}

void MapEditorButton::onClick()
{
	if (simRun)
	{
		simRun->openMapEditor = true;
	}
}

void MapEditorSaveButton::onClick()
{
	if (simRun)
	{
		std::cout << "save";
		for (auto& button : simRun->mapEditorButtons)
		{
			if (dynamic_cast<TextBoxSave*>(button.get()))
			{
				TextBoxSave* textBoxSave = dynamic_cast<TextBoxSave*>(button.get());
				if (textBoxSave->isPathValid())
				{
					simRun->mapEditorFileNameSave = textBoxSave->getText();
					simRun->mapEditorReload = true;
				}
			}
		}
	}
}

void MapEditorLoadButton::onClick()
{
	if (simRun)
	{
		std::cout << "load";
		for (auto& button : simRun->mapEditorButtons)
		{
			if (dynamic_cast<TextBoxLoad*>(button.get()))
			{
				TextBoxLoad* textBoxLoad = dynamic_cast<TextBoxLoad*>(button.get());
				if (textBoxLoad->isPathValid())
				{
					simRun->mapEditorFileNameLoad = textBoxLoad->getText();
					simRun->mapEditorLoad = true;
				}
			}
		}
	}
}

void MapEditorMapButton::onClick()
{
	if (simRun)
	{
		sf::Vector2i gridPosition = getGridPosition(buttonPosition);
		if (gridPosition.x >= 0 && gridPosition.x < simRun->fakeSpriteMap[0].size() && gridPosition.y >= 0 && gridPosition.y < simRun->fakeSpriteMap.size())
		{
			if (simRun->fakeSpriteMap[gridPosition.y][gridPosition.x] == 0)
			{
				simRun->fakeSpriteMap[gridPosition.y][gridPosition.x] = 1;
				buttonBackground.setFillColor(sf::Color(0,255,0,50));
			}
			else
			{
				simRun->fakeSpriteMap[gridPosition.y][gridPosition.x] = 0;
				buttonBackground.setFillColor(sf::Color::Transparent);
			}
		}
		simRun->mapEditorReload = true;
	}
}

const sf::Vector2i MapEditorMapButton::getGridPosition(const sf::Vector2f& pixelPosition) 
{
	int gridX = (pixelPosition.x - (settings.simulationBorderPosition.x + 3 * settings.simulationBorderThickness)) / settings.spriteMapTileSize.x;
	int gridY = (pixelPosition.y - (settings.simulationBorderPosition.y + 3 * settings.simulationBorderThickness)) / settings.spriteMapTileSize.y;
	return sf::Vector2i(gridX, gridY);
}
