#include "Road.h"
#include <iostream>


void Road::setRoadSprite()
{
    std::string filename;
    switch (roadType)
    {
    case RoadTypes::Empty:
        filename = "assets/empty2.png";
        break;
    case RoadTypes::VerticalRoad:
        filename = "assets/vertical_road2.png";
        break;
    case RoadTypes::HorizontalRoad:
        filename = "assets/horizontal_road2.png";
        break;
    case RoadTypes::TopLeftCorner:
        filename = "assets/top_left_corner2.png";
        break;
    case RoadTypes::TopRightCorner:
        filename = "assets/top_right_corner2.png";
        break;
    case RoadTypes::BottomLeftCorner:
        filename = "assets/bottom_left_corner2.png";
        break;
    case RoadTypes::BottomRightCorner:
        filename = "assets/bottom_right_corner2.png";
        break;
    case RoadTypes::TIntersectionTop:
        filename = "assets/t_intersection_top2.png";
        break;
    case RoadTypes::TIntersectionBottom:
        filename = "assets/t_intersection_bottom2.png";
        break;
    case RoadTypes::TIntersectionLeft:
        filename = "assets/t_intersection_left2.png";
        break;
    case RoadTypes::TIntersectionRight:
        filename = "assets/t_intersection_right2.png";
        break;
    case RoadTypes::Crossroad:
        filename = "assets/crossroad2.png";
        break;
    default:
        filename = "assets/default.png";
    }

    if (!roadTexture.loadFromFile(filename))
    {
        std::cout << "Error: Could not load texture " << filename << std::endl;
        filename = "assets/empty.png";
    }
    roadSprite.setTexture(roadTexture);
}


Road::Road(sf::Vector2f position, RoadTypes roadType) : position(position), roadType(roadType)
{
	roadSprite.setPosition(position);
    setRoadSprite();
}

void Road::draw(sf::RenderWindow& window)
{
    window.draw(roadSprite);
}
