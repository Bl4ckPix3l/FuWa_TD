#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "screens.hpp"

int main()
{
	//Applications variables
	std::vector<cScreen*> Screens;
	int screen = 0;

	//Window creation
	sf::RenderWindow App(sf::VideoMode(1024, 768, 32), "Defense Grid");

	//Mouse cursor visible
	App.setMouseCursorVisible(true);

	//Screens preparations
	screen_0 s0;
	screenRace s1;
	screenMap s2;
	screen_4 s3;
	Screens.push_back(&s0);
	Screens.push_back(&s1);
	Screens.push_back(&s2);
	Screens.push_back(&s3);
	
	// Screen loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

	return EXIT_SUCCESS;
}