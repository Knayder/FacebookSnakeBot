#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "ImageSource.h"


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

	//WinAPI
	static HWND hwnd;

	//Various
	static float tileSize;

	/*************/
	static void input();
};