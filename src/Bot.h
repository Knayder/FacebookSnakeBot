#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "ImageSource.h"
#include "Pattern.h"


class Bot final {
public:
	Bot() = delete;
	Bot(const Bot&) = delete;
	void operator=(const Bot&) = delete;
	/*************/
	static int init();



private:
	//SFML
	static sf::RenderWindow window;
	static sf::Clock fpsClock;
	static sf::Vector2i headPosition;

	//WinAPI
	static HWND hwnd;

	//Various
	static sf::Vector2f tileSize;
	static sf::Vector2i size;
	static sf::Vector2i tilesAmount;

	/*************/
	static void input();
	static void loadMapArray(const ImageSource &raw, int *map);
	static void loadLiveMapArray(const ImageSource &raw, int * map);
	static void clickButton(const int &key);
};