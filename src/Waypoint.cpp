#include "Waypoint.h"

Waypoint::Waypoint(const sf::Vector2i & position, const int & direction) :
	position(position),
	direction(direction)
{
}

sf::Vector2i Waypoint::getPosition()
{
	return position;
}

int Waypoint::getDirection()
{
	return direction;
}
