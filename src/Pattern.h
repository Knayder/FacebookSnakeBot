#pragma once
#include "Waypoint.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <Windows.h>

class Pattern {
public:
	Pattern();
	~Pattern();
	sf::Vector2i getCurrent();
	int getKey();
	void next();
private:
	std::vector<Waypoint *> waypoints;
	unsigned int current;
};