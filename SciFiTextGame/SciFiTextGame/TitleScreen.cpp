#include "TitleScreen.h"
#include<iostream>

TitleScreen::TitleScreen() {}


TitleScreen::~TitleScreen() {}

void TitleScreen::Display() {
	std::cout << "**************************************************" << std::endl;
	std::cout << "*                                                *" << std::endl;
	std::cout << "*               On the Rocks                     *" << std::endl;
	std::cout << "*                                                *" << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "You are an astronaut on a scientific mission to   " << std::endl;
	std::cout << "land on the asteroid Ceres.  Your job is to take  " << std::endl;
	std::cout << "some samples, set up some remote experiments and  " << std::endl;
	std::cout << "then return to your orbiter for the journey back  " << std::endl;
	std::cout << "to Earth.  If everything goes well you will be the" << std::endl;
	std::cout << "first person to ever walk on the surface of an    " << std::endl;
	std::cout << "asteroid and return safely to earth.              " << std::endl;
	std::cout << "If everything goes well...                        " << std::endl;
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
	std::cout << "If you want instructions on how to play type 'help' at the prompt." << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Loading..." << std::endl;
}
