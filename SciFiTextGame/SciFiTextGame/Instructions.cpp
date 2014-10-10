#include "Instructions.h"
#include<iostream>

Instructions::Instructions() {}

Instructions::~Instructions() {}

void Instructions::Display() {
	std::cout << std::endl << std::endl;
	std::cout << "Instructions:" << std::endl << std::endl;
	std::cout << "You interact with the game by typing commands at the prompt '>>'" << std::endl;
	std::cout << "e.g." << std::endl;		
	std::cout << "			'go south'" << std::endl;
	std::cout << "			'take thing'" << std::endl;
	std::cout << "			'climb whatsit'" << std::endl;
	std::cout << "			'use gerbil on Richar Gere'" << std::endl;
	std::cout << std::endl;
	std::cout << "You can move around by using the go command plus a direction." << std::endl;
	std::cout << "The common directions are north, south, east, west, up and down." << std::endl;
	std::cout << "You can also use the abreviations n, s, e, w, u, d to move." << std::endl;
	std::cout << std::endl;
	std::cout << "The full description of a room will only be displayed the first time" << std::endl;
	std::cout << "you enter a room.  If you want to see the description again use the" << std::endl;
	std::cout << "'look' command or just 'l'." << std::endl;
	std::cout << std::endl;
	std::cout << "You can use the 'examine' command or 'x' followed by an object to see" << std::endl;
	std::cout << "the details of that object.  e.g. 'x pony'" << std::endl;
	std::cout << std::endl;
	std::cout << "You can pick up items by using 'take' and drop them by using 'drop'." << std::endl;
	std::cout << "To display a list of the items you are carrying use 'inventory' or 'i'" << std::endl;
	std::cout << std::endl;
	std::cout << "The 'help' command will display these instructions at any time." << std::endl;
	std::cout << "The 'score' command will display your score." << std::endl;
	std::cout << "The 'quit' command will end the game." << std::endl;
	std::cout << std::endl;
	std::cout << "There are many other commands you will find during the game." << std::endl;
	std::cout << "If it seems like something should work - try it." << std::endl;
	std::cout << std::endl;
}