#include "MapHandler.h"

MapHandler::MapHandler(std::string fileName)
{
	setMapFileName(fileName);
	loadMapFromFile(fileName);
}

void MapHandler::setMapFileName(std::string fileName)
{
    mapFileName = fileName;
}

std::vector<std::vector<unsigned int>> MapHandler::convertSpriteMapToRoadMap()
{
    RoadPatterns& roadPatterns = RoadPatterns::getInstance(); 
    roadMap = std::vector<std::vector<unsigned int>>(spriteMap.size() * roadPatterns.patterns[static_cast<RoadTypes>(0)].size(), std::vector<unsigned int>(spriteMap[0].size() * roadPatterns.patterns[static_cast<RoadTypes>(0)].size(), 0));
    for (int i = 0; i < spriteMap.size(); i++)
    {
        for (int j = 0; j < spriteMap[i].size(); j++)
        {
            unsigned int patternNumber = spriteMap[i][j];

            const auto& pattern = roadPatterns.patterns[static_cast<RoadTypes>(patternNumber)];
            for (int k = 0; k < settings.roadMapTileSize.x ; k++)
            {
                for (int l = 0; l < settings.roadMapTileSize.x; ++l)
                {
                    roadMap[i * settings.roadMapTileSize.x + k][j * settings.roadMapTileSize.x + l] = pattern[k][l];
                }
            }
        }
    }
    return roadMap;
}


void MapHandler::loadMapFromFile(const std::string& fileName)
{
    if (!std::filesystem::exists(fileName))
    {
        std::cout << "Error: File " << fileName << " does not exist." << std::endl;
        return;
    }

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<unsigned int> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            if (!cell.empty() && std::all_of(cell.begin(), cell.end(), ::isdigit))
            {
                row.push_back(std::stoi(cell));
            }
        }

        spriteMap.push_back(row);
    }
    file.close();
}

void MapHandler::convertSpriteMap()
{

    for (int row = 1; row < spriteMap.size()-1; row++)
    {
        for (int col = 1; col < spriteMap[0].size()-1; col++)
        {
            auto r = [&](int r, int c) { return spriteMap[row + r][col + c] != 0; };
            RoadTypes road = RoadTypes::Empty;           
            if (r(0, 0) != 0)
            {
                if (r(0, -1) && r(0, 1) && !r(-1, 0) && !r(1, 0)) road = RoadTypes::HorizontalRoad;
                if (!r(0, -1) && r(0, 1) && !r(-1, 0) && !r(1, 0)) road = RoadTypes::HorizontalRoad;
                if (r(0, -1) && !r(0, 1) && !r(-1, 0) && !r(1, 0)) road = RoadTypes::HorizontalRoad;
                if (r(-1, 0) && r(1, 0) && !r(0, -1) && !r(0, 1)) road = RoadTypes::VerticalRoad;
                if (!r(-1, 0) && r(1, 0) && !r(0, -1) && !r(0, 1)) road = RoadTypes::VerticalRoad;
                if (r(-1, 0) && !r(1, 0) && !r(0, -1) && !r(0, 1)) road = RoadTypes::VerticalRoad;

                if (r(0, 1) && r(1, 0) && !r(-1, 0) && !r(0, -1)) road = RoadTypes::TopLeftCorner;
                if (r(0, -1) && r(1, 0) && !r(-1, 0) && !r(0, 1)) road = RoadTypes::TopRightCorner;
                if (r(-1, 0) && r(0, -1) && !r(0, 1) && !r(1, 0)) road = RoadTypes::BottomRightCorner;
                if (r(-1, 0) && r(0, 1) && !r(0, -1) && !r(1, 0)) road = RoadTypes::BottomLeftCorner;

                if (r(-1, 0) && r(0, 1) && r(0, -1) && !r(1, 0)) road = RoadTypes::TIntersectionTop;
                if (r(0, -1) && r(1, 0) && r(-1, 0) && !r(0, 1)) road = RoadTypes::TIntersectionLeft;
                if (r(1, 0) && r(0, -1) && r(0, 1) && !r(-1, 0)) road = RoadTypes::TIntersectionBottom;
                if (r(0, 1) && r(-1, 0) && r(1, 0) && !r(0, -1)) road = RoadTypes::TIntersectionRight;

                if (r(-1, 0) && r(1, 0) && r(0, -1) && r(0, 1)) road = RoadTypes::Crossroad; 


                spriteMap[row][col] = static_cast<unsigned int>(road);
            }
        }
    }

    int rows = spriteMap.size();
    int cols = spriteMap[0].size();

    // top border
    for (int col = 0; col < cols; col++)
    {
        if (spriteMap[1][col] != 0)
        {
            spriteMap[0][col] = spriteMap[1][col];
        }
    }

    // bottom border
    for (int col = 0; col < cols; col++)
    {
        if (spriteMap[rows - 2][col] != 0)
        {
            spriteMap[rows - 1][col] = spriteMap[rows - 2][col];
        }
    }

    // left border
    for (int row = 0; row < rows; row++)
    {
        if (spriteMap[row][1] != 0)
        {
            spriteMap[row][0] = spriteMap[row][1];
        }
    }

    // right border
    for (int row = 0; row < rows; row++)
    {
        if (spriteMap[row][cols - 2] != 0)
        {
            spriteMap[row][cols - 1] = spriteMap[row][cols - 2];
        }
    }
}

void MapHandler::findCarSpawnPoints()
{
  
    for (int col = 0; col < roadMap[0].size(); col++)
    {
        if (roadMap[0][col] == 3 || roadMap[0][col] == 4)
        {
			carSpawnPoints.push_back(sf::Vector2i(col, 0));
		}
        if (roadMap[roadMap.size() - 1][col] == 3 || roadMap[roadMap.size() - 1][col] == 4)
        {
			carSpawnPoints.push_back(sf::Vector2i(col, roadMap.size() - 1));
		}

	}
    for (int row = 0; row < roadMap.size(); row++)
    {
        if (roadMap[row][0] == 3 || roadMap[row][0] == 4)
        {
            carSpawnPoints.push_back(sf::Vector2i(0, row));
        }
        if (roadMap[row][roadMap[0].size() - 1] == 3 || roadMap[row][roadMap[0].size() - 1] == 4)
        {
            carSpawnPoints.push_back(sf::Vector2i(roadMap[0].size() - 1, row));
        }
    }
    for (const auto& point : carSpawnPoints)
    {
		std::cout << "Car spawn point: (" << point.x << "," << point.y << ")" << std::endl;
	}
}

std::vector<sf::Vector2i> MapHandler::getCarSpawnPoints()
{
    return carSpawnPoints;
}

RoadTypes MapHandler::getSpriteMapRoadType(sf::Vector2i currentPos)
{

        int chunkX = currentPos.x / settings.roadMapTileSize.x;
        int chunkY = currentPos.y / settings.roadMapTileSize.y;

        if (chunkX < 0 || chunkX >= spriteMap.size() || chunkY < 0 || chunkY >= spriteMap[0].size()) 
        {
            std::cerr << "Error: Out of bounds access in spriteMap." << std::endl;
            return RoadTypes::Empty;  
        }

        return static_cast<RoadTypes>(spriteMap[chunkY][chunkX]);
}

void MapHandler::displayRoadMap() 
{
    for (size_t y = 0; y < roadMap.size(); ++y) 
    {
        for (size_t x = 0; x < roadMap[y].size(); ++x) 
        {
            std::cout << "(" << x << "," << y << ") -> " << roadMap[y][x] << " ";
        }
        std::cout << std::endl; 
    }
}

std::vector<std::vector<unsigned int>> MapHandler::getSpriteMap()
{
	return spriteMap;
}

std::vector<std::vector<unsigned int>> MapHandler::getRoadMap()
{
    return roadMap;
}

void MapHandler::mapClear()
{
    spriteMap.clear();
    roadMap.clear();
    carSpawnPoints.clear();
}

void MapHandler::saveSpriteMapToFile(const std::string& fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
		std::cout << "Error: Could not open file " << fileName << std::endl;
		return;
	}
    for (int i = 0; i < spriteMap.size(); i++)
    {
        for (int j = 0; j < spriteMap[i].size(); j++)
        {
			file << spriteMap[i][j];
            if (j != spriteMap[i].size() - 1)
            {
				file << ",";
			}
		}
		file << std::endl;
	}
	file.close();
}



