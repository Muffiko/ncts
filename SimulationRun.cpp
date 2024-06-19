#include "SimulationRun.h"

std::string getRandomCarAsset();

void SimulationRun::initializeWindow()
{
	window.create(sf::VideoMode(settings.windowSize.x,settings.windowSize.y), "ncts");
	window.setFramerateLimit(60);
}

void SimulationRun::createButtonObjects()
{
	buttonObjects.push_back(std::make_unique<StartButton>("Start", "arial.ttf", settings.StartButtonPosition, this));
	auto stopButton = std::make_unique<StopButton>("Stop", "arial.ttf", settings.StopButtonPosition, this);
	stopButton->setButtonBackgroundColorPressed(sf::Color::Red);
	buttonObjects.push_back(std::move(stopButton));

	auto scaleButton = std::make_unique<ScaleButton>("Scale", "arial.ttf", sf::Vector2f(settings.StopButtonPosition.x, settings.StopButtonPosition.y + 10 + settings.buttonSize.x), this);
	scaleButton->setButtonBackgroundColorPressed(sf::Color::Green);
	buttonObjects.push_back(std::move(scaleButton));
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
	//carObjects.push_back(std::make_unique<Car>(sf::Vector2i(54,79), Direction::UP, roadMap, 2.0f));
	//carObjects.push_back(std::make_unique<Car>(sf::Vector2i(54, 79), Direction::UP, roadMap, 2.0f));
	//carObjects.push_back(std::make_unique<Car>(sf::Vector2i(54, 79), Direction::UP, roadMap, 3.0f));
	//carObjects.push_back(std::make_unique<Car>(sf::Vector2i(54, 79), Direction::UP, roadMap, 1.2f));
	//carObjects.push_back(std::make_unique<Car>(sf::Vector2i(18, 0), Direction::DOWN, roadMap, 0.5f));
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

void SimulationRun::updateDynamicObjects(sf::RenderWindow& window)
{
	// Step 1: Identify cars that are out of bounds
	std::vector<std::unique_ptr<DynamicObject>>::iterator it = carObjects.begin();
	while (it != carObjects.end())
	{
		Car* car = dynamic_cast<Car*>(it->get());
		if (car != nullptr && car->outOfBounds)
		{
			it = carObjects.erase(it); 
		}
		else
		{
			++it;
		}
	}
	for (auto& car : carObjects)
	{
		car->update(window);
	}
}
void SimulationRun::createMoreCars(MapHandler mapH)
{
	if (carObjects.size() < 30)
	{
		for (int i = 0; i < 30 - carObjects.size(); i++)
		{
			std::vector<sf::Vector2i> carSpawnPoints = mapH.getCarSpawnPoints();
			int randomIndex = rand() % carSpawnPoints.size();
			float randomSpeed = (rand() % 21) / 10.0f + 2.0f;
			Direction setDirection = Direction::UP; // Default direction

			sf::Vector2i spawnPoint = carSpawnPoints[randomIndex];
			int roadTile = mapH.getRoadMap()[spawnPoint.y][spawnPoint.x];

			// Check if the car is spawned at the top border
			if (spawnPoint.y == 0)
			{
				setDirection = Direction::DOWN;
			}
			// Check if the car is spawned at the bottom border
			else if (spawnPoint.y == mapH.getRoadMap().size() - 1)
			{
				setDirection = Direction::UP;
			}
			// Check if the car is spawned at the left border
			else if (spawnPoint.x == 0)
			{
				setDirection = Direction::RIGHT;
			}
			// Check if the car is spawned at the right border
			else if (spawnPoint.x == mapH.getRoadMap()[0].size() - 1)
			{
				setDirection = Direction::LEFT;
			}

			carObjects.push_back(std::make_unique<Car>(spawnPoint, setDirection, std::make_shared<std::vector<std::vector<unsigned int>>>(mapH.getRoadMap()), randomSpeed, getRandomCarAsset()));
		}
	}
}

std::string getRandomCarAsset() 
{
	// List of car asset paths
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





void SimulationRun::runSimulation()
{
	srand(time(NULL));
	MapHandler mapHandler("map.txt");
	mapHandler.convertSpriteMap();

	initializeWindow();
	createButtonObjects();
	createStaticObjects(mapHandler.getSpriteMap());
	mapHandler.convertSpriteMapToRoadMap();
	mapHandler.findCarSpawnPoints();
	createDynamicObjects(std::make_shared<std::vector<std::vector<unsigned int>>>(mapHandler.getRoadMap()));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}


		window.clear(sf::Color::White);
		drawStaticObjects(window);
		updateButtonObjects(window);
		//drawButtonObjects(window);
		drawDynamicObjects(window);
		if (isRunning) updateDynamicObjects(window);

		//mapHandler.displayRoadMapGrid(window, "arial.ttf");

		window.display();
		if (carObjects.size() < 10)createMoreCars(mapHandler);
	}
}
