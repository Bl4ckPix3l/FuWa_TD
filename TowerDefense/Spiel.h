#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include<fstream>
#include <cctype>
#include <vector>
#include "BodenGegner.h"
#include "Map.h"
#include "Turm.h"
#include "Einheit.h"

class Spiel
{
private:
	Map *karte;
	sf::Sprite feldSprite;
	sf::Sprite gegnerSprite;
	sf::Sprite turmSprite;
	sf::RenderWindow *window;
	std::vector<Einheit> t�rme;
	std::vector<Einheit> gegner;
	BodenGegner gegner1;
	Turm turm1;
	void drawAll();
	void drawMap();
	void drawGegner();
	void drawT�rme();
	void l�schePositionen();
	
public:
	void run();
	
	Spiel();
	~Spiel();
};

