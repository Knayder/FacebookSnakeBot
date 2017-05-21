#include "Bot.h"



sf::RenderWindow Bot::window;
sf::Clock Bot::fpsClock;
float Bot::tileSize;

HWND Bot::hwnd;
int Bot::init() {
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

	/*Define tileSize*/
	tileSize = 466.f / 17.f;

	/*Define object with image source*/
	ImageSource raw(sf::IntRect({ 709 + 10, 120 + 74 }, { 466,466 }), hwnd);

	int map[17 * 17];
	//bool liveMap[17 * 17];
	sf::RectangleShape shape({ tileSize,tileSize });

	//Load map array
	loadMapArray(raw, map);

	float deltaTime = 0;
	while (window.isOpen()) {
		deltaTime = fpsClock.getElapsedTime().asSeconds();
		if (deltaTime >= 1.f / 60.f) {
			input();
			raw.update();

			/*Refresh map if 'S' button clicked*/
			if (GetAsyncKeyState(0x53))
				loadMapArray(raw, map);

			//Load liveMap array
			loadLiveMapArray(raw, map);

			window.clear(sf::Color(37, 37, 48));
			
			for (int y = 0; y < 17; y++) {
				for (int x = 0; x < 17; x++) {
					shape.setPosition(500 + x*tileSize, y*tileSize);

					if (map[y * 17 + x] == 3)
						shape.setFillColor(sf::Color::Blue);
					else if (map[y * 17 + x] == 2)
						shape.setFillColor(sf::Color::Red);
					else if (map[y * 17 + x] == 1)
						shape.setFillColor(sf::Color::Black);
					else
						shape.setFillColor(sf::Color::White);
					window.draw(shape);
					
				}
			}

			
			
			

			window.draw(raw);
			window.display();
			fpsClock.restart();
		}
		
	}
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
			int X = tileSize / 2 + x * tileSize;
			int Y = tileSize / 2 + y * tileSize;
			int Z = tileSize / 4;
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
				int X = tileSize / 2 + x * tileSize;
				int Y = tileSize / 2 + y * tileSize;
				int Z = tileSize / 4;
				if (raw.getColor(X, Y) == sf::Color::Black ||
					raw.getColor(X - Z, Y - Z) == sf::Color::Black ||
					raw.getColor(X + Z, Y - Z) == sf::Color::Black ||
					raw.getColor(X - Z, Y + Z) == sf::Color::Black ||
					raw.getColor(X + Z, Y + Z) == sf::Color::Black
					)
				{
					int decent = 0;
					for (int y2 = y*tileSize; y2 < (y + 1)*tileSize; y2++) {
						for (int x2 = x*tileSize; x2 < (x + 1)*tileSize; x2++) {
							decent += raw.getColor(x2, y2).r;
						}
					}
					decent /= tileSize*tileSize;
					if (decent < 160) {
						if (*temp == 0)
							*temp = 3;
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
