#include "SimulationRun.h"

std::string getRandomCarAsset();

void SimulationRun::initializeWindow()
{
	window.create(sf::VideoMode(settings.windowSize.x,settings.windowSize.y), "ncts");
	window.setFramerateLimit(60);
}

void SimulationRun::createButtonObjects()
{
	buttonObjects.clear();
	auto startButton = std::make_unique<StartButton>("Start", "arial.ttf", settings.StartButtonPosition, this);
	startButton->setButtonBackgroundColor(sf::Color(0, 255, 0, 200));
	buttonObjects.push_back(std::move(startButton));
	
	auto stopButton = std::make_unique<StopButton>("Stop", "arial.ttf", settings.StopButtonPosition, this);
	stopButton->setButtonBackgroundColorPressed(sf::Color::Red);
	stopButton->setButtonBackgroundColor(sf::Color(255, 0, 0, 200));
	buttonObjects.push_back(std::move(stopButton));

	auto scaleButton = std::make_unique<ScaleButton>("+", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 10 + settings.buttonSize.x), this);
	scaleButton->setButtonBackgroundColorPressed(sf::Color::Green);
	scaleButton->setButtonSize(sf::Vector2f(settings.buttonSize.y + 10, settings.buttonSize.y));
	scaleButton->setButtonBackgroundColor(sf::Color(0, 255, 0, 100));
	buttonObjects.push_back(std::move(scaleButton));

	auto scaleButtonMinus = std::make_unique<ScaleButtonMinus>("-", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x + 40, settings.StopButtonPosition.y + 10 + settings.buttonSize.x), this);
	scaleButtonMinus->setButtonBackgroundColorPressed(sf::Color::Red);
	scaleButtonMinus->setButtonSize(sf::Vector2f(settings.buttonSize.y + 10, settings.buttonSize.y));
	scaleButtonMinus->setButtonBackgroundColor(sf::Color(255, 0, 0, 100));
	buttonObjects.push_back(std::move(scaleButtonMinus));

	auto speedButtonPlus = std::make_unique<SpeedButtonPlus>("+", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 10 + settings.buttonSize.x + 2*settings.buttonSize.y), this);
	speedButtonPlus->setButtonBackgroundColorPressed(sf::Color::Green);
	speedButtonPlus->setButtonSize(sf::Vector2f(settings.buttonSize.y + 10, settings.buttonSize.y));
	speedButtonPlus->setButtonBackgroundColor(sf::Color(0, 255, 0, 100));
	buttonObjects.push_back(std::move(speedButtonPlus));

	auto speedButtonMinus = std::make_unique<SpeedButtonMinus>("-", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x + 40, settings.StopButtonPosition.y + 10 + settings.buttonSize.x + 2*settings.buttonSize.y), this);
	speedButtonMinus->setButtonBackgroundColorPressed(sf::Color::Red);
	speedButtonMinus->setButtonSize(sf::Vector2f(settings.buttonSize.y + 10, settings.buttonSize.y));
	speedButtonMinus->setButtonBackgroundColor(sf::Color(255, 0, 0, 100));
	buttonObjects.push_back(std::move(speedButtonMinus));

	auto speedButtonRandom = std::make_unique<SpeedButtonRandom>("random speed", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 20 + settings.buttonSize.x + 1 * settings.buttonSize.y), this);
	speedButtonRandom->setButtonBackgroundColorPressed(sf::Color::Blue);
	speedButtonRandom->setButtonSize(sf::Vector2f(settings.buttonSize.x, settings.buttonSize.y - 10));
	speedButtonRandom->setButtonBackgroundColor(sf::Color(0, 0, 255, 100));
	buttonObjects.push_back(std::move(speedButtonRandom));

	auto numberOfCarsButtonPlus = std::make_unique<NumberOfCarsButtonPlus>("+", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 10 + settings.buttonSize.x + 4 * settings.buttonSize.y), this);
	numberOfCarsButtonPlus->setButtonBackgroundColorPressed(sf::Color::Green);
	numberOfCarsButtonPlus->setButtonSize(sf::Vector2f(settings.buttonSize.y + 10, settings.buttonSize.y));
	numberOfCarsButtonPlus->setButtonBackgroundColor(sf::Color(0, 255, 0, 100));
	buttonObjects.push_back(std::move(numberOfCarsButtonPlus));

	auto numberOfCarsButtonMinus = std::make_unique<NumberOfCarsButtonMinus>("-", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x + 40, settings.StopButtonPosition.y + 10 + settings.buttonSize.x + 4 * settings.buttonSize.y), this);
	numberOfCarsButtonMinus->setButtonBackgroundColorPressed(sf::Color::Red);
	numberOfCarsButtonMinus->setButtonSize(sf::Vector2f(settings.buttonSize.y + 10, settings.buttonSize.y));
	numberOfCarsButtonMinus->setButtonBackgroundColor(sf::Color(255, 0, 0, 100));
	buttonObjects.push_back(std::move(numberOfCarsButtonMinus));

	auto mapEditorButton = std::make_unique<MapEditorButton>("Map Editor", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 10 + settings.buttonSize.x + 8.5 * settings.buttonSize.y), this);
	mapEditorButton->setButtonBackgroundColorPressed(sf::Color::Blue);
	mapEditorButton->setButtonBackgroundColor(sf::Color(0, 0, 255, 100));
	buttonObjects.push_back(std::move(mapEditorButton));

	auto statsDisplay = std::make_unique<StatsDisplay>();
	buttonObjects.push_back(std::move(statsDisplay));
}
void SimulationRun::drawButtonObjects(sf::RenderWindow& window)
{
	for (auto& button : buttonObjects)
	{
		button->draw(window);
	}
}

void SimulationRun::updateButtonObjects(sf::RenderWindow& window)
{
	for (auto& button : buttonObjects)
	{
		button->update(window);
	}
}

void SimulationRun::createStaticObjects(std::vector<std::vector<unsigned int>> spriteMap)
{
	staticObjects.clear();
	staticObjects.push_back(std::make_unique<WindowElements>());
	for (int i = settings.simulationBorderPosition.x + 3*settings.simulationBorderThickness; i < settings.simulationBorderSize.x + settings.simulationBorderPosition.x; i += settings.spriteMapTileSize.x)
	{
		for (int j = settings.simulationBorderPosition.y + 3*settings.simulationBorderThickness; j < settings.simulationBorderSize.y + settings.simulationBorderPosition.y; j += settings.spriteMapTileSize.y)
		{
			staticObjects.push_back(std::make_unique<Road>(sf::Vector2f(i, j), static_cast<RoadTypes>(spriteMap[(j - settings.simulationBorderPosition.y) / settings.spriteMapTileSize.y][(i - settings.simulationBorderPosition.x) / settings.spriteMapTileSize.x])));
		}
	}
}

void SimulationRun::createDynamicObjects(std::shared_ptr<std::vector<std::vector<unsigned int>>> roadMap)
{
	carObjects.push_back(std::make_unique<Car>(sf::Vector2i(0, 21), Direction::RIGHT, roadMap, 3.0f, getRandomCarAsset()));
	carObjects.push_back(std::make_unique<Car>(sf::Vector2i(0, 21), Direction::RIGHT, roadMap, 6.0f, getRandomCarAsset()));
	carObjects.push_back(std::make_unique<Car>(sf::Vector2i(0, 21), Direction::RIGHT, roadMap, 3.0f, getRandomCarAsset()));
	carObjects.push_back(std::make_unique<Car>(sf::Vector2i(135, 57), Direction::LEFT, roadMap, 6.0f, getRandomCarAsset()));
	carObjects.push_back(std::make_unique<Car>(sf::Vector2i(135, 58), Direction::LEFT, roadMap, 6.0f, getRandomCarAsset()));
	carObjects.push_back(std::make_unique<Car>(sf::Vector2i(17, 0), Direction::DOWN, roadMap, 6.0f, getRandomCarAsset()));
	carObjects.push_back(std::make_unique<Car>(sf::Vector2i(53, 79), Direction::UP, roadMap, 6.0f, getRandomCarAsset()));
	carObjects.push_back(std::make_unique<Car>(sf::Vector2i(54, 79), Direction::UP, roadMap, 6.0f, getRandomCarAsset()));
}


void SimulationRun::drawStaticObjects(sf::RenderWindow& window)
{
	for (auto& staticObject : staticObjects)
	{
		staticObject->draw(window);
	}
}

void SimulationRun::drawDynamicObjects(sf::RenderWindow& window)
{
	for (auto& car : carObjects)
	{
		car->draw(window);
	}
	for (auto& button : buttonObjects)
	{
		button->draw(window);
	}
}

void SimulationRun::updateDynamicObjects(sf::RenderWindow& window, MapHandler& mapH)
{
	if(isRunning)
	{
		for (auto& car : carObjects)
		{
			Car* carPtr = dynamic_cast<Car*>(car.get());
			if (carPtr != nullptr && carPtr->outOfBounds)
			{
				std::pair<sf::Vector2i, Direction> spawnPointAndDirection = getNewSpawnPointAndDirection(mapH);
				if ((std::find_if(carObjects.begin(), carObjects.end(), [&](std::unique_ptr<DynamicObject>& car) {return dynamic_cast<Car*>(car.get())->getCarCurrentPositionPoint() == spawnPointAndDirection.first || dynamic_cast<Car*>(car.get())->getCarNextPositionPoint() == spawnPointAndDirection.first; }) == carObjects.end()))
				{
					Car::currentPositions.erase(std::remove_if(Car::currentPositions.begin(), Car::currentPositions.end(), [&](const PositionInfo& info) {
						return info.position == carPtr->getCarCurrentPositionPoint();
						}), Car::currentPositions.end());
					Car::nextPositions.erase(std::remove_if(Car::nextPositions.begin(), Car::nextPositions.end(), [&](const PositionInfo& info) {
						return info.position == carPtr->getCarNextPositionPoint();
						}), Car::nextPositions.end());
					carPtr->resetToNewPosition(spawnPointAndDirection.first, spawnPointAndDirection.second);
				}
			}
			else
			{
				car->update(window);
			}
		}
	}

	for (auto& button : buttonObjects)
	{

		Button* buttonPtr = dynamic_cast<Button*>(button.get());
		if (buttonPtr != nullptr)
		{
			buttonPtr->update(window);
			continue; 
		}

		StatsDisplay* statsDisplayPtr = dynamic_cast<StatsDisplay*>(button.get());
		if (statsDisplayPtr != nullptr)
		{
			if (!carObjects.empty())
			{
				Car* carPtr = dynamic_cast<Car*>(carObjects.back().get());
				if (carPtr != nullptr)
				{
					carAvgSpeed = 0;
					for (auto& car : carObjects)
					{
						Car* carPtr = dynamic_cast<Car*>(car.get());
						if (carPtr != nullptr)
						{
							carAvgSpeed += carPtr->getCarOriginalSpeed();
						}
					}
					carAvgSpeed /= carObjects.size(); 
					statsDisplayPtr->updateStats(carObjects.size(), carPtr->getCarSprite().getScale().x, carAvgSpeed);
				}
			}
			statsDisplayPtr->update(window);
		}
	}
}

void SimulationRun::createMoreCars(MapHandler& mapH)
{
	if (carObjects.size() < numberOfCars)
	{
		for (int i = 0; i < numberOfCars - carObjects.size(); i++)
		{
			std::pair<sf::Vector2i, Direction> spawnPointAndDirection = getNewSpawnPointAndDirection(mapH);
			if ((std::find_if(carObjects.begin(), carObjects.end(), [&](std::unique_ptr<DynamicObject>& car) {return dynamic_cast<Car*>(car.get())->getCarCurrentPositionPoint() == spawnPointAndDirection.first || dynamic_cast<Car*>(car.get())->getCarNextPositionPoint() == spawnPointAndDirection.first; }) == carObjects.end()))
			{
				float randomSpeed = (rand() % 21) / 4.0f + 2.0f;
				carObjects.push_back(std::make_unique<Car>(spawnPointAndDirection.first, spawnPointAndDirection.second, std::make_shared<std::vector<std::vector<unsigned int>>>(mapH.getRoadMap()), randomSpeed, getRandomCarAsset()));
			}
		}
	}
	else if(carObjects.size() > numberOfCars)
	{
		for (int i = 0; i < carObjects.size() - numberOfCars; i++)
		{
			Car* carPtr = dynamic_cast<Car*>(carObjects.back().get());
			if (carPtr != nullptr)
			{
				Car::currentPositions.erase(std::remove_if(Car::currentPositions.begin(), Car::currentPositions.end(), [&](const PositionInfo& info) {
					return info.position == carPtr->getCarCurrentPositionPoint();
					}), Car::currentPositions.end());
				Car::nextPositions.erase(std::remove_if(Car::nextPositions.begin(), Car::nextPositions.end(), [&](const PositionInfo& info) {
					return info.position == carPtr->getCarNextPositionPoint();
					}), Car::nextPositions.end());
			}
			carObjects.pop_back();
		}
	}
}

std::pair<sf::Vector2i, Direction> SimulationRun::getNewSpawnPointAndDirection(MapHandler& mapH)
{
	std::vector<sf::Vector2i> carSpawnPoints = mapH.getCarSpawnPoints();
	int randomIndex = rand() % carSpawnPoints.size();
	Direction setDirection = Direction::UP;
	sf::Vector2i spawnPoint = carSpawnPoints[randomIndex];
	int roadTile = mapH.getRoadMap()[spawnPoint.y][spawnPoint.x];

	if (spawnPoint.y == 0)
	{
		setDirection = Direction::DOWN;
	}
	else if (spawnPoint.y == mapH.getRoadMap().size() - 1)
	{
		setDirection = Direction::UP;
	}
	else if (spawnPoint.x == 0)
	{
		setDirection = Direction::RIGHT;
	}
	else if (spawnPoint.x == mapH.getRoadMap()[0].size() - 1)
	{
		setDirection = Direction::LEFT;
	}

	return { spawnPoint, setDirection };
}


std::string getRandomCarAsset() 
{
	std::vector<std::string> carAssets = {
		"assets/basic_car1.png",
		"assets/basic_car2.png",
		"assets/basic_car3.png",
		"assets/basic_car4.png",
		"assets/basic_car5.png",
		"assets/basic_car6.png"
	};


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, carAssets.size() - 1);

	return carAssets[distr(gen)];
}
void SimulationRun::runMapEditor()
{
	std::lock_guard<std::mutex> lock(mutex);

	mapEditorButtons.clear();
	mapEditorStaticObjects.clear();
	sf::RenderWindow mapEditorWindow;
	mapEditorWindow.create(sf::VideoMode(settings.windowSize.x, settings.windowSize.y), "Map Editor");
	mapEditorWindow.setFramerateLimit(60);
	MapHandler editorMapHandler(mapEditorFileNameLoad);
	editorMapHandler.convertSpriteMap();
	mapEditorCreateRoads(editorMapHandler.getSpriteMap());

	sf::RectangleShape simulationBorder;
	simulationBorder.setSize(settings.simulationBorderSize);
	simulationBorder.setFillColor(sf::Color::Transparent);
	simulationBorder.setOutlineColor(sf::Color::Black);
	simulationBorder.setOutlineThickness(settings.simulationBorderThickness);
	simulationBorder.setPosition(50 + 1 * settings.simulationBorderThickness, 50 + 1 * settings.simulationBorderThickness);

	mapEditorCreateButtons();

	for (auto& button : mapEditorButtons)
	{
		TextBox* textBoxPtr = dynamic_cast<TextBox*>(button.get());
		if (textBoxPtr != nullptr)
		{
			textBoxPtr->setText(mapEditorFileNameLoad);
		}
	}
	
	while (mapEditorWindow.isOpen())
	{
		sf::Event event;
		while (mapEditorWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				openMapEditor = false;
				reloadSimulation = true;
				isRunning = true;
				mapEditorButtons.clear();
				mapEditorStaticObjects.clear();
				mapEditorWindow.close();
			}
			if (event.type == sf::Event::TextEntered)
			{
				for (auto& button : mapEditorButtons)
				{
					TextBox* textBoxPtr = dynamic_cast<TextBox*>(button.get());
					if (textBoxPtr != nullptr)
					{
						textBoxPtr->handleEvent(event);
					}
				}
			}
			if (mapEditorReload == true)
			{
				mapEditorFileNameLoad = mapEditorFileNameSave;
				editorMapHandler.spriteMap = fakeSpriteMap;
				editorMapHandler.saveSpriteMapToFile(mapEditorFileNameSave);
				editorMapHandler.loadMapFromFile(mapEditorFileNameSave);
				editorMapHandler.convertSpriteMap();
				mapEditorCreateRoads(editorMapHandler.getSpriteMap());
				for (auto& button : mapEditorButtons)
				{
					TextBox* textBoxPtr = dynamic_cast<TextBox*>(button.get());
					if (textBoxPtr != nullptr)
					{
						textBoxPtr->setText(mapEditorFileNameSave);
					}
				}
				mapEditorReload = false;
			}
			if (mapEditorLoad == true)
			{
				editorMapHandler.mapClear();
				mapEditorFileNameSave = mapEditorFileNameLoad;
				editorMapHandler.loadMapFromFile(mapEditorFileNameSave);
				editorMapHandler.convertSpriteMap();
				mapEditorCreateRoads(editorMapHandler.getSpriteMap());
				for (auto& button : mapEditorButtons)
				{
					TextBox* textBoxPtr = dynamic_cast<TextBox*>(button.get());
					if (textBoxPtr != nullptr)
					{
						textBoxPtr->setText(mapEditorFileNameLoad);
					}
				}
				mapEditorLoad = false;
			}

			mapEditorWindow.clear(sf::Color::White);
			mapEditorUpdateButtons(mapEditorWindow);
			mapEditorWindow.draw(simulationBorder);
			mapEditorWindow.display();
		}
		
	}
}

void SimulationRun::mapEditorCreateRoads(std::vector<std::vector<unsigned int>> spriteMap)
{
	mapEditorStaticObjects.clear();
	for (int i = settings.simulationBorderPosition.x + 3 * settings.simulationBorderThickness; i < settings.simulationBorderSize.x + settings.simulationBorderPosition.x; i += settings.spriteMapTileSize.x)
	{
		for (int j = settings.simulationBorderPosition.y + 3 * settings.simulationBorderThickness; j < settings.simulationBorderSize.y + settings.simulationBorderPosition.y; j += settings.spriteMapTileSize.y)
		{
			mapEditorStaticObjects.push_back(std::make_unique<Road>(sf::Vector2f(i, j), static_cast<RoadTypes>(spriteMap[(j - settings.simulationBorderPosition.y) / settings.spriteMapTileSize.y][(i - settings.simulationBorderPosition.x) / settings.spriteMapTileSize.x])));
		}
	}
}


void SimulationRun::mapEditorCreateButtons()
{
	mapEditorButtons.clear();
	auto mapEditorSaveButton = std::make_unique<MapEditorSaveButton>("Save", "arial.ttf", settings.StartButtonPosition, this);
	mapEditorSaveButton->setButtonBackgroundColor(sf::Color(0, 0, 0, 100));
	mapEditorButtons.push_back(std::move(mapEditorSaveButton));

	sf::Vector2f temp = sf::Vector2f(0, 60);
	auto mapEditorLoadButton = std::make_unique<MapEditorLoadButton>("Load", "arial.ttf", settings.StopButtonPosition + temp, this);
	mapEditorLoadButton->setButtonBackgroundColorPressed(sf::Color::Red);
	mapEditorLoadButton->setButtonBackgroundColor(sf::Color(0, 0, 0, 100));
	mapEditorButtons.push_back(std::move(mapEditorLoadButton));

	auto mapEditorTextBoxSave = std::make_unique<TextBoxSave>("", "arial.ttf", sf::Vector2f(settings.StartButtonPosition.x, 2*settings.StartButtonPosition.y - 15), this);
	mapEditorButtons.push_back(std::move(mapEditorTextBoxSave));
	auto mapEditorTextBoxLoad = std::make_unique<TextBoxLoad>("", "arial.ttf", sf::Vector2f(settings.StartButtonPosition.x, 4 * settings.StartButtonPosition.y - 15), this);
	mapEditorButtons.push_back(std::move(mapEditorTextBoxLoad));

	for (int i = settings.simulationBorderPosition.x + 3 * settings.simulationBorderThickness; i < settings.simulationBorderSize.x + settings.simulationBorderPosition.x; i += settings.spriteMapTileSize.x)
	{
		for (int j = settings.simulationBorderPosition.y + 3 * settings.simulationBorderThickness; j < settings.simulationBorderSize.y + settings.simulationBorderPosition.y; j += settings.spriteMapTileSize.y)
		{
			auto button = std::make_unique<MapEditorMapButton>("", "arial.ttf", sf::Vector2f(i, j), this);
			button->setButtonSize(sf::Vector2f(settings.spriteMapTileSize.x, settings.spriteMapTileSize.y));
			button->setButtonBackgroundColor(sf::Color::Transparent);
			button->setButtonBackgroundColorHovered(sf::Color(0,0, 0, 50));
			mapEditorButtons.push_back(std::move(button));
		}
	}
}



void SimulationRun::mapEditorUpdateButtons(sf::RenderWindow& window)
{
	for (auto& elem : mapEditorStaticObjects)
	{
		elem->draw(window);
	}
	for (auto& button : mapEditorButtons)
	{
		button->update(window);
		button->draw(window);
	}
	
}

void SimulationRun::initializeSimulation() 
{
	mapHandler.mapClear();
	Car::currentPositions.clear();
	Car::nextPositions.clear();
	buttonObjects.clear();
	staticObjects.clear();
	carObjects.clear();
	bool isRunning = true;
	
	mapHandler.setMapFileName(mapEditorFileNameLoad); 
	mapHandler.loadMapFromFile(mapEditorFileNameLoad);
	mapHandler.convertSpriteMap();
	
	createButtonObjects();
	createStaticObjects(mapHandler.getSpriteMap());
	mapHandler.convertSpriteMapToRoadMap();
	mapHandler.findCarSpawnPoints();
	reloadSimulation = false;
}

void SimulationRun::runSimulation()
{
	initializeWindow();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		if (reloadSimulation)
		{
			initializeSimulation();
		}
		if (openMapEditor)
		{
			std::lock_guard<std::mutex> lock(mutex);
			isPaused = true;
			mapEditorThread = std::make_unique<std::thread>(&SimulationRun::runMapEditor, this);
			isPaused = false;
			openMapEditor = false;
			
		}
		if (mapEditorThread && mapEditorThread->joinable())
		{
			mapEditorThread->join();
			mapEditorThread.release();
		}

		if (!isPaused)
		{
			window.clear(sf::Color(211, 211, 211, 200));
			drawStaticObjects(window);
			drawDynamicObjects(window);
			updateDynamicObjects(window, mapHandler);
			window.display();
			if (carObjects.size() != numberOfCars) createMoreCars(mapHandler);
		}
	}


}
