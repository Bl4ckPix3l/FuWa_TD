#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include<fstream>
#include <cctype>
#include "Einheit.h"

class Turm:public Einheit
{
private:
	int angriffsWert;
	int range;
	int attackSpeed;
public:
	Turm();
	~Turm();
	int getRange();
	int getAngriff();
	int getAttackSpeed();
	void setRange(int pRange);
	void setAngriff(int pAngriff);
	void setAttackSpeed(int pAttackSpeed);
	std::vector<Position*> getInRange();
	bool angriff(Einheit *angriffsZiel);
	sf::Clock getAttackClock();
	void berechneRangeFelder(std::vector<std::vector<Position*>> positionen);
};

