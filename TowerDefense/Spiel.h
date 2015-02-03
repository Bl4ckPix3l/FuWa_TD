#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include<fstream>
#include <cctype>
#include <vector>
#include "BodenGegner.h"
#include "Map.h"

class Spiel
{
private:
	Map karte;
	sf::Sprite feldSprite;
	sf::Sprite gegnerSprite;
	sf::RenderWindow *window;
	BodenGegner gegner1;
	void drawAll();
	void drawMap();
	void drawGegner();
	
public:
	void run();
	
	Spiel();
	~Spiel();
};

