#include "Bot.h"



sf::RenderWindow Bot::window;
sf::Clock Bot::fpsClock;
sf::Vector2f Bot::tileSize;
sf::Vector2i Bot::headPosition;
sf::Vector2i Bot::size;
sf::Vector2i Bot::tilesAmount;

HWND Bot::hwnd;
int Bot::init() {
	headPosition = { 0,0 };
	/*Find window*/
	hwnd = FindWindow(NULL, "Facebook - Google Chrome");
	if (hwnd == NULL)
		return 1;

	/*Wait for init - 'D' button*/
	std::cout << "Press 'D' button to init Bot." << std::endl;
	while (!GetAsyncKeyState(0x44));
	std::cout << "Bot initialized." << std::endl;

	/*Create window*/
	window.create(sf::VideoMode(1280, 866), "Bot");

	/*Define game size*/
	size = { 466,466 };

	/*Define amount of tiles*/
	tilesAmount = { 17,17 };

	/*Define tileSize*/
	tileSize = {(float)size.x/tilesAmount.x, (float)size.y / tilesAmount.y};


	/*Define object with image source*/
	ImageSource raw(sf::IntRect({ 709 + 10, 120 + 74 }, size), hwnd);

	int *map = new int[tilesAmount.x * tilesAmount.y];

	sf::RectangleShape shape(tileSize);

	//Load map array
	loadMapArray(raw, map);

	/*Define pattern*/
	Pattern pattern;

	float deltaTime = 0;
	while (window.isOpen()) {
		deltaTime = fpsClock.getElapsedTime().asSeconds();
		if (deltaTime >= 1.f / 560.f) {
			input();
			raw.update();
			if (pattern.getCurrent() == headPosition) {
				clickButton(pattern.getKey());
				pattern.next();
			}

			/*Refresh map if 'S' button clicked*/
			if (GetAsyncKeyState(0x53))
				loadMapArray(raw, map);

			//Load liveMap array
			loadLiveMapArray(raw, map);

			window.clear(sf::Color(37, 37, 48));
			window.draw(raw);
			for (int y = 0; y < 17; y++) {
				for (int x = 0; x < 17; x++) {
					shape.setPosition(0 + x*tileSize.x, y*tileSize.y);
					if (map[y * 17 + x] == 2)
						shape.setFillColor(sf::Color(255,0,0,180));
					else if (map[y * 17 + x] == 1)
						shape.setFillColor(sf::Color(0,0,0,180));
					else
						shape.setFillColor(sf::Color::Transparent);
					window.draw(shape);
					
				}
			}
			shape.setPosition(0 + headPosition.x * tileSize.x, headPosition.y * tileSize.y);
			shape.setFillColor(sf::Color(0,0,255,180));
			window.draw(shape);
			

			
			window.display();
			fpsClock.restart();
		}
		
	}
	delete[]map;
	return 0;
}

void Bot::input(){
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Bot::loadMapArray(const ImageSource &raw, int *map){
	for (int y = 0; y < 17; y++) {
		for (int x = 0; x < 17; x++) {
			int X = (int)tileSize.x / 2 + x * tileSize.x;
			int Y = (int)tileSize.y / 2 + y * tileSize.y;
			int Z = (int)tileSize.x / 4;
			if (
				raw.getColor(X - Z, Y - Z) == sf::Color::Black &&
				raw.getColor(X + Z, Y - Z) == sf::Color::Black &&
				raw.getColor(X - Z, Y + Z) == sf::Color::Black &&
				raw.getColor(X + Z, Y + Z) == sf::Color::Black &&
				raw.getColor(X, Y) == sf::Color::White
				)
				map[y * 17 + x] = 1;
			else
				map[y * 17 + x] = 0;

		}
	}
}

void Bot::loadLiveMapArray(const ImageSource & raw, int * map){
	for (int y = 0; y < 17; y++) {
		for (int x = 0; x < 17; x++) {
			int *temp = map + (y * 17 + x);
			if (*temp != 1) {
				int X = tileSize.x / 2 + x * tileSize.x;
				int Y = tileSize.y / 2 + y * tileSize.y;
				int Z = tileSize.x / 4;
				if (raw.getColor(X, Y) == sf::Color::Black ||
					raw.getColor(X - Z, Y - Z) == sf::Color::Black ||
					raw.getColor(X + Z, Y - Z) == sf::Color::Black ||
					raw.getColor(X - Z, Y + Z) == sf::Color::Black ||
					raw.getColor(X + Z, Y + Z) == sf::Color::Black
					)
				{
					int decent = 0;
					for (int y2 = y*tileSize.y; y2 < (y + 1)*tileSize.y; y2++) {
						for (int x2 = x*tileSize.x; x2 < (x + 1)*tileSize.x; x2++) {
							decent += raw.getColor(x2, y2).r;
						}
					}
					decent /= tileSize.x*tileSize.y;
					if (decent < 190) {
						if (*temp == 0) {
							*temp = 3;
							headPosition = { x,y };
						}
						else
							*temp = 2;

					}
					else
						*temp = 0;
				}
				else
					*temp = 0;
			}

		}
	}
}

void Bot::clickButton(const int & key)
{
	std::cout << "Zakret" << std::endl;
	PostMessageA(hwnd, WM_KEYUP, key, NULL);
	PostMessageA(hwnd, WM_KEYDOWN, key, NULL);
}
