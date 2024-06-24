#include "RoadPatterns.h"

RoadPatterns* RoadPatterns::instance = nullptr;

RoadPatterns::RoadPatterns()
{
    initializePatterns();
    setPossibleTurnDirections();
}

RoadPatterns& RoadPatterns::getInstance()
{
    if (!instance)
    {
        instance = new RoadPatterns();
    }
    return *instance;
}

void RoadPatterns::initializePatterns()
{
    // Empty road
    patterns[RoadTypes::Empty] = std::vector<std::vector<unsigned int>>(8, std::vector<unsigned int>(8, 0));

    // Horizontal road
    patterns[RoadTypes::HorizontalRoad] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 4 },
        { 1, 1, 1, 1, 1, 1, 1, 4 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 3, 1, 1, 1, 1, 1, 1, 1 },
        { 3, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    // Vertical road
    patterns[RoadTypes::VerticalRoad] =
    {
        { 0, 4, 4, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 3, 3, 0 }
    };

    // Top left corner
    patterns[RoadTypes::TopLeftCorner] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 6, 1, 1, 1, 1, 1, 1 },
        { 0, 1, 6, 1, 1, 1, 1, 1 },
        { 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 5, 1, 1 },
        { 0, 1, 1, 0, 0, 1, 5, 1 },
        { 0, 1, 1, 0, 0, 1, 1, 0 }
    };

    // Top right corner
    patterns[RoadTypes::TopRightCorner] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 7, 0 },
        { 1, 1, 1, 1, 1, 7, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 6, 0, 0, 1, 1, 0 },
        { 1, 6, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 }
    };

    // Bottom left corner
    patterns[RoadTypes::BottomLeftCorner] =
    {
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 8, 1 },
        { 0, 1, 1, 0, 0, 8, 1, 1 },
        { 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 5, 1, 1, 1, 1, 1 },
        { 0, 5, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    // Bottom right corner
    patterns[RoadTypes::BottomRightCorner] =
    {
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 7, 1, 0, 0, 1, 1, 0 },
        { 1, 1, 7, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 8, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 8, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    // T intersection top
    patterns[RoadTypes::TIntersectionTop] =
    {
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 10, 1, 1, 1, 1, 9, 1 },
        { 1, 1, 10, 1, 1, 9, 1, 1 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 1, 5, 1, 1, 11, 1, 1 },
        { 1, 5, 1, 1, 1, 1, 11, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    // T intersection bottom
    patterns[RoadTypes::TIntersectionBottom] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 10, 1, 1, 1, 1, 7, 1 },
        { 1, 1, 10, 1, 1, 7, 1, 1 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 1, 12, 1, 1, 11, 1, 1 },
        { 1, 12, 1, 1, 1, 1, 11, 1 },
        { 0, 1, 1, 0, 0, 1, 1, 0 }
    };

    // T intersection left
    patterns[RoadTypes::TIntersectionLeft] =
    {
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 10, 1, 1, 1, 1, 9, 0 },
        { 1, 1, 10, 1, 1, 9, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 1, 12, 1, 1, 8, 1, 0 },
        { 1, 12, 1, 1, 1, 1, 8, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 }
    };

    // T intersection right
    patterns[RoadTypes::TIntersectionRight] =
    {
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 6, 1, 1, 1, 1, 9, 1 },
        { 0, 1, 6, 1, 1, 9, 1, 1 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 12, 1, 1, 11, 1, 1 },
        { 0, 12, 1, 1, 1, 1, 11, 1 },
        { 0, 1, 1, 0, 0, 1, 1, 0 }
    };

    // Crossroad
    patterns[RoadTypes::Crossroad] =
    {
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 10, 1, 1, 1, 1, 9, 1 },
        { 1, 1, 10, 1, 1, 9, 1, 1 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 1, 12, 1, 1, 11, 1, 1 },
        { 1, 12, 1, 1, 1, 1, 11, 1 },
        { 0, 1, 1, 0, 0, 1, 1, 0 }
    };
}

void RoadPatterns::setPossibleTurnDirections()
{
    possibleTurnDirections[5] = { Direction::RIGHT };
    possibleTurnDirections[6] = { Direction::DOWN };
    possibleTurnDirections[7] = { Direction::LEFT };
    possibleTurnDirections[8] = { Direction::UP };
    possibleTurnDirections[9] = { Direction::UP, Direction::LEFT };
    possibleTurnDirections[10] = { Direction::DOWN, Direction::LEFT };
    possibleTurnDirections[11] = { Direction::UP, Direction::RIGHT };
    possibleTurnDirections[12] = { Direction::DOWN, Direction::RIGHT };
}