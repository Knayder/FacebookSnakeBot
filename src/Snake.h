#pragma once
#include <SFML\Graphics.hpp>

class Snake {
public:
	Snake(const sf::Vector2f &tileSize, const sf::Vector2i &tilesAmount, const sf::Vector2i &size);

private:
	sf::Vector2f tileSize;
	sf::Vector2i tilesAmount;
	sf::Vector2i size;
};