#pragma once

#include <SFML/Graphics.hpp>

class Waypoint {
public:
	Waypoint(const sf::Vector2i &position, const int &direction);
	sf::Vector2i getPosition();
	int getDirection();
private:
	sf::Vector2i position;
	int direction;
};