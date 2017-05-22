#include "Pattern.h"

Pattern::Pattern():
	current(0)
{
	for (int i = 0; i <= 10 ; i+=2) {
		waypoints.push_back(new Waypoint(sf::Vector2i(0, 14-i), VK_RIGHT));
		waypoints.push_back(new Waypoint(sf::Vector2i(16, 14-i), VK_UP));
		waypoints.push_back(new Waypoint(sf::Vector2i(16, 13-i), VK_LEFT));
		waypoints.push_back(new Waypoint(sf::Vector2i(0, 13-i), VK_UP));//
	}
	waypoints.push_back(new Waypoint(sf::Vector2i(16, 0), VK_DOWN));//
	for (int i = 0; i <= 10; i += 2) {
		waypoints.push_back(new Waypoint(sf::Vector2i(16, 14 - i), VK_LEFT));
		waypoints.push_back(new Waypoint(sf::Vector2i(0, 14 - i), VK_UP));
		waypoints.push_back(new Waypoint(sf::Vector2i(0, 13 - i), VK_RIGHT));
		waypoints.push_back(new Waypoint(sf::Vector2i(16, 13 - i), VK_UP));//
	}
}

Pattern::~Pattern()
{
	for (auto obj : waypoints) {
		delete obj;
	}
}

sf::Vector2i Pattern::getCurrent()
{
	return waypoints[current]->getPosition();
}



int Pattern::getKey()
{
	return waypoints[current]->getDirection();
}

void Pattern::next()
{
	if (++current > waypoints.size()-1)
		current = 0;
}
