#include "Bot.h"
#include <iostream>

int main(int, char**) {
	int value;
	switch (value = Bot::init()) {
	case 0:
		std::cout << "Finished correctly";
		break;
	case 1:
		std::cout << "Cannot find window!";
		break;
	case 2:
		std::cout << "Finished correctly";
		break;
	case 3:
		std::cout << "Finished correctly";
		break;
	default:
		std::cout << "ERROR CODE: " << value;
		break;
	}
	
	if(value)
		Sleep(1000);
	return 0;
}