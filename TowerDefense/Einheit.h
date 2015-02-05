#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"
#include <vector>
class Einheit
{
protected:
	Position *position;
	int speed;
	int range;
	sf::Texture unitTexture;
	sf::Sprite unit;
	std::vector<Position*> inRange;
	
public:
	Einheit();
	~Einheit();
	Position *getPosition();
	int getRange();
	void spawn(Position *spawnPos);
	void setRange(int pRange);
	void berechneRangeFelder(std::vector<std::vector<Position*>> positionen);
	std::vector<Einheit*> isInRange(std::vector<Einheit> *pEinheiten);
	std::vector<Position*> getInRange();
};

