#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include<fstream>
#include <cctype>
#include <vector>
#include "Position.h"


class Map
{
private:
	std::string name;
	std::vector<std::vector<Position*>> positionen;
	sf::Texture mauerTexture;
	sf::Texture bauplatzTexture;
	sf::Sprite feld;
	Position *start;
	Position *ziel;

	//wegfindung
	std::vector<Position*> queue;
	std::vector<Position*> path;
	void berechneWeg();
	
	void addNachbar(Position *pos, Position *pVater);
	double berechneAbstand();
	void sortiereVector();
public:
	Map(const char*filename);
	Map();
	~Map();
	int getBreite();
	int getHöhe();
	std::string getName();
	Position *getStartPosition();
	Position *getZielPosition();
	std::vector<std::vector<Position*>> getPositionen();
	std::vector<Position*> getPath();
	void initWegfindung();
};

