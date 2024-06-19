#pragma once
enum class RoadTypes
{
	Empty = 0,
	VerticalRoad = 1,
	HorizontalRoad = 2,
	TopLeftCorner = 3,
	TopRightCorner = 4,
	BottomLeftCorner = 5,
	BottomRightCorner = 6,
	TIntersectionTop = 7,
	TIntersectionBottom = 8,
	TIntersectionLeft = 9,
	TIntersectionRight = 10,
	Crossroad = 11,
};

enum class Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };